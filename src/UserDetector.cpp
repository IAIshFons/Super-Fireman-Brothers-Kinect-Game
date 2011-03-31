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
 *  @file UserDetector.cpp
 *                                                                      
 *  @brief implementation file for the class UserDetector.
 *
 *  This file contains the implementation of the functions and methods
 *  of the class UserDetector. The user detector class contains functions 
 *  and methods to manage all the atributes relative to user recognition, 
 *  and user handling.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */


# include "UserDetector.h"

/**
 *  Function used to cast void* to UserDetector* object
 *  @param object object to be cast.
 */
static UserDetector* cast(void* object) 
{
    return static_cast<UserDetector *>(object);
}

/**
 *  Method that calls the equivalent new user callback function 
 *  for the user detector introduced.
 *  @param gen reference to an user generator.
 *  @param userID user ID of the current user.
 *  @param userDet current passed user detector.
 */

static void XN_CALLBACK_TYPE c_NewUser(UserGenerator& gen, 
                                       XnUserID userID, 
                                       void *userDet)
{
    cast(userDet) -> newUser(userID);
}


/**
 *  Method that calls the equivalent lost user callback function 
 *  for the user detector introduced.
 *  @param gen reference to an user generator.
 *  @param userID user ID of the current user.
 *  @param userDet current passed user detector.
 */
static void XN_CALLBACK_TYPE c_LostUser(UserGenerator& gen, 
                                        XnUserID userID, 
                                        void *userDet)
{
    cast(userDet) -> lostUser(userID);
}

/**
 *  Method that calls the equivalent start calibration callback function 
 *  for the user detector introduced.
 *  @param skeleton reference to a skeleton capability type (OpenNI).
 *  @param userID user ID of the current user.
 *  @param userDet current passed user detector.
 */
static void XN_CALLBACK_TYPE c_StartCalibration(SkeletonCapability& skeleton, 
                                                XnUserID userID, 
                                                void *userDet)
{
    cast(userDet) -> startCalibration(userID);
}

/**
 *  Method that calls the equivalent end calibration callback function 
 *  for the user detector introduced.
 *  @param skeleton reference to a skeleton capability type (OpenNI).
 *  @param userID user ID of the current user.
 *  @param success boolean that indicates the calibration success.
 *  @param userDet current passed user detector.
 */
static void XN_CALLBACK_TYPE c_EndCalibration(SkeletonCapability& skeleton, 
                                              XnUserID userID, 
                                              XnBool success,
                                              void *userDet)
{
    cast(userDet) -> endCalibration(userID, success);
}

/**
 *  Method that calls the equivalent pose detection callback function 
 *  for the user detector introduced.
 *  @param pose reference to a pose capability type (OpenNI).
 *  @param poseName array where the pose name will be stored.
 *  @param userID user ID of the current user.
 *  @param userDet current passed user detector.
 */
static void XN_CALLBACK_TYPE c_PoseDetected(PoseDetectionCapability &pose,
                                            const XnChar *poseName, 
                                            XnUserID userID,
                                            void *userDet)
{
    cast(userDet) -> poseDetected(poseName, userID);
}


/**
 *  Constructor of the class.
 */
UserDetector :: UserDetector()
{
    memset(strPose, '\0', sizeof(strPose) * sizeof(char));
    userGenerator = NULL;
    depthGenerator = NULL;
    listener = vector<UserListener *>();
    usersTracked = map <XnUserID, int>();
    userHandle = NULL;
    userPoseHandle = NULL;
    userSkelHandle = NULL;
    needPose = false;
    stopDetection = false;
}


/**
 *  Constructor of the class.
 *  @param userGen reference to a OpenNI user generator class.
 *  @param depthGen reference to a OpenNI depth generator class.
 */
UserDetector :: UserDetector(UserGenerator& userGen, DepthGenerator& depthGen)
{
    memset(strPose, '\0', sizeof(strPose) * sizeof(char));
    userGenerator = userGen;
    depthGenerator = depthGen;
    listener = vector<UserListener *>(); 
    usersTracked = map <XnUserID, int>();
    userHandle = NULL;
    userPoseHandle = NULL;
    userSkelHandle = NULL;
    needPose = false;
    stopDetection = false;
}


/** 
 *  Method that register the callbacks relative to user
 *  interaction with the Kinect (new user, calibrate user, etc).
 */
void UserDetector :: registerCallbacks() 
{

    // Register user handling functions
    userGenerator.RegisterUserCallbacks(
        c_NewUser, 
        c_LostUser, 
        this, 
        userHandle
    );
    
    // Skeleton handling callbacks
    userGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(
        c_StartCalibration, 
        c_EndCalibration, 
        this, 
        userSkelHandle
    );

    // If calibration pose needed
    if (userGenerator.GetSkeletonCap().NeedPoseForCalibration()) {
        needPose = true;

        // Checking capability for pose
        if (!userGenerator.IsCapabilitySupported(
            XN_CAPABILITY_POSE_DETECTION)) 
        {
            printf("Pose required, but not supported\n");
            exit(EXIT_FAILURE);
        }
        
        // Getting pose 
        userGenerator.GetSkeletonCap().GetCalibrationPose(strPose);

        // Register pose callback
        userGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(
            c_PoseDetected, 
            NULL, 
            this,
            userPoseHandle
        );
    }
    else {
        memset(strPose, '\0', sizeof(strPose));
        userPoseHandle = NULL;
    }

    // Detect a skeleton with all joins
    userGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);
    
}


/**
 *  Adds a new listener type, listener types are used to 
 *  describe and implement behaviours of diferent user
 *  transformations, p.e, zamus and linq types are listener
 *  types.
 */
void UserDetector :: addListener(UserListener *newListener)
{
    if(newListener != NULL){
        //Check for more user listeners
        listener.push_back(newListener);

    } else{
        reportError("Null Listener could not be added\n");
    }

}


/**
 *  Callback function called when the calibration of an user
 *  starts.
 *  @param userID user ID of the user to be calibrated.
 */
void UserDetector :: initCalibration(XnUserID userID) 
{
    // Check pose
    if(needPose) {
        printf("Start Pose Detection\n");
        userGenerator.GetPoseDetectionCap().StartPoseDetection(
            strPose,
            userID
        );
    }
    else {
        userGenerator.GetSkeletonCap().RequestCalibration(userID, true);
    }
}


/**
 *  Callback function called when new user appears.
 *  @param userID user ID of the new user.
 */
void UserDetector :: newUser(XnUserID userID)
{
    int i, j;

    if (stopDetection) {
        return;
    }
   
    printf("New user detected %d\n", userID);

    for(i = 0; i < listener.size(); i++) {
        if (listener[i] -> isListened(userID)) {
            listener[i] -> newUser(userID);
            break;
        }
    }

    initCalibration(userID);        
}


/**
 *  Callback function called when an user is lost.
 *  @param userID user ID of the user lost.
 */
void UserDetector :: lostUser(XnUserID userID)
{
    int i;
 
    if (!stopDetection) {
        printf("Lost user %d\n", userID);
    }

    /* Call lost user of the specified listener */
    for(i = 0; i < listener.size(); i++) {
        if (listener[i] -> isListened(userID)) {
            listener[i] -> lostUser(userID);
            break;
        }
    }

    // Remove user from user tracked
    if (isTracked(userID)) {
        remTrackedUser(userID);
    }
}


/**
 *  Callback function called when thecalibration for a 
 *  detected user begins.
 *  @param user ID of the user to be calibrated.
 */
void UserDetector :: startCalibration(XnUserID userID)
{
    printf("Calibration start user %d\n", userID);
}


/**
 *  Callback function called when calibration of the 
 *  user ends.
 *  @param userID user ID of the user calibrated.
 *  @param success indicates if the calibration succeded or not.
 */
void UserDetector :: endCalibration(XnUserID userID, 
                                    XnBool success)
{
    printf("Calibration for user %d %s\n", 
        userID, success ? "Succeded" : "Failed");

    // On calibration succeded
    if(success) {
        userGenerator.GetSkeletonCap().StartTracking(userID);
        usersTracked.insert(pair <XnUserID, int> (userID, NO_LISTENED));
    }    
    else {
        initCalibration(userID);
    }
}


/**
 *  Callback function called when a new pose is detected.
 *  @param poseName name of the pose detected.
 *  @param userID user ID of the user that made the pose.
 */
void UserDetector :: poseDetected(const XnChar *poseName, 
                                  XnUserID userID)
{
    printf("Pose %s detected for user %d\n", poseName, userID);

    // Stop pose detection
    userGenerator.GetPoseDetectionCap().StopPoseDetection(userID);

    // Request calibration
    userGenerator.GetSkeletonCap().RequestCalibration(userID, true);
}


/**
 *  Returns the name of the pose.
 *  @return string name of the pose.
 */
char* UserDetector :: retPoseStr()
{
    return strPose;
}


/**
 *  Returns the user handler of callbacks.
 *  @return user handle.
 */
XnCallbackHandle UserDetector :: retUserHandle()
{
    return userHandle;
}


/**
 *  Returns the user pose handler of callbacks.
 *  @return user pose handler.
 */
XnCallbackHandle UserDetector :: retUserPoseHandle()
{
    return userPoseHandle;
}       


/**
 *  Returns the user skeleton handler of callbacks.
 *  @return user skeleton handler.
 */
XnCallbackHandle UserDetector :: retUserSkelHandle()
{
    return userSkelHandle;
}     


/**
 *  Returns the user generator.
 *  @return user generator.
 */
UserGenerator UserDetector :: retUserGenerator ()
{
    return userGenerator;
}


/**
 *  Returns depth generator.
 *  @param depth generator.
 */
DepthGenerator UserDetector :: retDepthGenerator ()
{
    return depthGenerator;
}


/**
 *  Returns the user listener vector.
 *  @return user listener vector.
 */
vector<UserListener *> UserDetector :: retUserListenerVector ()
{
    return listener;
}


/**
 *  Returns the transformation stage of an user.
 *  @param userID user ID of the user.
 *  @return user current transformation stage.
 */
int UserDetector :: retStage(XnUserID userID) {
    if (usersTracked.count(userID) == 1) {
        return usersTracked[userID];
    }
}


/**
 *  Modifies the current transformation stage of the user.
 *  @param userID user ID to modify the stage.
 *  @param stage new stage.
 */
void UserDetector :: changeStage(XnUserID userID, int stage) 
{
    usersTracked[userID] = stage;
}


/**
 *  Indicates if an user is being tracked.
 *  @param userID user ID of the user to be checked.
 *  @return true if the user is tracked, false otherwise.
 */
bool UserDetector ::  isTracked(XnUserID userID) 
{
    return (usersTracked.count(userID) == 1);
}


/**
 *  Remove a tracked user from tracked user map.
 *  @param userID userID of the user to be removed.
 */
void UserDetector :: remTrackedUser(XnUserID userID)
{
    usersTracked.erase(userID);
}


/**
 *  Returns the cantity of users that are being tracked.
 *  @return cantity of users tracked.
 */
int UserDetector :: retNumUsersTracked() 
{
    return usersTracked.size();
}
 

/**
 *  Returns the tracked user vector.
 *  @return vector of currently tracked users.
 */
vector<XnUserID> UserDetector :: trackedUsers() 
{
    int i;
    
    XnUserID currentUsers[MAX_USERS];
    XnUInt16 numUsers;

    vector<XnUserID> userVec;

    numUsers = MAX_USERS;

    userGenerator.GetUsers(currentUsers, numUsers);

    for(i = 0; i < numUsers; i++) {
        if(userGenerator.GetSkeletonCap().IsTracking(currentUsers[i]) ) {
            userVec.push_back(currentUsers[i]);
        }
    }
    return userVec;
}


/**
 *  Returns the detection status parameter.
 *  @param detection status (detect, no detect).
 *  @return detection status.
 */
bool UserDetector :: retDetectionStat() 
{
    return stopDetection;
}

/**
 *  Changes the stop detection parameter.
 *  @param value new value of the stop detection parameter.
 */
void UserDetector :: changeStopDetection (bool value) 
{
    stopDetection = value;
}

