/*
    EDebug.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef EdzUp_Debug
    #define EdzUp_Debug
    #include <sstream>
    class DebugClass {
        std::string Filename;
        public:
        bool StartLog( std::string filename ){
            FILE* debugHandle;

            debugHandle = fopen( filename.c_str(), "w" );
            if ( debugHandle == NULL ) return( false );

            fclose( debugHandle );
            Filename = filename;

            return( true );
        }

        bool AddLine( std::string data ) {
            FILE* debugHandle;

            if ( Filename == "" ) return( false );

            debugHandle = fopen( Filename.c_str(), "a" );
            if ( debugHandle == NULL ) return( false );
            fputs( data.c_str(), debugHandle );
            fputc( 10, debugHandle );
            fputc( 13, debugHandle );
            fclose( debugHandle );

            return( true );
        }

        bool AddString( std::string data ) {
            FILE* debugHandle;

            if ( Filename == "" ) return( false );

            debugHandle = fopen( Filename.c_str(), "a" );
            if ( debugHandle == NULL ) return( false );
            fputs( data.c_str(), debugHandle );
            fclose( debugHandle );

            return( true );
        }
    };
#endif
