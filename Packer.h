/*
    Packer.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef FRAMEWORKPACKER
    #define FRAMEWORKPACKER
    #include "FileSystem.h"
    #include "ERandom.h"
    #include "Convert.h"
    #include "EDebug.h"

    class PackerClass {
    public:
        FileSystemClass     FileSystem;
        ConversionClass     Convert;
        DebugClass          Debug;
        RNDGenerator        Random;

        char*               Buffer;
        long                Size;

        long Length( void ) {
            return( Size );
        }

        char BufferData( int Pos ) {
            if ( Pos >Size -1 ) return( 0 );

            return( Buffer[ Pos ] );
        }

        void CleanUpPacker(){
            delete [] Buffer;
        }

        bool PackDatafile( std::string filename, std::string outfile, long key ) {
            //filename is a list of files to pack into the target
            //outfile is the outputted pack file
            //key is the standard key

            return( false );
        }

        void PackFile( std::string filename, std::string outfile, long key ) {
            //filename is the file to pack
            //outfile is the target file that is written out
            //key is a hex int that will be used to encrypt the data then its written out
            long    Pos;

            Size = FileSystem.FileSize( filename );
            Buffer = new char[ Size ];

            //now the buffer is set we need to read the file
            FileSystem.OpenFile( filename );
            for ( Pos=0; Pos<Size-1; Pos++ ) {
                Buffer[ Pos ] = FileSystem.UseByte();
            }
            FileSystem.CloseFile();

            Random.Seed( key );             //setup the randomizer
            for ( Pos=0; Pos<Size-1; Pos++ ) {
                Buffer[ Pos ] -= Random.Generate( 255 );
            }

            //write out the converted data
            FileSystem.OpenFile( outfile, false );
            for ( Pos=0; Pos<Size-1; Pos++ ) {
                FileSystem.UseByte( Buffer[ Pos ] );
            }
            FileSystem.CloseFile();

            delete [] Buffer;
        }

        char* UnpackFile( std::string filename, std::string outfile, long key, bool datafile = false ) {
            //this will extra filename from the packfile and allow the system to use it
            //filename is the pack file
            //outfile is the target file that is created for the data
            //key is a hex key that will be used to unencrypt the data
            //datafile if set to true will just return the buffer and not write the data to a file
            long Pos;

            Size = FileSystem.FileSize( filename );
            if ( Size <1 ) {
                //nothing there
                Debug.AddLine( "No data to load" );
                return( nullptr );
            }
            printf( "Size: %li", Size );

            Buffer = new char[ Size ];

            //read in the data
            FileSystem.OpenFile( filename );
            for ( Pos =0; Pos<Size-1; Pos++ ) {
                Buffer[ Pos ] = FileSystem.UseByte();
            }
            FileSystem.CloseFile();

            //unencrypt the data
            Random.Seed( key );
            for ( Pos=0; Pos<Size; Pos++ ) {
                Buffer[ Pos ] -= Random.Generate( 255 );//Convert.WrapChar( Buffer[ Pos ], 0 -Random.Generate( 255 ) );
//                printf( "%c", Buffer[ Pos ] );
            }

            if ( datafile == true ) return( Buffer );

            FileSystem.OpenFile( outfile, false );
            for ( Pos=0; Pos<Size-1; Pos++ ) {
                FileSystem.UseByte( Buffer[ Pos ] );
            }
            FileSystem.CloseFile();

            return( nullptr );
        }
    };
#endif // FRAMEWORKPACKER
