/*
	EdzUp Engine information - Copyright EdzUp 2015

fullscreen opengl system:
Basically it's just resizing the window and specifying flags that the border is invisible.

SetWindowLongPtr(hWnd, GWL_STYLE,
    WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
MoveWindow(hWnd, 0, 0, width, height, TRUE);
to set it back:

RECT rect;
rect.left = 0;
rect.top = 0;
rect.right = width;
rect.bottom = height;
SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
MoveWindow(hWnd, 0, 0, rect.right-rect.left, rect.bottom-rect.top, TRUE);
or for a not-resizable window:

SetWindowLongPtr(hWnd, GWL_STYLE, WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE);
AdjustWindowRect(&rect, WS_CAPTION | WS_POPUPWINDOW, FALSE);
MoveWindow(hWnd, 0, 0, rect.right-rect.left, rect.bottom-rect.top, TRUE);
and then just resize your OpenGL viewport settings.

If you want to set the display mode too, use this:

// change display mode if destination mode is fullscreen
if (fullscreen) {
    DEVMODE dm;
    dm.dmSize = sizeof(DEVMODE);
    dm.dmPelsWidth = width;
    dm.dmPelsHeight = height;
    dm.dmBitsPerPel = bitsPerPixel;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
    success = ChangeDisplaySettings(&dm, 0) == DISP_CHANGE_SUCCESSFUL;
}

// reset display mode if destination mode is windowed
if (!fullscreen)
    success = ChangeDisplaySettings(0, 0) == DISP_CHANGE_SUCCESSFUL;


That answers my question almost perfectly, thank you. However, I have run into another odd problem...
Once I return to windowed mode, I have leftover data from my fullscreen drawing still hanging around.
Nothing I've tried(InvalidateRect(), RedrawWindow(), ChangeDisplaySettings()) seems to work at causing
the screen to repaint itself. (I ended up using ChangeDisplaySettings(&saved, 0) and a workaround of
							using ShowWindow(hwnd, SW_HIDE) just before ChangeDisplaySettings(), except
							the window loses focus for a moment and thus can have its input grabbed by
							some other app. Is there a better option? –  Azuvector Aug 26 '11 at 8:07
4
I found a bit of extra info. Apparently you want to use SetWindowPos() rather than MoveWindow(), when
							using SetWindowLongPtr(). Also, using ChangeDisplaySettings(NULL, 0) AFTER
							resizing my window appears to fix issues with dirty backgrounds

mouse info:
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

    switch( msg ){
		case WM_PAINT:
                        // do some painting
                        break;
                case WM_LBUTTONDOWN:
                        // get the x and y coordinates
                        x = LOWORD(lparam);
                        y = HIWORD(lparam);
                        break;
// more code...

Re: How to get the mouse position ?
Hey FredonMouse! Yup i agree with ya...people are pretty nice on this forum..that's why i love posting here. Now about your problem:

I can help with with your first issue. I don't know glut so i don't know how to answer your second question.

Ok in the WndProc procedure when you are handling each and every message you need to (like WM_CREATE, WM_QUIT, etc.), add in WM_MOUSEMOVE. Whenever your mouse is moved, that message gets pushed on the stack. Ok, the wParam is going to contain the state of the mouse buttons. It can be set to any of the following:

MK_CONTROL Set if the ctrl key is down.
MK_LBUTTON Set if the left mouse button is down.
MK_MBUTTON Set if the middle mouse button is down.
MK_RBUTTON Set if the right mouse button is down.
MK_SHIFT Set if the shift key is down.

LRESULT APIENTRY MainWndProc(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                       // handle to device context
    RECT rcClient;                 // client area rectangle
    POINT ptClientUL;              // client upper left corner
    POINT ptClientLR;              // client lower right corner
    static POINTS ptsBegin;        // beginning point
    static POINTS ptsEnd;          // new endpoint
    static POINTS ptsPrevEnd;      // previous endpoint
    static BOOL fPrevLine = FALSE; // previous line flag

    switch (uMsg)
    {
       case WM_LBUTTONDOWN:

            // Capture mouse input.

            SetCapture(hwndMain);

            // Retrieve the screen coordinates of the client area,
            // and convert them into client coordinates.

            GetClientRect(hwndMain, &rcClient);
            ptClientUL.x = rcClient.left;
            ptClientUL.y = rcClient.top;

            // Add one to the right and bottom sides, because the
            // coordinates retrieved by GetClientRect do not
            // include the far left and lowermost pixels.

            ptClientLR.x = rcClient.right + 1;
            ptClientLR.y = rcClient.bottom + 1;
            ClientToScreen(hwndMain, &ptClientUL);
            ClientToScreen(hwndMain, &ptClientLR);

            // Copy the client coordinates of the client area
            // to the rcClient structure. Confine the mouse cursor
            // to the client area by passing the rcClient structure
            // to the ClipCursor function.

            SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
                ptClientLR.x, ptClientLR.y);
            ClipCursor(&rcClient);

            // Convert the cursor coordinates into a POINTS
            // structure, which defines the beginning point of the
            // line drawn during a WM_MOUSEMOVE message.

            ptsBegin = MAKEPOINTS(lParam);
            return 0;

        case WM_MOUSEMOVE:

            // When moving the mouse, the user must hold down
            // the left mouse button to draw lines.

            if (wParam & MK_LBUTTON)
            {

                // Retrieve a device context (DC) for the client area.

                hdc = GetDC(hwndMain);

                // The following function ensures that pixels of
                // the previously drawn line are set to white and
                // those of the new line are set to black.

                SetROP2(hdc, R2_NOTXORPEN);

                // If a line was drawn during an earlier WM_MOUSEMOVE
                // message, draw over it. This erases the line by
                // setting the color of its pixels to white.

                if (fPrevLine)
                {
                    MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
                        (LPPOINT) NULL);
                    LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
                }

                // Convert the current cursor coordinates to a
                // POINTS structure, and then draw a new line.

                ptsEnd = MAKEPOINTS(lParam);
                MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT) NULL);
                LineTo(hdc, ptsEnd.x, ptsEnd.y);

                // Set the previous line flag, save the ending
                // point of the new line, and then release the DC.

                fPrevLine = TRUE;
                ptsPrevEnd = ptsEnd;
                ReleaseDC(hwndMain, hdc);
            }
            break;

        case WM_LBUTTONUP:

            // The user has finished drawing the line. Reset the
            // previous line flag, release the mouse cursor, and
            // release the mouse capture.

            fPrevLine = FALSE;
            ClipCursor(NULL);
            ReleaseCapture();
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        // Process other messages.


And now if you want to know where the coordinates for the cursor are, you would get them like this:

The x-position of the cursor is retrieved by:

Code :
LOWORD(lParam)
The y-position of the cursor is retrieved by:

Code :
HIWORD(lParam)
So for your purposes, the code might look like this:

Code :

//This is inside the switch statement to handle messages

case WM_MOUSEMOVE:
   // Set the x-coord variable
   xPos = LOWORD(lParam)
   // Set the y-coord variable
   yPos = HIWORD(lParam)

   //finish the case
   break;
Ok to wrap things up, you check for the WM_MOUSEMOVE message and then use LOWORD and HIWORD on the lParam to get the x and y coordinates. The wParam stuff is just if you need it. And actually i THINK that GetCursorPos is supposed to give you the current coordinate...but as to why it isn't i don't know. I hope all this helps. If you have any more questions ask away!

Happy Holidays!

- Halcyon


//==================================================================
#include <windows.h> // defines for POINT, and GetCursorPos().
#include <iostream>
#include <conio.h>
#include <Winuser.h>

//using namespace std;

int main(int argc, char* argv[])
{
SetConsoleTitle("Ajedrez");
HWND hwnd;
for (int i=1;i<20;i++)
hwnd = FindWindow(NULL, "Ajedrez");
HDC hdc = GetDC(hwnd);

POINT aPoint;


while(1)
{
clrscr();
GetCursorPos(&aPoint);
ScreenToClient(hwnd,&aPoint);

cout << "Mouse position (x/y) was: " << aPoint.x << "/" << aPoint.y << endl;
}
getch();
return 0;
}
//===========================================================


DELAY SYSTEM:
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main()
{
  pollingDelay = 100
  //do stuff

  //sleep:
  #ifdef _WIN32
  Sleep(pollingDelay);
  #else
  usleep(pollingDelay*1000);  // sleep for 100 milliSeconds
  #endif

  //do stuff again
  return 0;
}
*/
