/*
 *  EEntity.h - Copyright (C)EdzUp
 *  Programmed by Ed 'EdzUp' Upton
 */

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

C++
// constructing vectors
#include <iostream>
#include <vector>

int main ()
{
  unsigned int i;

  // constructors used in the same order as described above:
  std::vector<int> first;                                // empty vector of ints
  std::vector<int> second (4,100);                       // four ints with value 100
  std::vector<int> third (second.begin(),second.end());  // iterating through second
  std::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
*/

#ifndef EEntityDef
    #define EEntityDef

#include "Vec3.h"
#include "ESurface.h"
#include "ERender.h"
#include <iostream>
#include <vector>           //required for vector lists

using namespace std;
long NextEntityID =0;

class EEntity {      //Engine EEntity class
    public:
    GLuint VBOid;
    long ID;
    long *IDPointer;
    float OpenGLMatrix[ 16 ];
    Vec3 position;
    Vec3r rotation;
    vector<ESurface> SurfaceList;
    vector<long> SurfaceID;             //this will allow Identification of surfaces even when some have been removed etc
    bool hidden;
};

class EntityClass {
    vector <EEntity> EntityList;

    long    NextEntityID;
    unsigned long    ECCount;                        //so it dont have to keep being recreated
    bool    VBOOk;

    public:
    void InitialiseEntitySystem( bool VBO ) {
        NextEntityID =0;
        VBOOk = VBO;
    }

    void ReleaseAll( ) {
        //this will release all the entities from the files
        for ( ECCount=0; ECCount < EntityList.size(); ECCount++ ) {
                if ( EntityList[ ECCount ].VBOid != 0 ) {
                    glDeleteBuffersARB(1, &EntityList[ ECCount ].VBOid );
                }
        }
    }

    long CreateEntity( long Parent ){
        EEntity* temp = new EEntity();
        temp->VBOid =0;              //zeroed as its a basic entity
        temp->ID = NextEntityID;
        temp->IDPointer = &Parent;

        if ( VBOOk == true ){
            //we have VBOs
 /*           glGenBuffersARB( 1, &temp->VBOid );
            glBindBufferARB( GL_ARRAY_BUFFER_ARB, temp->VBOid );
            glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof( float ), 0, GL_STATIC_DRAW_ARB );
            glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, sizeof( float ), &temp->SurfaceList[ 0 ].VertexList);
            glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, sizeof( float ), &temp->SurfaceList[ 0 ].NormalList);
            glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, sizeof( float ), &temp->SurfaceList[ 0 ].ColourList);
            */
        } else {
            //we dont have VBOs
        }

        NextEntityID++;
        return( NextEntityID -1 );
    }

    void PositionEntity( long ID, double X, double Y, double Z ) {
//      position.PositionAt( X, Y, Z );
        EntityList[ ID ].position.PositionAt( X, Y, Z );
    }

    void MoveEntity( long ID, double X, double Y, double Z ) {
 //     position.TranslateBy( X, Y, Z, rotation );
        EntityList[ ID ].position.TranslateBy( X, Y, Z, EntityList[ ID ].rotation );

        //getting new position will be in here for OpenGL stuffs
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
        */
    }
};

#endif // EEntityDef
