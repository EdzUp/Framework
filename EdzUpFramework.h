/*
	EdzUpFramework.h - Copyright (C)EdzUp
	Programmed by Ed 'EdzUp' Upton
*/

#ifdef USE_MSDOS
    #define FRAMEWORKSET

	 #include "..\Engine\EdzUpF~2.h"				//DOS calling conventions

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
#endif // USE_MSDOS

#ifndef FRAMEWORKSET
	#define FRAMEWORKSET
	#include <GL/gl.h>
	#ifdef _WIN32
		#include <Windows.h>
	#else
		#include <unistd.h>
	#endif

	#include "Graphics.h"                       //this will be the graphics library

	#include "ThreeD/ThreeD.h"

	#include "KeyDefines.h"
	#include "EdzUpFrameworkGlobals.h"
	#include "EAudio.h"
	#include "EdzUpMath.h"
	#include "ETexture.h"
	#include "KeyDefines.h"
	#include "ESystem.h"
//	#include "ECamera.h"
	#include "EFont.h"
	#include "TwoD/TwoD.h"
	#include "ThreeD/ThreeD.h"
	#include "ETimer.h"
	#include "FileSystem.h"
	#include "ERandom.h"
	#include "Convert.h"
	#include "Packer.h"
	#include "EDebug.h"
	#include "Networking.h"
	#include "EInput.h"
	#include "TextSystem.h"
	#include "FontSystem.h"

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
        GraphicsClass               Graphics;
		FrameworkAudioClass			Audio;
		EdzUpMathClass				Math;
		SystemClass					System;
		EFCamera					Camera;
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
		TextSystemClass             TextSystem;

		int DisplayWidth( void ) {
		    #ifdef _WIN32
                return( Win32.CurrentWidth() );
		    #endif

		    return( 0 );
		}

		int DisplayHeight( void ) {
		    #ifdef _WIN32
                return( Win32.CurrentHeight() );
		    #endif

		    return( 0 );
		}

		int Shutdown( void ) {
		    #ifdef _WIN32
                return( Win32.Shutdown() );
		    #endif

			 exit( 1 );
		}

		void Error( std::string tit, std::string mes ) {
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

            ThreeD.Renderer.Initialise( Camera.WorldPosition );

            ErrorMessage = "";
            ErrorSet = false;
		}

		std::string CheckError( void ) {
		    if ( ErrorSet == true ) {
                return( ErrorMessage );
		    }

		    return( "" );
		}

		float VisualWidth( void ) {
		    return( ActualWidth );
		}

		float VisualHeight( void ) {
		    return( ActualHeight );
		}

		int MoveMouse( int x, int y ) {
		    #ifdef _WIN32
                Win32.MoveMouse( x, y );
		    #endif
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
/*
I'm assuming what you want to achieve is a "square" projection, e.g. when you draw a
circle you want it to look like a circle rather than an ellipse.

The only thing you should play with is your projection (camera) aspect ratio. In
normal cases, monitors keep pixels square and all you have to do is set your camera
aspect ratio equal to your viewport's aspect ratio:

viewport_aspect_ratio = viewport_res_x / viewport_res_y;
camera_aspect_ratio = viewport_aspect_ratio;
In the stretched case you describe (4:3 image stretched on a 16:10 screen for example),
pixels are not square anymore and you have to take that into account in your camera
aspect ratio:

stretch_factor_x = screen_size_x / viewport_res_x;
stretch_factor_y = screen_size_y / viewport_res_y;
pixel_aspect_ratio = stretch_factor_x / stretch_factor_y;
viewport_aspect_ratio = viewport_res_x / viewport_res_y;
camera_aspect_ratio = viewport_aspect_ratio * pixel_aspect_ratio;
Where screen_size_x and screen_size_y are multiples of the real size of the monitor (e.g. 16:10).

However, you should simply assume square pixels (unless you have a specific reason no to),
as the monitor may report incorrect physical size informations to the system, or no
informations at all. Also monitors don't always stretch, mine for example keeps 1:1 pixels
aspect ratio and adds black borders for lower resolutions.

Edit

If you want to adjust your viewport to some aspect ratio and fit it on an arbitrary resolution
then you could do like that :

viewport_aspect_ratio = 16.0 / 10.0; // The aspect ratio you want your viewport to have
screen_aspect_ratio = screen_res_x / screen_res_y;

if (viewport_aspect_ratio > screen_aspect_ratio) {
    // Viewport is wider than screen, fit on X
    viewport_res_x = screen_res_x;
    viewport_res_y = viewport_res_x / viewport_aspect_ratio;
} else {
    // Screen is wider than viewport, fit on Y
    viewport_res_y = screen_res_y;
    viewport_res_x = viewport_res_y * viewport_aspect_ratio;
}

camera_aspect_ratio = viewport_res_x / viewport_res_y;
*/

			#ifdef _WIN32
				if ( Win32.InFullscreen() == false ) {
					width = Win32.WindowWidth();
					height = Win32.WindowHeight();
				} else {
					width = Win32.DesktopWidth();
					height = Win32.DesktopHeight();
				}
			#endif

			//In the stretched case you describe (4:3 image stretched on a 16:10 screen for example),
			//pixels are not square anymore and you have to take that into account in your camera
			//aspect ratio:
/*
			float screen_size_x = 4.0;          //4:3 mode
			float screen_size_y = 3.0;
			float viewport_res_x = width;
			float viewport_res_y = height;

            float stretch_factor_x = screen_size_x / viewport_res_x;
            float stretch_factor_y = screen_size_y / viewport_res_y;
            float pixel_aspect_ratio = stretch_factor_x / stretch_factor_y;
            float viewport_aspect_ratio = viewport_res_x / viewport_res_y;
            float camera_aspect_ratio = viewport_aspect_ratio * pixel_aspect_ratio;
            //Where screen_size_x and screen_size_y are multiples of the real size of the monitor (e.g. 16:10).
			return;
*/
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
			glDisable( GL_SCISSOR_TEST );

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if ( Using3D == false ) {
				glOrtho(0.0f, WIDTH / ar_origin, HEIGHT / ar_origin, 0, 0.0f, 100.0f );
			} else {
				glFrustum( 0.0f, WIDTH, 0.0f, HEIGHT, 0.0f, 100.0f );
			}
			glViewport(margin_x, margin_y, (WIDTH * scale_w ), HEIGHT * scale_h);

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
