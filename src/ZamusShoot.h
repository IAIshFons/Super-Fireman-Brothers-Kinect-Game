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
 *  @file ZamusShoot.h
 *
 *  @brief This file contains the drescription for the class ZamusShoot.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "common.h"
# include "util.h"
# include "config.h"

# ifndef ZAMUS_SHOOT_H
# define ZAMUS_SHOOT_H

/**
 *  @class ZamusShoot
 *
 *  @brief This class contain the information about one shoot of water from
 *  Zamus. The direction of the shoot and the position.
 *
 *  It also has the function to draw it in OpenGL.
 *
 */

class ZamusShoot {
    public:

        /**
         *  Initial position for the shoot.
         *
         *  This is used as a point of reference to know when the shoot
         *  is too far.
         *
         */
        XnPoint3D initialPosition;

        /**
         *  Actual position of the shoot.
         */
        XnPoint3D position;

        /**
         *  Direction from where the shoot goes.
         */
        Vector3D direction;

        /**
         *  Constructor of the Class.
         */
        ZamusShoot();

        /**
         *  Constructor of the Class.
         */
        ZamusShoot(XnPoint3D pos, Vector3D dir, XnUserID p);

        /**
         *  True if the shoot is not too far.
         *
         *  @return true if the shoot is not too far or false if it
         *  passed the Z_SHOOT_MAX_DIST limit.
         *
         */
        bool isAlive();

        /**
         *  Player who made this shoot.
         *
         *  This variable is important to set the scores.
         *
         */
        XnUserID player;
        
        /**
         *  Set the next position of the shoot by the parameters set in
         *  the config.h file.
         */
        void nextPosition();

        /**
         *  Uses the OpenGL functions to draw the sphere representing
         *  the water shoot.
         */
        void drawShoot();
};

# endif
