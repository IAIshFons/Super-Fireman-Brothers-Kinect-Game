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
 *  @file util.h
 *                                                                      
 *  @brief This is the header file of the utility functions.
 *
 *  This file contains all the functions and methods
 *  that works as utility for the program, they are not
 *  directly related to the application.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef UTIL
# define UTIL

# include <cmath>

# define PI 3.14159265

/**
 *  Transform a given radian to its equivalent angle.
 *  @param radian radian to be transformed.
 *  @param angle of the radian.
 */
inline float toAngle(float radian) 
{
    return (radian * 180) / PI;
}

/**
 *  Takes the percentage of time given a maximun time.
 *  @param time actual time given.
 *  @param maxTime maximun time.
 *  @return percentage of time.
 */
inline int transPercent(float time, float maxTime) 
{
    return (int)floor(((time * 100.0) / maxTime));
}

# endif
