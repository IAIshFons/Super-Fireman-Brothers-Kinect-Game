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
 *  @file TimeCounter.cpp
 *                                                                      
 *  @brief implementation file for the class TimeCounter.
 *
 *  This file contains the implementation of the functions and methods
 *  of the class TimeCounter.
 *
 *  @authors Alfonso Ros e Ismael Mendonça.
 *
 */

# include "TimeCounter.h"

/**
 *  Class constructor
 */
TimeCounter :: TimeCounter() 
{
    lastTime = 0.0f;
}


/**
 *  Take the time and returns the difference between 
 *  the current time and the last time taken.
 *  @return difference between current time and las time.
 */
double TimeCounter :: takeTime() 
{
 
    double time;
    double difference;

    time = 0.0f;
 
    if(!gettimeofday(&t_p, NULL)) {
        time = (double)t_p.tv_sec + ((double)t_p.tv_usec) / 1000000.0f;
    } 
    
    difference = (lastTime == 0.0f) ?  0.0f : time - lastTime;

    lastTime = time;

    return difference;
}
