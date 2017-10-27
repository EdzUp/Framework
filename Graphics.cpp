/*
    Graphics.cpp - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#include "Graphics.h"       //include the graphics header for use
#include <GL/gl.h>          //opengl calls
#include <math.h>
#include <vector>
#include <stdio.h>

void GraphicsClass::SetPerspective( GLdouble width, GLdouble height, GLdouble zNear, GLdouble zFar ) {
    //new function for perspective rendering
    GLdouble fov, top, bottom, left, right, aspect;

    top =0.0f;
    bottom = height;
    left = 0.0f;
    right = width;

    fov = atan( ( top -bottom ) *0.5 /zNear );
    top = tan(fov*0.5) * zNear;
    bottom = -top;
    left = aspect * bottom;
    right = aspect * top;

    glFrustum( left, right, bottom, top, zNear, zFar );
}

void GraphicsClass::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar ) {
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}


bool GraphicsClass::Initialise( int width, int height, int depth ){
    Width = width;
    Height = height;
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    glFrustum( 0.0f, width, height, 0.0f, CameraNear, CameraFar );
    glOrtho( 0.0, width, height, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
//        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void GraphicsClass::TestRender( void ){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                   // Reset The Current Modelview Matrix

    glTranslatef(-1.5f,0.0f,-6.0f);             // Left 1.5 Then Into Screen Six Units

    glBegin(GL_TRIANGLES);                  // Begin Drawing Triangles
glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
glVertex3f( 0.0f, 1.0f, 0.0f);          // Move Up One Unit From Center (Top Point)
glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
glVertex3f(-1.0f,-1.0f, 0.0f);          // Left And Down One Unit (Bottom Left)
   glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
    glVertex3f( 1.0f,-1.0f, 0.0f);          // Right And Down One Unit (Bottom Right)
glEnd();                        // Done Drawing A Triangle

glTranslatef(3.0f,0.0f,0.0f);               // From Right Point Move 3 Units Right
 glColor3f(0.5f,0.5f,1.0f);              // Set The Color To Blue One Time Only
    glBegin(GL_QUADS);                  // Start Drawing Quads
        glVertex3f(-1.0f, 1.0f, 0.0f);          // Left And Up 1 Unit (Top Left)
        glVertex3f( 1.0f, 1.0f, 0.0f);          // Right And Up 1 Unit (Top Right)
        glVertex3f( 1.0f,-1.0f, 0.0f);          // Right And Down One Unit (Bottom Right)
        glVertex3f(-1.0f,-1.0f, 0.0f);          // Left And Down One Unit (Bottom Left)
    glEnd();                        // Done Drawing A Quad
}
