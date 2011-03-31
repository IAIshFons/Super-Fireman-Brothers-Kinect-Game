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
 *  @file Zamus.cpp
 *
 *  @brief This file contain the implementation of the functions of the
 *  class Zamus.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "Zamus.h"

/**
 *  Zamus constructor 
 *
 *  @param userDetector is a pointer to the userDetector of the
 *  game.
 */
Zamus :: Zamus(UserDetector *userDetector) : 
        AbstractPoseDetection(userDetector)
{
    listenerType = ZAMUS_TYPE;
    userDetector -> addListener(this);                   
    setRequiredPoseTime(Z_POSE_TIME);
    busterStatus = map <XnUserID, int>();
    shoots = vector <ZamusShoot > ();
}

/**
 *  Add shoot function.
 *
 *  This function adds a new shoot to the vector shoots.
 *
 *  @param position is the initial position of the water shoot.
 *  @param direction is the vector that representes the direction
 *  of the water shoot.
 *  @param p is the player's ID.
 */
void Zamus :: addShoot (XnPoint3D position, Vector3D direction, XnUserID p)
{
    shoots.push_back(ZamusShoot(position, direction, p));
}

/**
 *  Indicates if the pose is being applied.
 *
 *  @param userID is the player's id.
 *  @parma poseTime is the time that the user has been posing.
 *
 *  @return True if the user is doing the pose to transform in
 *  Zamus.
 */
bool Zamus :: isPosing(XnUserID userID, double poseTime) 
{
    //printf("Entre al isposing de zamus\n");
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition rs, re, rh, ls, le, lh;

    Vector3D vrs, vre, vrh;
    Vector3D vrse, vreh;

    Vector3D vlsrs, vrsls;

    Vector3D vls, vle, vlh;
    Vector3D vlse, vleh;

    int percent;
    int index;
    int stage;
    
    bool isStraightLeft;
    bool isFrontLeft;
    bool isRightPlaced;
    bool isFrontRight;

    // Check if userID is in listener
    if (userDetector -> isTracked(userID)) {
        stage = userDetector -> retStage(userID);
    }
    else {
        return false;
    }

    userGen = userDetector -> retUserGenerator();

    // Get joint positions (positions are switched)
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
            return false;
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

    // Shoulder line
    vlsrs = vrs - vls;
    vrsls = vls - vrs;
    
    vrse.normalize();
    vreh.normalize();
    vlse.normalize();
    vleh.normalize();
    vlsrs.normalize();
    vrsls.normalize();

    // For left Arm
    isStraightLeft = toAngle(acos(vlse.dot(vleh))) <= STRAIGHT_RANGE;
    
    isFrontLeft = toAngle(acos(vlse.dot(g_Vmz))) <= 30;
 
    // For right Arm
    isFrontRight = toAngle(acos(vrse.dot(g_Vmz))) <= 30;
    
    isRightPlaced = toAngle(acos(vreh.dot(g_Vy))) <= 30;
      
    // Transformation course
    if(stage == NO_LISTENED ||
       stage == T_STAGE_1 ||
       stage == T_STAGE_2 ||
       stage == T_STAGE_3) 
       {
        if (isStraightLeft && isFrontLeft && isRightPlaced && 
            isFrontRight) {
            
            percent = transPercent(poseTime, Z_POSE_TIME);

            printf("Zamus transformation %d%% -- \n", percent);

            // For printing stages
            if (percent < 35) {
                printf("Zamus transformation %d%% -- Stage 1\n", percent);
                userDetector -> changeStage(userID, T_STAGE_1);
                //currentStage = T_STAGE_1;
            }
            else if (percent < 70) {
                printf("Zamus transformation %d%% -- Stage 2\n", percent);
                userDetector -> changeStage(userID, T_STAGE_2);
                //currentStage = T_STAGE_2;
            }
            else if (percent <= 100) {
                printf("Zamus transformation %d%% -- Stage 3\n", percent);
                userDetector -> changeStage(userID, T_STAGE_3);
                //currentStage = T_STAGE_3;
            }

            return true;
        } 
        else {
            //stage = NO_TRANSFORMATION;
            userDetector -> changeStage(userID, NO_LISTENED);
            return false;
        }
    }
    return false;
}

/**
 *  Function to be applied when the pose is detected 
 *
 *  @param userID is the player's id.
 */
void Zamus :: poseDetected(XnUserID userID)
{
    usersListened.insert(pair <XnUserID, int> (userID, TRANSFORMED));
    busterStatus.insert(pair <XnUserID, int> (userID, DEACTIVATED));

    userDetector -> remTrackedUser(userID);

    printf("Zamus transformation for user %d Completed...!\n", userID);
}

/**
 *  Returns buster status.
 *
 *  @param userID is the player's id.
 *
 *  @return the integer that represents the buster status.
 *
 */
int Zamus :: retBusterStatus(XnUserID userID)
{
    if (busterStatus.count(userID) == 1) {
        return busterStatus[userID];
    }

    return -1;
}


/** 
 *  Changes buster Status
 *
 *  @param userID is the id of the player.
 *  @param status to set the buster of the player.
 */
void Zamus :: changeBusterStatus(XnUserID userID, int status) 
{
    busterStatus[userID] = status;
}

/**
 *  Return listener user stage.
 *  
 *  @param userID is the player's id.
 *
 *  @return the stage of the user.
 *
 */
int Zamus :: retLisUserStage(XnUserID userID) 
{
    return UserListener :: retLisUserStage(userID);
    //if (usersListened.count(userID) == 1) {
    //    return usersListened[userID];
    //}
}

/**
 *  Returns if the user is currently listened 
 *
 *  @param userID is the player's id.
 *
 *  @return true if the user is been tracked.
 */
bool Zamus :: isListened(XnUserID userID)
{
    return UserListener :: isListened(userID);
}


/**
 *  New user handler, this function is called when new user
 *  appears.
 *
 *  @param userID is the player's id.
 */
void Zamus :: newUser(XnUserID userID) {
    printf("Zamus user %d\n", userID);
}

/**
 *  Lost user handler, this function is called when user is lost
 *
 *  @parma userID is the player's id.
 */
void Zamus :: lostUser(XnUserID userID) {

    // Remove user from listener
    if (isListened(userID) == 1) {
        usersListened.erase(userID);
    }
    
    // Remove user from buster
    if (busterStatus.count(userID) == 1) {
        busterStatus.erase(userID);
    }

    printf("Lost Zamus user %d\n", userID);
}

/**
 *  Start calibration handler, this function is called when 
 *  calibration of a detected user begins
 *
 *  @param userID is the player's id.
 */
void Zamus :: startCalibration(XnUserID userID) {}

/**
 *  End calibration handler, this function is called when
 *  calibration of the user ends
 *
 *  @param userID is the player's id.
 *  @param Success True is the user successfully calibrate.
 */
void Zamus :: endCalibration(XnUserID userID, XnBool Success) {}

/**
 *  Pose Handler, this function is called when a new pose
 *  is detected
 *
 *  @param poseName The name of the pose 
 *  @param userID The id of the user.
 */
void Zamus :: poseDetected(const XnChar *poseName, XnUserID userID) {}
