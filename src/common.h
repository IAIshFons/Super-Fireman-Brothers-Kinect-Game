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
 *  @file common.h
 *                                                                      
 *  @brief This is the header file for the common functions.
 *
 *  This file contains all the common functions and methods
 *  needed to the entire program.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef COMMON_H
# define COMMON_H

//------------------------------------------------------------------------
//  OpenNI
//------------------------------------------------------------------------

# include <XnOpenNI.h>
# include <XnOS.h>
# include <XnCppWrapper.h>

//------------------------------------------------------------------------
//  OpenGL
//------------------------------------------------------------------------

# include <GL/glut.h>
# include <GL/glu.h>
# include <GL/gl.h>


//------------------------------------------------------------------------
//  C++
//------------------------------------------------------------------------

# include <cmath>
# include <cstdio>
# include <string>
# include <vector>
# include <map>
# include <ctime>

//------------------------------------------------------------------------
//  Libraries
//------------------------------------------------------------------------

# include "TimeCounter.h"
# include "Vector3D.h"

# define STATUS_CHECK(f, msg) checkGlobalErrorStatus(f, msg, #f)

# define XML_CONFIG_FILE "config/Config.xml"

/* Vectors indicating the coordinates axis */

static Vector3D g_Vx = Vector3D(1, 0, 0);
static Vector3D g_Vy = Vector3D(0, 1, 0);
static Vector3D g_Vz = Vector3D(0, 0, 1);
static Vector3D g_Vmx = Vector3D(-1, 0, 0);
static Vector3D g_Vmy = Vector3D(0, -1, 0);
static Vector3D g_Vmz = Vector3D(0, 0, -1);

using namespace std;
using namespace xn;


/**
 * Checks global status error messages of XN.
 * @param status indicates the actual XN status.
 * @param errorMsg string containing the error message to be
   shown.
 * @param error code line of error message to be shown.
 */
inline void checkGlobalErrorStatus (XnStatus status, string errorMsg, const char* error)
{
    if(status != XN_STATUS_OK) {
        printf("%s: %s (%s)\n\n", errorMsg.c_str(), xnGetStatusString(status), error);
        exit(EXIT_FAILURE);
    }
}

/**
 * Report and errpr and exit the program.
 * @param string containing the error message.
 */
inline void reportError(string error) 
{
    printf("%s\n", error.c_str());
    exit(EXIT_FAILURE);
}

/**
 * Function used to check the OpenNI registered enumeration errors.
 * @param status actual XN status.
 * @param error enumeration error struct containing the errors.
 */
void checkEnumError (XnStatus status, EnumerationErrors& error);

#endif
