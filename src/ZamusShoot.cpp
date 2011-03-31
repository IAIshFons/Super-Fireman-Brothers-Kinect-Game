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
 *  @file ZamusShoot.cpp
 *
 *  @brief This file contains the implementation of the methods
 *  described in ZamusShoot.h.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "ZamusShoot.h"

/**
 *  Constructor of the Class.
 */
ZamusShoot :: ZamusShoot ()
{
    initialPosition.X = 0.0f;
    initialPosition.Y = 0.0f;
    initialPosition.Z = 0.0f;

    position = initialPosition;

    direction = Vector3D(1.0, 1.0, 1.0);
    direction.normalize();
}

/**
 *  Constructor of the Class.
 */
ZamusShoot :: ZamusShoot (XnPoint3D pos, Vector3D dir, XnUserID p)
{
    initialPosition = pos;
    position        = pos;
    direction       = dir;
    player = p;

    if (dir.magnitude() != 1.0) {
        dir.normalize();
    }
}

/**
 *  True if the shoot is not too far.
 *
 *  @return true if the shoot is not too far or false if it
 *  passed the Z_SHOOT_MAX_DIST limit.
 *
 */
bool ZamusShoot :: isAlive ()
{
    Vector3D distance;

    distance.x = position.X - initialPosition.X;
    distance.y = position.Y - initialPosition.Y;
    distance.z = position.Z - initialPosition.Z;

    if (distance.magnitude() > Z_SHOOT_MAX_DIST) {
        return false;
    }
    else {
        return true;
    }
}

/**
 *  Set the next position of the shoot by the parameters set in
 *  the config.h file.
 */
void ZamusShoot :: nextPosition ()
{
    Vector3D speed = direction * Z_SHOOT_SPEED;
    position.X += speed.x;
    position.Y += speed.y;
    position.Z += speed.z;

}

/**
 *  Uses the OpenGL functions to draw the sphere representing
 *  the water shoot.
 */
void ZamusShoot :: drawShoot ()
{
    //Material information
    GLfloat materialColor[] = {0.2f, 0.2f, 1.0f, 1.0f};
    GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
                            
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

    glPushMatrix();
        glTranslatef(position.X, position.Y, position.Z);
        glutSolidSphere(30.0, 8, 8);
    glPopMatrix();
}
