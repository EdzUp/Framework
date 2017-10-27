//
//   Vec3.h - Copyright ©EdzUp
//   programmed by Ed 'EdzUp' Upton
//

/*
SetGraphicsDriver GLGraphicsDriver()
Graphics 800,600

' Do all model rotating and translation code here :-
glMatrixMode(GL_MODEL_VIEW)
glLoadIdentity()
glRotatef( 45.0, 0.0, 1.0, 0.0 )
glTranslatef( 1.0, 0.0, 0.0 )

Local Matrix#[16]
glGetFloatv(GL_MODELVIEW_MATRIX,Matrix)

' Final translation will be:-
' X : Matrix[12]
' Y : Matrix[13]
' Z : Matrix[14]


'Display the model matrix contents
For Local i = 0 Until 16
Print Matrix[i]
Next

Matrix elements [12,13,14] are the X,Y,Z for your Translation that you want.
*/

#ifndef VECTOR_CLASSES
    #define VECTOR_CLASSES

    class Colour {
		public:
		float	Red;
		float	Green;
		float 	Blue;
		float	Alpha;
    };

    class Vec3Quat {        //Quaternion call
    public:
        double w;
        double x;
        double y;
        double z;
    };

    class Vec3r {      //rotation vector
        public:
        double Pitch;
        double Yaw;
        double Roll;
    };

    class Vec3 {      //positional vector
        public:
        double X;
        double Y;
        double Z;
    };

    class VecVertex {
        public:
        float X;
        float Y;
        float Z;

        float U;
        float V;
        float W;

        float Red;
        float Green;
        float Blue;
        float Alpha;
    };

    class VecRGBA {    //RGBA graphics
        public:
        float Red;
        float Green;
        float Blue;
        float Alpha;
    };

    class VecUV {
    public:
        float U;
        float V;
        float W;
    };

    class VecTri {
    public:
        long One;
        long Two;
        long Three;
    };

    Vec3 UpdateMatrix( float MatrixMode );
#endif
