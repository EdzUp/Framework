/*
    Graphics.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef GRAPHICSCLASS
    #define GRAPHICSCLASS
    #include "Vec3.h"
    #include <GL/gl.h>

    class GraphicsClass {
        Vec3                    CameraPosition;
        Vec3r                   CameraRotation;

        float                   CameraNear;
        float                   CameraFar;

        float                   Width;
        float                   Height;

        int                     gColorMode;

        void SetPerspective( GLdouble width, GLdouble height, GLdouble zNear, GLdouble zFar );
        void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );

    public:
        bool Initialise( int width, int height, int depth );
        void TestRender( void );
    };
#endif // GRAPHICSCLASS
