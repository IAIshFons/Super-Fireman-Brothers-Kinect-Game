/**
 * This application consist of a simple game that we called "Super Fireman Brothers". 
 * This applications uses the XBox Kinect sensor to track the player's moves.
 *
 * Copyright (C) 2011 Alfonso Ros, Ismael Mendonca
 *
 * This file is part of Super Fireman Brothers.
 *
 * Super Fireman Brothers is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Super Fireman Brothers is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Super Fireman Brothers. Check the txt file "LICENSE",
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */

# include "IceRodDetector.h"

/**
 *  Constructor of the class.
 *  @param linq pointer to a linq struture.
 *  @param userD pointer to a user detector structure.
 */
IceRodDetector :: IceRodDetector (Linq *linq, UserDetector *userD) : 
    AbstractPoseDetection (userD)
{
    lDetector = linq;
    setRequiredPoseTime(L_ICEROD_POSE_TIME);
}

/** 
 *  Implementation of the isPosing function wich returns 
 *  if the user is doing the Ice Rod pose.
 *  @param userID ID of the user to pose.
 *  @param poseTime time of the user.
 *  @return true if the user is posing for the Ice Rod, 
 *  false otherwise.
 */
bool IceRodDetector :: isPosing(XnUserID userID, double poseTime) 
{
    detectIceRodPose(userID, poseTime);

    if (lDetector -> retIceRodStatus(userID) == Linq :: DEACTIVATED) {
        lDetector -> changeIceRodCharge(userID, true);
    }
    
    if (lDetector -> retIceCharge(userID)) {
        if (lDetector -> retIceRodStatus(userID) == Linq :: ACTIVATED) {
            lDetector -> changeIceRodCharge(userID, false);
            return true;
        } 
    }

    return false;
}


/** 
 *  Specifies the actions that should be taken 
 *  when the Ice Rod pose is detected.
 *  @param userID ID of the user.
 */
void IceRodDetector ::  poseDetected(XnUserID userID) 
{
    invokeIce(userID);
}


/** 
 *  Method that is called when the Ice Rod pose is 
 *  detected.
 *  @param userID user ID of the user who is appliying
 *  the Ice Rod pose.
 */
void IceRodDetector :: invokeIce(XnUserID userID)
{
    static int iceSpawnDelay = 0;

    //printf("ice %d\n", iceSpawnDelay++);

    UserGenerator userGen;
    DepthGenerator depthGen;
    XnSkeletonJointPosition elbow;
    XnSkeletonJointPosition hand;
    XnPoint3D points[2];
    Vector3D dir;
    Vector3D dir2;

    userGen  = userDetector -> retUserGenerator();
    depthGen = userDetector -> retDepthGenerator();

    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_LEFT_ELBOW, 
        elbow
    );
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_LEFT_HAND, 
        hand
    );

    points[0] = elbow.position;
    points[1] = hand.position;

    depthGen.ConvertRealWorldToProjective(2, points, points);

    dir.x = points[1].X - points[0].X;
    dir.y = points[1].Y - points[0].Y;
    dir.z = points[1].Z - points[0].Z;

    lDetector -> addIceSpawn(points[1], dir, userID);
    dir2 = dir;
    dir2.y += 8.0;
    dir2.x += 8.0;
    lDetector -> addIceSpawn(points[1], dir2, userID);
    dir2.x -= 16.0;
    lDetector -> addIceSpawn(points[1], dir2, userID);
}


/** 
 *  Function that detects if the Ice Rod pose is being applied,
 *  it determines when the linq user should invoke magic ice.
 *  @param userID id of the user applying the pose.
 *  @param poseTime pose time of the Ice Rod pose.
 */
bool IceRodDetector :: detectIceRodPose(XnUserID userID, double poseTime) 
{
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition rs, re, rh;

    Vector3D vrs, vre, vrh;
    Vector3D vrse, vreh;

    bool isStraight;
    bool isNotStraight;

    int index;
    
    if (!((lDetector -> isListened(userID)) && 
       (lDetector -> retLisUserStage(userID) == Linq :: TRANSFORMED))) {
        return false;
    }


    userGen = userDetector -> retUserGenerator();

    // Get joint positions (positions are switched
    // because the view is from backwards
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_LEFT_SHOULDER, 
        rs
    );
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_LEFT_ELBOW, 
        re
    );
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_LEFT_HAND, 
        rh
    );

    // Confidence test
    if( (rs.fConfidence < CONFIDENCE) || 
        (re.fConfidence < CONFIDENCE) ||
        (rh.fConfidence < CONFIDENCE))
        {
            return false;
        }
    

    vrs = Vector3D((rs.position).X, (rs.position).Y, (rs.position).Z);
    vre = Vector3D((re.position).X, (re.position).Y, (re.position).Z);
    vrh = Vector3D((rh.position).X, (rh.position).Y, (rh.position).Z);

    // Right Shoulder to elbow
    vrse = vre - vrs;
    
    // Right Elbow to hand
    vreh = vrh - vre;

    vrse.normalize();
    vreh.normalize();
    
    // For right arm 
    isStraight = toAngle(acos(vrse.dot(vreh))) <= 30;

    isNotStraight = toAngle(acos(vrse.dot(vreh))) >= 90;


    if (isNotStraight) {
        lDetector -> changeIceRodStatus(userID, Linq :: DEACTIVATED);
    } 
    else if (isStraight) {
        lDetector -> changeIceRodStatus(userID, Linq :: ACTIVATED);
    }

    return isStraight;
}



