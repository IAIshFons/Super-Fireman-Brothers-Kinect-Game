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

# ifndef LINQ
# define LINQ

# include "common.h"
# include "config.h"
# include "util.h"
# include "AbstractPoseDetection.h"
# include "UserListener.h"
# include "UserDetector.h"
# include "LinqSpawnIce.h"

/**
 *  @class Linq
 *
 *  @brief This class hanldes all aspects about the detection and
 *  information referred to the Linq players.
 *
 *  This class handles the detection of the pose to transform in Linq
 *  and other things like the pose to spawn ice and the ice spawned by
 *  the users.
 *
 */

class Linq : public AbstractPoseDetection, UserListener
{
    public:

        /**
         *  Linq constructor.
         *
         *  @param userDetector is a pointer to the userDetector of the
         *  game.
         */
        Linq(UserDetector *userDetector);
        
        /**
         *  Linq destructor 
         */
        ~Linq() {}

        /**
         * Specifies transformation stages.
         *
         * - T_STAGE_1 the right arm of the user is transformed.
         * - T_STAGE_2 the right and left arm of the user is transformed.
         * - TRANSFORMED the user is transformed completly.
         */
        enum lStages {
            T_STAGE_1 = 4,
            T_STAGE_2,
            TRANSFORMED,
        };

        /**
         * Ice rod stages.
         *
         * - DEACTIVATED the user can't shoot.
         * - ACTIVATED the user can shoot.
         */
        enum IceRodStates {
            DEACTIVATED,
            ACTIVATED
        };
        
        /**
         * Vector of linq ice spawns 
         */
        vector <LinqSpawnIce> iceSpawn;

        /**
         * Add shoot function.
         *
         * This function adds a new ice to the vector iceSpawn.
         *
         * @param position is the initial position of the ice
         * @param direction is the vector that represents the direction
         * of the ice.
         * @oaram p is the player's id.
         */
        void addIceSpawn (XnPoint3D position, Vector3D direction, XnUserID p);
       
        /**
         *  Returns buster status.
         *
         *  @param userID is the player's id.
         *
         *  @return the integer that represents the status of the ice
         *  rod.
         *
         */
        int retIceRodStatus(XnUserID userID);

        /**
         *  Changes buster Status.
         *
         *  @param userID is the player's id.
         *  @param status status to set the ice rod.
         */
        void changeIceRodStatus(XnUserID userID, int status);
        
        /**
         *  Returns ice rod charge status.
         *
         *  @param userID is the player's id.
         *
         *  @return True if the player can shoot. False in other case.
         */
        bool retIceCharge(XnUserID userID);

        /**
         *  Changes ice rod charge Status.
         *
         *  This is needed to sequence the poses to spawn ice.
         *
         *  @param userID is the player's id.
         *  @param satus is the value to set the charge map.
         */
        void changeIceRodCharge(XnUserID userID, bool status);
        
        /**
         *  Return listener user stage 
         *
         *  @param userID is the player's id.
         *
         *  @return the stage of the user given by the UserListener.
         */
        virtual int retLisUserStage(XnUserID userID);

        /**
         *  Returns if the user is currently listened.
         *
         *  @param userID is the player's ID.
         *
         *  @return True if the user is tracked.
         */
        virtual bool isListened(XnUserID userID);

     private:

        /**
         *  Ice rod status
         */
        map <XnUserID, int> iceRodStatus; 
        
        /**
         *  Map of icerod secuence activaton
         */
        map <XnUserID, bool> charge;

        /**
         *  Pose for stage1 transformation. 
         *
         *  @param userID is the player's id.
         *  @param stage is the stage in where is the player. 
         */
        void stage1(XnUserID userID, int stage);

        /**
         *  Pose for stage2 transformation. 
         *
         *  @param userID is the player's id.
         *  @param stage is the stage in where is the player. 
         */

        /* Pose for stage2 transformation */
        void stage2(XnUserID userID, int stage);

        /**
         *  Pose for stage3 transformation. 
         *
         *  @param userID is the player's id.
         *  @param stage is the stage in where is the player. 
         */
        void stage3(XnUserID userID, int stage);

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
        virtual bool isPosing(XnUserID userID, double poseTime = 0.0);

        /**
         *  Function to be applied when the pose is detected.
         *  
         *  @param userID is the player's id.
         */
        virtual void poseDetected(XnUserID userID);




        /******* Callback functions *******/


        /**
         * New user handler, this function is called when new user
         * appears.
         *  
         *  @param userID is the player's id.
         */
        virtual void newUser(XnUserID userID);

        /**
         * Lost user handler, this function is called when user is lost.
         *  
         *  @param userID is the player's id.
         */
        virtual void lostUser(XnUserID userID);

        /**
         * Start calibration handler, this function is called when 
         * calibration of a detected user begins.
         *  
         *  @param userID is the player's id.
         */
        virtual void startCalibration(XnUserID userID);

        /**
         * End calibration handler, this function is called when
         * calibration of the user ends
         *  
         *  @param userID is the player's id.
         *  @param Success is True if the calibration was successfull.
         */
        virtual void endCalibration(XnUserID userID, XnBool Success);
        
        /**
         * Pose Handler, this function is called when a new pose
         * is detected
         *
         * @param poseName name of the pose.
         * @param userID is the id of the player.
         */
        virtual void poseDetected(const XnChar *poseName, XnUserID userID);
        
};

#endif
