/*
 *     ESurface.h - Copyright (c)EdzUp
 *     Programmed by Ed 'EdzUp' Upton
 */

#ifndef EdzUpSurfaces
   #define EdzUpSurfaces
   #include "ETexture.h"
   #include "EDebug.h"

   #include <vector>        //for the vector class

   class VertexData {
      public:
      float x;
      float y;
      float z;
   };

   class NormalData {
      public:
      float x;
      float y;
      float z;
   };

   class ColourData {
      float red;
      float green;
      float blue;
      float alpha;
   };

   class VertexTextureData {
      public:
      float u;
      float v;
      float w;
   };

   class TriangleData {
       public:
      float vertex[ 3 ];
   };

   class ESurface {
      public:
      std::vector<VertexData> VertexList;
      std::vector<NormalData> NormalList;
      std::vector<ColourData> ColourList;
      std::vector<VertexTextureData> VertexTextureList;
      std::vector<TriangleData> TriangleList;
      std::vector<long> TriangleID;
      std::vector<long> VertexID;
      long NextId;
      long NextTriangleId;

      public:
      void CreateSurface( void ) {
        NextId =0;
        NextTriangleId =0;
      }

      long AddTriangle( unsigned long vert1, unsigned long vert2, unsigned long vert3 ) {
          TriangleData Tri;

          if ( VertexList.size() >vert1 ) {
                DebugLog.AddLine( "AddTriangle>>Vertex1 does not exist" );
                exit( 1 );
          }
          if ( VertexList.size() >vert2 ) {
                DebugLog.AddLine( "AddTriangle>>Vertex2 does not exist" );
                exit( 1 );
          }
          if ( VertexList.size() >vert3 ) {
                DebugLog.AddLine( "AddTriangle>>Vertex3 does not exist" );
                exit( 1 );
          }

          Tri.vertex[ 0 ] = vert1;
          Tri.vertex[ 1 ] = vert2;
          Tri.vertex[ 2 ] = vert3;

          TriangleList.push_back( Tri );
          TriangleID.push_back( NextTriangleId );

          NextTriangleId++;

          return( NextTriangleId -1 );
      }

      long TriangleVertex( long Id, long index ) {
          //this will return a vertex at a certain index
          unsigned long Count;

          if ( index <0 || index>2 ) {
            DebugLog.AddLine( "TriangleVertex>>index out of bounds error (0-2 only)" );
            exit( 1 );
          }

          for ( Count =0; Count<TriangleID.size(); Count++ ) {
            if ( TriangleID[ Count ] == Id ) return( TriangleList[ Count ].vertex[ index ] );
          }
      }

      long AddVertex( float x, float y, float z, float u, float v, float w ) {
         VertexData vert;
         VertexTextureData vertTex;

         vert.x = x;
         vert.y = y;
         vert.z = z;

         vertTex.u = u;
         vertTex.v = v;
         vertTex.w = w;

         VertexList.push_back( vert );
         VertexTextureList.push_back( vertTex );

         VertexID.push_back( NextId );              //store ID for easy retrieval

         NextId++;

         return( NextId -1 );
      }

      float VertexX( long Id ) {
        //this will return the x position of a vertex
        unsigned long Count;

        for ( Count =0; Count<VertexID.size(); Count++ ) {
            if ( VertexID[ Count ] == Id ) return( VertexList[ Count ].x );
        }

        return( 0.0 );
      }

      float VertexY( long Id ) {
        //this will return the x position of a vertex
        unsigned long Count;

        for ( Count =0; Count<VertexID.size(); Count++ ) {
            if ( VertexID[ Count ] == Id ) return( VertexList[ Count ].y );
        }

        return( 0.0 );
      }

      float VertexZ( long Id ) {
        //this will return the x position of a vertex
        unsigned long Count;

        for ( Count =0; Count<VertexID.size(); Count++ ) {
            if ( VertexID[ Count ] == Id ) return( VertexList[ Count ].z );
        }

        return( 0.0 );
      }

      float VertexU( long Id ) {
        //this will return the x position of a vertex
        unsigned long Count;

        for ( Count =0; Count<VertexID.size(); Count++ ) {
            if ( VertexID[ Count ] == Id ) return( VertexTextureList[ Count ].u );
        }

        return( 0.0 );
      }

      float VertexV( long Id ) {
        //this will return the x position of a vertex
        unsigned long Count;

        for ( Count =0; Count<VertexID.size(); Count++ ) {
            if ( VertexID[ Count ] == Id ) return( VertexTextureList[ Count ].v );
        }

        return( 0.0 );
      }

      float VertexW( long Id ) {
        //this will return the x position of a vertex
        unsigned long Count;

        for ( Count =0; Count<VertexID.size(); Count++ ) {
            if ( VertexID[ Count ] == Id ) return( VertexTextureList[ Count ].w );
        }

        return( 0.0 );
      }
   };
#endif
