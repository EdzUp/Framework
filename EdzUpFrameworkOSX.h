/*
	EdzUpFramework.h - Copyright (C)EdzUp
	Programmed by Ed 'EdzUp' Upton
*/

#ifdef USE_MSDOS
    #define FRAMEWORKSET

	 #include "..\Engine\EdzUpF~2.h"				//DOS calling conventions
	 #include "..\Engine\DOS\Memory.h"

    class EdzUpFrameworkClass {
    public:

        volatile unsigned char      *VideoAddress;

        DOSClass                    DOS;
        MemoryClass                 Memory;

        void Initialise( void ) {
            *VideoAddress = 0xB800;
        }
    };

    EdzUpFrameworkClass             Framework;
#else
#ifndef FRAMEWORKSET
	#define FRAMEWORKSET
	#include <gl/gl.h>
	#ifdef _WIN32
		#include <Windows.h>
	#else
		#include <unistd.h>
	#endif

	#include "ThreeD/ThreeD.h"

	#include "KeyDefines.h"
	#include "EdzupFrameworkGlobals.h"
	#include "EAudio.h"
	#include "EdzUpMath.h"
	#include "ETexture.h"
	#include "KeyDefines.h"
	#include "ESystem.h"
//	#include "ECamera.h"
	#include "EFont.h"
	#include "TwoD.h"
	#include "ThreeD/ThreeD.h"
	#include "ETimer.h"
	#include "FileSystem.h"
	#include "ERandom.h"
	#include "Convert.h"
	#include "Packer.h"
	#include "EDebug.h"
	#include "Networking.h"
	#include "EInput.h"

	#ifdef _WIN32
        #include "EdzUpFrameworkWin32.h"
	 #endif
    #ifdef __linux__
        #include "EdzUpFrameworkLinux.h"
    #endif

	class EdzUpFrameworkClass {
		public:
        #ifdef _WIN32
            FrameworkWin32				Win32;
        #endif
        #ifdef __linux__
            FrameworkLinux              Linux;
        #endif
		FrameworkAudioClass			Audio;
		EdzUpMathClass				Math;
		SystemClass					System;
		CameraClass					Camera;
		FontClass					Font;
		TwoDClass					TwoD;
		ThreeDClass                 ThreeD;
		TimerClass					Timer;
		RNDGenerator                Random;
		ConversionClass             Convert;
		PackerClass                 Packer;
		FileSystemClass             FileSystem;
		DebugClass                  Debug;
		NetworkingClass             Network;
		InputClass                  Input;

		int Shutdown( void ) {
		    #ifdef _WIN32
                return( Win32.Shutdown() );
		    #endif

			 exit( 1 );
		}

		void Error( string tit, string mes ) {
			#ifdef _WIN32
				Win32.DisplayError( tit, mes );
			#endif

			//others will silently fail at present
			exit( 1 );
		}

		bool ApplicationQuit( void ) {
		    return( AppQuit );
		}

		void SetApplicationDetails( void* ProgramName, void* title ){
		    #ifdef _WIN32
                //windows call
                Win32.SetApplicationDetails( (LPCSTR)ProgramName, (LPCSTR)title );
		    #endif
		}

		void EnableOpenGL( void ) {
		    #ifdef _WIN32
                Win32.EnableOpenGL();
		    #endif
            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		}

		void Windowed( int width, int height ) {
		    #ifdef _WIN32
                Win32.Windowed( width, height );
			 #endif
		}

		void Fullscreen( void ){
		    #ifdef _WIN32
                Win32.Fullscreen();
		    #endif
		}

		void Initialise( void ){
		    Random.Initialise();
            TwoD.Initialise();
            Math.Initialise();
            Input.Initialise();

            ErrorMessage = "";
            ErrorSet = false;
		}

		std::string CheckError( void ) {
		    if ( ErrorSet == true ) {
                return( ErrorMessage );
		    }

		    return( "" );
		}

		float DisplayWidth( void ) {
		    return( ActualWidth );
		}

		float DisplayHeight( void ) {
		    return( ActualHeight );
		}

		int MouseX( void ){
            return( MouseXPos );
		}

		int MouseY( void ){
		    return( MouseYPos );
		}

		void Delay( long millisecDelay ) {
			#ifdef _WIN32
				Sleep( millisecDelay );
			#else
				usleep(millisecDelay *1000 );  // sleep for 100 milliSeconds
			#endif
		}

		void ClsColor( int r, int g, int b ){
            ClsRed = ( 1.0f /255.0f ) *r;
            ClsGreen = ( 1.0f /255.0f ) *g;
            ClsBlue = ( 1.0f /255.0f ) *b;
            glClearColor( ClsRed, ClsGreen, ClsBlue, 0.5f);
		}

		void Cls( void ) {
			glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
		}

		void SetDisplayResolution( int width, int height ){
			WIDTH = width;
			HEIGHT = height;
		}

	// reshape function, call with glutReshapeFunc(reshape) in yout main function
		void CorrectAspectRatio( void ) {
			int width = 640, height =480;
			#ifdef _WIN32
				if ( Win32.InFullscreen() == false ) {
					width = Win32.WindowWidth();
					height = Win32.WindowHeight();
				} else {
					width = Win32.DesktopWidth();
					height = Win32.DesktopHeight();
				}
			#endif
			const float ar_origin = (float) WIDTH / (float) HEIGHT;
			const float ar_new = (float) width / (float) height;

			float scale_w = (float) width / (float) WIDTH;
			float scale_h = (float) height / (float) HEIGHT;
			if (ar_new > ar_origin) {
				scale_w = scale_h;
			} else {
				scale_h = scale_w;
			}

			float margin_x = (width - WIDTH * scale_w) / 2;
			float margin_y = (height - HEIGHT * scale_h) / 2;

			glViewport(margin_x, margin_y, WIDTH * scale_w, HEIGHT * scale_h);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if ( Using3D == false ) {
				glOrtho(0, WIDTH / ar_origin, 0, HEIGHT / ar_origin, 0.0f, 100.0f );
			} else {
				glFrustum( 0, WIDTH /ar_origin, 0, HEIGHT /ar_origin, 0.0f, 100.0f );
			}

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		void Flip( void ) {
		    //calls all screen data stuff
		    Input.UpdateInput();                //check for keys
		    #ifdef _WIN32
   				Win32.Flip();
            #endif
		}
	};

	EdzUpFrameworkClass Framework;
#endif // FRAMEWORKSET
#endif