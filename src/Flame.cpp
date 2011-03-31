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
 *  @file Flame.cpp
 *
 *  @brief This file contains the implementation of the class Flame.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "Flame.h" 
 
/**
 *  Constructor
 */
Flame :: Flame ()
{
    position = Vector3D();
    hp = 0.0;
    flameModel = NULL;
    dimensions[0] = 0.0;
    dimensions[1] = 0.0;
    dimensions[2] = 0.0;
}

/**
 *  Constructor
 *
 *  @param pos is the position of the Flame.
 *  @param lifePoint is how much hp will have the Flame.
 *  @param model is the pointer to the flame model loaded by GLM. 
 */
Flame :: Flame (Vector3D pos, int lifePoint, GLMmodel *model)
{
    position = pos;
    hp = lifePoint;
    flameModel = model;
    glmDimensions(flameModel, dimensions);
}

/**
 *  Return true if the flame is steel alive.
 */
bool Flame :: isAlive ()
{
    if (hp == 0) {
        return false;
    }
    else {
        return true;
    }
}

/**
 *  Down the hp of the flame.
 */
int Flame :: extinguish ()
{
    if (hp > 0) {
        hp--;
        return hp;
    }
    else {
        return hp;
    }
}

/**
 *  Advance the flame.
 *
 *  @param distance is the amount of distance that the flame will
 *  advance.
 */
void Flame :: advance (float distance)
{
    position.z += distance;
}

/**
 *  Returns if a shot is inside of flame 
 *  bounding box.
 *
 *  @param shoot is the position of the shoot to test if it hit the
 *  flame.
 *
 *  @return True if the point shoot is in the bounding box of
 *  the flame.
 */
bool Flame :: isInBoundingBox (Vector3D shoot)
{
    float width; 
    float height; 
    float depth;

    float diffFlameShoot[3];

    /**
     *  TODO:
     *  The GLM library have a function that is call glmDimensions. This
     *  function can calculate the dimentions of the model and can be
     *  used to calculate the bounding box. But, when we used it, we
     *  dont get a good result, so we decided to get aproximated values.
     *
     *  In future releases we should use this method to get a more exact
     *  result.
     */

    width  = 50 + (hp * 100);
    height = 50 + (hp * 100);
    depth  = 50 + (hp * 100);

    diffFlameShoot[0] = fabs(shoot.x - position.x);
    diffFlameShoot[1] = fabs(shoot.y - position.y);
    diffFlameShoot[2] = fabs(shoot.z - position.z);

    // Check width.
    if (diffFlameShoot[0] < width) {
        if (diffFlameShoot[1] < height) {
            if (diffFlameShoot[2] < depth) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
    
}

/**
 *  Draw the flame in OpenGL.
 */
void Flame :: drawFlame ()
{
    int mode;
    float alfa;
    float scale;

    mode = GLM_SMOOTH | GLM_MATERIAL;

    alfa = (float)rand() / (float)RAND_MAX;
    alfa += rand() % 360;

    scale = (float)hp / 2.0f;

    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(scale, scale, scale);
      
        glRotatef(180, 1.0, 0.0, 0.0);
        glRotatef(alfa, 0.0, 1.0, 0.0);
        glmDraw(flameModel, mode);
        
    glPopMatrix();
}

/**
 *  Draw Shadow.
 *  Draws a shadown at the floor level.
 *  This is helfull to the users to get a better perspective
 *  on where is the actually the flame.
 *
 *  @param floorLevel is a value in the Y axis where the shadows
 *  will be drawn
 */
void Flame :: drawShadow (float floorLevel)
{
    GLfloat shadowColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, shadowColor);

    glPushMatrix();
        glTranslatef( position.x, floorLevel, position.z);
        glScalef(hp, 0.1, hp);
        glutSolidSphere(40.0, 2, 20);
    glPopMatrix();
}

/**
 *  Get z position of the flame.
 */
float Flame :: getZPos ()
{
    return position.z;
}
