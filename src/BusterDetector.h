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
 *  @file BusterDetector.h
 *                                                                      
 *  @brief Header file for the class BusterDetector.
 *
 *  This file contains all the information referenced to the class
 *  BusterDetector, which consists in functions and methods for the 
 *  Buster pose detection and application.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef BUSTER_DETECTOR

# define BUSTER_DETECTOR

# define MAS

# include "common.h"
# include "Zamus.h"

/**
 *  @class BusterDetector
 *
 *  @brief This class handles the necessary functions for Buster pose
 *  detection.
 * 
 *  In this class we implement the functions that are necessary for
 *  Zamus Buster pose. This functions are those referents to pose 
 *  detection, pose application and specifications of the actions 
 *  to take when the named pose is detected.
 *
 *  @see AbstractPoseDetection
 * 
 */

class BusterDetector : public AbstractPoseDetection 
{

    public:

        /**
         *  Constructor of the class.
         *  @param zamus pointer to a zamus struture.
         *  @param userD pointer to a user detector structure.
         */
        BusterDetector (Zamus *zamus, UserDetector *userD);

        /**
         *  Class destructor 
         */
        ~BusterDetector() {}

        /** 
         *  Implementation of the isPosing function wich returns 
         *  if the user is doing the Buster pose.
         *  @param userID ID of the user to pose.
         *  @param poseTime time of the user.
         *  @return true if the user is posing for the buster, 
         *  false otherwise.
         */
        virtual bool isPosing(XnUserID userID, double poseTime = 0.0);

        /** 
         *  Specifies the actions that should be taken 
         *  when the Buster pose is detected.
         *  @param userID ID of the user.
         */
        virtual void poseDetected(XnUserID userID);

        /** 
         *  Method that is called when the Buster pose is 
         *  detected.
         *  @param userID user ID of the user who is appliying
         *  the Buster pose.
         */
        void shootBuster(XnUserID userID);


    private:
 
        /** 
         *  Pointer to the zamus detector.
         */
        Zamus *zDetector;

        /** 
         *  Map that contains the delay of the shoots of 
         *  every user transformed into zamus character.
         */
        map <XnUserID, int> shootDelay; 

        /** 
         *  Map used to print the buster activation message
         *  of every user as zamus.
         */
        map <XnUserID, bool> busterActivationMsg;

        /** 
         *  Function that detects if the Buster pose is being applied,
         *  it determines when the zamus user should shoot.
         *  @param userID id of the user applying the pose.
         *  @param poseTime pose time of the Buster pose.
         */
        bool detectBusterPose(XnUserID userID, double poseTime = 0.0);

        /** 
         *  Function that detects the activation of the zamus Buster.
         *  @param userID id of the user applying the pose.
         *  @param poseTime pose time of the Buster pose.
         */
        void detectBusterActivationPose(XnUserID userID, 
                                        double poseTime = 0.0);

        /** 
         *  Function that detects the deactivation of the zamus
         *  Buster.
         *  @param userID id of the user applying the pose.
         *  @param poseTime pose time of the Buster pose.
         */
        void detectBusterDeactivationPose(XnUserID userID, 
                                          double poseTime = 0.0);
};

# endif
