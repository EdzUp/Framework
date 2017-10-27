/*
    TwoD.cpp - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#include "TwoD.h"

float		DrawAngle;
float		DrawScaleX, DrawScaleY;
Colour		DrawColor;
float Colors[18] = { 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f};
float Vertices[18] = {-1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f };
float TextureUV[12] = {0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f};

void TwoDClass::Initialise( void ) {
    DrawAngle = 0.0f;
    DrawScaleX = 1.0f;
    DrawScaleY = 1.0f;
    DrawColor.Red = 1.0f;
    DrawColor.Green = 1.0f;
    DrawColor.Blue = 1.0f;
    DrawColor.Alpha = 1.0f;
}

void TwoDClass::Begin2d( void ){
    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable( GL_TEXTURE_2D );
    glEnableClientState (GL_TEXTURE_COORD_ARRAY);						//Enable texturing
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
}

void TwoDClass::End2d( void ){
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState (GL_TEXTURE_COORD_ARRAY);
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    glPopMatrix();
}

void TwoDClass::PasteImage( ETexture Image, float X, float Y ) {
    //vert data for glDrawArray stuff
    glLoadIdentity();
    glTranslatef( X, Y, 0.0 );
    glRotatef(DrawAngle, 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, Image.Texture );					//bind the Player ship texture
    glColorPointer(3, GL_FLOAT, 0, Colors);
    glVertexPointer(3, GL_FLOAT, 0, Vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, TextureUV);						//setup UV's
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void TwoDClass::SetScale( float newScaleX, float newScaleY ) {
    float nSX = 1.0f *newScaleX;
    float nSY = 1.0f *newScaleY;
    Vertices[ 0 ] = -nSX;
    Vertices[ 1 ] = nSY;
    //0.0
    Vertices[ 3 ] = nSX;
    Vertices[ 4 ] = nSY;
    //0.0
    Vertices[ 6 ] = nSX;
    Vertices[ 7 ] = -nSY;
    //0.0
    Vertices[ 9 ] = -nSX;
    Vertices[ 10 ] = -nSY;
    //0.0
    Vertices[ 12 ] = -nSX;
    Vertices[ 13 ] = nSY;
    //0.0
    Vertices[ 15 ] = nSX;
    Vertices[ 16 ] = -nSY;
    //0.0
}

void TwoDClass::SetRotation( float newAngle ) {
    //sets the rotation of all new drawing images
    DrawAngle = newAngle;
}

void TwoDClass::SetColor( float Red, float Green, float Blue, float Alpha =1.0f ){
    DrawColor.Red = Red;
    DrawColor.Green = Green;
    DrawColor.Blue = Blue;
    DrawColor.Alpha = Alpha;

    for ( int ncol=0; ncol<18; ncol+=3 ){
        Colors[ ncol ] = Red;
        Colors[ ncol +1 ] = Green;
        Colors[ ncol +2 ] = Blue;
    }
}
