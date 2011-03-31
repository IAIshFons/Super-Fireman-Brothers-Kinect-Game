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
 *  @file LinqSpawnIce.h
 *
 *  @brief This file contains the definition of the class LinqSpawnIce.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "common.h"
# include "util.h"
# include "config.h"

# ifndef LINQ_SPAWN_ICE_H
# define LINQ_SPAWN_ICE_H

/**
 *  @class LinqSpawnIce
 *
 *  @brief This class handles the Ice spawned by Linq.
 *
 *  This class is the equivalent to the class ZamusShoot. It has the
 *  information about the position and direction of the Ice.
 *
 */
class LinqSpawnIce {

    public:

        /**
         * Initial position of the spawnIce
         */

        XnPoint3D initialPosition;

        /**
         * Actual position 
         */
        XnPoint3D position;

        /**
         * Direction 
         */
        Vector3D direction;

        /**
         * Constructor
         */
        LinqSpawnIce();
        
        /**
         * Constructor
         */
        LinqSpawnIce(XnPoint3D pos, Vector3D dir, XnUserID p);

        /**
         * Player who spawn this ice 
         */
        XnUserID player;

        /**
         *  True if the spawnIce is not too far.
         *
         *  @return True if the ice dosen't whent too far. False in
         *  other case.
         */
        bool isAlive();

        /**
         * Calculate next spawnIce position 
         */
        void nextPosition();

        /** 
         * Opengl function to display 
         */
        void drawSpawnIce();
};

# endif
