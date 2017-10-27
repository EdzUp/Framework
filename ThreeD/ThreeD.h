/*
    ThreeD.h - Copyright (C)EdzUp and Simon Harrison
    Programmed by Ed 'EdzUp' Upton and Simon Harrison
*/

#ifndef THREED
    #define THREED

	#include <GL/gl.h>
	#include <math.h>
	#include <vector>
	#include "inc/Matrix.h"
	#include "inc/TGlobal.h"
	#include "inc/EntityRenderClass.h"
	#include "inc/TEntity.h"
	#include "inc/TCamera.h"
//    #include "../EdzUpFramework.h"

//    #include "inc/TGlobal.h"
    class ThreeDClass {
        float Width;
        float Height;

        float rtri = 0.0f;
        float rquad = 0.0f;

        void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar ) {
            const GLdouble pi = 3.1415926535897932384626433832795;
            GLdouble fW, fH;

            //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
            fH = tan( fovY / 360 * pi ) * zNear;
            fW = fH * aspect;

            glFrustum( -fW, fW, -fH, fH, zNear, zFar );
        }

    public:
        EFCamera            *Camera;
        TEntityRenderClass  Renderer;
        Entity              EntityEntry;

        void Initialise3D( float width, float height, EFCamera Entry ) {
            //configure OpenGL for 3d rendering
            Camera = &Entry;

            Width = width;
            Height = height;

            glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
            glEnable(GL_DEPTH_TEST); /* enable depth buffering */
            //glDepthFunc(GL_LESS);    /* pedantic, GL_LESS is the default */
            glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
            glClearDepth(1.0);       /* pedantic, 1.0 is the default */
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

            /* set up projection transform */
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            // Calculate The Aspect Ratio Of The Window
            perspectiveGL( 45.0f, (GLfloat)Width /(GLfloat)Height, (GLfloat)Camera->CameraNear, (GLfloat)Camera->CameraFar );
        }

        void Begin3d( void ){
            glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
            glLoadIdentity();									// Reset The Projection Matrix
            glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
            glClearDepth(1.0);       /* pedantic, 1.0 is the default */
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
            // Calculate The Aspect Ratio Of The Window
            perspectiveGL( 45.0f, (GLfloat)Width /(GLfloat)Height, (GLfloat)Camera->CameraNear, (GLfloat)Camera->CameraFar );

//            Camera->UpdateCamera();                              //update the 3d camera

            glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
            glLoadIdentity();									// Reset The Modelview Matrix
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glEnable( GL_TEXTURE_2D );
            glEnableClientState (GL_TEXTURE_COORD_ARRAY);						//Enable texturing
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable( GL_BLEND );
            glEnable( GL_DEPTH_TEST );
        }

        void End3d( void ){
            glDisable( GL_DEPTH_TEST );
            glDisable( GL_BLEND );
            glDisableClientState (GL_TEXTURE_COORD_ARRAY);
            glDisable( GL_TEXTURE_2D );
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
            glPopMatrix();
        }

        void RenderWorld( void ) {
            Renderer.RenderWorld();
        }

        void UpdateWorld( void ) {
            Renderer.UpdateWorld();
        }

        int TestRender( void )									// Here's Where We Do All The Drawing
        {
            glDisable( GL_TEXTURE_2D );

            glLoadIdentity();									// Reset The Current Modelview Matrix
            glTranslatef(1.5f,0.0f,-7.0f);						// Move Right 1.5 Units And Into The Screen 7.0
            glRotatef(rquad,1.0f,1.0f,1.0f);					// Rotate The Quad On The X axis ( NEW )
            glBegin(GL_QUADS);									// Draw A Quad
                glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Blue
                glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Top)
                glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Top)
                glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Top)
                glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)

                glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
                glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Bottom)
                glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
                glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Bottom)
                glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Bottom)

                glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
                glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Front)
                glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Front)
                glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Front)
                glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Front)

                glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
                glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Back)
                glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Back)
                glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Back)
                glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Back)

                glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
                glVertex3f(-1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Left)
                glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Left)
                glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Left)
                glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Left)

                glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
                glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Right)
                glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Right)
                glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
                glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Right)
            glEnd();											// Done Drawing The Quad
            glFlush();
            glEnable( GL_TEXTURE_2D );

            rtri+=0.2f;											// Increase The Rotation Variable For The Triangle ( NEW )
            rquad-=0.15f;										// Decrease The Rotation Variable For The Quad ( NEW )
            return( true );										// Keep Going
        }
    };
#endif // THREEDMINIB3D

/*
' global
Include "inc/TGlobal.bmx"
Include "inc/TScenegraph.bmx"

' entity
Include "inc/TEntity.bmx"
Include "inc/TCamera.bmx"
Include "inc/TLight.bmx"
Include "inc/TPivot.bmx"
Include "inc/TMesh.bmx"
Include "inc/TSprite.bmx"
Include "inc/TBone.bmx"
Include "inc/TTerrain.bmx"

' mesh structure
Include "inc/TSurface.bmx"
Include "inc/TTexture.bmx"
Include "inc/TBrush.bmx"
Include "inc/TAnimation.bmx"
Include "inc/TModel.bmx"
Include "inc/T3DSLoader.bmx"

' picking/collision
Include "inc/TColTree.bmx"
Include "inc/TPick.bmx"
Include "inc/TCollision.bmx"

' geom
Include "inc/TVector.bmx"
Include "inc/TMatrix.bmx"
Include "inc/TQuaternion.bmx"
Include "inc/BoxSphere.bmx"

' misc
Include "inc/THardwareInfo.bmx"
Include "inc/TBlitz2D.bmx"
Include "inc/TUtility.bmx"
Include "inc/TDebug.bmx"

' data
Include "inc/data.bmx"

' functions
Include "inc/functions.bmx"

Extern

	Function C_UpdateNormals(no_tris:Int,no_verts:Int,tris:Short Ptr,vert_coords:Float Ptr,vert_norms:Float Ptr) ' used by TMesh.bmx

	Function C_NewMeshInfo:Byte Ptr()
	Function C_DeleteMeshInfo(mesh_info:Byte Ptr)
	Function C_AddSurface(mesh_info:Byte Ptr,no_tris:Int,no_verts:Int,tris:Short Ptr,verts:Float Ptr,surf:Int)
	Function C_AddTriangle(mesh_info:Byte Ptr,index:Int,v0:Short,v1:Short,v2:Short,surf:Int)
	Function C_AddVertex(mesh_info:Byte Ptr,x:Float,y:Float,z:Float,surf:Int)

	Function C_CreateColTree:Byte Ptr(mesh_info:Byte Ptr)
	Function C_DeleteColTree(col_tree:Byte Ptr)

	Function C_CreateCollisionInfoObject:Byte Ptr(vec_a:Byte Ptr,vec_b:Byte Ptr,vec_radius:Byte Ptr)
	Function C_UpdateCollisionInfoObject(col_info:Byte Ptr,dst_radius:Float,ax:Float,ay:Float,az:Float,bx:Float,by:Float,bz:Float)
	Function C_DeleteCollisionInfoObject(col_info:Byte Ptr)

	Function C_CreateCollisionObject:Byte Ptr()
	Function C_DeleteCollisionObject(coll:Byte Ptr)

	Function C_Pick:Int(col_info:Byte Ptr,line:Byte Ptr,radius:Float,coll:Byte Ptr,dst_tform:Byte Ptr,mesh_col:Byte Ptr,pick_geom:Int)

	Function C_CollisionDetect:Int(col_info:Byte Ptr,coll:Byte Ptr,tform:Byte Ptr,col_tree:Byte Ptr,method_no:Int)
	Function C_CollisionResponse:Int(col_info:Byte Ptr,coll:Byte Ptr,response:Int)
	Function C_CollisionFinal:Int(col_info:Byte Ptr)

	Function C_CollisionPosX:Float()
	Function C_CollisionPosY:Float()
	Function C_CollisionPosZ:Float()
	Function C_CollisionX:Float()
	Function C_CollisionY:Float()
	Function C_CollisionZ:Float()
	Function C_CollisionNX:Float()
	Function C_CollisionNY:Float()
	Function C_CollisionNZ:Float()
	Function C_CollisionTime:Float()
	Function C_CollisionSurface:Int()
	Function C_CollisionTriangle:Int()

	Function C_CreateVecObject:Byte Ptr(x:Float,y:Float,z:Float)
	Function C_DeleteVecObject(v:Byte Ptr)
	Function C_UpdateVecObject(vec:Byte Ptr,x:Float,y:Float,z:Float)
	Function C_VecX:Float(vec:Byte Ptr)
	Function C_VecY:Float(vec:Byte Ptr)
	Function C_VecZ:Float(vec:Byte Ptr)

	Function C_CreateLineObject:Byte Ptr(ox:Float,oy:Float,oz:Float,dx:Float,dy:Float,dz:Float)
	Function C_DeleteLineObject(line:Byte Ptr)
	Function C_UpdateLineObject(line:Byte Ptr,ox:Float,oy:Float,oz:Float,dx:Float,dy:Float,dz:Float)

	Function C_CreateMatrixObject:Byte Ptr(vec_i:Byte Ptr,vec_j:Byte Ptr,vec_k:Byte Ptr)
	Function C_DeleteMatrixObject(mat:Byte Ptr)
	Function C_UpdateMatrixObject(mat:Byte Ptr,vec_i:Byte Ptr,vec_j:Byte Ptr,vec_k:Byte Ptr)

	Function C_CreateTFormObject:Byte Ptr(mat:Byte Ptr,vec_v:Byte Ptr)
	Function C_DeleteTFormObject(tform:Byte Ptr)
	Function C_UpdateTFormObject(tform:Byte Ptr,mat:Byte Ptr,vec_v:Byte Ptr)

End Extern

Const USE_MAX2D=True	' true to enable max2d/minib3d integration
Const USE_VBO=False	 	' true to use vbos if supported by hardware
Const VBO_MIN_TRIS=250	' if USE_VBO=True and vbos are supported by hardware, then surface must also have this minimum no. of tris before vbo is used for surface (vbos work best with surfaces with high amount of tris)
Const LOG_NEW=False	' true to write to debuglog when new minib3d object created
Const LOG_DEL=False	' true to write to debuglog when minib3d object destroyed
Const FIX_BRAM=True	' true to disable specular problems
*/
