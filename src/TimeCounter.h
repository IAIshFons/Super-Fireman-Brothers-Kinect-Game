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
 *  @file TimeCounter.h
 *                                                                      
 *  @brief Header file for the class TimeCounter.
 *
 *  This file contains the definition of the class TimeCounter, wich
 *  is used to store the time between frames for pose detection usages.
 *
 *  @authors Alfonso Ros e Ismael Mendonça.
 *
 */

# ifndef TIME
# define TIME

# include <sys/time.h>
# include <ctime>


/**
 *  @class TimeCounter.
 *
 *  @brief TimeCounter class for timing in pose detection.
 *
 *  This class is used to take the time difference between frames
 *  in order to calculate the amount of time a user is doing a 
 *  determined pose.
 *
 *  @see AbstractPoseDetection
 */
class TimeCounter
{
    private:

        /**
         *  Time taken in a determined frame.
         */
        double lastTime;
        
        /**
         *  Time structure for time storage.
         */
        struct timeval t_p;
        
    public:

        /**
         *  Class constructor.
         */
        TimeCounter();
        
        /**
         *  Class Destructor.
         */
        ~TimeCounter(){}

        /**
         *  Take the time and returns the difference between 
         *  the current time and the last time taken.
         *  @return difference between current time and las time.
         */
        double takeTime();
        
};

# endif
