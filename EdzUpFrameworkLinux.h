/*
    EdzUpFrameworkLinux.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

/*

/* A simple program to show how to set up an X window for OpenGL rendering.
 * X86 compilation: gcc -o -L/usr/X11/lib   main main.c -lGL -lX11
 * X64 compilation: gcc -o -L/usr/X11/lib64 main main.c -lGL -lX11
 */
 #ifndef LINUXMODULE
    #define LINUXMODULE
    #include <stdio.h>
    #include <stdlib.h>

    #include <GL/glx.h>    /* this includes the necessary X headers */
    #include <GL/gl.h>

    #include <X11/X.h>    /* X11 constant (e.g. TrueColor) */
    #include <X11/keysym.h>

    #include "EdzUpFramework.h"
    #include "EInput.h"
    #include "EdzUpFrameworkGlobals.h"

    class FrameworkLinux {
        int snglBuf[ 4 ];
        int dblBuf[ 4 ];

        Display   *dpy;
        Window     win;
        GLfloat    xAngle = 42.0, yAngle = 82.0, zAngle = 112.0;
        GLboolean  doubleBuffer = GL_TRUE;

        XVisualInfo         *vi;
        Colormap             cmap;
        XSetWindowAttributes swa;
        GLXContext           cx;
        XEvent               event;
        GLboolean            needRedraw = GL_FALSE, recalcModelView = GL_TRUE;
        int                  dummy;

        void SetBuf( void ) {
            snglBuf[ 0 ] = GLX_RGBA;
            snglBuf[ 1 ] = GLX_DEPTH_SIZE;
            snglBuf[ 2 ] = 16;
            snglBuf[ 3 ] = None;
            dblBuf[ 0 ] = GLX_RGBA;
            dblBuf[ 1 ] = GLX_DEPTH_SIZE;
            dblBuf[ 2 ] = 16;
            dblBuf[ 3 ] = GLX_DOUBLEBUFFER;
        }

        void fatalError(char *message) {
            fprintf(stderr, "main: %s\n", message);
            exit(1);
        }

    public:
        void Flip( void ) {
            if (doubleBuffer)
                glXSwapBuffers(dpy, win);/* buffer swap does implicit glFlush */
            else
                glFlush();  /* explicit flush for single buffered case */
        }

        void MakeWindow( int width, int height, int argc, char* argv) {
            SetBuf();   //internal buffer fluffer
            /*** (1) open a connection to the X server ***/
            dpy = XOpenDisplay(NULL);
            if (dpy == NULL) fatalError("could not open display");

            /*** (2) make sure OpenGL's GLX extension supported ***/
            if(!glXQueryExtension(dpy, &dummy, &dummy)) fatalError("X server has no OpenGL GLX extension");

            /*** (3) find an appropriate visual ***/

            /* find an OpenGL-capable RGB visual with depth buffer */
            vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);
            if (vi == NULL) {
                vi = glXChooseVisual(dpy, DefaultScreen(dpy), snglBuf);
                if (vi == NULL) fatalError("no RGB visual with depth buffer");
                doubleBuffer = GL_FALSE;
            }
            if( &vi->class != TrueColor) fatalError("TrueColor visual required for this program");

            /*** (4) create an OpenGL rendering context  ***/
            /* create an OpenGL rendering context */
            cx = glXCreateContext(dpy, vi, /* no shared dlists */ None, /* direct rendering if possible */ GL_TRUE);
            if (cx == NULL) fatalError("could not create rendering context");

            /*** (5) create an X window with the selected visual ***/
            /* create an X colormap since probably not using default visual */
            cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
            swa.colormap = cmap;
            swa.border_pixel = 0;
            swa.event_mask = KeyPressMask | ExposureMask | ButtonPressMask | StructureNotifyMask;
            win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &swa);
            XSetStandardProperties(dpy, win, "main", "main", None, argv, argc, NULL);

            /*** (6) bind the rendering context to the window ***/
            glXMakeCurrent(dpy, win, cx);

            /*** (7) request the X window to be displayed on the screen ***/
            XMapWindow(dpy, win);

            /*** (8) configure the OpenGL context for rendering ***/
        }

        bool CheckHostOSMessages( void ) {
            do {
                XNextEvent(dpy, &event);
                switch (event.type) {
                case KeyPress: {
                        KeySym     keysym;
                        XKeyEvent *kevent;
                        char       buffer[1];
                        /* It is necessary to convert the keycode to a
                        * keysym before checking if it is an escape */
                        kevent = (XKeyEvent *) &event;
                        if (   (XLookupString((XKeyEvent *)&event,buffer,1,&keysym,NULL) == 1) && (keysym == (KeySym)XK_Escape) ) return( true );
                        break;
                    }
                case ButtonPress:
                    recalcModelView = GL_TRUE;
                    switch (event.xbutton.button) {
                        case 1: MouseLeftDown = true; break;
                        case 2: MouseMiddleDown = true; break;
                        case 3: MouseRightDown = true; break;
                    }
                    break;
                case ConfigureNotify:
                    glViewport(0, 0, event.xconfigure.width, event.xconfigure.height);
                    break;
                }
            } while( XPending( dpy ) ); /* loop to compress events */
        }
    };
#endif // LINUXMODULE

/*
int main(int argc, char **argv)
{
  glEnable(GL_DEPTH_TEST); // enable depth buffering
  glDepthFunc(GL_LESS);    // pedantic, GL_LESS is the default
  glClearDepth(1.0);       // pedantic, 1.0 is the default

  // frame buffer clears should be to black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // set up projection transform
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
  // establish initial viewport
  // pedantic, full window size is default viewport
  glViewport(0, 0, 300, 300);

  printf( "Press left mouse button to rotate around X axis\n" );
  printf( "Press middle mouse button to rotate around Y axis\n" );
  printf( "Press right mouse button to rotate around Z axis\n" );
  printf( "Press ESC to quit the application\n" );

  // (9) dispatch X events

  while (1)
  {
    if ( Framework.Linux.CheckHostOSMessages() == true ) exit( 0 );

  }

  return 0;
}

*/
