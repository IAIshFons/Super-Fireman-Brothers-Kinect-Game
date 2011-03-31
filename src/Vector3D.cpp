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
 *  @file Vector3D.cpp
 *
 *  @brief This file contains the implementation of the class Vector3D.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# include "Vector3D.h"

/**
 *  Constructor.
 */
Vector3D :: Vector3D ()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

/**
 *  Constructor.
 */
Vector3D :: Vector3D (float X, float Y, float Z)
{
    x = X;
    y = Y;
    z = Z;
}

/**
 *  Constructor.
 */
Vector3D :: Vector3D (XnPoint3D& point)
{
    x = point.X;
    y = point.Y;
    z = point.Z;
}

/**
 *  Constructor.
 *
 *  Create a vector that represent the distance between
 *  the start point and the end point.
 *
 *  @param start is the origin of the vector.
 *  @param end is the end point of the vector.
 */
Vector3D :: Vector3D (XnPoint3D& start, XnPoint3D& end)
{
    x = end.X - start.X;
    y = end.Y - start.Y;
    z = end.Z - start.Z;
}

/**
 *  Overloaded operator plus.
 */
Vector3D Vector3D :: operator+ (Vector3D& v)
{
    return Vector3D (x + v.x,
                     y + v.y,
                     z + v.z);
}

/**
 *  Overloaded operator minus.
 */
Vector3D Vector3D :: operator- (Vector3D& v)
{
    return Vector3D (x - v.x,
                     y - v.y,
                     z - v.z);
}

/**
 *  Overloaded operator divition.
 */
Vector3D Vector3D :: operator/ (float f)
{
    return Vector3D ( x / f,
                      y / f,
                      z / f);
}

/**
 *  Overloaded operator multiplication.
 */
Vector3D Vector3D :: operator* (float f)
{
    return Vector3D ( x * f,
                      y * f,
                      z * f);
}

/**
 *  Get the magnitude from the vector.
 */
float Vector3D :: magnitude ()
{
    return sqrt(x * x + y * y + z * z);
}

/**
 *  Normalize the vector.
 */
void Vector3D :: normalize ()
{
    float m;

    m = magnitude();
    x = x / m;
    y = y / m;
    z = z / m;
}

/**
 *  Dot product.
 */
float Vector3D :: dot (Vector3D& v)
{
    return x * v.x + y * v.y + z * v.z;
}

/**
 *  Cross product between twe vectors.
 */
Vector3D Vector3D :: cross (Vector3D& v)
{
    return Vector3D (y * v.z - z * v.y,
                     z * v.x - x * v.z,
                     x * v.y - y * v.x);
}
