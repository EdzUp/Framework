/*
    ERender.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef ERenderSetup
    #define ERenderSetup            //so its not called LOADS of times

    #include <vector>
    #include "EEntity.h"
    #include "ETexture.h"           //need texture system for texture references
    #include "Vec3.h"               //vector class required for the whole system to use in the game engine
    #include "EDebug.h"				//for debugging data

    using namespace std;

    class EntityData {
    	public:
    	long				Id;
    	GLuint				Texture;
    	Vec3				Position;
    	Vec3				Rotation;
    	vector<Vec3>		VertexCoords;
    	vector<int>			TriangleIndices;
    	vector<Vec3>		VertexNormals;
    	vector<VecRGBA>		ColourCoords;
    	vector<VecUV>		TextureCoords;
    	bool				BackFaceCulling;

    	void AddVertex( float x, float y, float z ) {
    		//Add a vertex to the vertex list for processing
    		Vec3		Temp;

    		Temp.x = x;
    		Temp.y = y;
    		Temp.z = z;
    		VertexCoords.push_back( Temp );
    	}

    	void AddNormals( float x, float y, float z ) {
    		//Add a vertex to the vertex list for processing
    		Vec3		Temp;

    		Temp.x = x;
    		Temp.y = y;
    		Temp.z = z;
    		VertexNormals.push_back( Temp );
    	}

    	void AddColour( float Red, float Green, float Blue, float Alpha ) {
    		//Add a colour to the vector for ColourCoords
    		VecRGBA		Temp;

    		Temp.Alpha = Alpha;
    		Temp.Red = Red;
    		Temp.Green = Green;
    		Temp.Blue = Blue;

    		ColourCoords.push_back( Temp );
    	}

    	void AddTextureUVW( float U, float V, float W ) {
    		VecUV		Temp;

    		Temp.U = U;
    		Temp.V = V;
    		Temp.W = W;

    		TextureCoords.push_back( Temp );
    	}

    	void AddTriangle( int vert1, int vert2, int vert3 ) {
    		TriangleIndices.push_back( vert1 );
    		TriangleIndices.push_back( vert2 );
    		TriangleIndices.push_back( vert3 );
    	}

    	void CreateNew( long CNId, ETexture CNTexture ) {
    		//create a new quad entry
    		Id = CNId;
    		Texture = CNTexture.Texture;
    		BackFaceCulling = false;

    		Position.x = 0.0f;
    		Position.y = 0.0f;
    		Position.z = 0.0f;

    		Rotation.x = 0.0f;
    		Rotation.y = 0.0f;
    		Rotation.z = 0.0f;
    	}
    };

    class EdzUpRenderClass {
    	long				NextId;					//this is the Id of the next one
    	vector<EntityData>	Entity;					//this is the list of data that is in the current scene

    public:
		long CreateQuad( ETexture Image, float x, float y, float z ) {
			//this will basically create a quad with the relevant data
			EntityData		Temp;

			//create new texture entry
			Temp.CreateNew( NextId, Image );

			//now we need to make the quad
			Temp.AddVertex( x-0.5f, y+0.5f, z );
			Temp.AddNormals( 0.0f, 0.0f, 1.0f );
			Temp.AddColour( 1.0f, 1.0f, 1.0f, 1.0f );
			Temp.AddVertex( x-0.5f, y-0.5f, z );
			Temp.AddNormals( 0.0f, 0.0f, 1.0f );
			Temp.AddColour( 1.0f, 1.0f, 1.0f, 1.0f );
			Temp.AddVertex( x+0.5f, y-0.5f, z );
			Temp.AddNormals( 0.0f, 0.0f, 1.0f );
			Temp.AddColour( 1.0f, 1.0f, 1.0f, 1.0f );
			Temp.AddVertex( x+0.5f, y+0.5f, z );
			Temp.AddNormals( 0.0f, 0.0f, 1.0f );
			Temp.AddColour( 1.0f, 1.0f, 1.0f, 1.0f );

			//set the texture UV's
			Temp.AddTextureUVW( 1, 1, 0 );
			Temp.AddTextureUVW( 1, 0, 0 );
			Temp.AddTextureUVW( 0, 0, 0 );
			Temp.AddTextureUVW( 0, 1, 0 );

			Temp.AddTriangle( 0, 1, 2 );
			Temp.AddTriangle( 2, 3, 0 );

			Temp.BackFaceCulling = true;

			Entity.push_back( Temp );			//add it to the render queue

			NextId++;

			return( NextId -1 );
		}

		void UpdateWorld( void ) {
			//this will update the render loop
		}

		void RenderWorld( void ) {
			//this will run through the entire EEntity vector and then add the items that are
			//shown so that this entire engine will render each scene and allow the entire project
			//to move forwards and allow for loads of diffrent entities to be rendered on screen at
			//once
			/*
		QTemp.Surface[ TSurf ].AddVertex( -1.0, 1.0, 0.0, 0.0, 0.0 )
		QTemp.Surface[ TSurf ].AddVertex( -1.0, -1.0, 0.0, 0.0, 1.0 )
		QTemp.Surface[ TSurf ].AddVertex( 1.0, -1.0, 0.0, 1.0, 1.0 )
		QTemp.Surface[ TSurf ].AddVertex( 1.0, 1.0, 0.0, 1.0, 0.0 )
		QTemp.Surface[ TSurf ].AddTriangle( 0, 1, 2 )
		QTemp.Surface[ TSurf ].AddTriangle( 2, 3, 1 )
			*/
			float vertexs[] = { -1.0, 1.0, 0.5, -1.0, -1.0, 0.5, 1.0, -1.0, 0.5, 1.0, 1.0, 0.5 };
			int indices[] = { 0, 1, 2, 2, 3, 1 };

			glColor3f( 1.0, 1.0, 1.0 );
			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();
			glVertexPointer( 3, GL_FLOAT, 0, &vertexs );
			glDrawElements( GL_POINTS, 6, GL_UNSIGNED_SHORT, &indices );
			glPopMatrix();
			glMatrixMode( GL_PROJECTION );
			glFlush();
/*
        //Clear color buffer
        glEnable( GL_TEXTURE_2D );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //Render quad
        glPushMatrix();
//        glBindTexture( GL_TEXTURE_2D, tex );
		glTranslatef( 0.5, 0.0, 0.0 );
        glBegin( GL_QUADS );
            glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -0.5f, -0.5f, 0.5f );
            glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  0.5f, -0.5f, 0.5f );
            glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  0.5f,  0.5f, 0.5f );
            glTexCoord2d( 0.0f, 0.0f ); glVertex3f( -0.5f,  0.5f, 0.5f );
        glEnd();
        glPopMatrix();
        glDisable( GL_TEXTURE_2D );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glPopMatrix();
*/

        /*
        Example 1:
glTranslatef(0.0f,0.0f,-6.0f);
const GLfloat quadVertices[] = { -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f
    };

glVertexPointer(4, GL_FLOAT, 0, quadVertices);
glDrawArrays(GL_QUADS, 0, 4);		//GL_QUADS is depricated in GL3 removed in 3.1 use GL_TRIANGLES instead
        */
			/*
			unsigned int Pos;            					//so we can iterate through the vector

			glEnableClientState( GL_COLOR_ARRAY );			//so we can use vertex colours
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );	//so we can use textures
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_INDEX_ARRAY );
			glEnable( GL_TEXTURE_2D );						//so we can use 2d textures

			for ( Pos=0; Pos<Entity.size(); Pos++ ) {
				//now we can setup all the images
				glPushMatrix();

				if ( Entity[ Pos ].BackFaceCulling == true ) {
					// disable culling on this entity
					glDisable( GL_CULL_FACE );
				} else {
					glEnable( GL_CULL_FACE );
				}

				glLoadIdentity();

				//reposition Quad or Entity
				glTranslatef( Entity[ Pos ].Position.x, Entity[ Pos ].Position.y, Entity[ Pos ].Position.z );
				glRotatef( Entity[ Pos ].Rotation.x, 1, 0, 0 );
				glRotatef( Entity[ Pos ].Rotation.y, 0, 1, 0 );
				glRotatef( Entity[ Pos ].Rotation.z, 0, 0, 1 );

				if ( Entity[ Pos ].Texture ) {
					//we have a texture now we need to set it up
					glEnable( GL_TEXTURE_2D );
					glBindTexture( GL_TEXTURE_2D, Entity[ Pos ].Texture );
				} else {
					//no texture so disable texturing
					glDisable( GL_TEXTURE_2D );
				}

				//rendering goes in here
				glColorPointer( 4, GL_FLOAT, 0, &Entity[ Pos ].ColourCoords );
				glNormalPointer( GL_FLOAT, 0, &Entity[ Pos ].VertexNormals );
				glTexCoordPointer( 3, GL_FLOAT, 0, &Entity[ Pos ].TextureCoords );				//Create triangles (0,1,2)
				glVertexPointer( 3, GL_FLOAT, 0, &Entity[ Pos ].VertexCoords );
				glDrawElements( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, &Entity[ Pos ].TriangleIndices );

				glPopMatrix();

				//close up entity entry
				if ( Entity[ Pos ].Texture ) {
				} else {
					glEnable( GL_TEXTURE_2D );		//re-enable for closing down
				}
			}

			glDisable( GL_TEXTURE_2D );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY );	//so we can use textures
			*/
		}
    };
#endif // ERenderSetup
