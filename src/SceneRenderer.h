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
 *  @file SceneRenderer.h 
 *                                                                      
 *  @brief Header file form the class SceneRenderer.
 *
 *  In this file is contained all the information referenced to the class
 *  SceneRenderer. The signatures form functions and variables.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

# ifndef SCENE_RENDERER_H
# define SCENE_RENDERER_H

# include "config.h"
# include "common.h"

# include "../glm/include/glm.h"
# include "NeutralModel.h"
# include "ZamusModel.h"
# include "LinqModel.h"
# include "ZamusShoot.h"
# include "UserDetector.h"
# include "UserListener.h"
# include "Zamus.h"
# include "Linq.h"

/**
 *  @class SceneRenderer
 *
 *  @brief This class handle the graphic part of the program.
 *
 *  In this class we handle the graphic part of the program. It has
 *  basically one principal function. The function drawScene() is called
 *  from the main function and there is where all the openGL part is
 *  done. Also, here are defined functions to draw the 3D models that
 *  maybe will be move to other files y next versions.
 *
 */

class SceneRenderer
{
    public:

        /**
         *  Constructor of the Class. 
         *
         *  This constructor not need arguments.
         */
        SceneRenderer();

        /**
         *  Constructor of the class.
         *
         *  This constructor get the image and the user generator.
         *
         *  @param igen an image generator pointer.
         *  @param dgen a depth generator pointer.
         *  @param ugen a user detector pointer.
         *  @param zamus a zamus detector pointer.
         *  @param linq a linq detector pointer.
         *
         */
        SceneRenderer(ImageGenerator *igen, 
                      DepthGenerator *dgen, 
                      SceneAnalyzer *sa,
                      UserDetector *ugen,
                      Zamus *zamus,
                      Linq  *linq);

        /**
         * Destructor.
         */
        ~SceneRenderer() {};

        /**
         *  The principal function of the class.
         *  This function execute all the openGL part of the program.
         */
        void drawScene();

        /**
         *  This function activate or deactivate the RGB image drawing.
         *  Basically it switches a bool variable to indicate to the
         *  function drawScene if it must draw the RGB image in a plane.
         */
        void switchDrawImage();

        /**
         *  This function activate or deactivate the drawing of the user
         *  pixels image.
         *  Basically it switches a bool variable to indicate to the
         *  function drawScene if it must draw the user pixels when
         *  detected over the plane that might have the RGB image.
         */
        void switchDrawUser ();

    private:

        /**
         *  Draw the RGB image.
         *  If true, drawScene will draw the RGB image on a plane.
         */
        bool drawImagePixels;

        /**
         *  Draw User highlighted.
         *  If true, drawScene will draw the detected user pixels on a
         *  plane.
         */
        bool drawUserPixels;

        /**
         *  Pointer to the texture.
         *  This is the pointer to the final texture that will be apply
         *  to the plane. May contain the RGB image, users pixels image
         *  or both.
         */
        XnRGB24Pixel *texMap;

        /**
         *  Image generator pointer.
         *  This points to the image generator created in the context.
         */
        ImageGenerator *sr_ImageGenerator;

        /**
         *  Depth generator pointer.
         *  This points to the depth generator created in the context.
         *  This class needs this generator because of the convertion to
         *  real world coordinate with OpenNI to draw the objects.
         */
        DepthGenerator *sr_DepthGenerator;

        /**
         *  Scene Analyzer pointer.
         *  This object is needed to get que floor of the scene.
         */
        SceneAnalyzer *sr_SceneAnalyzer;

        /**
         *  User detector pointer.
         *  This user detector contain all the information abount the
         *  users.
         */
        UserDetector *sr_UserDetector;

        /**
         *  Neutral Model.
         *  This class is who draw the stick figure for the users that
         *  has not been transformed.
         *  Also this class handles the transformation stages for the
         *  diferent kinds of characters.
         */
        NeutralModel neutralModel;

        /**
         *  Zamus detector.
         *  This detector contain all the information about the users
         *  transformed in zamus. This class must contain one detector
         *  type for every model that the users can transform in. Maybe
         *  is a good idea to generalize this thing.
         */
        Zamus *sr_ZamusDetector;

        /**
         *  Linq detector.
         *  This detector contain all the information about the users
         *  transformed in linq. This class must contain one detector
         *  type for every model that the users can transform in. Maybe
         *  is a good idea to generalize this thing.
         */
        Linq *sr_LinqDetector;

        /**
         *  Zamus Model Parts.
         *  This structure loads all the parts of the 3D model of zamus.
         *  It loads the obj files with the GLM library. Again, it must
         *  be one of this classes by each model and it must be
         *  generalized.
         */
        ZamusModel zamusParts;

        /**
         *  Linq Model Parts.
         *  This structure loads all the parts of the 3D model of linq.
         *  It loads the obj files with the GLM library. Again, it must
         *  be one of this classes by each model and it must be
         *  generalized.
         */
        LinqModel linqParts;

        /**
         *  Gets the type of model that will be apply to the player. 
         *
         *  This function search for the player in the listeners and
         *  depending in where is he finded, it will be drawed in a
         *  diferent way.
         *
         *  @param player is the ID of the player to get his listener
         *  type.
         *  @return int that represents the type of the player
         *  (NEUTRAL_TYPE, ZAMUS_TYPE, LINQ_TYPE).
         */
        int getUserListenerType(XnUserID player);

        /**
         *  Determine the type of model to draw over the player
         *  This function switch between the diferent display options
         *  giben by the user listeners.
         *  @param player the ID of the player to draw on
         *  @param type is the model to draw over the player
         */
        void displayUserType (XnUserID player, unsigned int type);

        /**
         *  Draw the Zamus model over the player.
         *  This function display the zamus model for the player if he
         *  is been tracked.
         *  @param player the ID of the player.
         */
        void drawZamus (XnUserID player);

        /**
         *  Draw the Zamus shoots.
         *  This function draws all the zamus shoots maded by the player
         *  that are in the Zamus detector.
         */
        void drawZamusShoots();

        /**
         *  Draw the Linq model over the player.
         *  This function display the linq model for the player if he
         *  is been tracked.
         *  @param player the ID of the player.
         */
        void drawLinq (XnUserID player);

        /**
         *  Draw the Zamus shoots.
         *  This function draws all the zamus shoots maded by the player
         *  that are in the Zamus detector.
         */
        void drawIceSpawns();

        /**
         *  Modify the modeling matrix of OpenGL positioning the center
         *  in the point one and orienting the Y axis to the point two.
         *  @param point1 the point where the matrix will be center.
         *  @param point2 the point where the Y axis will go.
         */
        void orientAxis (XnPoint3D& point1, XnPoint3D& point2);

};

#endif
