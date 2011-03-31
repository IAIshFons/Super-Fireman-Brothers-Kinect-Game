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
 *  @file UserDetector.h
 *                                                                      
 *  @brief Header file for the class UserDetector.
 *
 *  This file contains all the information referenced to the class
 *  UserDetector. The user detector class contains functions and methods
 *  to manage all the atributes relative to user recognition, and 
 *  user handling.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef USER_DETECTOR
# define USER_DETECTOR

# include "common.h"
# include "UserListener.h"

/**
 *  @class UserDetector
 *
 *  @brief This class handles the functions and methods of the user
 *  detection/handling for the application.
 * 
 *  In this class we implement the functions that are necessary for
 *  user handling and detection. This functions are those referents 
 *  to callbacks for user actions (new user, lost users, calibration,
 *  pose detection), specifications about tracked users and current
 *  transformations status.
 *
 *  @see UserListener
 */

class UserDetector : private UserListener
{

    public:
        
       /**
        *  Constructor of the class.
        */
        UserDetector();

       /**
        *  Constructor of the class.
        *  @param userGen reference to a OpenNI user generator class.
        *  @param depthGen reference to a OpenNI depth generator class.
        */
        UserDetector(UserGenerator& userGen, DepthGenerator& depthGen);
        
        /**
         *  Class destructor.
         */
        ~UserDetector() {}

        /** 
         *  Method that register the callbacks relative to user
         *  interaction with the Kinect (new user, calibrate user, etc).
         */
        void registerCallbacks();

        /**
         *  Adds a new listener type, listener types are used to 
         *  describe and implement behaviours of diferent user
         *  transformations, p.e, zamus and linq types are listener
         *  types.
         */
        void addListener(UserListener *newListener);

        /**
         *  Callback function called when the calibration of an user
         *  starts.
         *  @param userID user ID of the user to be calibrated.
         */
         void initCalibration(XnUserID userID);
        
        /**
         *  Callback function called when new user appears.
         *  @param userID user ID of the new user.
         */
         void newUser(XnUserID userID);

        /**
         *  Callback function called when an user is lost.
         *  @param userID user ID of the user lost.
         */
         void lostUser(XnUserID userID);

        /**
         *  Callback function called when the calibration for a 
         *  detected user begins.
         *  @param user ID of the user to be calibrated.
         */
         void startCalibration(XnUserID userID);

        /**
         *  Callback function called when calibration of the 
         *  user ends.
         *  @param userID user ID of the user calibrated.
         *  @param success indicates if the calibration succeded or not.
         */
         void endCalibration(XnUserID userID, 
                             XnBool success);

        /**
         *  Callback function called when a new pose is detected.
         *  @param poseName name of the pose detected.
         *  @param userID user ID of the user that made the pose.
         */
         void poseDetected(const XnChar *poseName, 
                           XnUserID userID);

        /**
         *  Returns the name of the pose.
         *  @return string name of the pose.
         */
        XnChar* retPoseStr();

        /**
         *  Returns the user handler of callbacks.
         *  @return user handle.
         */
        XnCallbackHandle retUserHandle();
  
        /**
         *  Returns the user pose handler of callbacks.
         *  @return user pose handler.
         */
        XnCallbackHandle retUserPoseHandle();

        /**
         *  Returns the user skeleton handler of callbacks.
         *  @return user skeleton handler.
         */
        XnCallbackHandle retUserSkelHandle();

        /**
         *  Returns the user generator.
         *  @return user generator.
         */
        UserGenerator retUserGenerator(); 

        /**
         *  Returns depth generator.
         *  @param depth generator.
         */
        DepthGenerator retDepthGenerator(); 

        /**
         *  Returns the user listener vector.
         *  @return user listener vector.
         */
        vector<UserListener *> retUserListenerVector ();

        /**
         *  Returns the transformation stage of an user.
         *  @param userID user ID of the user.
         *  @return user current transformation stage.
         */
        int retStage(XnUserID userID);

        /**
         *  Modifies the current transformation stage of the user.
         *  @param userID user ID to modify the stage.
         *  @param stage new stage.
         */
        void changeStage(XnUserID userID, int stage);
 
        /**
         *  Indicates if an user is being tracked.
         *  @param userID user ID of the user to be checked.
         *  @return true if the user is tracked, false otherwise.
         */
        bool isTracked(XnUserID userID);

        /**
         *  Remove a tracked user from tracked user map.
         *  @param userID userID of the user to be removed.
         */
        void remTrackedUser(XnUserID userID);
        
        /**
         *  Returns the cantity of users that are being tracked.
         *  @return cantity of users tracked.
         */
        int retNumUsersTracked();
    
        /**
         *  Returns the tracked user vector.
         *  @return vector of currently tracked users.
         */
        vector<XnUserID> trackedUsers();

        /**
         *  Returns the detection status parameter.
         *  @param detection status (detect, no detect).
         *  @return detection status.
         */
        bool retDetectionStat();
        
        /**
         *  Changes the stop detection parameter.
         *  @param value new value of the stop detection parameter.
         */
        void changeStopDetection (bool value);

    private: 
    

        /** 
         *  String that contains the pose name.
         */
        XnChar strPose[20];

        /** 
         *  Current user generator.
         */
        UserGenerator userGenerator;

        /**
         *  Current depth generator.
         */
        DepthGenerator depthGenerator;

        /** 
         *  Vector of listeners, listeners are posible user
         *  transformations (zamus, linq).
         */
        vector<UserListener *> listener;

        /** 
         *  User detection handler. 
         */
        XnCallbackHandle userHandle;

        /** 
         *  User pose handler.
         */
        XnCallbackHandle userPoseHandle;
        
        /** 
         *  User skeleton handler.
         */
        XnCallbackHandle userSkelHandle;

        /** 
         *  Indicates if pose is needed.
         */
        XnBool needPose;

        /** 
         *  Indicates when to stop the detection of users, the
         *  detection of users must stop once the game is started.
         */
        bool stopDetection;
  
        /**
         *  Map of user being tracked, it indicates the stage 
         *  in wich the users are when transforming.
         */
        map <XnUserID, int> usersTracked;
       
};
# endif
