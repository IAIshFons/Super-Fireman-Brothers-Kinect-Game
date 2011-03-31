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
 *  @file Linq.h
 *
 *  @brief This file contain the definitions of the functions of the
 *  class Linq.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "Linq.h"

/**
 *  Linq constructor.
 *
 *  @param userDetector is a pointer to the userDetector of the
 *  game.
 */
Linq :: Linq(UserDetector *userDetector) : 
        AbstractPoseDetection(userDetector)
{
    listenerType = LINQ_TYPE;
    userDetector -> addListener(this);                   
    setRequiredPoseTime(L_POSE_TIME);
    map <XnUserID, int> iceRodStatus = map <XnUserID, int> ();
    iceSpawn = vector <LinqSpawnIce> ();
    charge = map <XnUserID, bool> ();
}

/**
 *  Add shoot function.
 *
 *  This function adds a new ice to the vector iceSpawn.
 *
 *  @param position is the initial position of the ice
 *  @param direction is the vector that represents the direction
 *  of the ice.
 *  @oaram p is the player's id.
 */
void Linq :: addIceSpawn (XnPoint3D position, Vector3D direction, XnUserID p)
{
    iceSpawn.push_back(LinqSpawnIce(position, direction, p));
}

/**
 *  Pose for stage1 transformation. 
 *
 *  @param userID is the player's id.
 *  @param stage is the stage in where is the player. 
 */
void Linq :: stage1 (XnUserID userID, int stage) 
{ 
    //printf("Entre al isposing de linq\n");
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition rs, re, rh;

    Vector3D vrs, vre, vrh;
    Vector3D vrse, vreh;

    bool isStraightRight;
    bool isSideRight;
    bool isHigh;

    const float yAdjustement = 150.0;
    
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
            return ;
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

    // For Right Arm
    isStraightRight = toAngle(acos(vrse.dot(vreh))) <= STRAIGHT_RANGE;
    
    // Right arm in next of body
    isSideRight =  (toAngle(acos(vrse.dot(g_Vmx))) <= 30);

    // Hand High enough
    isHigh = (vrh.y >= (vrs.y - yAdjustement)) && 
             (vrh.y <= (vrs.y + yAdjustement));

    // Transformation course
    if (stage == NO_LISTENED) {
        if (isStraightRight && isSideRight && isHigh) {
            userDetector -> changeStage(userID, T_STAGE_1);
            printf("Stage 1 Done...\n");
        }
    } 
    
}

/**
 *  Pose for stage2 transformation. 
 *
 *  @param userID is the player's id.
 *  @param stage is the stage in where is the player. 
 */
void Linq :: stage2 (XnUserID userID, int stage) 
{
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition ls, le, lh;

    Vector3D vls, vle, vlh;
    Vector3D vlse, vleh;
    
    bool isStraightLeft;
    bool isSideLeft;
    bool isHigh;

    const float yAdjustement = 150.0;

    userGen = userDetector -> retUserGenerator();

    // Get joint positions (positions are switched
    // because the view is from backwards
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
    if( (ls.fConfidence < CONFIDENCE) || 
        (le.fConfidence < CONFIDENCE) ||
        (lh.fConfidence < CONFIDENCE))
        {
            return;
        }
    

    vls = Vector3D((ls.position).X, (ls.position).Y, (ls.position).Z);
    vle = Vector3D((le.position).X, (le.position).Y, (le.position).Z);
    vlh = Vector3D((lh.position).X, (lh.position).Y, (lh.position).Z);

    // Left Shoulder to elbow
    vlse = vle - vls;
    
    // Left Elbow to hand
    vleh = vlh - vle;

    vlse.normalize();
    vleh.normalize();

    // For left Arm
    isStraightLeft = toAngle(acos(vlse.dot(vleh))) <= STRAIGHT_RANGE;
    
    // Right arm in front of body
    isSideLeft = toAngle(acos(vlse.dot(g_Vx))) <= 30;

    // Hand high enough
    isHigh = (vlh.y >= (vls.y - yAdjustement)) && 
             (vlh.y <= (vls.y + yAdjustement));


    // Transformation course
    if (stage == T_STAGE_1) {
        if (isStraightLeft && isSideLeft && isHigh) {
            userDetector -> changeStage(userID, T_STAGE_2);
            printf("Stage 2 Done...\n");
        }
    } 
}

/**
 *  Pose for stage3 transformation. 
 *
 *  @param userID is the player's id.
 *  @param stage is the stage in where is the player. 
 */
void Linq :: stage3 (XnUserID userID, int stage) 
{
    //printf("Entre al isposing de linq\n");
    UserGenerator userGen;
    SkeletonCapability *skelCap;
    XnSkeletonJointPosition rs, re, rh, ls, le, lh, head;

    Vector3D vrs, vre, vrh;
    Vector3D vrse, vreh;

    Vector3D vls, vle, vlh;
    Vector3D vlse, vleh, vhead;

    Vector3D vtemp;

    int percent;
    
    const float yAdjustement = 150.0;

    bool isDiagElbowLeft;
    bool isDiagElbowRight;
    bool isDiagonalLeft;
    bool isDiagonalRight;
    bool isHigh;

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
    userGen.GetSkeletonCap().GetSkeletonJointPosition(
        userID, 
        XN_SKEL_HEAD, 
        head
    );

    // Confidence test
    if( (rs.fConfidence < CONFIDENCE) || 
        (re.fConfidence < CONFIDENCE) ||
        (rh.fConfidence < CONFIDENCE) ||
        (ls.fConfidence < CONFIDENCE) ||
        (le.fConfidence < CONFIDENCE) ||
        (lh.fConfidence < CONFIDENCE) ||
        (head.fConfidence < CONFIDENCE)) 
        {
            return;
        }
    

    vrs = Vector3D((rs.position).X, (rs.position).Y, (rs.position).Z);
    vre = Vector3D((re.position).X, (re.position).Y, (re.position).Z);
    vrh = Vector3D((rh.position).X, (rh.position).Y, (rh.position).Z);
    vls = Vector3D((ls.position).X, (ls.position).Y, (ls.position).Z);
    vle = Vector3D((le.position).X, (le.position).Y, (le.position).Z);
    vlh = Vector3D((lh.position).X, (lh.position).Y, (lh.position).Z);
    vhead = Vector3D((head.position).X, 
                     (head.position).Y, 
                     (head.position).Z);


    // Right Shoulder to elbow
    vrse = vre - vrs;
    
    // Right Elbow to hand
    vreh = vrh - vre;

    // Left Shoulder to Elbow
    vlse = vle - vls;
    
    // Left Elbow to hand
    vleh = vlh - vle;

    // Temporary vector
    
    vrse.normalize();
    vreh.normalize();
    vlse.normalize();
    vleh.normalize();

    // Left diagonal limbs
    vtemp = g_Vx + g_Vy;
    vtemp.normalize();
    
    isDiagonalLeft = toAngle(acos(vlse.dot(vtemp))) <= 30;
    isDiagElbowRight = toAngle(acos(vreh.dot(vtemp))) <= 30;
    
    // Right arm in front of body
    vtemp = g_Vmx + g_Vy;
    vtemp.normalize();

    isDiagonalRight = toAngle(acos(vrse.dot(vtemp))) <= 30; 
    isDiagElbowLeft = toAngle(acos(vleh.dot(vtemp))) <= 30;

    isHigh = (vrh.y >= vhead.y) && (vlh.y >= vhead.y);
  
    // Transformation course
    if (stage == T_STAGE_2) {
        if (isDiagonalLeft && isDiagonalRight && isDiagElbowLeft &&
            isDiagElbowRight && isHigh){
            userDetector -> changeStage(userID, TRANSFORMED);
            printf("Stage 3 Done...\n");
        }
    }

}

/**
 *  Indicates if the pose is being applied.
 *
 *  @param userID is the player's id.
 *  @param poseTime is the amount of time that the player has
 *  been doing the pose.
 *
 *  @return True if the player is doing the pose. False in other
 *  case.
 */
bool Linq :: isPosing(XnUserID userID, double poseTime) 
{
    int stage;

    // Check if user tracked, and gets his
    // current stage
    if (userDetector -> isTracked(userID)) {
        stage = userDetector -> retStage(userID);
    }
    else {
        return false;
    }

    // Action to take according to stage
    if(stage >= T_STAGE_1) {
        if (stage >= T_STAGE_2) {
            if(stage >= TRANSFORMED) {
                return true;
            }
            else{
                stage3(userID, stage);
            }
        }
        else{
            stage2(userID, stage);
        }
    }
    else{ 
        stage1(userID, stage);
    }

    return false;
}

/**
 *  Function to be applied when the pose is detected.
 *  
 *  @param userID is the player's id.
 */
void Linq :: poseDetected(XnUserID userID)
{
    usersListened.insert(pair <XnUserID, int> (userID, TRANSFORMED));
    iceRodStatus.insert(pair <XnUserID, int> (userID, DEACTIVATED));
    charge.insert(pair <XnUserID, int> (userID, false));

    userDetector -> remTrackedUser(userID);

    printf("Linq transformation for user %d Completed...!\n", userID);

}

/**
 *  Returns buster status.
 *
 *  @param userID is the player's id.
 *
 *  @return the integer that represents the status of the ice
 *  rod.
 *
 */
int Linq :: retIceRodStatus(XnUserID userID) 
{
    if (iceRodStatus.count(userID) == 1) {
        return iceRodStatus[userID];
    }

    return -1;
}

/**
 *  Changes buster Status.
 *
 *  @param userID is the player's id.
 *  @param status status to set the ice rod.
 */
void Linq :: changeIceRodStatus(XnUserID userID, int status)
{
    iceRodStatus[userID] = status;
}

/**
 *  Returns ice rod charge status.
 *
 *  @param userID is the player's id.
 *
 *  @return True if the player can shoot. False in other case.
 */
bool Linq :: retIceCharge(XnUserID userID) 
{
    if (charge.count(userID) == 1) {
        return charge[userID];
    }

    return -1;
}

/**
 *  Changes ice rod charge Status.
 *
 *  This is needed to sequence the poses to spawn ice.
 *
 *  @param userID is the player's id.
 *  @param satus is the value to set the charge map.
 */
void Linq :: changeIceRodCharge(XnUserID userID, bool status)
{
    if (charge.count(userID) != 1) {
        charge.insert(pair <XnUserID, bool> (userID, status));
    }
    else {
        charge[userID] = status;
    }
}

/**
 *  Return listener user stage 
 *
 *  @param userID is the player's id.
 *
 *  @return the stage of the user given by the UserListener.
 */
int Linq :: retLisUserStage(XnUserID userID) 
{
    return UserListener :: retLisUserStage(userID);
}

/**
 *  Returns if the user is currently listened.
 *
 *  @param userID is the player's ID.
 *
 *  @return True if the user is tracked.
 */
bool Linq :: isListened(XnUserID userID)
{
    return UserListener :: isListened(userID);
}

        /******* Callback functions *******/

/**
 * New user handler, this function is called when new user
 * appears.
 *  
 *  @param userID is the player's id.
 */
void Linq :: newUser(XnUserID userID) {
    printf("Linq user %d\n", userID);
}

/**
 * Lost user handler, this function is called when user is lost.
 *  
 *  @param userID is the player's id.
 */
void Linq :: lostUser(XnUserID userID) {
     
    // Remove user from listener
    if (isListened(userID)) {
        usersListened.erase(userID);
    }
    
    // Remove user from listener
    if (iceRodStatus.count(userID) == 1) {
        iceRodStatus.erase(userID);
    }

    printf("Lost Linq user %d\n", userID);
}

/**
 * Start calibration handler, this function is called when 
 * calibration of a detected user begins.
 *  
 *  @param userID is the player's id.
 */
void Linq :: startCalibration(XnUserID userID) {}

/**
 * End calibration handler, this function is called when
 * calibration of the user ends
 *  
 *  @param userID is the player's id.
 *  @param Success is True if the calibration was successfull.
 */
void Linq :: endCalibration(XnUserID userID, XnBool Success) {}

/**
 * Pose Handler, this function is called when a new pose
 * is detected
 *
 * @param poseName name of the pose.
 * @param userID is the id of the player.
 */
void Linq :: poseDetected(const XnChar *poseName, XnUserID userID) {}

