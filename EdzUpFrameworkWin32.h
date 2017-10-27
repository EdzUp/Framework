/*
	EdzUpFrameworkWindow32.h - Copyright (C)EdzUp
	Programmed by Ed 'EdzUp' Upton
*/

#include <windows.h>
#include <gl/gl.h>
#include "wtypes.h"
#include <iostream>

#include "EdzUpFramework.h"
#include "EInput.h"

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
//int			MouseXPos;
//int			MouseYPos;
InputClass      Input;

class FrameworkWin32 {
    WNDCLASSEX wcex;
//    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;

    bool		FullScreenView;
    int			Win32Width;
    int			Win32Height;
    int			Win32DesktopWidth;
    int			Win32DesktopHeight;

	public:
	HWND   		hwnd;
	LPCSTR		ProgramName = "Unnamed";
	LPCSTR		ApplicationName = "Unknown";

	int MouseXPosition( void ) {
	    return MouseXPos;
	}

	int MouseYPosition( void ) {
	    return MouseYPos;
	}

	void DisplayError( std::string title, std::string message ) {
		MessageBox( hwnd, message.c_str(), title.c_str(), MB_OK );
	}

	void SetCursor( bool hidden ) {
		if ( hidden == true ){
			while(ShowCursor(false)>=0);
		} else {
			ShowCursor( true );
		}
	}

	void MoveMouse( int x, int y ) {
        POINT pt;

        // you should set pt as a position in your Application
        ClientToScreen(hwnd, &pt);

        // now pt is a screen position
        pt.x =x;
        pt.y =y;
        SetCursorPos(pt.x, pt.y);
	}

	bool CheckInputs( void ) {
//		SHORT WINAPI GetAsyncKeyState( _In_ int vKey );
		return( false );
	}

	bool InFullscreen( void ) {
		return( FullScreenView );
	}

	int WindowWidth( void ){
		return( Win32Width );
	}

	int WindowHeight( void ) {
		return( Win32Height );
	}

	int CurrentWidth( void ) {
	    if ( FullScreenView == true ) {
            return( Win32DesktopWidth );
	    } else {
	        return( Win32Width );
	    }
	    return( 0 );
	}

	int CurrentHeight( void ) {
	    if ( FullScreenView == true ) {
            return( Win32DesktopHeight );
	    } else {
	        return( Win32Height );
	    }
	    return( 0 );
	}

	int DesktopWidth( void ){
		return( Win32DesktopWidth );
	}

	int DesktopHeight( void ) {
		return( Win32DesktopHeight );
	}

	void Fullscreen( void ) {
		//this will allow jumping to fullscreen
		FullScreenView = true;
		SetWindowLongPtr(hwnd, GWL_STYLE, WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
		MoveWindow(hwnd, 0, 0, Win32DesktopWidth, Win32DesktopHeight, TRUE);
		glViewport( 0, 0, Win32DesktopWidth, Win32DesktopHeight );
		ActualWidth = Win32DesktopWidth;
		ActualHeight = Win32DesktopHeight;
	}

	int ChangeResolution( int width, int height, int depth ) {
		int success;

		if ( FullScreenView == true ){
			DEVMODE dm;
			dm.dmSize = sizeof(DEVMODE);
			dm.dmPelsWidth = width;
			dm.dmPelsHeight = height;
			dm.dmBitsPerPel = depth;
			dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
			success = ChangeDisplaySettings(&dm, 0) == DISP_CHANGE_SUCCESSFUL;
		} else {
			success = ChangeDisplaySettings(0, 0) == DISP_CHANGE_SUCCESSFUL;
		}

		return( success );
	}

	void Windowed( int width, int height, bool resizeable = false ) {
		//take back from fullscreen and set window size
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = width;
		rect.bottom = height;

		if ( resizeable == true ) {
			SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
			MoveWindow(hwnd, 0, 0, rect.right-rect.left, rect.bottom-rect.top, TRUE);
		} else {
			SetWindowLongPtr(hwnd, GWL_STYLE, WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE);
			AdjustWindowRect(&rect, WS_CAPTION | WS_POPUPWINDOW, FALSE);
			MoveWindow(hwnd, 0, 0, rect.right-rect.left, rect.bottom-rect.top, TRUE);
		}
		FullScreenView = false;
		glViewport( 0, 0, Win32Width, Win32Height );
		ActualWidth = Win32Width;
		ActualHeight = Win32Height;
	}

	HWND MakeWindow( int width, int height, HINSTANCE Hin, int show ) {
		/* register window class */
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_OWNDC;
		wcex.lpfnWndProc = WindowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = Hin;
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = ProgramName;
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wcex))
			return 0;

		Win32Width = width;
		Win32Height = height;
		ActualWidth = Win32Width;
		ActualHeight = Win32Height;

		/* create main window */
		hwnd = CreateWindowEx(0,
							ProgramName,
							ApplicationName,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							width,
							height,
							NULL,
							NULL,
							Hin,
							NULL);

		ShowWindow( hwnd, show );

		RECT desktop;
		// Get a handle to the desktop window
		const HWND hDesktop = GetDesktopWindow();
		// Get the size of screen to the variable desktop
		GetWindowRect(hDesktop, &desktop);
		// The top left corner will have coordinates (0,0)
		// and the bottom right corner will have coordinates
		// (horizontal, vertical)
		Win32DesktopWidth = desktop.right;
		Win32DesktopHeight = desktop.bottom;

		return( hwnd );
	}

	void Flip( void ){
		SwapBuffers(hDC);
	}

	bool CheckHostOSMessages( void ) {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                AppQuit = true;
            	return( true );
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        return( false );
	}

	void SetApplicationDetails( LPCSTR Prog, LPCSTR App ) {
		//this sets up to application details so we can use it
		ProgramName = Prog;
		ApplicationName = App;
	}

	void SetHWND( HWND winhwnd ) {
		//used to sort some errors and for shutdown purposes
		hwnd = winhwnd;
	}

	void EnableOpenGL( void ) //HDC* hDC, HGLRC* hRC )
	{
		PIXELFORMATDESCRIPTOR pfd;

		int iFormat;

		/* get the device context (DC) */
		hDC = GetDC(hwnd);

		/* set the pixel format for the DC */
		ZeroMemory(&pfd, sizeof(pfd));

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW |
					PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 16;
		pfd.iLayerType = PFD_MAIN_PLANE;

		iFormat = ChoosePixelFormat(hDC, &pfd);

		SetPixelFormat(hDC, iFormat, &pfd);

		/* create and enable the render context (RC) */
		hRC = wglCreateContext(hDC);

		wglMakeCurrent(hDC, hRC);
	}

	void DisableOpenGL ( HDC hDC, HGLRC hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hwnd, hDC);
	}

	int Shutdown( void ) {
	    DisableOpenGL( hDC, hRC);

		/* destroy the window explicitly */
		DestroyWindow(hwnd);

		return( msg.wParam );
	}

	void KeyDown( WPARAM wParam ) {
//	    printf( "%i is pressed", wParam );
        keybank[ wParam ] = true;
	}

	void KeyUp( WPARAM wParam ) {
	    keybank[ wParam ] = false;
	}
};

FrameworkWin32 Entry;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_RBUTTONDOWN:
			MouseRightDown = true;
		break;
		case WM_RBUTTONUP:
			MouseRightDown = false;
		break;
		case WM_MBUTTONDOWN:
			MouseMiddleDown = true;
		break;
		case WM_MBUTTONUP:
			MouseMiddleDown = false;
		break;
		case WM_LBUTTONDOWN:
			MouseLeftDown = true;
		break;
		case WM_LBUTTONUP:
			MouseLeftDown = false;
		break;
		case WM_MOUSEMOVE:
			// get the x and y coordinates
			MouseXPos = LOWORD(lParam);
			MouseYPos = HIWORD(lParam);
		break;
		case WM_CLOSE:
			PostQuitMessage(0);
		break;

		case WM_DESTROY:
			return 0;

        case WM_KEYUP:
            Entry.KeyUp( wParam );
            break;

        case WM_KEYDOWN:
//		case WM_KEYDOWN:
		{
		    Entry.KeyDown( wParam );    //make sure key is setup
		    if ( Input.KeyDown( KEY_ESCAPE ) == true ) {
                PostQuitMessage( 0 );
		    }
		}
		break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

/*
// The Matrix  falling numbers

#include <iostream>
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
using namespace std;


#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
#define KB_F8 66


// Variables

char screen_buffer[2000]={' '};
int y_coord[2000]={0};
int x=0, y=0,dy=0;
int XMAX=77;
int YMAX=23;
int KB_code=0;
bool QuitGame=false;
int platformX=35, platformY=23;

// function prototypes

void gotoxy(int x, int y);
void clrscr(void);
void setcolor(WORD color);
void simple_keyboard_input();
void draw_falling_numbers();
void draw_platform();

//  main

int main(void)
{
  // generate random seed
  srand ( time(NULL) );

  // generate random number
  for(int i=0;i<XMAX;i++) y_coord[i]=   rand() % YMAX;

  while(!QuitGame)
  {
      // simple keyboard input
      simple_keyboard_input();

      // draw falling numbers
      draw_falling_numbers();

  }

  // restore text color
  setcolor(7);
  clrscr( );
  cout<<" \n";

  cout<<" \nPress any key to continue\n";
  cin.ignore();
  cin.get();

   return 0;
}

// functions

void draw_falling_numbers()
{

    for(x=0;x<=XMAX;x++)
    {
        // generate random number
        int MatixNumber=rand() % 2 ;

        // update falling number
        y_coord[x]=y_coord[x]+1;

        if (y_coord[x]>YMAX) y_coord[x]=0;

        // draw dark color
        setcolor(2);
        gotoxy(x ,y_coord[x]-1); cout<<"  "<<MatixNumber<<"   ";

        // draw light color
        setcolor(10);
        gotoxy(x ,y_coord[x]); cout<<"  "<<MatixNumber<<"   ";
    }
    // wait some milliseconds
    Sleep(50);
    //clrscr( );
}


void draw_platform()
{
  setcolor(7);
 gotoxy(platformX ,platformY);cout<<"       ";

 gotoxy(platformX ,platformY);cout<<"ÜÜÜÜÜÜ";
 setcolor(7);
 Sleep(5);
}




void simple_keyboard_input()
{
    if (kbhit())
      {
            KB_code = getch();
            //cout<<"KB_code = "<<KB_code<<"\n";

            switch (KB_code)
            {

                case KB_ESCAPE:

                    QuitGame=true;

                break;

                case KB_LEFT:
                           //Do something
                    platformX=platformX-4;if(platformX<3) platformX=3;
                break;

                case KB_RIGHT:
                           //Do something
                    platformX=platformX+4;if(platformX>74) platformX=74;
                break;

                case KB_UP:
                           //Do something
                break;

                case KB_DOWN:
                           //Do something
                break;

            }

      }

}


void setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    return;
}


void gotoxy(int x, int y)
{
  static HANDLE hStdout = NULL;
  COORD coord;

  coord.X = x;
  coord.Y = y;

  if(!hStdout)
  {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  }

  SetConsoleCursorPosition(hStdout,coord);
}


void clrscr(void)
{
  static HANDLE hStdout = NULL;
  static CONSOLE_SCREEN_BUFFER_INFO csbi;
  const COORD startCoords = {0,0};
  DWORD dummy;

  if(!hStdout)
  {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout,&csbi);
  }

  FillConsoleOutputCharacter(hStdout,
                             ' ',
                             csbi.dwSize.X * csbi.dwSize.Y,
                             startCoords,
                             &dummy);
  gotoxy(0,0);
}
*/
