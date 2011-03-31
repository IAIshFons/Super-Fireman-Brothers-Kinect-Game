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

# include "SuperFiremanBrothers.h"

/** 
 *  Constructor of the class.
 */
SuperFiremanBrothers :: SuperFiremanBrothers () 
{
    userDetector  = NULL;
    sceneAnalyzer = NULL;
    zamusDetector = NULL;
    linqDetector = NULL;
    players = map <XnUserID, int> ();
    fireBalls = vector <Flame> (MAX_FIREBALLS, Flame());
    level = 0;
    numFlames = 0;
    maxPlayers = 0;
    floorLevel = 0;
    winGame  = false;
    lostGame = false;
    gameStatus = NOT_STARTED;
    flameModel = FlameModel();
}


/** 
 *  Constructor of the class.
 *  @param ud pointer to a User Detector type.
 *  @param sa pointer to a Scene Analyzer type.
 *  @param zd pointer to Zamus Listener type.
 *  @ṕaram ld pointer to Linq Listener type.
 *  @param mp max numer of players allowed.
 */
SuperFiremanBrothers :: SuperFiremanBrothers (UserDetector *ud,
                                              SceneAnalyzer *sa,
                                              Zamus *zd,
                                              Linq *ld,
                                              int mp) 
{ 
    XnPlane3D floor;
    DepthGenerator dgen;

    dgen = ud -> retDepthGenerator();
    sa -> GetFloor(floor);
    dgen.ConvertRealWorldToProjective(1,
                                      &floor.ptPoint,
                                      &floor.ptPoint);

    floorLevel = floor.ptPoint.Y + 100;
    userDetector  = ud;
    sceneAnalyzer = sa;
    zamusDetector = zd;
    linqDetector = ld;
    players = map <XnUserID, int> ();
    fireBalls = vector <Flame> (MAX_FIREBALLS, Flame());
    level = 0;
    numFlames = 0;
    maxPlayers = mp;
    winGame  = false;
    lostGame = false;
    gameStatus = NOT_STARTED;
    flameModel = FlameModel();
}


/**
 *  Method that checks the users during the game.
 *  This function controls the entry of players to
 *  the game as well the players that have left the
 *  game after it started.
 */
void SuperFiremanBrothers ::  checkUsers() 
{
    int i;

    vector <XnUserID> users;
    map <XnUserID, int> p;
    map <XnUserID, int> :: iterator iter;

    users = userDetector -> trackedUsers();
    
    // Check for tracked listened players
    for(i = 0; i < users.size(); i++) {
        if (zamusDetector -> isListened (users[i]) || 
            linqDetector -> isListened (users[i])) {
            p.insert(pair <XnUserID, int> (users[i], 0));
        }
    }
    
    // Check if the users have left the game
    if (gameStatus == STARTED) {
        
        // Check players who left the game
        for (iter = players.begin(); iter != players.end(); iter++) {
            if (p.count(iter -> first) == 0) {
                printf("Player %d has left the game\n", iter -> first);
                players.erase(iter -> first);
            } 
        }
        
        // No players in game
        if (p.size() == 0) {
            gameStatus = NO_PLAYERS;
            return;
        }


    }
    else if (gameStatus == NOT_STARTED) {
        players = p;
    }

    // All players ready to start game
    if (players.size() == maxPlayers) {
        userDetector -> changeStopDetection(true);
        gameStatus  = STARTED;
        return;
    }
}

/**
 *  Method that checks the condition required for the
 *  game to finish changing the game status depending on
 *  the condition assumed.
 */
void SuperFiremanBrothers :: checkGameOver()
{
    if (gameStatus == STARTED) {
    
        // Not enough players
        if (players.size() == 0) {
            printf("Players left the game...!\n");
            gameStatus = NO_PLAYERS;
        }
    
        // Game Lost 
        if (lostGame) {
            printf("You have lost the game...!\n");
            gameStatus = LOST_GAME;
        }

        // Game won
        if (winGame) {
            printf("Congratulations you have won...!\n");
            gameStatus = WON_GAME;
        }
    }
}
 

/**
 *  Function that returns the score of a specified player.
 *  @param player user ID of the player to check the score.
 *  @return score of the player.
 */
int SuperFiremanBrothers :: retScore(XnUserID player) 
{
    if (players.count(player) == 1) {
        return players[player];
    }
}


/**
 *  Return the actual game status.
 *  @return game status.
 */
int SuperFiremanBrothers :: retGameStatus() 
{
    return gameStatus;
}


/**
 *  Method that indicates if the game has started
 *  or not.
 *  @return true if game has started, false otherwise.
 */
bool SuperFiremanBrothers :: isGameOn() 
{
    return gameStatus >= STARTED;
}


/**
 *  Method that indicates if the game has finished
 *  or not.
 *  @return true if game has finished, false otherwise.
 */
bool SuperFiremanBrothers :: isGameOver() 
{
    return ((gameStatus == NO_PLAYERS) || (gameStatus == LOST_GAME) ||
            (gameStatus == WON_GAME));
}


/**
 *  Method that draws the Fireballs of the game and 
 *  controls the vector of fireballs.
 */
void SuperFiremanBrothers :: drawFireBalls ()
{
    int i;

    for (i = 0; i < fireBalls.size(); i++) {
        if (fireBalls[i].isAlive()) {
            fireBalls[i].drawFlame();

            // Draw Shadow.
            fireBalls[i].drawShadow(floorLevel);
        }
        else {
            fireBalls.erase(fireBalls.begin() + i);
            i--;
        }
    }
}


/**
 *  Draw the scores over the users in the game (openGL).
 */
void SuperFiremanBrothers :: drawGameInfo ()
{
    float y;
    int score;
    char strLabel[20] = "";
    char strLevel[20] = "";
    char strStart[20] = "Calibrate to begin";
    char strEnd[20] = "Game Over";
    UserGenerator uGen;
    DepthGenerator dGen;
    XnUserID player;
    XnPoint3D com;
    map <XnUserID, int> :: iterator iter;

    float amb[3] = {1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glDisable(GL_LIGHTING);
    y = -768;

    uGen = userDetector -> retUserGenerator();
    dGen = userDetector -> retDepthGenerator();

    for (iter = players.begin(); iter != players.end(); iter++) {
        player = iter -> first;
        score  = iter -> second;
        sprintf(strLabel, "Score: %d", score);
        uGen.GetCoM(player, com);
        dGen.ConvertRealWorldToProjective(1, &com, &com);

        glRasterPos3f( com.X + 100, com.Y - 300, com.Z);
        glPrintString(GLUT_BITMAP_HELVETICA_18, strLabel);
        y += 150;
    }

    sprintf(strLevel, "Level %d", level);
    glRasterPos2f( 500, -768);
    glPrintString(GLUT_BITMAP_HELVETICA_18, strLevel);

    if (gameStatus == NOT_STARTED) {
        glRasterPos2f( 500, 0);
        glPrintString(GLUT_BITMAP_HELVETICA_18, strStart);
    }
    else if (gameStatus > STARTED) {
        glRasterPos2f( 500, 0);
        glPrintString(GLUT_BITMAP_HELVETICA_18, strEnd);
    }

    glEnable(GL_LIGHTING);
}


/**
 *  Prints the given string to Bitmap.
 *  @param font type of font to print.
 *  @param str string to be printed.
 */
void SuperFiremanBrothers :: glPrintString(void *font, char *str)
{
    int i,l = strlen(str);
    for(i = 0; i < l; i++) {
        glutBitmapCharacter(font, *str++);
    }
}


/**
 *  Method that controls the fireballs that are 
 *  going to be spawned per frames.
 */
void SuperFiremanBrothers :: nextFrame ()
{
    if (gameStatus != STARTED) {
        return;
    }

    static int counter = 0;
    static int spawnRate = (SPAWN_RATE_FIRST_LEVEL) * players.size();
    static float speedRate = (SPEED_RATE_FIRST_LEVEL) * players.size(); 
    static int flamesInLevel = (FLAMES_IN_FIRST_LEVEL) * players.size();
    const static int riseSpawnRate = (RISE_SPAWN_RATE) * players.size();
    const static int riseSpeedRate = (RISE_SPEED_RATE) * players.size();
    const static int riseFlamesInLevel = (RISE_FLAMES_IN_LEVEL) * players.size();

    int i;
    int j;
    int hp;
    float x;
    float y;
    Vector3D position;

    vector <ZamusShoot> zShoot; 
    vector <LinqSpawnIce> lShoot; 

    zShoot = zamusDetector -> shoots;
    lShoot = linqDetector -> iceSpawn;
        
    UserGenerator  ugen;
    DepthGenerator dgen;
    map <XnUserID, int> :: iterator iter;
    XnUserID  player;
    XnSkeletonJointPosition joint;
    XnPoint3D foots[2];

    ugen  = userDetector -> retUserGenerator();
    dgen  = userDetector -> retDepthGenerator();

    for (i = 0; i < fireBalls.size(); i++) {

        for (j = 0; j < zShoot.size(); j++) {
            if (fireBalls[i].isInBoundingBox(zShoot[j].position)) {
                fireBalls[i].extinguish();
                players[zShoot[j].player] += POINTS_PER_HIT;
                zShoot.erase(zShoot.begin() + j);
                j--;
            }
        }

        for (j = 0; j < lShoot.size(); j++) {
            if (fireBalls[i].isInBoundingBox(lShoot[j].position)) {
                fireBalls[i].extinguish();
                players[lShoot[j].player] += POINTS_PER_HIT;
                lShoot.erase(lShoot.begin() + j);
                j--;
            }
        }

        for (iter = players.begin(); iter != players.end(); iter++) {
            player = iter -> first;
            ugen.GetSkeletonCap().GetSkeletonJointPosition(player, 
                                             XN_SKEL_RIGHT_FOOT,
                                             joint);
            foots[0] = joint.position;
            ugen.GetSkeletonCap().GetSkeletonJointPosition(player, 
                                             XN_SKEL_RIGHT_FOOT,
                                             joint);
            foots[1] = joint.position;
            dgen.ConvertRealWorldToProjective(2, foots, foots);
            if (fireBalls[i].isInBoundingBox(foots[0])) {
                fireBalls[i].extinguish();
                players[player] += POINTS_PER_HIT;
                j--;
            }
            if (fireBalls[i].isInBoundingBox(foots[1])) {
                fireBalls[i].extinguish();
                players[player] += POINTS_PER_HIT;
                j--;
            }
        }    

        zamusDetector -> shoots  = zShoot;
        linqDetector -> iceSpawn = lShoot;

        if (fireBalls[i].getZPos() > FIRE_LIMIT) {
            lostGame = true;
            return;
        }
        else {
            fireBalls[i].advance(speedRate);
        }

    }

    if ((counter == spawnRate) &&
        (numFlames < flamesInLevel)){
        x = (float)rand() / (float)RAND_MAX;
        y = (float)rand() / (float)RAND_MAX;

        x = (rand() % 800) + x;
        y = (rand() % 600) + y - floorLevel;

        hp = rand() % 3 + 1;

        position = Vector3D(x, y, -3500.0);

        fireBalls.push_back(Flame(position, hp, flameModel.flame));
        counter = 0;
        numFlames++;
    }
    else {
        counter += 1;
    }

    if ((numFlames == flamesInLevel) &&
        (fireBalls.size() == 0)) {
        level++;
        numFlames = 0;
        counter   = 0;
        flamesInLevel += riseFlamesInLevel;
        if ( (spawnRate - riseSpawnRate) > 0) {
            spawnRate -= riseSpawnRate ;
        }
        else {
            spawnRate = 1;
        }
        speedRate += riseSpeedRate;
        printf("Level %d start!\n", level);
    }
}
