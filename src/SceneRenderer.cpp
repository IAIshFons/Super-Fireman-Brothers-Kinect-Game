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
 *  @file SceneRenderer.cpp
 *
 *  @brief This file contain the definitions of the functions of the
 *  class SceneRenderer.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 *
 */

#include "SceneRenderer.h"

/**
 *  Constructor of the Class. 
 *
 *  This constructor not need arguments.
 */
SceneRenderer :: SceneRenderer ()
{
    sr_ImageGenerator = NULL;
    sr_DepthGenerator = NULL;
    sr_SceneAnalyzer  = NULL;
    sr_UserDetector   = NULL;
    sr_ZamusDetector  = NULL;
    sr_LinqDetector   = NULL;

    drawImagePixels = false;
    drawUserPixels  = false;
    zamusParts = ZamusModel();
    linqParts  = LinqModel();
    neutralModel = NeutralModel();
}

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
SceneRenderer :: SceneRenderer (ImageGenerator *igen,
                                DepthGenerator *dgen,
                                SceneAnalyzer  *sa,
                                UserDetector *ugen,
                                Zamus *zamus,
                                Linq  *linq)
{
    sr_ImageGenerator = igen;
    sr_DepthGenerator = dgen;
    sr_SceneAnalyzer  = sa;
    sr_UserDetector   = ugen;
    sr_ZamusDetector  = zamus;
    sr_LinqDetector   = linq;

    drawImagePixels = false;
    drawUserPixels  = false;
    zamusParts = ZamusModel();
    linqParts  = LinqModel();
    neutralModel = NeutralModel(ugen, zamusParts, linqParts);
}

/**
 *  This function activate or deactivate the RGB image drawing.
 *  Basically it switches a bool variable to indicate to the
 *  function drawScene if it must draw the RGB image in a plane.
 */
void SceneRenderer :: switchDrawImage ()
{
    drawImagePixels = !drawImagePixels;
}

/**
 *  This function activate or deactivate the drawing of the user
 *  pixels image.
 *  Basically it switches a bool variable to indicate to the
 *  function drawScene if it must draw the user pixels when
 *  detected over the plane that might have the RGB image.
 */
void SceneRenderer :: switchDrawUser ()
{
    drawUserPixels = !drawUserPixels;
}

/**
 *  Gets the type of model that will be apply to the player. 
 *
 *  This function search for the player in the listeners and
 *  depending in where is he finded, it will be drawed in a
 *  diferent way.
 *
 *  @param player is the ID of the player to get his listener
 *  type.
 *  @return int that represents the type of the player (NEUTRAL_TYPE,
 *  ZAMUS_TYPE, LINQ_TYPE).
 */
int SceneRenderer :: getUserListenerType (XnUserID player)
{
    unsigned int i;

    // Pointer to the vector of users to be displayed
    vector<UserListener *> usersListener;

    // Get the vector of users
    usersListener = sr_UserDetector -> retUserListenerVector();

    for (i = 0; i < usersListener.size(); i++) {
        if (usersListener[i] -> isListened(player)) {
            return usersListener[i] -> listenerType;
        }
    }

    return NEUTRAL_TYPE;
}

/**
 *  The principal function of the class.
 *  This function execute all the openGL part of the program.
 */
void SceneRenderer :: drawScene ()
{
    // This variables are used to iterate.
    unsigned int i;
    unsigned int type;

    XnUInt x;
    XnUInt y;
    
    // This fist two variables contain the image resolution.
    unsigned int xRes;
    unsigned int yRes;

    // This two variables contain the texture resolution.
    unsigned int texResX;
    unsigned int texResY;

    // This are the image and scene meta data.
    ImageMetaData imd;
    SceneMetaData smd;

    // This pointer will point the resulting OpenGL texture.
    XnRGB24Pixel* texMap;

    // This two are used to iterate for the texture.
    XnRGB24Pixel* texRow;
    XnRGB24Pixel* texPixel;

    // This are used to iterate through the image pixels.
    const XnRGB24Pixel* imagePixel;
    const XnRGB24Pixel* imageRow;

    // This are used to iterate through the user labels.
    const XnLabel* labelRow;
    const XnLabel* label;

    // This is for the floor.
    XnPlane3D floor;
    float yPos;
    GLfloat materialColor[] = {0.5f, 0.25f, 0.05f, 1.0f};
    GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};


    XnUserID usersIDs[MAX_USERS];
    XnUInt16 numUsers = MAX_USERS;

    UserGenerator userGen;

    userGen = sr_UserDetector -> retUserGenerator();

    if (drawUserPixels) {

        // Start getting the image and scene metadata.
        sr_UserDetector -> retUserGenerator().GetUserPixels(0, smd);

        if (drawImagePixels) {
            sr_ImageGenerator -> GetMetaData(imd);
            imageRow = imd.RGB24Data();
        }

        // Get the image resolution.
        xRes = smd.XRes();
        yRes = smd.YRes();

        // Init the texture map
        // OpenGL need the texture map to be a power of two.
        texResX = (((unsigned short)(smd.FullXRes() - 1) / 512) + 1) * 512;
        texResY = (((unsigned short)(smd.FullYRes() - 1) / 512) + 1) * 512;
        texMap  = (XnRGB24Pixel*) malloc (texResX * 
                                          texResY * 
                                          sizeof(XnRGB24Pixel));
        xnOSMemSet(texMap, 0, texResX * texResY * sizeof(XnRGB24Pixel));

        // Get the data from labels and the image.
        labelRow = smd.Data();

        // Init the pointer to the texture map to start feeling it.
        texRow   = texMap;

        // Starts itarating through the rows of the image.
        for (y = 0; y < yRes; y++) {
            
            if (drawImagePixels) {
                imagePixel = imageRow;
                imageRow += xRes;
            }
            texPixel   = texRow;
            label      = labelRow;

            for (x = 0; x < xRes; x++) {

                if (drawImagePixels) {
                    *texPixel = *imagePixel;
                    imagePixel++;
                }

                if (*label != 0) {
                    if (*label <= MAX_USERS) {
                          texPixel -> nBlue = 200;
                    }
                }

                // go to next pixel
                texPixel++;
                label++;

            }
            
            // go to next row
            labelRow += xRes;
            texRow   += texResX;
        }


        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexParameteri( GL_TEXTURE_2D, 
                         GL_TEXTURE_MIN_FILTER, 
                         GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri( GL_TEXTURE_2D, 
                         GL_TEXTURE_MAG_FILTER, 
                         GL_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 
                      0, 
                      GL_RGB, 
                      texResX, 
                      texResY, 
                      0, 
                      GL_RGB, 
                      GL_UNSIGNED_BYTE, 
                      texMap);

        glColor4f(1,1,1,1);

        // Draw the plane an set the coordinates for the texture.
        glBegin(GL_QUADS);

        glNormal3f(0.0, 0.0,-1.0);

        // upper left
        glTexCoord2f(CROPLEFT, CROPUP);
        glVertex2f(0, 0);
       
        // upper right
        glTexCoord2f((float)xRes/(float)texResX + CROPRIGHT, CROPUP);
        glVertex2f(640, 0);

        // bottom right
        glTexCoord2f((float)xRes/(float)texResX + CROPRIGHT,
                     (float)yRes/(float)texResY + CROPDOWN);
        glVertex2f(640, 480);

        // bottom left
        glTexCoord2f(CROPLEFT, (float)yRes/(float)texResY + CROPDOWN);
        glVertex2f(0, 480);

        glEnd();

    }

    sr_SceneAnalyzer -> GetFloor(floor);

    sr_DepthGenerator -> ConvertRealWorldToProjective(1, 
                                                      &floor.ptPoint, 
                                                      &floor.ptPoint); 
    yPos = floor.ptPoint.Y + 100;

    // Draw floor.
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glBegin(GL_QUADS);
    glNormal3f( 0.0,-1.0, 0.0);
        glVertex3f( 4000, yPos,-4000);
        glVertex3f(-4000, yPos,-4000);
        glVertex3f(-4000, yPos, 4000);
        glVertex3f( 4000, yPos, 4000);
    glEnd();

    userGen.GetUsers(usersIDs, numUsers);

    for (i = 0; i < numUsers; i++) {
        
        // Search user ID in the listeners array
        type = getUserListenerType(usersIDs[i]);

        if (!((sr_UserDetector -> retDetectionStat() == true) 
               && (type == NEUTRAL_TYPE))) {
            
            // Display player with type
            displayUserType(usersIDs[i], type);
        }
    }
    drawZamusShoots();
    drawIceSpawns();
}


/**
 *  Determine the type of model to draw over the player
 *  This function switch between the diferent display options
 *  giben by the user listeners.
 *  @param player the ID of the player to draw on
 *  @param type is the model to draw over the player
 */
void SceneRenderer :: displayUserType (XnUserID player, unsigned int type)
{
    int stage;

    // NOTE: Add more cases if you create more models
    switch (type) {

        case NEUTRAL_TYPE:
            stage = sr_UserDetector -> retStage(player);
            neutralModel.drawNeutral(player);
            break;

        case ZAMUS_TYPE:
            drawZamus(player);
            break;

        case LINQ_TYPE:
            drawLinq (player);
            break;

        default:
            neutralModel.drawNeutral(player);
            break;
    }
}


/**
 *  Draw the Zamus model over the player.
 *  This function display the zamus model for the player if he
 *  is been tracked.
 *  @param player the ID of the player.
 */
void SceneRenderer :: drawZamus (XnUserID player)
{
    float ax;
    Vector3D a;
    Vector3D b;
    Vector3D c;
    Vector3D d;
    Vector3D u;
    Vector3D v;
    Vector3D w;

    GLuint mode;
    UserGenerator      userGen;

    XnPoint3D points[15];

    // Skeleton Joints
    XnSkeletonJointPosition headJoint;
    XnSkeletonJointPosition neckJoint;
    XnSkeletonJointPosition leftShoulderJoint;
    XnSkeletonJointPosition rightShoulderJoint;
    XnSkeletonJointPosition leftHipJoint;
    XnSkeletonJointPosition rightHipJoint;
    XnSkeletonJointPosition torsoJoint;
    XnSkeletonJointPosition leftArmJoint;
    XnSkeletonJointPosition rightArmJoint;
    XnSkeletonJointPosition leftHandJoint;
    XnSkeletonJointPosition rightHandJoint;
    XnSkeletonJointPosition leftKneeJoint;
    XnSkeletonJointPosition rightKneeJoint;
    XnSkeletonJointPosition leftFootJoint;
    XnSkeletonJointPosition rightFootJoint;

    userGen = sr_UserDetector -> retUserGenerator();
    SkeletonCapability skelCap = userGen.GetSkeletonCap();

    mode =  GLM_SMOOTH | GLM_MATERIAL;

    if (skelCap.IsTracking(player)) {

    // GET SKELETON JOINT POSITIONS
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_HEAD,
                                     headJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_NECK,
                                     neckJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_LEFT_SHOULDER,
                                     leftShoulderJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_RIGHT_SHOULDER,
                                     rightShoulderJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_TORSO,
                                     torsoJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_LEFT_ELBOW,
                                     leftArmJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_RIGHT_ELBOW,
                                     rightArmJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_LEFT_HAND,
                                     leftHandJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_RIGHT_HAND,
                                     rightHandJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_LEFT_HIP,
                                     leftHipJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_RIGHT_HIP,
                                     rightHipJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_LEFT_KNEE,
                                     leftKneeJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_RIGHT_KNEE,
                                     rightKneeJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_LEFT_FOOT,
                                     leftFootJoint);
    skelCap.GetSkeletonJointPosition(player, 
                                     XN_SKEL_RIGHT_FOOT,
                                     rightFootJoint);

    points[0]  = headJoint.position;
    points[1]  = neckJoint.position;
    points[2]  = leftShoulderJoint.position;
    points[3]  = rightShoulderJoint.position;
    points[4]  = leftHipJoint.position;
    points[5]  = rightHipJoint.position;
    points[6]  = torsoJoint.position;
    points[7]  = leftArmJoint.position;
    points[8]  = rightArmJoint.position;
    points[9]  = leftHandJoint.position;
    points[10]  = rightHandJoint.position;
    points[11]  = leftKneeJoint.position;
    points[12] = rightKneeJoint.position;
    points[13] = leftFootJoint.position;
    points[14] = rightFootJoint.position;

    sr_DepthGenerator -> ConvertRealWorldToProjective(15, 
                                                      points, 
                                                      points); 

        a = Vector3D(points[5].X,points[5].Y,points[5].Z);
        b = Vector3D(points[2].X,points[2].Y,points[2].Z);
        c = Vector3D(points[4].X,points[4].Y,points[4].Z);
        d = Vector3D(points[3].X,points[3].Y,points[3].Z);

        u = a - b;
        v = c - d;

        w   = u.cross(v);
        w.y = 0.0;
        w.normalize();

        ax = 57.2957795 * acos(w.z);

        if (w.x <= 0.0) {
            ax = -ax;
        }


    // DRAW ZAMUS HEAD

    if ((headJoint.fConfidence >= 0.5) && (neckJoint.fConfidence >= 0.5)) {

        glPushMatrix();

            orientAxis(points[0],points[1]);
            glScalef(400.0, 400.0, 400.0);
            glTranslatef(0.0, -0.1, 0.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.head, mode); 

        glPopMatrix();
    }

    // DRAW ZAMUS CHEST

    if ((torsoJoint.fConfidence >= 0.5) && (neckJoint.fConfidence >= 0.5)) {

        glPushMatrix();

            orientAxis(points[1],points[6]);
            glScalef(400.0, 400.0, 400.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(ax, 0.0,-1.0, 0.0);
            glTranslatef(0.0, -0.1, 0.0);
            glmDraw(zamusParts.chest, mode); 

        glPopMatrix();
    }

    // DRAW ZAMUS SHOULDERS
    
    if ((leftShoulderJoint.fConfidence >= 0.5) && 
        (rightShoulderJoint.fConfidence >= 0.5)) {

        glPushMatrix();
            glTranslatef(points[2].X, points[2].Y, points[2].Z);
            glRotatef(-ax, 0.0,-2.0, 0.0);
            glTranslatef(-30.0,-40.0, 0.0);
            glScalef(500.0,-500.0, 500.0);
            glmDraw(zamusParts.shoulder, mode); 

        glPopMatrix();
        glPushMatrix();
            glTranslatef(points[3].X, points[3].Y, points[3].Z);
            glRotatef(-ax, 0.0,-1.0, 0.0);
            glTranslatef( 30.0,-40.0, 0.0);
            glScalef(500.0,-500.0, 500.0);
            glmDraw(zamusParts.shoulder, mode); 

        glPopMatrix();

    }

    // DRAW ZAMUS LEFT ARM
    
    if ((rightArmJoint.fConfidence >= 0.5) && 
        (rightHandJoint.fConfidence >= 0.5) &&
        (rightShoulderJoint.fConfidence >= 0.5)) {

        glPushMatrix();
            orientAxis(points[3],points[8]);
            glTranslatef( 0.0, 0.0, 50.0);
            glScalef(500.0, 500.0, 500.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.arm, mode); 

        glPopMatrix();
        
        glPushMatrix();
            orientAxis(points[8],points[10]);
            glTranslatef( 0.0, 0.0, 60.0);
            glScalef(250.0, 250.0, 250.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(-ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.forearm, mode); 

        glPopMatrix();
        

    }

    // DRAW ZAMUS RIGHT ARM
    
    if ((leftArmJoint.fConfidence >= 0.5) && 
        (leftHandJoint.fConfidence >= 0.5) &&
        (leftShoulderJoint.fConfidence >= 0.5)) {

        glPushMatrix();
            orientAxis(points[2],points[7]);
            glTranslatef( 0.0, 0.0, 50.0);
            glScalef(500.0, 500.0, 500.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.arm, mode); 

        glPopMatrix();
        
        glPushMatrix();
            orientAxis(points[7],points[9]);
            glTranslatef( 0.0, 0.0, 80.0);
            glScalef(300.0, 300.0, 300.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(-ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.cannon, mode); 

        glPopMatrix();
        

    }

    // DRAW ZAMUS LEFT LEG
    
    if ((rightHipJoint.fConfidence >= 0.5) && 
        (rightKneeJoint.fConfidence >= 0.5) &&
        (rightFootJoint.fConfidence >= 0.5)) {

        glPushMatrix();
            orientAxis(points[5],points[12]);
            glTranslatef( 0.0, 0.0, 50.0);
            glScalef(250.0, 250.0, 250.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.thigh, mode); 

        glPopMatrix();
        
        glPushMatrix();
            orientAxis(points[12],points[14]);
            glTranslatef( 0.0, 0.0, 50.0);
            glScalef(100.0, 100.0, 100.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.leg, mode); 

        glPopMatrix();
        

    }

    // DRAW ZAMUS RIGHT LEG
    
    if ((leftHipJoint.fConfidence >= 0.5) && 
        (leftKneeJoint.fConfidence >= 0.5) &&
        (leftFootJoint.fConfidence >= 0.5)) {

        glPushMatrix();
            orientAxis(points[4],points[11]);
            glTranslatef( 0.0, 0.0, 50.0);
            glScalef(-250.0, 250.0, 250.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(-ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.thigh, mode); 

        glPopMatrix();
        
        glPushMatrix();
            orientAxis(points[11],points[13]);
            glTranslatef( 0.0, 0.0, 50.0);
            glScalef(-100.0, 100.0, 100.0);
            glRotatef(90, -1.0, 0.0, 0.0);
            glRotatef(-ax, 0.0,-1.0, 0.0);
            glmDraw(zamusParts.leg, mode); 

        glPopMatrix();
        

    }

    // DRAW ZAMUS RIGHT FOOT
    
    if ((leftFootJoint.fConfidence >= 0.5) && 
        (rightFootJoint.fConfidence >= 0.5)) {

        glPushMatrix();
            glTranslatef( points[13].X, points[13].Y, points[13].Z);
            glScalef(40.0,-40.0,-40.0);
            glRotatef(ax, 0.0,-1.0, 0.0);
            glTranslatef(0.0,-0.25, 0.5);
            glmDraw(zamusParts.foot, mode); 

        glPopMatrix();
        
        glPushMatrix();
            glTranslatef( points[14].X, points[14].Y, points[14].Z);
            glScalef(-40.0,-40.0,-40.0);
            glRotatef(-ax, 0.0,-1.0, 0.0);
            glTranslatef(0.0,-0.25, 0.5);
            glmDraw(zamusParts.foot, mode); 

        glPopMatrix();
        

    }

    }
    
}

/**
 *  Draw the Zamus shoots.
 *  This function draws all the zamus shoots maded by the player
 *  that are in the Zamus detector.
 */
void SceneRenderer :: drawZamusShoots ()
{
    int i;
    int nShoots;
    vector <ZamusShoot > shoots;

    shoots = sr_ZamusDetector -> shoots;

    for (i = 0; i < shoots.size(); i++) {
        shoots[i].nextPosition();
        if (shoots[i].isAlive()) {
            shoots[i].drawShoot();
        }
        else {
            shoots.erase(shoots.begin() + i);
            i--;
        }
    }

    sr_ZamusDetector -> shoots = shoots;
}

/**
 *  Draw the Zamus shoots.
 *  This function draws all the zamus shoots maded by the player
 *  that are in the Zamus detector.
 */
void SceneRenderer :: drawIceSpawns ()
{
    int i;
    int nShoots;
    vector <LinqSpawnIce> ices;

    ices = sr_LinqDetector -> iceSpawn;

    for (i = 0; i < ices.size(); i++) {
        ices[i].nextPosition();
        if (ices[i].isAlive()) {
            ices[i].drawSpawnIce();
        }
        else {
            ices.erase(ices.begin() + i);
            i--;
        }
    }

    sr_LinqDetector -> iceSpawn = ices;
}

/**
 *  Modify the modeling matrix of OpenGL positioning the center
 *  in the point one and orienting the Y axis to the point two.
 *  @param point1 the point where the matrix will be center.
 *  @param point2 the point where the Y axis will go.
 */
void SceneRenderer :: orientAxis (XnPoint3D& p1,XnPoint3D& p2)
{
    Vector3D v1;
    Vector3D v2;
    Vector3D v3;

    float zero;
    float ax;
    float rx;
    float ry;

    float limpLength;

    v1 = Vector3D (p1.X, p1.Y, p1.Z);
    v2 = Vector3D (p2.X, p2.Y, p2.Z);

    v3 = v2 - v1;

    limpLength = v3.magnitude();

    zero = 1.0e-3;

    if (fabs(v3.z) < zero) {
        ax = 57.2957795 * acos(v3.x / limpLength);
    
        if (v3.x <= 0.0) {
            ax = -ax;
        }
    }
    else {
    
        ax = 57.2957795 * acos(v3.z / limpLength);

        if (v3.z <= 0.0) {
            ax = -ax;
        }

        rx = -v3.y * v3.z;
        ry = v3.x * v3.z;

        glTranslatef(p1.X, p1.Y, p1.Z);


        if (fabs(v3.z) < zero) {

            glRotated(90.0, 0, 1, 0.0);
            glRotated(ax, -1.0, 0.0, 0.0); 

        }
        else {

            glRotated(ax, rx, ry, 0.0);

        }

    }
}

/**
 *  Draw the Linq model over the player.
 *  This function display the linq model for the player if he
 *  is been tracked.
 *  @param player the ID of the player.
 */
void SceneRenderer :: drawLinq (XnUserID player)
{
    float ax;
    Vector3D a;
    Vector3D b;
    Vector3D c;
    Vector3D d;
    Vector3D u;
    Vector3D v;
    Vector3D w;
    Vector3D n;

    GLuint mode;
    UserGenerator      userGen;

    XnPoint3D points[15];
    XnPoint3D staffDirection;
    XnPoint3D shieldDirection;
    XnPoint3D shieldPosition;

    // Skeleton Joints
    XnSkeletonJointPosition headJoint;
    XnSkeletonJointPosition neckJoint;
    XnSkeletonJointPosition leftShoulderJoint;
    XnSkeletonJointPosition rightShoulderJoint;
    XnSkeletonJointPosition leftHipJoint;
    XnSkeletonJointPosition rightHipJoint;
    XnSkeletonJointPosition torsoJoint;
    XnSkeletonJointPosition leftArmJoint;
    XnSkeletonJointPosition rightArmJoint;
    XnSkeletonJointPosition leftHandJoint;
    XnSkeletonJointPosition rightHandJoint;
    XnSkeletonJointPosition leftKneeJoint;
    XnSkeletonJointPosition rightKneeJoint;
    XnSkeletonJointPosition leftFootJoint;
    XnSkeletonJointPosition rightFootJoint;

    userGen = sr_UserDetector -> retUserGenerator();
    SkeletonCapability skelCap = userGen.GetSkeletonCap();

    mode =  GLM_SMOOTH | GLM_MATERIAL;

    if (skelCap.IsTracking(player)) {

        // GET SKELETON JOINT POSITIONS
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_HEAD,
                                         headJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_NECK,
                                         neckJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_LEFT_SHOULDER,
                                         leftShoulderJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_RIGHT_SHOULDER,
                                         rightShoulderJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_TORSO,
                                         torsoJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_LEFT_ELBOW,
                                         leftArmJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_RIGHT_ELBOW,
                                         rightArmJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_LEFT_HAND,
                                         leftHandJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_RIGHT_HAND,
                                         rightHandJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_LEFT_HIP,
                                         leftHipJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_RIGHT_HIP,
                                         rightHipJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_LEFT_KNEE,
                                         leftKneeJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_RIGHT_KNEE,
                                         rightKneeJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_LEFT_FOOT,
                                         leftFootJoint);
        skelCap.GetSkeletonJointPosition(player, 
                                         XN_SKEL_RIGHT_FOOT,
                                         rightFootJoint);

        points[0]  = headJoint.position;
        points[1]  = neckJoint.position;
        points[2]  = leftShoulderJoint.position;
        points[3]  = rightShoulderJoint.position;
        points[4]  = leftHipJoint.position;
        points[5]  = rightHipJoint.position;
        points[6]  = torsoJoint.position;
        points[7]  = leftArmJoint.position;
        points[8]  = rightArmJoint.position;
        points[9]  = leftHandJoint.position;
        points[10]  = rightHandJoint.position;
        points[11]  = leftKneeJoint.position;
        points[12] = rightKneeJoint.position;
        points[13] = leftFootJoint.position;
        points[14] = rightFootJoint.position;

        sr_DepthGenerator -> ConvertRealWorldToProjective(15, 
                                                          points, 
                                                          points); 

            a = Vector3D(points[5].X,points[5].Y,points[5].Z);
            b = Vector3D(points[2].X,points[2].Y,points[2].Z);
            c = Vector3D(points[4].X,points[4].Y,points[4].Z);
            d = Vector3D(points[3].X,points[3].Y,points[3].Z);

            u = a - b;
            v = c - d;

            w   = u.cross(v);
            w.y = 0.0;
            w.normalize();

            ax = 57.2957795 * acos(w.z);

            if (w.x <= 0.0) {
                ax = -ax;
            }

        //Calculate staff direction
        v = Vector3D(points[7], points[9]);
        u = Vector3D(points[2], points[7]);

        w = v.cross(u);
        n = v.cross(w);

        staffDirection.X = points[9].X;
        staffDirection.Y = n.y + points[9].Y;
        staffDirection.Z = n.z + points[9].Z;

        //Calculate shield direction
        v = Vector3D(points[8], points[10]);
        u = Vector3D(points[3], points[8]);

        w = v.cross(u);

        shieldDirection.X = w.x + points[8].X;
        shieldDirection.Y = w.y + points[8].Y;
        shieldDirection.Z = w.z + points[8].Z;

        w.normalize();
        shieldPosition.X = points[8].X + (w.x * 30);
        shieldPosition.Y = points[8].Y + (w.y * 30);
        shieldPosition.Z = points[8].Z + (w.z * 30);

        // DRAW LINQ HEAD

        if ((headJoint.fConfidence >= 0.5) && (neckJoint.fConfidence >= 0.5)) {

            glPushMatrix();

                orientAxis(points[0],points[1]);
                glScalef(450.0, 450.0, 450.0);
                glTranslatef(0.0, -0.1, 0.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.head, mode); 

            glPopMatrix();
        }

        // DRAW LINQ CHEST

        if ((torsoJoint.fConfidence >= 0.5) && (neckJoint.fConfidence >= 0.5)) {

            glPushMatrix();

                orientAxis(points[1],points[6]);
                glScalef(300.0, 300.0, 300.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glTranslatef(0.0, -0.2, 0.0);
                glmDraw(linqParts.chest, mode); 

            glPopMatrix();
        }

        // DRAW LINQ SHOULDERS
        
        if ((leftShoulderJoint.fConfidence >= 0.5) && 
            (rightShoulderJoint.fConfidence >= 0.5)) {

            glPushMatrix();
                glTranslatef(points[2].X, points[2].Y, points[2].Z);
                glRotatef(-ax, 0.0,-2.0, 0.0);
                glScalef(500.0,-500.0, 500.0);
                glmDraw(linqParts.shoulder, mode); 

            glPopMatrix();
            glPushMatrix();
                glTranslatef(points[3].X, points[3].Y, points[3].Z);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glScalef(500.0,-500.0, 500.0);
                glmDraw(linqParts.shoulder, mode); 

            glPopMatrix();

        }

        // DRAW LINQ LEFT ARM
        
        if ((rightShoulderJoint.fConfidence >= 0.5) && 
            (rightArmJoint.fConfidence >= 0.5) && 
            (rightHandJoint.fConfidence >= 0.5)) {

            glPushMatrix();
                orientAxis(points[3],points[8]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(350.0, 350.0, 350.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.arm, mode); 

            glPopMatrix();
            
            glPushMatrix();
                orientAxis(points[8],points[10]);
                glTranslatef( 0.0, 0.0, 60.0);
                glScalef(250.0, 250.0, 250.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.forearm, mode); 

            glPopMatrix();
            

        }

        // DRAW LINQ RIGHT ARM
        
        if ((leftShoulderJoint.fConfidence >= 0.5) && 
            (leftArmJoint.fConfidence >= 0.5) &&
            (leftHandJoint.fConfidence >= 0.5)) {

            glPushMatrix();
                orientAxis(points[2],points[7]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(350.0, 350.0, 350.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.arm, mode); 

            glPopMatrix();
            
            glPushMatrix();
                orientAxis(points[7],points[9]);
                glTranslatef( 0.0, 0.0, 60.0);
                glScalef(-250.0, 250.0, 250.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.forearm, mode); 

            glPopMatrix();
            

        }

        // DRAW LINQ SHIELD
        if (leftHandJoint.fConfidence >= 0.5) {
             
            glPushMatrix();
                orientAxis(shieldPosition,shieldDirection);
                //glTranslatef( 0.0, 0.0,-50.0);
                glScalef(300.0, 300.0, 300.0);
                glRotatef(90, 0.0, 1.0, 0.0);
                glRotatef(180, 1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.shield, mode); 
            glPopMatrix();
        
        }

        // DRAW LINQ ICE STAFF
        if (leftHandJoint.fConfidence >= 0.5) {
             
            glPushMatrix();
                orientAxis(points[9],staffDirection);
                glTranslatef( 0.0, 0.0,-50.0);
                glScalef(250.0, 250.0, 250.0);
                glRotatef(-90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.staff, mode); 
            glPopMatrix();
        
        }
    /*
        // DRAW LINQ ICE STAFF
        if (leftHandJoint.fConfidence >= 0.5) {
             
            glPushMatrix();
                orientAxis(points[9],staffDirection);
                glTranslatef( 0.0, 0.0, 150.0);
                glScalef(350.0, 350.0, 350.0);
                glRotatef(-90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.sword, mode); 
            glPopMatrix();
        
        }
    */
        // DRAW LINQ LEFT LEG
        
        if ((rightHipJoint.fConfidence >= 0.5) && 
            (rightKneeJoint.fConfidence >= 0.5) &&
            (rightFootJoint.fConfidence >= 0.5)) {

            glPushMatrix();
                orientAxis(points[5],points[12]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(180.0, 180.0, 180.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.thigh, mode); 

            glPopMatrix();
            
            glPushMatrix();
                orientAxis(points[12],points[14]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(80.0,80.0, 80.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.leg, mode); 

            glPopMatrix();
            

        }

        // DRAW LINQ RIGHT LEG
        
        if ((leftHipJoint.fConfidence >= 0.5) && 
            (leftKneeJoint.fConfidence >= 0.5) &&
            (leftFootJoint.fConfidence >= 0.5)) {

            glPushMatrix();
                orientAxis(points[4],points[11]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(-180.0, 180.0, 180.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.thigh, mode); 

            glPopMatrix();
            
            glPushMatrix();
                orientAxis(points[11],points[13]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(-80.0, 80.0, 80.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqParts.leg, mode); 

            glPopMatrix();
            

        }

        // DRAW LINQ RIGHT FOOT
        
        if ((rightFootJoint.fConfidence >= 0.5) && 
            (leftFootJoint.fConfidence >= 0.5)) {

            glPushMatrix();
                glTranslatef( points[13].X, points[13].Y, points[13].Z);
                glScalef(40.0,-40.0,-40.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glTranslatef(0.0,-0.25, 0.5);
                glmDraw(linqParts.foot, mode); 

            glPopMatrix();
            
            glPushMatrix();
                glTranslatef( points[14].X, points[14].Y, points[14].Z);
                glScalef(-40.0,-40.0,-40.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glTranslatef(0.0,-0.25, 0.5);
                glmDraw(linqParts.foot, mode); 

            glPopMatrix();

        }
    }
}
