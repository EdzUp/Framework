//
//	EFont.h - Copyright (C)EdzUp
//	Programmed by Ed 'EdzUp' Upton
//

#include "EFont.h"
#include <GL/gl.h>
#include <GL/glu.h>

float 	Ecolor[4] = {1, 1, 1, 1};
int 	ScreenWidth;
int 	ScreenHeight;

void FontClass::InitialiseFontSystem( float width, float height, bool threeD ) {
    ScreenWidth = width;
    ScreenHeight = height;
    Using3D = threeD;
}

///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void FontClass::drawString3D(const char *str, float pos[3]) {
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(Ecolor);          // set text color
    glRasterPos3fv(pos);        // place text position

    // loop all characters in the string
    while(*str)
    {
//      glutBitmapCharacter(Efont, *str);
        ++str;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

void FontClass::drawString(const char *str, int x, int y) {
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(Ecolor);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str) {
        //glutBitmapCharacter(Efont, *str);
        ++str;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

void FontClass::DrawText( int x, int y, std::string txt, bool centerx, bool centery ) {
    //like blitz drawtext command
    float posi[ 3 ];
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);     // switch to projection matrix
    glPushMatrix();                  // save current projection matrix
    glLoadIdentity();                // reset projection matrix
    gluOrtho2D(0, ScreenWidth, 0, ScreenHeight);  // set to orthogonal projection

    if ( Using3D == true ) {
        posi[ 0 ] =(float)x;
        posi[ 1 ] =(float)y;
        posi[ 2 ] =0.0f;
        drawString3D( txt.c_str(), posi );
    } else {
        drawString( txt.c_str(), x, ScreenHeight -y );
    }
    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix

}
