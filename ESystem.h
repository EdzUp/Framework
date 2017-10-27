/*
 *  ESystem.h - Copyright (C)EdzUp
 *  Programming by Ed 'EdzUp' Upton
 */

#ifndef SYSTEMCLASS
    #define SYSTEMCLASS
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <stdio.h>
    #include <string>
    #include <cstring>
    #include "EDebug.h"

    #define SUPPORT_VBO         1

    class SystemClass {
        public:
        char* OpenGLVersion( void ) {
            return( (char*)glGetString( GL_VERSION ) );
        }

        bool OpenGLExtension( char* CheckFor ) {
            char* TempChar;

            TempChar = (char*)glGetString( GL_EXTENSIONS );

            if ( strstr( TempChar, CheckFor ) != NULL ) {
                //TempList.find( CheckFor ) != TempList.npos ) {
                return( true );
            }

            return( false );
        }

        bool Supports( long CheckFor ) {
            bool temp;

            switch( CheckFor ){
            case SUPPORT_VBO:
    //              temp = (std::string)OpenGLExtension( "ARB_vertex_buffer_object" );

                return( temp );
                break;
            }
            return( false );
        }

        char* OpenGLShaderVersion( void ) {
            //this returns the release version of the shader language
            #ifdef GL_SHADING_LANGUAGE_VERSION
                return( (char*)glGetString( GL_SHADING_LANGUAGE_VERSION ) );
            #endif // GL_SHADING_LANGUAGE_VERSION

            return( NULL );
        }
    };
#endif // SYSTEMCLASS
