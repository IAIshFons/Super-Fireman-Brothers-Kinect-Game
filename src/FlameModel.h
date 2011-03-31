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
 *  @file FlameModel.h
 *
 *  @brief This file contains the information about the class FlameModel.
 *
 */

#ifndef FLAMEMODEL_H
#define FLAMEMODEL_H

# include "../glm/include/glm.h"
# include "common.h"
# include "config.h"

/**
 *  @class FlameModel
 *
 *  @brief This class loads the flame model.
 *
 */

class FlameModel
{
    public:

        /**
         *  Pointer to the 3D model.
         */
        GLMmodel* flame;

        /**
         *  Constructor.
         */
        FlameModel () {
                
            flame = NULL;
           
            if (!flame) {
                flame = glmReadOBJ("./models/flameobj/flame.obj");
                glmUnitize(flame);
                glmScale(flame, 150);
            }
        }

};

#endif
