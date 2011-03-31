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
 *  @file LinqSpawnIce.h
 *
 *  @brief This file contains the definition of the class LinqSpawnIce.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "LinqSpawnIce.h"

/**
 * Constructor
 */
LinqSpawnIce :: LinqSpawnIce ()
{
    initialPosition.X = 0.0f;
    initialPosition.Y = 0.0f;
    initialPosition.Z = 0.0f;

    position = initialPosition;

    direction = Vector3D(1.0, 1.0, 1.0);
    direction.normalize();
}

/**
 * Constructor
 */
LinqSpawnIce :: LinqSpawnIce (XnPoint3D pos, Vector3D dir, XnUserID p)
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
 *  True if the spawnIce is not too far.
 *
 *  @return True if the ice dosen't whent too far. False in
 *  other case.
 */
bool LinqSpawnIce :: isAlive ()
{
    Vector3D distance;

    distance.x = position.X - initialPosition.X;
    distance.y = position.Y - initialPosition.Y;
    distance.z = position.Z - initialPosition.Z;

    if (distance.magnitude() > L_SHOOT_MAX_DIST) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * Calculate next spawnIce position 
 */
void LinqSpawnIce :: nextPosition ()
{
    Vector3D speed = direction * L_SHOOT_SPEED;
    position.X += speed.x;
    position.Y += speed.y;
    position.Z += speed.z;

}

/** 
 * Opengl function to display 
 */
void LinqSpawnIce :: drawSpawnIce ()
{
    //Material information
    GLfloat materialColor[] = {0.2f, 0.2f, 1.0f, 1.0f};
    GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat materialEmission[] = {0.5f, 0.5f, 0.5f, 1.0f};
                            
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

    glPushMatrix();
        glTranslatef(position.X, position.Y - 150.0, position.Z);
        glutSolidSphere(50.0, 4, 2);
    glPopMatrix();
}
