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

/**
 *  @file BusterDetector.cpp
 *                                                                      
 *  @brief implementacion file for the class BusterDetector.
 *
 *  This file contains the implementation of the Buster detector,
 *  it specifies the buster activation, deactivation and application
 *  poses, and other functions and methods for its functioning.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "BusterDetector.h"

/**
 *  Constructor of the class.
 *  @param zamus pointer to a zamus struture.
 *  @param userD pointer to a user detector structure.
 */
BusterDetector :: BusterDetector (Zamus *zamus, UserDetector *userD) : 
    AbstractPoseDetection (userD)
{
    zDetector = zamus;
    setRequiredPoseTime(Z_BUSTER_POSE_TIME);
}


/** 
 *  Implementation of the isPosing function wich returns 
 *  if the user is doing the Buster pose.
 *  @param userID ID of the user to pose.
 *  @param poseTime time of the user.
 *  @return true if the user is posing for the buster, 
 *  false otherwise.
 */
bool BusterDetector :: isPosing(XnUserID userID, double poseTime) 
{
    if (busterActivationMsg.count(userID) == 0) {
        busterActivationMsg.insert(pair <XnUserID, bool> (userID, false));
    }

    detectBusterActivationPose(userID);
    detectBusterDeactivationPose(userID);

    // Buster Status
    switch(zDetector -> retBusterStatus(userID)) {
        case (Zamus :: ACTIVATED):
            
            if (!busterActivationMsg[userID]) {
                printf("Buster Activated user %d\n", userID);
                busterActivationMsg[userID] = true;
            }
            return detectBusterPose(userID);

        case (Zamus :: DEACTIVATED):
            if (busterActivationMsg[userID]) {
                printf("Buster Deactivated user %d\n", userID);
                busterActivationMsg[userID] = false;
            }
            return false;

        default:
            return false;
    }
    
    return false;
}


/** 
 *  Specifies the actions that should be taken 
 *  when the Buster pose is detected.
 *  @param userID ID of the user.
 */
void BusterDetector ::  poseDetected(XnUserID userID) 
{
    shootBuster(userID);
}


/** 
 *  Method that is called when the Buster pose is 
 *  detected.
 *  @param userID user ID of the user who is appliying
 *  the Buster pose.
 */
void BusterDetector :: shootBuster(XnUserID userID)
{
    UserGenerator userGen;
    DepthGenerator depthGen;
    XnSkeletonJointPosition elbow;
    XnSkeletonJointPosition hand;
    XnPoint3D points[2];
    Vector3D dir;

    if (shootDelay.count(userID) != 1) {
        shootDelay.insert(pair <XnUserID, int> (userID, 0));
    }

    if (shootDelay[userID] > Z_SHOOT_DELAY) {

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

    zDetector -> addShoot(points[1], dir, userID);
    //printf("puf %d\n", count++);

    shootDelay[userID] = 0;

    }
    else {
        shootDelay[userID] += 1;
    }
}


/** 
 *  Function that detects if the Buster pose is being applied,
 *  it determines when the zamus user should shoot.
 *  @param userID id of the user applying the pose.
 *  @param poseTime pose time of the Buster pose.
 */
bool BusterDetector :: detectBusterPose(XnUserID userID, double poseTime) 
{
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition rs, re, rh;

    Vector3D vrs, vre, vrh;
    Vector3D vrse, vreh;

    bool isStraight;
    bool isFrontRight;

    int index;

    if (!((zDetector -> isListened(userID)) && 
       (zDetector -> retLisUserStage(userID) == Zamus :: TRANSFORMED) &&
       (zDetector -> retBusterStatus(userID) == Zamus :: ACTIVATED))) {

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

    return isStraight;
}


/** 
 *  Function that detects the activation of the zamus Buster.
 *  @param userID id of the user applying the pose.
 *  @param poseTime pose time of the Buster pose.
 */
void BusterDetector :: detectBusterActivationPose (XnUserID userID, 
                                                   double poseTime) 
{
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition rs, re, rh, ls, le, lh;

    Vector3D vrs, vre, vrh;
    Vector3D vrse, vreh;

    Vector3D vlsrs, vrsls;

    Vector3D vls, vle, vlh;
    Vector3D vlse, vleh;

    int percent;

    bool isStraight;
    bool isFrontRight;
    bool isFrontLeft;
    bool isCrossed;

    if (!((zDetector -> isListened(userID)) && 
       (zDetector -> retLisUserStage(userID) == Zamus :: TRANSFORMED) &&
       (zDetector -> retBusterStatus(userID) == Zamus :: DEACTIVATED))) {

        return;
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
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_RIGHT_SHOULDER, 
        ls
    );
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_RIGHT_ELBOW, 
        le
    );
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_RIGHT_HAND, 
        lh
    );

    // Confidence test
    if( (rs.fConfidence < CONFIDENCE) || 
        (re.fConfidence < CONFIDENCE) ||
        (rh.fConfidence < CONFIDENCE) ||
        (ls.fConfidence < CONFIDENCE) ||
        (le.fConfidence < CONFIDENCE) ||
        (lh.fConfidence < CONFIDENCE)) 
        {
            return;
        }
    

    vrs = Vector3D((rs.position).X, (rs.position).Y, (rs.position).Z);
    vre = Vector3D((re.position).X, (re.position).Y, (re.position).Z);
    vrh = Vector3D((rh.position).X, (rh.position).Y, (rh.position).Z);
    vls = Vector3D((ls.position).X, (ls.position).Y, (ls.position).Z);
    vle = Vector3D((le.position).X, (le.position).Y, (le.position).Z);
    vlh = Vector3D((lh.position).X, (lh.position).Y, (lh.position).Z);

    // Right Shoulder to elbow
    vrse = vre - vrs;
    
    // Right Elbow to hand
    vreh = vrh - vre;

    // Left Shoulder to Elbow
    vlse = vle - vls;
    
    // Left Elbow to hand
    vleh = vlh - vle;

    vrse.normalize();
    vreh.normalize();
    vlse.normalize();
    vleh.normalize();
    
    // For right arm 
    isStraight = toAngle(acos(vrse.dot(vreh))) <= STRAIGHT_RANGE;
    
    isFrontRight = toAngle(acos(vrse.dot(g_Vmz))) <= 30;

    // For left Arm
    isFrontLeft = toAngle(acos(vlse.dot(g_Vmz))) <= 30;

    isCrossed = (toAngle(acos(vleh.dot(vreh))) <= 120) && 
                (toAngle(acos(vleh.dot(vreh))) >= 60);
     
    // Activation course
    if (isStraight && isFrontRight && isFrontLeft && isCrossed) {
        zDetector -> changeBusterStatus(userID, Zamus :: ACTIVATED);
    }
}


/** 
 *  Function that detects the deactivation of the zamus
 *  Buster.
 *  @param userID id of the user applying the pose.
 *  @param poseTime pose time of the Buster pose.
 */
void BusterDetector :: detectBusterDeactivationPose (XnUserID userID, 
                                                     double poseTime) 
{
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition rs, re, rh, ls, le, lh;

    Vector3D vrs, vre, vrh;
    Vector3D vrse, vreh;

    Vector3D vlsrs, vrsls;

    Vector3D vls, vle, vlh;
    Vector3D vlse, vleh;

    int percent;

    bool isStraight;
    bool isFrontRight;
    bool isFrontLeft;
    bool isCrossed;
    
   if (!((zDetector -> isListened(userID)) && 
      (zDetector -> retLisUserStage(userID) == Zamus :: TRANSFORMED) &&
      (zDetector -> retBusterStatus(userID) == Zamus :: ACTIVATED))) {

        return;
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
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_RIGHT_SHOULDER, 
        ls
    );
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_RIGHT_ELBOW, 
        le
    );
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_RIGHT_HAND, 
        lh
    );

    // Confidence test
    if( (rs.fConfidence < CONFIDENCE) || 
        (re.fConfidence < CONFIDENCE) ||
        (rh.fConfidence < CONFIDENCE) ||
        (ls.fConfidence < CONFIDENCE) ||
        (le.fConfidence < CONFIDENCE) ||
        (lh.fConfidence < CONFIDENCE)) 
        {
            return;
        }
    

    vrs = Vector3D((rs.position).X, (rs.position).Y, (rs.position).Z);
    vre = Vector3D((re.position).X, (re.position).Y, (re.position).Z);
    vrh = Vector3D((rh.position).X, (rh.position).Y, (rh.position).Z);
    vls = Vector3D((ls.position).X, (ls.position).Y, (ls.position).Z);
    vle = Vector3D((le.position).X, (le.position).Y, (le.position).Z);
    vlh = Vector3D((lh.position).X, (lh.position).Y, (lh.position).Z);

    // Right Shoulder to elbow
    vrse = vre - vrs;
    
    // Right Elbow to hand
    vreh = vrh - vre;

    // Left Shoulder to Elbow
    vlse = vle - vls;
    
    // Left Elbow to hand
    vleh = vlh - vle;

    vrse.normalize();
    vreh.normalize();
    vlse.normalize();
    vleh.normalize();
    
    // For left arm 
    isStraight = toAngle(acos(vlse.dot(vleh))) <= STRAIGHT_RANGE;
    
    isFrontLeft = toAngle(acos(vlse.dot(g_Vmz))) <= 30;

    // For right Arm
    isFrontRight = toAngle(acos(vrse.dot(g_Vmz))) <= 30;

    isCrossed = (toAngle(acos(vreh.dot(vleh))) <= 120) && 
                (toAngle(acos(vreh.dot(vleh))) >= 60);
     
    // Activation course
    if (isStraight && isFrontRight && isFrontLeft && isCrossed) {
        zDetector -> changeBusterStatus(userID, Zamus :: DEACTIVATED);
    }
}
