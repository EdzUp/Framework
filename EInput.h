/*
// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
*/

#ifndef EINPUT
    #define EINPUT

    #include <conio.h>
    #include "KeyDefines.h"

    bool    keybank[ 512 ];
    bool    mousebutton[ 4 ];
    int     mousex;
    int     mousey;
    bool    inWindow;

    void processNormalKeys(unsigned char key, int x, int y ) {
        if ( key>=97 && key<=122 ) key-=32;
        keybank[ key ] = true;
    }

    void processSpecialKeys(int key, int x, int y ) {
        keybank[ key+255 ] = true;
    }

    class InputClass {
        public:
        void UpdateInput( void ) {
            char KeyA;
            char KeyB;
            #ifdef _WIN32
            if ( kbhit() ) {
                KeyA = getch();
                if ( KeyA == 0 ) KeyB = getch();        //if KeyA is 0 could mean control key pressed
                printf( "%c:%c\n", KeyA, KeyB );
            }
            #endif
        }

        int MouseX( void ) {
            return MouseXPos;
        }

        int MouseY( void ) {
            return MouseYPos;
        }

        bool MouseDown( int button ) {
            switch( button ) {
            case 0:
                return( MouseLeftDown );
            case 1:
                return( MouseRightDown );
            case 2:
                return( MouseMiddleDown );
            }

            return( false );
        }

        void FlushKeys( void ) {
            for ( unsigned int FK=0; FK<512; FK++ ) {
                keybank[ FK ] =  false;
            }
        }

        bool KeyDown( int key ) {
            if ( keybank[ key ] == true ) {
                keybank[ key ] = false;             //deactivate the key for next time
                return true;
            }

            return false;
        }

        void KeyUp( int key ) {
            keybank[ key ] =false;
        }

        void Initialise( void ) {
            int kp;

            for( kp =0; kp<512; kp++ ) {
                keybank[ kp ] = false;
            }
        }
    };
#endif // EINPUT
