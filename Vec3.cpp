/*
    Vec3.cpp class for EdzUp Framework
    Copyright (C)EdzUp
*/

#include "Vec3.h"
#include "GL/gl.h"

Vec3 UpdateMatrix( float MatrixMode ) {
	float Matrix[ 16 ];
	Vec3 Temp;

	glGetFloatv( MatrixMode, Matrix );
	Temp.X =Matrix[ 12 ];
	Temp.Y =Matrix[ 13 ];
	Temp.Z =Matrix[ 14 ];

	return( Temp );
}
