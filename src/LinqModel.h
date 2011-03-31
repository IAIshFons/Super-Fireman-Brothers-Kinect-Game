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
 *  @file LinqModel.h
 *  
 *  @brief This file contain the definition of the class LinqModel.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 */

# ifndef LINQMODEL_H
# define LINQMODEL_H

# include "../glm/include/glm.h"
# include "common.h"
# include "config.h"

/**
 *  @class LinqModel
 *
 *  @brief This class loads the diferent models of Linq.
 *
 *  To load the 3D model of Linq, we use the GLM library. This library
 *  can load models from .obj files and use it with OpenGL.
 *
 */

class LinqModel
{
    public:

        // This variables contain the Linq model parts.
        GLMmodel* foot;
        GLMmodel* leg;
        GLMmodel* thigh;
        GLMmodel* chest;
        GLMmodel* head;
        GLMmodel* shoulder;
        GLMmodel* arm;
        GLMmodel* forearm;
        GLMmodel* shield;
        GLMmodel* sword;
        GLMmodel* staff;

        /**
         *  Constructor.
         */
        LinqModel () {
                
            foot     = NULL;
            leg      = NULL;
            thigh    = NULL;
            chest    = NULL;
            head     = NULL;
            shoulder = NULL;
            arm      = NULL;
            forearm  = NULL;
            shield   = NULL;
            sword    = NULL;
            staff    = NULL;
           
            if (!foot) {
                foot    = glmReadOBJ("./models/linqobj/pieLinq.obj");
                glmUnitize(foot);
            }
            if (!leg) {
                leg     = glmReadOBJ("./models/linqobj/antepiernaLinq.obj");
                glmUnitize(leg);
            }
            if (!thigh) {
                thigh   = glmReadOBJ("./models/linqobj/piernaLinq.obj");
                glmUnitize(thigh);
            }
            if (!chest) {
                chest   = glmReadOBJ("./models/linqobj/torsoLinq.obj");
                glmUnitize(chest);
            }
            if (!head) {
                head    = glmReadOBJ("./models/linqobj/cabezaLinq.obj");
                glmUnitize(head);
            }
            if (!shoulder) {
                shoulder = glmReadOBJ("./models/linqobj/hombroLinq.obj");
                glmUnitize(shoulder);
            }
            if (!arm) {
                arm     = glmReadOBJ("./models/linqobj/brazoLinq.obj");
                glmUnitize(arm);
            }
            if (!forearm) {
                forearm = glmReadOBJ("./models/linqobj/antebrazoLinq.obj");
                glmUnitize(forearm);
            }
            if (!shield) {
                shield  = glmReadOBJ("./models/linqobj/escudoLinq.obj");
                glmUnitize(shield);
            }
            if (!sword) {
                sword  = glmReadOBJ("./models/linqobj/espadaLinq.obj");
                glmUnitize(sword);
            }
            if (!staff) {
                staff = glmReadOBJ("./models/linqobj/icestaff.obj");
                glmUnitize(staff);
            }
        }

};

# endif
