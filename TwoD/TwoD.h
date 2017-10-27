//
//	TwoD.h - Copyright (C)EdzUp
//	Programmed by Ed 'EdzUp' Upton
//

#ifndef Framework2D
	#define Framework2D
	#include "../EdzUpFramework.h"
    #include "../ETexture.h"           //need texture system for texture references
    #include "../Vec3.h"               //vector class required for the whole system to use in the game engine
    #include "../EDebug.h"				//for debugging data

	class TwoDClass {
		float		DrawAngle;
		float		DrawScaleX, DrawScaleY;
		Colour		DrawColor;
		float Colors[24] = { 1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f };
		float Vertices[18] = {-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f };
		float TextureUV[12] = {0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f};

		public:
		    void Plot( float x, float y ) {
		        float Colours[ 4 ];
		        Colours[ 0 ] = DrawColor.Red;
		        Colours[ 1 ] = DrawColor.Green;
		        Colours[ 2 ] = DrawColor.Blue;
		        Colours[ 3 ] = DrawColor.Alpha;

		        float plots[ 3 ];
		        plots[ 0 ] = x;
		        plots[ 1 ] = y;
		        plots[ 2 ] = 0.0f;

		        glDisable( GL_TEXTURE );
                glLoadIdentity();
                glTranslatef( x, y, 0.0 );
                glRotatef( 0.0f, 0.0f, 0.0f, 1.0f );
                glColorPointer(4, GL_FLOAT, 0, Colours );
                glVertexPointer(3, GL_FLOAT, 0, plots );
                glDrawArrays(GL_POINTS, 0, 3);
		        glEnable( GL_TEXTURE );
		    }

		    void DrawLine( float x, float y, float x1, float y1 ) {
		        float Colours[ 8 ];
		        Colours[ 0 ] = DrawColor.Red;
		        Colours[ 1 ] = DrawColor.Green;
		        Colours[ 2 ] = DrawColor.Blue;
		        Colours[ 3 ] = DrawColor.Alpha;
		        Colours[ 4 ] = DrawColor.Red;
		        Colours[ 5 ] = DrawColor.Green;
		        Colours[ 6 ] = DrawColor.Blue;
		        Colours[ 7 ] = DrawColor.Alpha;
		        float plots[ 6 ];
		        plots[ 0 ] = x;
		        plots[ 1 ] = y;
		        plots[ 2 ] = 0.0f;
		        plots[ 3 ] = x1;
		        plots[ 4 ] = y1;
		        plots[ 5 ] = 0.0f;

		        glDisable( GL_TEXTURE );
                glLoadIdentity();
                glTranslatef( x, y, 0.0 );
                glRotatef( 0.0f, 0.0f, 0.0f, 1.0f );
                glColorPointer(4, GL_FLOAT, 0, Colours );
                glVertexPointer(3, GL_FLOAT, 0, plots );
                glDrawArrays(GL_LINE, 0, 3);
		        glEnable( GL_TEXTURE );
		    }


/*
	void DrawRect( float x0, float y0, float x1, float y1, float tx, float ty ) {
		glBegin( GL_QUADS );
		glVertex2f( x0*ix+y0*iy+tx,x0*jx+y0*jy+ty );
		glVertex2f x1*ix+y0*iy+tx,x1*jx+y0*jy+ty
		glVertex2f x1*ix+y1*iy+tx,x1*jx+y1*jy+ty
		glVertex2f x0*ix+y1*iy+tx,x0*jx+y1*jy+ty
		glEnd
    }
/*
	Method DrawOval( x0#,y0#,x1#,y1#,tx#,ty# )

		Local xr#=(x1-x0)*.5
		Local yr#=(y1-y0)*.5
		Local segs=Abs(xr)+Abs(yr)

		segs=Max(segs,12)&~3

		x0:+xr
		y0:+yr

		DisableTex
		glBegin GL_POLYGON
		For Local i=0 Until segs
			Local th#=i*360#/segs
			Local x#=x0+Cos(th)*xr
			Local y#=y0-Sin(th)*yr
			glVertex2f x*ix+y*iy+tx,x*jx+y*jy+ty
		Next
		glEnd

	End Method
*/

		void Initialise( void ) {
			DrawAngle = 0.0f;
			DrawScaleX = 1.0f;
			DrawScaleY = 1.0f;
			DrawColor.Red = 1.0f;
			DrawColor.Green = 1.0f;
			DrawColor.Blue = 1.0f;
			DrawColor.Alpha = 1.0f;
		}

		void Begin2d( void ){
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1.0f, 1.0, 1.0, -1.0f, 0.0f, 1.0f);
            glPushMatrix();
            glMatrixMode( GL_MODELVIEW );
            glLoadIdentity();
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glEnable( GL_TEXTURE_2D );
			glEnableClientState (GL_TEXTURE_COORD_ARRAY);						//Enable texturing
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable( GL_BLEND );
			glDisable( GL_DEPTH_TEST );
		}

		void End2d( void ){
			glEnable( GL_DEPTH_TEST );
			glDisable( GL_BLEND );
			glDisableClientState (GL_TEXTURE_COORD_ARRAY);
			glDisable( GL_TEXTURE_2D );
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
            glPopMatrix();
		}

		void PasteImage( ETexture Image, float X, float Y ) {
			//vert data for glDrawArray stuff
			glLoadIdentity();
			glTranslatef( X, Y, 0.0 );
            glRotatef(DrawAngle, 0.0f, 0.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, Image.Texture );					//bind the Player ship texture
			glColorPointer(4, GL_FLOAT, 0, Colors);
			glVertexPointer(3, GL_FLOAT, 0, Vertices);
			glTexCoordPointer(2, GL_FLOAT, 0, TextureUV);						//setup UV's
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		void SetScale( float newScaleX, float newScaleY ) {
			float nSX = 1.0f *newScaleX;
			float nSY = 1.0f *newScaleY;
			Vertices[ 0 ] = -nSX;
			Vertices[ 1 ] = nSY;
			//0.0
			Vertices[ 3 ] = nSX;
			Vertices[ 4 ] = nSY;
			//0.0
			Vertices[ 6 ] = nSX;
			Vertices[ 7 ] = -nSY;
			//0.0
			Vertices[ 9 ] = -nSX;
			Vertices[ 10 ] = -nSY;
			//0.0
			Vertices[ 12 ] = -nSX;
			Vertices[ 13 ] = nSY;
			//0.0
			Vertices[ 15 ] = nSX;
			Vertices[ 16 ] = -nSY;
			//0.0
		}

		void SetRotation( float newAngle ) {
			//sets the rotation of all new drawing images
			DrawAngle = newAngle;
		}

		void SetColor( float Red, float Green, float Blue, float Alpha =1.0f ){
			DrawColor.Red = Red;
			DrawColor.Green = Green;
			DrawColor.Blue = Blue;
			DrawColor.Alpha = Alpha;

			for ( int ncol=0; ncol<24; ncol+=4 ){
				Colors[ ncol ] = Red;
				Colors[ ncol +1 ] = Green;
				Colors[ ncol +2 ] = Blue;
				Colors[ ncol +3 ] = Alpha;
			}
		}
	};
#endif // Framework2D
