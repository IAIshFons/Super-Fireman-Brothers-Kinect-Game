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
 *  @file Zamus.h
 *
 *  @brief This file contain the definitions of the functions of the
 *  class Zamus.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef ZAMUS
# define ZAMUS

# include "common.h"
# include "config.h"
# include "util.h"
# include "AbstractPoseDetection.h"
# include "ZamusShoot.h"
# include "UserListener.h"
# include "UserDetector.h"

/**
 *  @class Zamus
 *
 *  @brief This class hanldes all aspects about the detection and
 *  information referred to the Zamus players.
 *
 *  This class handles the detection of the pose to transform in Zamus
 *  and other things like the Buster status and the shoots made by the
 *  users.
 *
 */
class Zamus : public AbstractPoseDetection, UserListener
{
    public:

        /**
         *  Zamus constructor 
         *
         *  @param userDetector is a pointer to the userDetector of the
         *  game.
         */
        Zamus(UserDetector *userDetector);
        
        /**
         *  Zamus destructor 
         */
        ~Zamus() {}

         /**
          *  Specifies transformation stages.
          *
          *  - T_STAGE_1 the transformation is less than 35%
          *  - T_STAGE_2 the transformation is less than 70%
          *  - T_STAGE_3 the transformation is less than 100%
          */
        enum zStages{
            T_STAGE_1 = 0,
            T_STAGE_2,
            T_STAGE_3,
            TRANSFORMED
        };
       
        /**
         *  Busteer status.
         *
         *  - DEACTIVATED the user can't shoot.
         *  - ACTIVATED the user can shoot.
         */
        enum bStatus {
            DEACTIVATED,
            ACTIVATED
        };

        /**
         *  Vector of zamus shoots.
         *
         *  This vector contain the information about all the shoots made
         *  by the players.
         */
        vector <ZamusShoot > shoots;

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
        void addShoot (XnPoint3D position, Vector3D direction, XnUserID p);

        /**
         *  Returns buster status.
         *
         *  @param userID is the player's id.
         *
         *  @return the integer that represents the buster status.
         *
         */
        int retBusterStatus(XnUserID userID);

        /** 
         *  Changes buster Status
         *
         *  @param userID is the id of the player.
         *  @param status to set the buster of the player.
         */
        void changeBusterStatus(XnUserID userID, int status);

        /**
         *  Return listener user stage.
         *  
         *  @param userID is the player's id.
         *
         *  @return the stage of the user.
         *
         */
        virtual int retLisUserStage(XnUserID userID);

        /**
         *  Returns if the user is currently listened 
         *
         *  @param userID is the player's id.
         *
         *  @return true if the user is been tracked.
         */
        virtual bool isListened(XnUserID userID);

     private:
        
        /**
         *  Buster Status (Activated/Deactivated).
         */
        map <XnUserID, int> busterStatus;

        /**
         *  Indicates if the pose is being applied.
         *
         *  @param userID is the player's id.
         *  @parma poseTime is the time that the user has been posing.
         *
         *  @return True if the user is doing the pose to transform in
         *  Zamus.
         */
        virtual bool isPosing(XnUserID userID, double poseTime = 0.0);

        /**
         * Function to be applied when the pose is detected 
         *
         * @param userID is the player's id.
         */
        virtual void poseDetected(XnUserID userID);


        /**
         *  New user handler, this function is called when new user
         *  appears.
         *
         *  @param userID is the player's id.
         */
        virtual void newUser(XnUserID userID);

        /**
         *  Lost user handler, this function is called when user is lost
         *
         *  @parma userID is the player's id.
         */
        virtual void lostUser(XnUserID userID);

        /**
         *  Start calibration handler, this function is called when 
         *  calibration of a detected user begins
         *
         *  @param userID is the player's id.
         */
        virtual void startCalibration(XnUserID userID);

        /**
         *  End calibration handler, this function is called when
         *  calibration of the user ends
         *
         *  @param userID is the player's id.
         *  @param Success True is the user successfully calibrate.
         */
        virtual void endCalibration(XnUserID userID, XnBool Success);
        
        /**
         *  Pose Handler, this function is called when a new pose
         *  is detected
         *
         *  @param poseName The name of the pose 
         *  @param userID The id of the user.
         */
        virtual void poseDetected(const XnChar *poseName, XnUserID userID);
        

};

#endif
