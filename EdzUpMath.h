/*
 *  EdzUpEngineMath.h - Copyright (C)EdzUp
 *  Programmed by Ed 'EdzUp' Upton
 */

#ifndef EdzUpMathDef
    #define EdzUpMathDef
    # define M_PI           3.14159265358979323846  /* pi */

    #include <math.h>
    #include <stdlib.h>
    # include <cmath>

    class EdzUpMathClass  {
        public:
        double pi180;
        //pi/180

        void Initialise( void ) {
            pi180 = 0.017453292519943295769236907584886;
        }

        double ESin( double value ) {
            return( sin( value * (3.1415 / 180) ) );
        }

        double ECos( double value ) {
            return( cos( value * (3.1415 / 180) ) );
        }

        //replacement for gluPerspective
        void SetPerspective( GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar ){
            GLdouble top, bottom, left, right;

            top = zNear *tan( pi180 *fovy /2 );
            bottom = -top;
            right = aspect *top;
            left = -right;

            glMatrixMode( GL_PROJECTION );
            glLoadIdentity();
            glFrustum( left, right, bottom, top, zNear, zFar );
            glMatrixMode( GL_MODELVIEW );
        }

        void EEPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
        {
        /*   GLdouble xmin, xmax, ymin, ymax;

            ymax = zNear * tan(fovy * M_PI / 360.0);
            ymin = -ymax;
            xmin = ymin * aspect;
            xmax = ymax * aspect;

            glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);*/
        }

        //----------------------------------------------------------------------------------------------------
        float AngleDistance( float CurrentAngle, float NewAngle ) {
            //returns the distance between two angles
            float Temp;

            Temp = NewAngle -CurrentAngle;

            return( Temp +( ( Temp < -180.0f ) - ( Temp > 180.0f ) ) *360.0f );
        }

        //----------------------------------------------------------------------------------------------------
        float Distance( float x, float y, float z, float x2, float y2, float z2 ){
            //distance Function a very useful Function indeed.
            float value;

            value =sqrt( ( x -x2 ) *( x -x2 ) +( y -y2 ) *( y -y2 ) +( z -z2 ) *( z -z2 ) );

            return( value );
        }

        //----------------------------------------------------------------------------------------------------
        float FindAngle( float x1, float y1, float x2, float y2 ) {
            //returns the angle To a target
            return( ( ( atan2( y2 - y1, x2 -x1 ) * 180.0f/3.14159265f )-90.0f ) +180.0f );
        }

        /*
float getAngle (float x1,float y1,float z1,float x2,float y2,float z2)
{
    float theta = atan2(z1-z2,x1-x2);
    return -theta*180/3.1415926;
}
float getAngle2 (float x1,float y1,float z1,float x2,float y2,float z2)
{
    float dist=sqrt(pow(x1 - x2,2) + pow(y1 - y2,2) + pow(z1 - z2,2));
    float dist2=sqrt(pow(x1 - x2,2) + pow(z1 - z2,2));
    return acos(dist2/dist)*180/3.1415926;
}

        */
        bool InOval( float x, float y, float ox, float oy, float w, float h ) {
            float dx = ( x -ox ) /w;
            float dy = ( y -oy ) /h;

            if ( dx *dx + dy *dy <1 ) {
                return( true );
            }

            return( false );
        }

        bool InOvalold( double x, double y, double ox, double oy, double w, double h ) {
            double dx = ( x -ox ) /w;
            double dy = ( y -oy ) /h;

            if (( dx *dx ) +( dy *dy ) <1.0f ) {
                return( true );
            }

            return( false );
        }

        //----------------------------------------------------------------------------------------------------
        float DisplayRatio( long Size, long Required ) {
            //Function To Return the percentage of a particular calculation
            if ( Size == 0 ) return( 0 );

            return( (float)Required /( (float)Size /100.0f) );
        }

        //----------------------------------------------------------------------------------------------------
        float Percentage( long MaxValue, long CurrentValue ) {
            long Per;

            Per =MaxValue /100.0f;

            if ( CurrentValue == MaxValue ) return( 100.0f );
            if ( Per <= 0 ) return( 0 );

            return( (float)( CurrentValue /Per ) );
        }
    };
#endif
