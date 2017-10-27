//
//  FileSystem.h - Copyright (C)EdzUp
//  Programmed by Ed 'EdzUp' Upton
//

#ifndef _FRAMEWORK_FILESYSTEM_
    #define _FRAMEWORK_FILESYSTEM_
    #include <iostream>
    #include <ostream>
    #include <fstream>

    class FileSystemClass {
        std::ofstream    WriteData;
        std::ifstream    ReadData;
        char*       MemBlock;
        bool        writing;                    //true if the file is open for writing
        long long   Size;                       //this is the size of the file
        bool        FileOk;                     //true if this file is ok

        void SetError( std::string Err ) {
        }
        public:

        long FileSize( std::string filename ) {
            FILE *p_file = NULL;
            long Size = 0;

            p_file = fopen( filename.c_str(), "rb" );
            if ( p_file != NULL ) {
                fseek( p_file, 0, SEEK_END );
                Size = ftell( p_file );
                fclose( p_file );
            }

            return( Size );
        }

        std::string LongFilename( std::string filename, bool internal ) {
            return( "" );
        }

        bool FileExists( std::string filename ) {
            if ( FILE *file = fopen( filename.c_str(), "r" ) ) {
                fclose( file );

                return( true );
            }

            return( false );
        }

        bool FileExistsC( char* filename ) {
            if ( FILE *file = fopen( filename, "r" ) ) {
                fclose( file );

                return( true );
            }

            return( false );
        }

        bool IsOpen( void ) {
            return( FileOk );
        }

        char* AllFileData( char *Data, long length ) {
            //read or write an entire binary data file
            if ( writing == true ) {
                //write the data to the file
                WriteData.write( Data, length );
            } else {
                //read the data from the file into the data block
                char    *memblock;
                long    filesize;

                if ( ReadData.is_open() ) {
                    filesize = ReadData.tellg();
                    memblock = new char[ filesize ];
                    ReadData.seekg( 0, std::ios::beg );
                    ReadData.read( memblock, filesize );
                    return( memblock );
                } else SetError( "ERROR:File is not open" );
            }

            return( nullptr );
        }

        int UseInt( int value =0 ) {
            long val;

            if ( writing == true ) {
                //write data to the file
                WriteData.write( (char*)&value, sizeof( long ) );
            } else {
                //read the data from the file
                ReadData.read( (char*)&val, sizeof( long ) );
                return( val );
            }

            return( 0 );
        }

        char UseByte( char value =0 ) {
            char val;

            if ( writing == true ) {
                WriteData.write( (char*)&value, 1 );
            } else {
                ReadData.read( (char*)&val, 1 );
                return( val );
            }

            return( 0 );
        }

        short UseShort( short value =0 ) {
            short val;

            if ( writing == true ) {
                WriteData.write( ( char*)&value, sizeof( short ) );
            } else {
                ReadData.read( (char*)&val, sizeof( short ) );
                return( val );
            }

            return( 0 );
        }

        float UseFloat( float value =0.0f ){
            float val;

            if ( writing == true ) {
                WriteData.write( (char*)&value, sizeof( float ) );
            } else {
                ReadData.read( (char*)&val, sizeof( float ) );
                return( val );
            }

            return( 0.0f );
        }

        std::string UseLine( std::string value ="" ) {
            std::string val;

            if ( writing == true ) {
                WriteData.write( value.c_str(), value.length() );
            } else {
                std::getline( ReadData, val );
                return( val );
            }
            return( "" );
        }

        std::string UseString( std::string value ="" ) {
            int len;
            std::string val;

            if ( writing == true ) {
                len = value.length();
                WriteData.write( (char*)&len, sizeof( int ) );
                WriteData.write( value.c_str(), value.length() );
            } else {
                ReadData.read( (char*)& len, sizeof( int ) );
                ReadData.read( (char*)& val, len );
                return( val );
            }
            return( "" );
        }

        bool UseBool( bool value =false ) {
            bool val;

            if ( writing == true ) {
                WriteData.write( (char*)&value, sizeof( bool ) );
            } else {
                ReadData.read( (char*)&val, sizeof( bool ) );
                return( val );
            }
            return( false );
        }

        bool OpenFile( std::string filename, bool reading = true ) {
            //this opens a file and returns true if its ok
            if ( reading == true ){
                //file is for reading
                ReadData.open( filename, std::ios::in | std::ios::app | std::ios::binary );
                writing = false;
                FileOk = true;
                if ( ReadData.is_open() ) return( true );
            } else {
                WriteData.open( filename, std::ios::out | std::ios::app | std::ios::binary );
                writing = true;
                FileOk = true;
                if ( WriteData.is_open() ) return( true );
            }

            FileOk = false;
            return( false );
        }

        bool CloseFile( void ) {
            if ( writing == false ) {
                //close reading stream
                if ( ReadData.is_open() ) {
                    ReadData.close();
                    FileOk = false;
                    return( true );
                }
            } else {
                if ( WriteData.is_open() ) {
                    WriteData.close();
                    FileOk = false;
                    return( true );
                }
            }

            return( false );
        }

        bool EndOfFile( void ) {
            if ( writing == true ) {
                if ( WriteData.eof() ) {
                    return( true );
                }
            } else {
                if ( ReadData.eof() ) {
                    return( true );
                }
            }
            return( false );
        }
    };
#endif // _FRAMEWORK_FILESYSTEM_
