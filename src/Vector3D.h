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
 *  @file Vector3D.h
 *
 *  @brief This file contain all the definitions of the class Vector3D.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef VECTOR
# define VECTOR

// TODO: This file must include common.h but common.h also includes this
// file.

# include <XnOpenNI.h>
# include <XnOS.h>
# include <XnCppWrapper.h>

using namespace xn;

# include "config.h"
# include "util.h"

/**
 *  @class Vector3D
 *
 *  @brief This class is a simple implementation for vector operation
 *  calculation.
 *
 */
class Vector3D {

    public:

        float x;
        float y;
        float z;

        /**
         *  Constructor.
         */
        Vector3D ();

        /**
         *  Constructor.
         */
        Vector3D (float X, float Y, float Z);

        /**
         *  Constructor.
         */
        Vector3D (XnPoint3D& point);

        /**
         *  Constructor.
         *
         *  Create a vector that represent the distance between
         *  the start point and the end point.
         *
         *  @param start is the origin of the vector.
         *  @param end is the end point of the vector.
         */
        Vector3D (XnPoint3D& start, XnPoint3D& end);

        /**
         *  Destructor of the class.
         */
        ~Vector3D () {};

        /**
         *  Overloaded operator plus.
         */
        Vector3D operator+ (Vector3D& v);

        /**
         *  Overloaded operator minus.
         */
        Vector3D operator- (Vector3D& v);

        /**
         *  Overloaded operator divition.
         */
        Vector3D operator/ (float f);

        /**
         *  Overloaded operator multiplication.
         */
        Vector3D operator* (float f);

        /**
         *  Get the magnitude from the vector.
         */
        float magnitude();

        /**
         *  Normalize the vector.
         */
        void normalize();

        /**
         *  Dot product.
         */
        float dot (Vector3D& v);

        /**
         *  Cross product between twe vectors.
         */
        Vector3D cross (Vector3D& v);


};

# endif
