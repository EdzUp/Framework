/*
    EdzUpFrameworkGlobals.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef _FRAMEWORKGLOBALS
    #define _FRAMEWORKGLOBALS 1
	 #include <string.h>

    float       ambient_red = 0.5f;
    float       ambient_green =0.5f;
    float       ambient_blue =0.5f;

    int			MouseXPos;
    int			MouseYPos;
	bool		MouseLeftDown;
	bool		MouseRightDown;
	bool		MouseMiddleDown;

	int			WIDTH;
	int			HEIGHT;
	float       ActualWidth;
	float       ActualHeight;
	bool		Using3D = false;
	float		ClsRed = 0.0f;
	float		ClsGreen = 0.0f;
	float		ClsBlue = 0.0f;

	bool        AppQuit = false;

	std::string ErrorMessage;
	bool        ErrorSet;

	void SetError( std::string Error ) {
	    ErrorMessage = Error;
	    ErrorSet = true;
	}
#endif // _FRAMEWORKGLOBALS
