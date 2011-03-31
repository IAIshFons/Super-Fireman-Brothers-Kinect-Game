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
 *  @file NeutralModel.h
 *  
 *  @brief This file contain the definition of the class NeutralModel.
 *
 */

# ifndef NEUTRALMODEL_H
# define NEUTRALMODEL_H

# include "common.h"
# include "config.h"

# include "Vector3D.h"
# include "UserDetector.h"
# include "ZamusModel.h"
# include "LinqModel.h"

/**
 *  @class NeutralModel
 *  
 *  @brief This class handles the drawing of the users when they are not
 *  transfomated in some character.
 *
 *  This class draws a stick figure over the users when they are been
 *  tracked but not transformated. Depending on the state of the user,
 *  it draws some parts of the characters models.
 *
 *  When the players are not tracked, this draws a diamond in their
 *  center of mass.
 *
 */

class NeutralModel 
{
    public:

        /**
         *  Constructor.
         */
        NeutralModel();

        /**
         *  Constructor.
         */
        NeutralModel(UserDetector *userDetector,
                     ZamusModel&  zamusModel,
                     LinqModel&   linqModel);

        /**
         *  Joints enum.
         *
         *  This enumerate the joints that this class will use.
         */
        enum joints{
            HEAD = 0,
            NECK,
            RSHOULDER,
            RELBOW,
            RHAND,
            LSHOULDER,
            LELBOW,
            LHAND,
            TORSO,
            RHIP,
            RKNEE,
            RFOOT,
            LHIP,
            LKNEE,
            LFOOT
        };

        /**
         *  DrawNeutral function.
         *
         *  This function draws the stick figure depending on the
         *  transforming stage of the player or draws a diamond if the
         *  player is not tracked.
         *
         *  @param player is the ID of the player.
         *
         */
        void drawNeutral (XnUserID player);

    private:

        /**
         *  User Generator pointer.
         */
        UserDetector *nm_UserDetector;

        /**
         *  Depth Generator pointer.
         */
        DepthGenerator nm_DepthGenerator;

        /**
         *  Zamus Model.
         */
        ZamusModel zamusModelParts;

        /**
         *  Linq Model.
         */
        LinqModel linqModelParts;

        /**
         *  Joint position array.
         */
        XnPoint3D joint[15];

        /**
         *  Load actual joint positions.
         *
         *  Load the position of the joints in the joint array.
         *
         *  @param player is the player ID who needs to load the joints
         *  from.
         *  @param skelCap is the skeletonCapability taken from the User
         *  Generator.
         */
        void loadJoints (XnUserID player, SkeletonCapability skelCap);

        /**
         *  Orient the modeling matrix between two points.
         *
         *  Modify the modeling matrix to be centared in one point and
         *  with the Y axis looking to the second point.
         *
         *  @param point1 is where the matrix will be centered.
         *  @param point2 is where the Y axis will be.
         */
        void orientMatrix (XnPoint3D& point1, XnPoint3D& point2);

        /**
         *  Draw a stick between two points.
         *
         *  This function draws a cylincer and a sphere on its top
         *  between two points.
         *
         *  @param point1 is the first point.
         *  @param point2 is the second point where is going to be the
         *  sphere.
         */
        void drawLimp (XnPoint3D& point1, XnPoint3D& point2);

        /**
         *  Draw Torso.
         *
         *  This function draws a box that represents the torso of the
         *  player.
         */
        void drawTorso ();

        /**
         *  Draw head.
         *
         *  This function draws a sphere in the head joint of the
         *  player.
         */
        void drawHead ();
};

# endif
