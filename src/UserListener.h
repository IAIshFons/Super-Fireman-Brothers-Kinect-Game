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
 *  @file UserListener.h
 *                                                                      
 *  @brief Header file for the abstract class UserListener.
 *
 *  This file contains the definition of the abstract class UserListener
 *  which is used to manage the users that are currently listened, i.e,
 *  zamus users or linq users.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */


# ifndef USER_LISTENER 
# define USER_LISTENER
    
# include "common.h"
# include "config.h"

/**
 *  @class UserListener
 *
 *  @brief User listener abstract class represents the different users 
 *  types that the application can contain, p.e, Zamus, Linq.
 *
 *  This class is used to contain the information of the users that
 *  are listened and as an abstract class for the user listener types
 *  Zamus and Linq.
 *
 */

class UserListener
{
    public:

       /**
        *  Constructor of the class.
        */
        UserListener();

        /** 
         *  Class destructor 
         */
        ~UserListener(){}

        /** 
         *  Indicates the listener type (Zamus or Linq), it uses
         *  the macros ZAMUS_TYPE and LINQ_TYPE.
         */
        int listenerType;
        
        /** 
         *  Map of users IDs and status of users associated 
         *  with the listener.
         */
        map <XnUserID, int> usersListened;

        /** 
         *  Function that indicates if a user is being listened
         *  @param userID user ID of the user to be checked.
         *  @return true if the user is listened, false otherwise.
         */
        virtual bool isListened(XnUserID userID);

        /**
         *  Return the listener user Stage (Transformed). This function
         *  could be replaced because the only way that a user could be
         *  in a listener is that the user must be in TRANSFORMED stage.
         *  @param userID user ID of the intended user.
         *  @return stage of the user.
         */
        virtual int retLisUserStage(XnUserID userID);

        /**
         *  Callback function called when new user appears.
         *  @param userID user ID of the new user.
         */
        virtual void newUser(XnUserID userID)
        {
            printf("New user detected %d\n", userID);
        }

        /**
         *  Callback function called when an user is lost.
         *  @param userID user ID of the user lost.
         */
        virtual void lostUser(XnUserID userID)
        {
            printf("Lost user %d\n", userID);
        }

        /**
         *  Callback function called when the calibration for a 
         *  detected user begins.
         *  @param user ID of the user to be calibrated.
         */
        virtual void startCalibration(XnUserID userID)
        {
            printf("Calibration start user %d", userID);
        }

        /**
         *  Callback function called when calibration of the 
         *  user ends.
         *  @param userID user ID of the user calibrated.
         *  @param success indicates if the calibration succeded or not.
         */
        virtual void endCalibration(XnUserID userID, XnBool Success)
        {
            printf("Calibration end user %d", userID);
        }

        /**
         *  Callback function called when a new pose is detected.
         *  @param poseName name of the pose detected.
         *  @param userID user ID of the user that made the pose.
         */
        virtual void poseDetected(const XnChar *poseName, XnUserID userID)
        {
            printf("Pose %s detected for user %d\n", poseName, userID);
        }
        
};

# endif
