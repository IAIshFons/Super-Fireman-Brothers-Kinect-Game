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
 *  @file AbstractPoseDetection.cpp
 *                                                                      
 *  @brief This the implementation file of the class 
 *  AbstractPoseDetection.
 *
 *  This file contains all the implementation of the functions and
 *  methods for the AbstractPoseDetection header file.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "AbstractPoseDetection.h"


/** 
 *  Constructor of the class.
 */
AbstractPoseDetection :: AbstractPoseDetection()
{
    userDetector = NULL;
    poseTime = map <XnUserID, double>();
    requiredPoseTime = 0.0f;
    tc = TimeCounter();
}

/** 
 *  Constructor of the class.
 *  @param userD a pointer to an user detector type.
 */
AbstractPoseDetection :: AbstractPoseDetection(UserDetector *userD)
{
    userDetector = userD;
    poseTime = map <XnUserID, double>();
    requiredPoseTime = 0.0f;
    tc = TimeCounter();
}

/** 
 *  Virtual function which specifies the framework
 *  of user pose detection, it can be reimplemented
 *  in further poses if needed.
 */
void AbstractPoseDetection :: detectPose()
{
    int i;
    int numUsers;
    XnUserID id;

    double timeDifference;

    vector <XnUserID> currentUsers;
    
    currentUsers = userDetector -> trackedUsers();

    // If no user tracked, then no pose can be
    // detected
    if (currentUsers.size() == 0) {
        return;
    }

    timeDifference = tc.takeTime();

    for(i = 0; i < currentUsers.size(); i++) {
        id = currentUsers[i];
        if(isPosing(id, poseTime[id])) {
            // Pose detected
            if(poseTime[id] >= requiredPoseTime) {
                poseDetected(id);
            } 

            poseTime[id] += timeDifference;
        } 
        else {
            poseTime[id] = 0.0f;
        }
    }
}

/**
 *  Returns the pose time of a specified user.
 *  @param userID ID of the user to know the pose time.
 *  @return pose time of the user.
 */
double AbstractPoseDetection ::  userPoseTime (XnUserID userID) 
{
    if (poseTime.count(userID) == 1) {
        return poseTime[userID];
    }
    return -1;
}
