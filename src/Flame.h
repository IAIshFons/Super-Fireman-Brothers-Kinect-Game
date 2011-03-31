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
 *  @file Flame.h
 *
 *  @brief This file contais the definition of the class Flame.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef FLAME

# define FLAME

# include "../glm/include/glm.h"
# include "common.h"

/**
 *  @class Flame
 *
 *  @brief This class contains the information about one flame in the
 *  game.
 *
 *  Tha flames have helth points (hp) that gets reduced when the flames
 *  are hit by a shoot of a player. The flames are hit when the position
 *  of a shoot is into the bounding box of the flame.
 *
 *  Aditionaly the flames only move in the Z axis. When they go to far,
 *  the game ends.
 *
 */
class Flame {
    
    public:
        
        /**
         *  Constructor
         */
        Flame();
        
        /**
         *  Constructor
         *
         *  @param pos is the position of the Flame.
         *  @param lifePoint is how much hp will have the Flame.
         *  @param model is the pointer to the flame model loaded by GLM. 
         */
        Flame (Vector3D pos, int lifePoint, GLMmodel *model);

        /**
         *  Destructor
         */
        ~Flame() {}

        /**
         *  Returns if a shot is inside of flame 
         *  bounding box.
         *
         *  @param shoot is the position of the shoot to test if it hit the
         *  flame.
         *
         *  @return True if the point shoot is in the bounding box of
         *  the flame.
         */
        bool isInBoundingBox(Vector3D shoot);

        /**
         *  Return true if the flame is steel alive.
         */
        bool isAlive();

        /**
         *  Down the hp of the flame.
         */
        int extinguish();

        /**
         *  Advance the flame.
         *
         *  @param distance is the amount of distance that the flame will
         *  advance.
         */
        void advance(float distance);

        /**
         *  Draw the flame in OpenGL.
         */
        void drawFlame();

        /**
         *  Draw Shadow.
         *  Draws a shadown at the floor level.
         *  This is helfull to the users to get a better perspective
         *  on where is the actually the flame.
         *
         *  @param floorLevel is a value in the Y axis where the shadows
         *  will be drawn
         */
        void drawShadow(float floorLevel);

        /**
         *  Get z position of the flame.
         */
        float getZPos();

    private:

        /**
         *  Dimension of the flame.
         *
         *  (width, height, depth)
         */
        GLfloat dimensions[3];

        /**
         *  Pointer to flame model.
         */
        GLMmodel* flameModel;
        
        /**
         *  Position of the flame
         */
        Vector3D position;
        
        /**
         *  Health points
         */
        int hp;
};


# endif
