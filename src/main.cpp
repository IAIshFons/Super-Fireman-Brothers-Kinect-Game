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
 *  @file main.cpp
 *
 *  @brief main program file.
 *
 *  This is the main program file.
 */

/** @mainpage Super Fireman Brothers
 *
 * @authors 
 * - Alfonso Ros (alfonso@gia.usb.ve)
 * - Ismael Mendonça (ismael@gia.usb.ve)
 *
 * @section intro Introduction
 *
 * This application consist of a simple game that we called "Super Fireman
 * Brothers". This applications uses the XBox Kinect sensor to track the
 * player's moves.
 *
 * The program is in C++ language. We have used the <A
 * HREF='http://www.openni.org/'>OpenNI</A> framework and the PrimeSense
 * <A HREF='http://www.primesense.com/?p=515'>NITE</A> middleware with the
 * <A HREF='https://github.com/avin2/SensorKinect'>avin2</A>. For
 * install instrucction see the next section.
 *
 * Also note the existence of the following directories:
 * - <B>models</B>
 *  - Contains the obj models of Zamus and Linq. This files are loaded
 *   by the GLM library.
 * - <B>config</B>
 *  - Contains the doxygen and the OpenNI context xml file.
 * - <B>src</B>
 *  - Source files.
 *
 *  <hr>
 *  @section installation How to install
 *  
 *  First of all, you must be sure to have this packages:
 *
 *  - GCC 4.x
 *  - Python 2.6+/3.x
 *  - LibUSB 1.0.8
 *  - OpenGL/GLUT
 *
 *  To install this packages in Ubuntu just run the following
 *  for the missing packages.
 *
 *  - sudo apt-get install g++ python libusb-1.0-0-dev freeglut3-dev
 *    libjpeg-dev libpng-dev libglu1-mesa-dev mesa-common-dev
 *
 *  Next you need to install the OpenNI. We
 *  used the unstable version. Here are the steps to install it. We use
 *  the git command so if you don't have it installed you cand run.
 *
 *  -# aptitude install git-core
 *
 *  Ok here are the steps to install OpenNI:
 *  
 *  -# mkdir ~/Kinect && cd ~/Kinect
 *  -# git clone https://github.com/OpenNI/OpenNI.git 
 *  -# cd OpenNI/Platform/Linux-x86/CreateRedist && ./RedistMaker
 *  -# cd ../Redist && sudo ./install.sh
 *
 *  That's all. Now we have OpenNI installed. Now we can install the
 *  avin2 diver.
 *
 *  -# cd ~/Kinect
 *  -# git clone https://github.com/avin2/SensorKinect.git
 *  -# cd SensorKinect/Platform/Linux-x86/CreateRedist && ./RedistMaker
 *  -# cd ../Redist && sudo ./install.sh
 *
 *  Now we need to install the NITE
 *  middleware. We used Nite 1.3.0.18 (Unstable).
 *
 *  -# go to this page and <A
 *  HREF='http://www.openni.org/downloadfiles/openni-compliant-middleware-binaries/33-latest-unstable'>download the latest NITE</A>.
 *  -# Save the NITE tarball to ~/Kinect.
 *  -# tar -jxvf NITE-Bin-Linux32-v1.3.0.18.tar.bz2
 *  -# cd ~/kinect/NITE/Nite-1.3.0.18/Data 
 *  -# Edit all xml files and replace the license with this one
 *  "0KOIk2JeIBYClPWVnMoRKn5cdY4="
 *  -# Also replace the MapOutputMode line to look like this "<
 *  MapOutputMode xRes="640" yRes="480" FPS="30"/>"
 *  -# niLicense PrimeSense 0KOIk2JeIBYClPWVnMoRKn5cdY4=
 *  -# cd ~/kinect/NITE/Nite-1.3.0.18/
 *  -# sudo ./install.sh
 *  -# make && sudo make install
 *  
 *  All ready. Now we have the OpenNI, avin2 and NITE software
 *  installed. We only need to install GLM library to start playing. 
 *
 *  -# mkdir ~/glm
 *  -# Download the GLM library from this <A
 *  HREF="http://devernay.free.fr/hacks/glm/">page</A> and save it to
 *  ~/glm.
 *  -# cd ~/glm && tar -zxvf glm-0.3.1.tar.gz
 *  -# cd glm-0.3.1/
 *  -# ./configure && make && sudo makeinstall
 *
 *  Finally Super Fireman Brothers game.
 *
 *  -# Download it from this page to your ~/.
 *  -# cd ~/ && tar xzvf SuperFiremanBrothers-0.1.tar.gz
 *  -# cd SuperFiremanBrothers
 *  -# make
 *  -# make documentation (optional)
 * 
 *  Run the game with:
 *
 *  - ./Bin/Release/SuperFiremanBrothers
 *
 *  <hr>
 *
 *  @section playmode How to play
 *
 *  The game is very simple to play. First you need to specify how many
 *  players will be on the game. This is done through the console. We
 *  have set a maximun of 3 players, because if there are too many
 *  players, the tracking gets difficult.
 *
 *  Once the number of players is set, it promps a window where the game
 *  will be displayed. Make sure that the Kinect is looking some open area, 
 *  otherwise you may experiment some troubles with the floor tracking.
 *
 *  Step in front of the Kinect between 1.5 and 3 mts. You'll see a
 *  litle colored diamond appear in the window, this diamond represent
 *  your position.
 *
 *  \image html calPose.jpg "Calibration pose" width=0.2cm
 *
 *  Now you must make the calibration pose in order to get your skeleton
 *  tracked by the Kinect. Try to stay near the middle of the screen for
 *  faster/easier calibration. You must maintain this pose for a period of
 *  time until a stick figure appears in exchange of your diamond. This
 *  stick figure represents that the tracking of your body is been done.
 *
 *  Now is time to select one of two available characters of the game.
 *  One is an intergalactic fireman called Zamus and the other one is a
 *  mystic ice magician called Linq that can invoke the mighty power of 
 *  freezed water from other dimentions. 
 *
 *  To transform in Zamus, you must do the Zamus transformation pose
 *  once you are tracked as a stick figure.
 *
 *  \image html zamus.jpg "Zamus transformation pose" width=0.2cm
 *  \image html zamus2.jpg "Zamus transformation pose" width=0.2cm
 *
 *  When you are transformed in Zamus, you can activate your water
 *  cannon with the activation pose and deactivate it with the
 *  deactivation pose as show below.
 *
 *  \image html ZamusActivate.jpg "Zamus activate pose" width=0.2cm
 *  \image html ZamusDeactivate.jpg "Zamus deactivate pose" width=0.2cm
 *  
 *  Then you can fire if you maintain your arm straight.
 *
 *  \image html ZamusShoot.jpg "Zamus shoot pose" width=0.2cm
 *
 *  To transform in Linq you must make 3 poses sequentially.
 *
 *  \image html Linq1.jpg "Linq first pose" width=0.2cm
 *  \image html Linq2.jpg "Linq second pose" width=0.2cm
 *  \image html Linq3.jpg "Linq third pose" width=0.2cm
 * 
 *  To invoke the mighty power of ice you must bend your arm like the
 *  first figure, then you must put your arm straight like the second
 *  figure. Repeat this to invoke more ice.
 *
 *  \image html LinqShoot1.jpg "Arm bended to charge mana" width=0.2cm
 *  \image html ZamusShoot.jpg "Arm straight to invoke ice" width=0.2cm
 *  
 *  Now you are ready to play. When all the player are calibrated and
 *  transformed, the game will begin. The fireballs will start to spawn 
 *  and advance to your position. You must extinguish them or you are going 
 *  to lose. Every level you pass will turn harder and harder. For every 
 *  flame you extinguish you get more score. The objetive of the game is to
 *  get the higher score.
 *
 *  <hr>
 *  @section notes release.notes
 *  release.notes
 *  Super Fireman Brothers v0.1, in order to run the application:
 *  - Run make
 *  - Run make documentation (if you want the documentation)
 *  - Run the command ./SuperFiremanBrothers.
 *
 *  <hr>
 *  @section requirements requirements
 *
 *  We implement all the application in <A HREF='http://www.ubuntu.com/'>Ubuntu 10.10</A>.
 *
 *  To run the application first you will have to some dependencies are needed,
 *  download the following libraries, you could use "aptitude install" in Linux:
 *
 *  - GCC 4.x -- sudo apt-get install g++ 
 *  - Python 2.6+/3.x -- sudo apt-get install python
 *  - LibUSB 1.0.8 -- sudo apt-get install libusb-1.0-0-dev
 *  - OpenGL/GLUT -- sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
 *  - Glm -- http://devernay.free.fr/hacks/glm/
 * 
 *  Optional Requirements (To build the documentation):
 *  
 *  - Doxygen -- sudo apt-get install doxygen
 *  - GraphViz -- sudo apt-get install graphviz
 * 
 *  Now you will have to install the OpenNI, SensorKinect and Nite drivers to get
 *  the application work:
 *  
 *  - Unstable version of OpenNI-4c9ff97: https://github.com/OpenNI/OpenNI/tree/unstable or download
 *    directly from http://www.openni.org/downloadfiles/openni-binaries/20-latest-unstable.
 *
 *  - Sensor Kinect avin2 driver (Unstable): https://github.com/avin2/SensorKinect.
 *
 *  - Nite 1.3.0.18 (Unstable): http://www.openni.org/downloadfiles/openni-compliant-middleware-binaries/33-latest-unstable
 *    and you will have to introduce the next license key: 0KOIk2JeIBYClPWVnMoRKn5cdY4= 
 *
 *  This application was tested given successfull results in the following hardware:
 *
 *  - Hp pavilion dv2927la Notebook, Intel Core 2 Duo, RAM 3GB, Intel Corporation Mobile GM965/GL960 Integrated Graphics Controller.
 *  - Hp pavilion dv6000 Notebook, Intel Core 2 Duo, RAM 3GB, Intel Corporation Mobile GM965/GL960 Integrated Graphics Controller.
 *
 *  <hr> 
 *  @todo There is some problems with the floor drawing related to the Kinect position,
 *  the floor drawing is done by detecting the floor area with the OpenNI functions and
 *  draw the pixels of the detected floor. If you place the Kinect in an area that you 
 *  cannot see the floor it will be drawn in a wrong way so the application will not run
 *  effectively, the problems are experienced if the area you place the Kinect is really
 *  small or some objects obstruct the floor. Another way to draw the floor could be 
 *  a good solution.
 *  @todo There is a system of listeners wich consists in classes that describe the different
 *  type of characters you can use, the abstract listener type could be improved in a way that
 *  the new user callback could be used directly to listen for Zamus or Linq types.
 *  @todo Implement a way to win the game of Super Fireman Brothers, actually the game
 *  is intended for competing between players, the one with highest score is the winner.
 */

// [Common Header Files]
# include "common.h"

// [Configuration macros]
# include "config.h"

// [Utility functions]
# include "util.h"

# include "SceneRenderer.h"
# include "UserDetector.h"
# include "BusterDetector.h"
# include "IceRodDetector.h"
# include "Zamus.h"
# include "Linq.h"
# include "SuperFiremanBrothers.h"

/**
 *  OpenNI objects forward declarations.
 */
Context             g_Context;
EnumerationErrors   g_Error;
DepthGenerator      g_DepthGenerator;
UserGenerator       g_UserGenerator;
ImageGenerator      g_ImageGenerator;
SceneAnalyzer       g_SceneAnalyzer;
SceneMetaData       g_SceneMD;

/**
 *  Forward declaration of our clases.
 */
UserDetector        g_UserDetector;
SceneRenderer       g_SceneRenderer;
Zamus               *g_ZamusDetector;
Linq                *g_LinqDetector;
BusterDetector      *g_BusterDetector;
IceRodDetector      *g_IceRodDetector;
SuperFiremanBrothers g_SFBgame;

int g_MaxPlayers;
int g_gameOver;

/**
 *  Lights
 */
GLfloat light_diffuse[]  = {0.8, 0.8, 0.8, 1.0};
GLfloat light_ambient[]  = {0.2, 0.2, 0.2, 1.0};
GLfloat light_specular[] = { 0.7, 0.7, 0.3, 1.0 };
GLfloat light_position[] = {-10.0,-10.0, 20.0, 0.0};

/**
 *  Materials
 */
GLfloat mat_diffuse[]  = { 0.9, 0.9, 0.9, 0.9 };
GLfloat mat_specular[] = { 0.3, 0.3, 0.3, 0.3 };
GLfloat mat_shininess[] = { 10.0 };

/**
 * Initialize XN functions
 */
void initialize() 
{
    ImageMetaData imageMD;
    XnStatus status;
    int dummy;
    
    srand ( time(NULL) );

    // Initializing context and checking for enumeration errors
    status = g_Context.InitFromXmlFile(XML_CONFIG_FILE, &g_Error);
    checkEnumError(status, g_Error);

    // Finding nodes and checking for errors
    STATUS_CHECK(g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator), "Finding depth node");
    STATUS_CHECK(g_Context.FindExistingNode(XN_NODE_TYPE_SCENE, g_SceneAnalyzer), "Finding scene analizer");


    //  Note: when the image generation node is handled the program gets
    //  too slow.

    // STATUS_CHECK(g_Context.FindExistingNode(XN_NODE_TYPE_IMAGE, g_ImageGenerator), "Finding image node");

    // Set view point of Depth generator to the image generator point of
    // view.
    // STATUS_CHECK(g_DepthGenerator.GetAlternativeViewPointCap().SetViewPoint(g_ImageGenerator), "Set View Point");

    STATUS_CHECK(g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator), "Finding user node");
    
    //g_ImageGenerator.GetMetaData(imageMD);
    
    // Checking camera pixel format
    //if (imageMD.PixelFormat() != XN_PIXEL_FORMAT_RGB24) {
    //    reportError("Camera format not supported...!\n");
    //}

    // Checking user generator capabilities
    if(!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON)) {
        reportError("Skeleton capability not supported\n");
    }
    
    if(!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION)) {
        reportError("Pose detection capability not supported\n");
    }

    printf("Number of players: ");
    dummy = scanf("%d", &g_MaxPlayers);
    printf("\n");

    //Initialize user detector object
    g_UserDetector = UserDetector(g_UserGenerator, g_DepthGenerator);
    g_UserDetector.registerCallbacks();
    
    g_ZamusDetector = new Zamus(&g_UserDetector);
    g_LinqDetector = new Linq(&g_UserDetector);
    g_BusterDetector = new BusterDetector(g_ZamusDetector, &g_UserDetector);
    g_IceRodDetector = new IceRodDetector(g_LinqDetector, &g_UserDetector);

    // Initialize image render object
    g_SceneRenderer = SceneRenderer(&g_ImageGenerator,
                                    &g_DepthGenerator,
                                    &g_SceneAnalyzer,
                                    &g_UserDetector,
                                    g_ZamusDetector,
                                    g_LinqDetector);

    STATUS_CHECK(g_Context.StartGeneratingAll(), "Context generation");

    g_SFBgame = SuperFiremanBrothers(&g_UserDetector, 
                                     &g_SceneAnalyzer, 
                                     g_ZamusDetector, 
                                     g_LinqDetector, 
                                     g_MaxPlayers
                                    );

}

/**
 * Shut down the context generation
 */
void cleanupExit() 
{
    g_Context.Shutdown();
    exit(EXIT_SUCCESS);
}

/**
 * OpenGL Functions
 */

/**
 *  OpenGL update function.
 *
 *  This function calls the display function every 25 milliseconds.
 *  
 */
void update (int value)
{
    // Display the frame
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

/**
 *  OpenGL display function.
 *
 *  This function is called every 25 milliseconds by the update
 *  function.
 */
void glutDisplay (void)
{
    /**
     *  Update every node of OpenNI.
     */
    g_Context.WaitOneUpdateAll(g_DepthGenerator);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 1.05, 1.0, 10000.0);
    gluLookAt(320.0, -300.0, 4200.0,
              320.0, 240.0, 1500.0,
              0.0,-1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glPushMatrix();

    // Checking fot game starting and finishing
    g_SFBgame.checkUsers();

    if (g_SFBgame.isGameOn()) {
        
        g_UserDetector.changeStopDetection(true);
        g_SFBgame.checkGameOver();

        if (!g_SFBgame.isGameOver()) {
            g_BusterDetector -> detectPose();
            g_IceRodDetector -> detectPose();
        } 
        else {
            STATUS_CHECK(g_Context.StopGeneratingAll(), 
                "Context generation shutdown");
        }
    }
    else {
        // Detects poses
        g_ZamusDetector -> detectPose();
        g_LinqDetector -> detectPose();
    }
    
   
    /**
     *  Use the draw functions of every class to display the game with
     *  OpenGL.
     */
    g_SceneRenderer.drawScene();
    g_SFBgame.drawFireBalls();
    g_SFBgame.drawGameInfo();
    g_SFBgame.nextFrame();

    glPopMatrix();
    glutSwapBuffers();
}

/**
 *  OpenGL Keyboard function.
 *
 *  Exit the program when escape key is pressed.
 */
static void onGlutKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
             exit(1);
    }
}

/**
 *  Init the OpenGL functions.
 */
static void initGL (int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow ("Super Fireman Brothers");

    glutDisplayFunc(glutDisplay);
    glutKeyboardFunc(onGlutKeyboard);
    
    glShadeModel(GL_SMOOTH);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    glutTimerFunc(25, update, 0);
    glutMainLoop();
}

/**
 * Main Program
 */
int main(int argc, char* argv[]) 
{   
    initialize();
    initGL (argc, argv);
    cleanupExit();

    return 0;
}
