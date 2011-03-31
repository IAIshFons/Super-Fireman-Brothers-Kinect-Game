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
 *  @file UserListener.cpp
 *                                                                      
 *  @brief Implementation file for the abstract class UserListener.
 *
 *  This file contains the implementation of the functions for the
 *  user listener class.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "UserListener.h"


/**
 *  Constructor of the class.
 */
UserListener :: UserListener()
{
    listenerType = -1;
    usersListened = map <XnUserID, int> ();
}


/** 
 *  Function that indicates if a user is being listened
 *  @param userID user ID of the user to be checked.
 *  @return true if the user is listened, false otherwise.
 */
bool UserListener :: isListened(XnUserID userID)
{
    return (usersListened.count(userID) == 1);
}


/**
 *  Return the listener user Stage (Transformed). This function
 *  could be replaced because the only way that a user could be
 *  in a listener is that the user must be in TRANSFORMED stage.
 *  @param userID user ID of the intended user.
 *  @return stage of the user.
 */
int UserListener :: retLisUserStage(XnUserID userID) 
{
    if (usersListened.count(userID) == 1) {
        return usersListened[userID];
    }

    return NO_LISTENED;
}
