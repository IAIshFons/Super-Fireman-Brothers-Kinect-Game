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
 *  @file NeutralModel.cpp
 *  
 *  @brief This file contains the implementation of the functions
 *  defined in NeutralModel.h.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 */

# include "NeutralModel.h"

/**
 *  Colors contain the diferent colors that can be asign to the users.
 */

const static XnFloat Colors[][3] =
{
     {0,1,1},
     {0,0,1},
     {0,1,0},
     {1,1,0},
     {1,0,0},
     {1,.5,0},
     {.5,1,0},
     {0,.5,1},
     {.5,0,1},
     {1,1,.5},
     {1,1,1}
};

/**
 *  Number of diferent type of colors.
 */
const static XnUInt32 nColors = 10;

/**
 *  Constructor.
 */
NeutralModel :: NeutralModel ()
{
    nm_UserDetector = NULL;
    nm_DepthGenerator = NULL;
}

/**
 *  Constructor.
 */
NeutralModel :: NeutralModel (UserDetector *userDetector,
                              ZamusModel&   zamusModel,
                              LinqModel&    linqModel)
{
    nm_UserDetector   = userDetector;
    nm_DepthGenerator = nm_UserDetector -> retDepthGenerator();

    // Classes with the 3D model parts
    zamusModelParts   = zamusModel;
    linqModelParts    = linqModelParts;
}

/**
 *  Load actual joint positions.
 *
 *  Load the position of the joints in the joint array.
 *
 *  @param player is the player ID who needs to load the joints
 *  from.
 *  @param skelCap is the skeletonCapability taken from the User
 *  Generator.
 */
void NeutralModel :: loadJoints (XnUserID player, SkeletonCapability skelCap)
{
    // Skeleton Joint.
    XnSkeletonJointPosition jointPos;

    if (skelCap.IsTracking(player)) {

        // Get skeleton jointPos positions.
        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_HEAD, 
                jointPos
        );
        joint[HEAD] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_NECK, 
                jointPos
        );
        joint[NECK] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_LEFT_SHOULDER, 
                jointPos
        );
        joint[LSHOULDER] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_RIGHT_SHOULDER, 
                jointPos
        );
        joint[RSHOULDER] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_TORSO, 
                jointPos
        );
        joint[TORSO] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_LEFT_ELBOW, 
                jointPos
        );
        joint[LELBOW] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_RIGHT_ELBOW, 
                jointPos
        );
        joint[RELBOW] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_LEFT_HAND, 
                jointPos
        );
        joint[LHAND] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_RIGHT_HAND, 
                jointPos
        );
        joint[RHAND] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_LEFT_HIP, 
                jointPos
        );
        joint[LHIP]  = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_RIGHT_HIP, 
                jointPos
        );
        joint[RHIP]  = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_LEFT_KNEE, 
                jointPos
        );
        joint[LKNEE] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_RIGHT_KNEE, 
                jointPos
        );
        joint[RKNEE] = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_LEFT_FOOT, 
                jointPos
        );
        joint[LFOOT]  = jointPos.position;

        skelCap.GetSkeletonJointPosition(
                player, 
                XN_SKEL_RIGHT_FOOT, 
                jointPos
        );
        joint[RFOOT]  = jointPos.position;

        nm_DepthGenerator.ConvertRealWorldToProjective(15, joint, joint); 
    }


}

/**
 *  Orient the modeling matrix between two points.
 *
 *  Modify the modeling matrix to be centared in one point and
 *  with the Y axis looking to the second point.
 *
 *  @param point1 is where the matrix will be centered.
 *  @param point2 is where the Y axis will be.
 */
void NeutralModel :: orientMatrix (XnPoint3D& point1, XnPoint3D& point2)
{
    Vector3D v1;
    Vector3D v2;
    Vector3D v3;

    float zero;
    float ax;
    float rx;
    float ry;

    float limpLength;

    v1 = Vector3D (point1);
    v2 = Vector3D (point2);

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

        glTranslatef(point1.X, point1.Y, point1.Z);


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
 *  Draw Torso.
 *
 *  This function draws a box that represents the torso of the
 *  player.
 */
void NeutralModel :: drawTorso ()
{
    Vector3D a;
    Vector3D b;
    Vector3D c;
    Vector3D d;

    Vector3D ab;
    Vector3D ac;

    Vector3D n;

    a = Vector3D (joint[LSHOULDER]);
    b = Vector3D (joint[RSHOULDER]);
    c = Vector3D (joint[RHIP]);
    d = Vector3D (joint[LHIP]);

    ab = b - a;
    ac = c - a;

    n = ab.cross(ac);
    n.normalize();

    glPushMatrix();
        glBegin(GL_QUADS);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(a.x, a.y, a.z);
            glVertex3f(b.x, b.y, b.z);
            glVertex3f(c.x, c.y, c.z);
            glVertex3f(d.x, d.y, d.z);
        glEnd();
    glPopMatrix();
}

/**
 *  Draw head.
 *
 *  This function draws a sphere in the head joint of the
 *  player.
 */
void NeutralModel :: drawHead ()
{
    XnPoint3D head;

    head = joint[HEAD];

    glPushMatrix();
        glTranslatef(head.X, head.Y, head.Z);
        glutSolidSphere(40.0, 15, 15);
    glPopMatrix();
}

/**
 *  Draw a stick between two points.
 *
 *  This function draws a cylincer and a sphere on its top
 *  between two points.
 *
 *  @param point1 is the first point.
 *  @param point2 is the second point where is going to be the
 *  sphere.
 */
void NeutralModel :: drawLimp (XnPoint3D& point1, XnPoint3D& point2)
{
    Vector3D v;
    Vector3D u;
    Vector3D w;
    
    float limpLength;

    GLUquadricObj *quadratic;

    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricOrientation(quadratic,GLU_OUTSIDE);

    v = Vector3D (point1);
    u = Vector3D (point2);

    w = u - v;

    limpLength = w.magnitude();

    glPushMatrix();
        orientMatrix(point1, point2);
        gluCylinder(quadratic, 15.0f, 15.0f,limpLength, 10, 1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(point2.X, point2.Y, point2.Z);
        glutSolidSphere(20.0, 10, 10);
    glPopMatrix();
}

/**
 *  DrawNeutral function.
 *
 *  This function draws the stick figure depending on the
 *  transforming stage of the player or draws a diamond if the
 *  player is not tracked.
 *
 *  @param player is the ID of the player.
 *
 */
void NeutralModel :: drawNeutral (XnUserID player)
{
    // UserGenerator.
    UserGenerator userGen;

    // Color of the stick figure.
    XnFloat color[3];

    // Material properties.
    GLfloat mat_specular[] = { 0.3, 0.3, 0.3, 0.3 };
    GLfloat mat_shininess[] = { 10.0 };

    // Center of mass.
    XnPoint3D com;

    // Player's stage.
    int stage;

    float ax;
    Vector3D a;
    Vector3D b;
    Vector3D c;
    Vector3D u;
    Vector3D v;
    Vector3D w;

    GLuint mode;

    // Select the players color according his ID.
    color[0] = Colors[player % nColors][0];
    color[1] = Colors[player % nColors][1];
    color[2] = Colors[player % nColors][2];

    // Set the material for the stick figure.
    GLfloat materialColor[] = {color[0], color[1], color[2], 1.0f};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    userGen = nm_UserDetector -> retUserGenerator();
    SkeletonCapability skelCap = userGen.GetSkeletonCap();

    mode =  GLM_SMOOTH | GLM_MATERIAL;


    a = Vector3D(joint[LSHOULDER]);
    b = Vector3D(joint[RSHOULDER]);
    c = Vector3D(joint[RHIP]);

    u = b - a;
    v = c - a;

    w = u.cross(v);
    w.y = 0.0;
    w.normalize();

    ax = 57.2957795 * acos(w.z);

    if (w.x <= 0.0) {
        ax = -ax;
    }

    // Init the drawing process.
    // Draws a stick figure if player is been tracked.
    if (skelCap.IsTracking(player)) {
       
        // Get player's stage.
        stage = nm_UserDetector -> retStage(player);

        loadJoints(player, skelCap);

        // Drawing legs.
        if ((stage >= 0) && (stage < 4)) { 

            // Left leg.
            glPushMatrix();
                orientMatrix(joint[RHIP],joint[RKNEE]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(250.0, 250.0, 250.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.thigh, mode); 

            glPopMatrix();
            
            glPushMatrix();
                orientMatrix(joint[RKNEE],joint[RFOOT]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(100.0, 100.0, 100.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.leg, mode); 
            glPopMatrix();

            // Right leg.
            glPushMatrix();
                orientMatrix(joint[LHIP], joint[LKNEE]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(-250.0, 250.0, 250.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.thigh, mode); 

            glPopMatrix();
            
            glPushMatrix();
                orientMatrix(joint[LKNEE], joint[LFOOT]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(-100.0, 100.0, 100.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.leg, mode); 

            glPopMatrix();
                  
            // Foots.
            glPushMatrix();
                glTranslatef( joint[LFOOT].X, joint[LFOOT].Y, joint[LFOOT].Z);
                glScalef(40.0,-40.0,-40.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glTranslatef(0.0,-0.25, 0.5);
                glmDraw(zamusModelParts.foot, mode); 

            glPopMatrix();
            
            glPushMatrix();
                glTranslatef( joint[RFOOT].X, joint[RFOOT].Y, joint[RFOOT].Z);
                glScalef(-40.0,-40.0,-40.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glTranslatef(0.0,-0.25, 0.5);
                glmDraw(zamusModelParts.foot, mode); 

            glPopMatrix();
            


        } 
        else {
            drawLimp(joint[LKNEE],joint[LFOOT]);
            drawLimp(joint[RKNEE],joint[RFOOT]);
            drawLimp(joint[LHIP],joint[LKNEE]);
            drawLimp(joint[RHIP],joint[RKNEE]);
        }

        // Draw torso.
        if ((stage > 0) && (stage < 4)) {

            glPushMatrix();
                orientMatrix(joint[NECK],joint[TORSO]);
                glScalef(400.0, 400.0, 400.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glTranslatef(0.0, -0.1, 0.0);
                glmDraw(zamusModelParts.chest, mode); 
            glPopMatrix();

        }
        else {
            drawTorso();
        }

        // Drawing arms.
        if (stage == 2) {
    
            // Shoulders
            glPushMatrix();
                glTranslatef(joint[LSHOULDER].X, 
                             joint[LSHOULDER].Y,
                             joint[LSHOULDER].Z);
                glRotatef(-ax, 0.0,-2.0, 0.0);
                glTranslatef(-30.0,-40.0, 0.0);
                glScalef(500.0,-500.0, 500.0);
                glmDraw(zamusModelParts.shoulder, mode); 
            glPopMatrix();
            glPushMatrix();
                glTranslatef(joint[RSHOULDER].X, 
                             joint[RSHOULDER].Y,
                             joint[RSHOULDER].Z);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glTranslatef( 30.0,-40.0, 0.0);
                glScalef(500.0,-500.0, 500.0);
                glmDraw(zamusModelParts.shoulder, mode); 
            glPopMatrix();

            // LeftArm
            glPushMatrix();
                orientMatrix(joint[RSHOULDER], joint[RELBOW]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(500.0, 500.0, 500.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.arm, mode); 
            glPopMatrix();
            glPushMatrix();
                orientMatrix(joint[RELBOW], joint[RHAND]);
                glTranslatef( 0.0, 0.0, 60.0);
                glScalef(250.0, 250.0, 250.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.forearm, mode); 
            glPopMatrix();
            
            glPushMatrix();
                orientMatrix(joint[LSHOULDER], joint[LELBOW]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(500.0, 500.0, 500.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.arm, mode); 
            glPopMatrix();
            
            glPushMatrix();
                orientMatrix(joint[LELBOW],joint[LHAND]);
                glTranslatef( 0.0, 0.0, 80.0);
                glScalef(300.0, 300.0, 300.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(zamusModelParts.cannon, mode); 
            glPopMatrix();
           
        }
        else if ((stage == 4) || (stage == 5)) {

            glPushMatrix();
                glTranslatef(joint[LSHOULDER].X, 
                             joint[LSHOULDER].Y,
                             joint[LSHOULDER].Z);
                glRotatef(-ax, 0.0,-2.0, 0.0);
                glScalef(500.0,-500.0, 500.0);
                glmDraw(linqModelParts.shoulder, mode); 
            glPopMatrix();

            glPushMatrix();
                orientMatrix(joint[LSHOULDER],joint[LELBOW]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(-180.0, 180.0, 180.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqModelParts.thigh, mode); 
            glPopMatrix();
            
            glPushMatrix();
                orientMatrix(joint[LELBOW],joint[LHAND]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(-80.0, 80.0, 80.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqModelParts.leg, mode); 
            glPopMatrix();
            
        }
        else {
            drawLimp(joint[LSHOULDER],joint[LELBOW]);
            drawLimp(joint[LELBOW],joint[LHAND]);
        }
        
        if (stage == 5) {
        
            
            glPushMatrix();
                glTranslatef(joint[RSHOULDER].X, 
                             joint[RSHOULDER].Y, 
                             joint[RSHOULDER].Z);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glScalef(500.0,-500.0, 500.0);
                glmDraw(linqModelParts.shoulder, mode); 
            glPopMatrix();


            glPushMatrix();
                orientMatrix(joint[RSHOULDER],joint[RELBOW]);
                glTranslatef( 0.0, 0.0, 50.0);
                glScalef(350.0, 350.0, 350.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(ax, 0.0,-1.0, 0.0);
                glmDraw(linqModelParts.arm, mode); 
            glPopMatrix();
            
            glPushMatrix();
                orientMatrix(joint[RELBOW],joint[RHAND]);
                glTranslatef( 0.0, 0.0, 60.0);
                glScalef(250.0, 250.0, 250.0);
                glRotatef(90, -1.0, 0.0, 0.0);
                glRotatef(-ax, 0.0,-1.0, 0.0);
                glmDraw(linqModelParts.forearm, mode); 
            glPopMatrix();
        
        } 
        else {
            drawLimp(joint[RSHOULDER],joint[RELBOW]);
            drawLimp(joint[RELBOW],joint[RHAND]);
        }


        // Draw head.
        drawHead();
    }
    // Draws a diamond in the player's center of mass.
    else {
        userGen.GetCoM(player, com);
        nm_DepthGenerator.ConvertRealWorldToProjective(1, &com, &com);

        glPushMatrix();

            glTranslatef(com.X, com.Y, com.Z);
            glutSolidSphere(60.0, 4, 2);

        glPopMatrix();
    }

}
