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
 *  @file SuperFiremanBrothers.h
 *                                                                      
 *  @brief Header file for the class SuperFiremanBrothers.
 *
 *  This file contains all the information referenced to the class
 *  SuperFiremanBrothers. It contains all the specifications of
 *  the Super Fireman Brothers game, related to game starting, 
 *  current players, game status and situations where the game could
 *  be finished.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */


# ifndef SUPER_FIREMAN_BROTHERS

# define SUPER_FIREMAN_BROTHERS


# include "common.h"
# include "config.h"
# include "FlameModel.h"
# include "ZamusShoot.h"
# include "LinqSpawnIce.h"
# include "Flame.h"
# include "Zamus.h"
# include "Linq.h"
# include "UserDetector.h"

/**
 *  @class SuperFiremanBrothers
 *
 *  @brief This class handles the functions and methods for the Super
 *  Fireman Brothers game.
 * 
 *  In this class we implement the functions that are necessary for
 *  the game playing. This functions are those referents to game status,
 *  starting game, end game conditions, score counting, actual users
 *  in the game and the relatives to OpenGL graphics.
 */

class SuperFiremanBrothers
{
    public:
        
        /** 
         *  Constructor of the class.
         */
        SuperFiremanBrothers();
        
        /** 
         *  Constructor of the class.
         *  @param ud pointer to a User Detector type.
         *  @param sa pointer to a Scene Analyzer type.
         *  @param zd pointer to Zamus Listener type.
         *  @ṕaram ld pointer to Linq Listener type.
         *  @param mp max numer of players allowed.
         */
        SuperFiremanBrothers(UserDetector *ud,
                             SceneAnalyzer *sa,
                             Zamus *zd,
                             Linq *ld,
                             int mp);

        /** 
         *  Class destructor
         */
        ~SuperFiremanBrothers() {}

        
        /**
         *  Method that checks the users during the game.
         *  This function controls the entry of players to
         *  the game as well the players that have left the
         *  game after it started.
         */
        void checkUsers();

        /**
         *  Method that checks the condition required for the
         *  game to finish changing the game status depending on
         *  the condition assumed.
         */
        void checkGameOver();

        /**
         *  Function that returns the score of a specified player.
         *  @param player user ID of the player to check the score.
         *  @return score of the player.
         */
        int retScore(XnUserID player);
  
        /**
         *  Return the actual game status.
         *  @return game status.
         */
        int retGameStatus();
        
        /**
         *  Method that indicates if the game has started
         *  or not.
         *  @return true if game has started, false otherwise.
         */
        bool isGameOn();
        
        /**
         *  Method that indicates if the game has finished
         *  or not.
         *  @return true if game has finished, false otherwise.
         */
        bool isGameOver();

       
        /**
         *  Method that draws the Fireballs of the game and 
         *  controls the vector of fireballs.
         */
        void drawFireBalls();

        /**
         *  Draw the scores over the users in the game (openGL).
         */
        void drawGameInfo();

        /**
         *  Prints the given string to Bitmap.
         *  @param font type of font to print.
         *  @param str string to be printed.
         */
        void glPrintString(void *font, char *str);

        /**
         *  Method that controls the fireballs that are 
         *  going to be spawned per frames.
         */
        void nextFrame();


    private:
    
        /** 
         *  Posible status of the game.
         *  - NOT_STARTED the game hasn't started yet.
         *  - STARTED the game is now started.
         *  - NO_PLAYERS the game has started but the players have
         *    left the game.
         *  - LOST_GAME the game is over and the players lost.
         *  - WON_GAME the game is over and the game is won.
         *    (not implemented).
         */
        enum gameStatus {
            NOT_STARTED = 0,
            STARTED,
            NO_PLAYERS,
            LOST_GAME,
            WON_GAME
        };

        /** 
         *  Maximun players in the game.
         */
        int maxPlayers;

        /**
         *  Floor Level.
         */
        float floorLevel;

        /**
         *  Flame Model.
         */
        FlameModel flameModel;

        /**
         * Pointer to the application user detector.
         */
        UserDetector *userDetector;

        /**
         *  Pointer to the Scene Analyzer.
         */
        SceneAnalyzer *sceneAnalyzer;

        /**
         *  Pointer to the application Zamus detector.
         */
        Zamus *zamusDetector;

        /**
         *  Pointer tot he application Linq detector.
         */
        Linq *linqDetector;

        /**
         *  Map of players of the game, maps users to
         *  scores.
         */
        map <XnUserID, int> players;
        
        /**
         *  Vector of flames in the game.
         */
        vector <Flame> fireBalls;

        /**
         *  Indicates if game lost.
         */
        bool lostGame;

        /**
         *  Indicates if win game.
         */
        bool winGame;

        /**
         *  Indicates the game status.
         *  @see gameStatus.
         */
        int gameStatus;

        /**
         *  Level of the game.
         */
        int level;

        /**
         *  Number of flames in this level.
         */
        int numFlames;

};

# endif
