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
 *  @file ZamusModel.h
 *
 *  @brief This file contain the information about the class ZamusModel.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

#ifndef ZAMUSMODEL_H
#define ZAMUSMODEL_H

# include "../glm/include/glm.h"
# include "common.h"
# include "config.h"

/**
 *  @class ZamusModel
 *
 *  @brief This class loads the diferent models of Zamus.
 *
 *  To load the 3D models we use the GLM library. It can load .obj models
 *  generated with a 3D modeling software like Blender or Maya.
 *
 */

class ZamusModel
{
    public:

        // This variables contain the Zamus model parts.
        GLMmodel* foot;
        GLMmodel* leg;
        GLMmodel* thigh;
        GLMmodel* chest;
        GLMmodel* head;
        GLMmodel* shoulder;
        GLMmodel* arm;
        GLMmodel* forearm;
        GLMmodel* cannon;

        /**
         *  Constructor.
         */
        ZamusModel () {
                
            foot     = NULL;
            leg      = NULL;
            thigh    = NULL;
            chest    = NULL;
            head     = NULL;
            shoulder = NULL;
            arm      = NULL;
            forearm  = NULL;
            cannon   = NULL;
           
            if (!foot) {
                foot    = glmReadOBJ("./models/zamusobj/pieZamus.obj");
                glmUnitize(foot);
            }
            if (!leg) {
                leg     = glmReadOBJ("./models/zamusobj/antepiernaZamus.obj");
                glmUnitize(leg);
            }
            if (!thigh) {
                thigh   = glmReadOBJ("./models/zamusobj/musloZamus.obj");
                glmUnitize(thigh);
            }
            if (!chest) {
                chest   = glmReadOBJ("./models/zamusobj/torsoZamus.obj");
                glmUnitize(chest);
            }
            if (!head) {
                head    = glmReadOBJ("./models/zamusobj/cascoZamus.obj");
                glmUnitize(head);
            }
            if (!shoulder) {
                shoulder = glmReadOBJ("./models/zamusobj/hombrera.obj");
                glmUnitize(shoulder);
            }
            if (!arm) {
                arm     = glmReadOBJ("./models/zamusobj/brazo2Zamus.obj");
                glmUnitize(arm);
            }
            if (!forearm) {
                forearm = glmReadOBJ("./models/zamusobj/brazoZamus.obj");
                glmUnitize(forearm);
            }
            if (!cannon) {
                cannon  = glmReadOBJ("./models/zamusobj/cannonZamus.obj");
                glmUnitize(cannon);
            }
        }

};

#endif
