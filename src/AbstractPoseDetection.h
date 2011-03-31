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
 *  @file AbstractPoseDetection.h
 *                                                                      
 *  @brief Header file for the class AbstractPoseDetection.
 *
 *  This file contains all the information referenced to the class
 *  AbstractPoseDetection. It specifies an interface for coding 
 *  user poses for interaction with Kinect.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef ABSTRACT_POSE_DETECTION
# define ABSTRACT_POSE_DETECTION

# include "common.h"
# include "UserDetector.h"

/**
 *  @class AbstractPoseDetection
 *
 *  @brief This class handles the basics functions to code a pose for
 *  Kinect interaction.
 * 
 *  In this class we implement the functions that are necessary for
 *  user defined poses. This functions are those referents to pose
 *  time, pose definition and the action to take when a pose is detected,
 *  this class works as an abstract class for further pose specifications
 *
 */

class AbstractPoseDetection 
{
    public:
        
        /** 
         *  Constructor of the class.
         */
        AbstractPoseDetection();

        /** 
         *  Constructor of the class.
         *  @param userD a pointer to an user detector type.
         */
        AbstractPoseDetection(UserDetector *userD);
        
        /**
         *  Class destructor.
         */
        virtual ~AbstractPoseDetection(){}

        /** 
         *  Virtual function which specifies the framework
         *  of user pose detection, it can be reimplemented
         *  in further poses if needed.
         */
        virtual void detectPose();

    private:

        /** 
         *  Contains the required posing time for the
         *  pose to be detected
         */
        double requiredPoseTime;
        
        /** 
         *  Map that contains the information about the 
         *  users and the time that they have been posing,
         *  it receives de user ID and returns the pose time.
         */
        map <XnUserID, double> poseTime;

        /** 
         *  Time counter that is used to calculate the differences
         *  of time between frames to use it for pose time calculation.
         */
        TimeCounter tc;
        
        /**
         *  Returns the pose time of a specified user.
         *  @param userID ID of the user to know the pose time.
         *  @return pose time of the user.
         */
        double userPoseTime (XnUserID userID); 

    protected:

        /** 
         *  User detector structure wich will be used 
         *  to apply pose detection
         */
        UserDetector *userDetector; 

        /** 
         *  Virtual function wich should be implemented for
         *  the pose detection, it returns if the user is
         *  posing.
         *  @param userID ID of the user to pose.
         *  @param poseTime time of the user.
         *  @return true if the user is posing, false otherwise.
         */
        virtual bool isPosing(XnUserID userID, double poseTime = 0) = 0;

        /** 
         *  Virtual function wich should be implemented for
         *  the pose detection, it specifies the actions that
         *  should be taken when the pose is detected.
         *  @param userID ID of the user.
         */
        virtual void poseDetected(XnUserID userID) = 0;

        /** 
         *  This method changes the required pose time for 
         *  the pose that will be set.
         *  @param time duration of the pose for detection.
         */
        void setRequiredPoseTime(float time) 
        {
            requiredPoseTime = time;
        }
};

# endif
