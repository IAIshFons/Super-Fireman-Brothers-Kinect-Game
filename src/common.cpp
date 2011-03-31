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
 *  @file common.cpp
 *                                                                      
 *  @brief This is the implementation file of the common header file.
 *
 *  This file contains the implementation of the functions and methods
 *  for the common header file.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "common.h"

/**
 *  Function used to check the OpenNI registered enumeration errors.
 *  @param status actual XN status.
 *  @param error enumeration error struct containing the errors.
 */
void checkEnumError (XnStatus status, EnumerationErrors& error)
{
    XnChar errorBuffer[1024];

    if (status == XN_STATUS_NO_NODE_PRESENT) {
        error.ToString(errorBuffer, 1024);
        printf("%s\n", errorBuffer);
        exit(EXIT_FAILURE);
    }
    else if (status != XN_STATUS_OK) {
        printf("Open failed: %s\n", xnGetStatusString(status));
        exit(EXIT_FAILURE);
    }
}
