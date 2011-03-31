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
 *  @file IceRodDetector.h
 *                                                                      
 *  @brief Header file for the class IceRodDetector.
 *
 *  This file contains all the information referenced to the class
 *  IceRodDetector wich consists in functions and methods for the
 *  Ice rod pose detection and application.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef ICE_ROD_DETECTOR

# define ICE_ROD_DETECTOR

# include "common.h"
# include "Linq.h"

/**
 *  @class IceRodDetector
 *
 *  @brief This class handles the necessary functions for Ice Rod pose
 *  detection.
 * 
 *  In this class we implement the functions that are necessary for
 *  Linq Ice Rod pose. This functions are those referents to pose 
 *  detection, pose application and specifications of the actions to 
 *  take when the named pose is detected.
 *
 *  @see AbstractPoseDetection
 * 
 */

class IceRodDetector : public AbstractPoseDetection 
{

    public:

        /**
         *  Constructor of the class.
         *  @param linq pointer to a linq struture.
         *  @param userD pointer to a user detector structure.
         */
        IceRodDetector (Linq *linq, UserDetector *userD);

        /** 
         *  Class destructor 
         */
        ~IceRodDetector() {}

        /** 
         *  Implementation of the isPosing function wich returns 
         *  if the user is doing the Ice Rod pose.
         *  @param userID ID of the user to pose.
         *  @param poseTime time of the user.
         *  @return true if the user is posing for the Ice Rod, 
         *  false otherwise.
         */
        virtual bool isPosing(XnUserID userID, double poseTime = 0.0);

        /** 
         *  Specifies the actions that should be taken 
         *  when the Ice Rod pose is detected.
         *  @param userID ID of the user.
         */
        virtual void poseDetected(XnUserID userID);

        /** 
         *  Method that is called when the Ice Rod pose is 
         *  detected.
         *  @param userID user ID of the user who is appliying
         *  the Ice Rod pose.
         */
        void invokeIce(XnUserID userID);


    private:
 

        /** 
         *  Pointer to the linq detector.
         */

        Linq *lDetector;

        /** 
         *  Function that detects if the Ice Rod pose is being applied,
         *  it determines when the linq user should invoke magic ice.
         *  @param userID id of the user applying the pose.
         *  @param poseTime pose time of the Ice Rod pose.
         */
        bool detectIceRodPose(XnUserID userID, double poseTime = 0.0);

};

# endif
