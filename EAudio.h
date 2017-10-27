/*
    EAudio.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>

class EAudioClass {
    //the OpenAL device and contexts
    public:
    long            ID;         //a long value so we can recognise the sound file
    ALuint          source;
    ALuint          buffer;
    ALuint          frequency;

    ALenum          format;
};

class FrameworkAudioClass {
    //this is the framework audio class for all the framework audio system
    ALCdevice* device;
    ALCcontext* context;

    std::vector<EAudioClass> AudioSystem;
    long NextID;
    float           CurrentVolume;
    int             SampleRate = 44100;
    int             SampleSize = 1024;
    ALbyte          buffer[22050];
    ALint           recordSample;
    ALCdevice       *recordingDevice;

    public:
    void SetVolume( float level ) {
        alListenerf( AL_GAIN, level );
        CurrentVolume = level;
    }

    float GetVolume( void ) {
        //used to get the current volume level
        return( CurrentVolume );
    }

    bool StartRecording() {
        alGetError();
        recordingDevice = alcCaptureOpenDevice( NULL, SampleRate, AL_FORMAT_STEREO16, SampleSize );
        if (alGetError() != AL_NO_ERROR) {
            return( false );
        }
        alcCaptureStart( recordingDevice );
    }

    void UpdateRecording(){
        alcGetIntegerv( recordingDevice, ALC_CAPTURE_SAMPLES, ( ALCsizei )sizeof( ALint ), &recordSample );
        alcCaptureSamples( recordingDevice, (ALCvoid *)buffer, recordSample );
    }

    void StopRecording() {
        alcCaptureStop( recordingDevice );
        alcCaptureCloseDevice( recordingDevice );
    }

    bool Initialise() {
        //this will start up the audio system for us
        ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
        ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
        ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

        device = alcOpenDevice( NULL );
        if (!device ) exit( 4 );
        context = alcCreateContext( device, NULL );
        if (!context ) exit( 5 );
        alcMakeContextCurrent( context );

        alListenerfv( AL_POSITION, ListenerPos );
        alListenerfv( AL_VELOCITY, ListenerVel );
        alListenerfv( AL_ORIENTATION, ListenerOri );
        CurrentVolume = 1.0;

        return( true );
    }

    void Shutdown() {
        //this will shutdown OpenAL
        alcMakeContextCurrent( NULL );
        alcDestroyContext( context );
        alcCloseDevice( device );
    }

    //audio sample functions
    long LoadSoundWAV( std::string filename ) {
        FILE *fp = NULL;
        char type[ 4 ];
        long size, chunkSize;
        short formatType, channels;
        long sampleRate, avgBytesPerSec;
        short bytesPerSample, bitsPerSample;
        long dataSize;
        EAudioClass Temp;

        fp = fopen( filename.c_str(), "rb" );
        if (!fp) exit( 1 );

        //check to make sure wav is ok
        fread( type, sizeof( char ), 4, fp );

        if ( type[ 0 ] != 'R' || type[ 1 ] != 'I' || type[ 2 ] != 'F' || type[ 3 ] != 'F' ) exit( 64 );

        fread( &size, sizeof( long ), 1, fp );
        fread( type, sizeof( char ), 4, fp );
        if ( type[ 0 ] != 'W' || type[ 1 ] != 'A' || type[ 2 ] != 'V' || type[ 3 ] != 'E' ) exit( 65 );

        fread( type, sizeof( char ), 4, fp );
        if ( type[ 0 ] != 'f' || type[ 1 ] != 'm' || type[ 2 ] != 't' || type[ 3 ] != ' ' ) exit( 66 );

        //now we know the file is a wav file we can load it
        fread( &chunkSize, sizeof( long ), 1, fp );
        fread( &formatType, sizeof( short ), 1, fp );
        fread( &channels, sizeof( short ), 1, fp );
        fread( &sampleRate, sizeof( long ), 1, fp );
        fread( &avgBytesPerSec, sizeof( long ), 1, fp );
        fread( &bytesPerSample, sizeof( short ), 1, fp );
        fread( &bitsPerSample, sizeof( short ), 1, fp );

        fread( type, sizeof( char ), 4, fp );
        if ( type[ 0 ] != 'd' || type[ 1 ] != 'a' || type[ 2 ] != 't' || type[ 3 ] != 'a' ) exit( 67 );

        fread( &dataSize, sizeof( long ), 1, fp );

        //we could display the info if we wanted
        unsigned char* buf= new unsigned char[ dataSize ];
        fread( buf, sizeof( char ), dataSize, fp );

        Temp.frequency=sampleRate;
        Temp.format =0;

        alGenBuffers( 1, &Temp.buffer );
        alGenSources( 1, &Temp.source );
        if( alGetError() != AL_NO_ERROR ) exit( 2 );

        if( bitsPerSample == 8 ){
            if ( channels == 1 )
                Temp.format = AL_FORMAT_MONO8;
            else if ( channels == 2)
                Temp.format = AL_FORMAT_STEREO8;
        }else if ( bitsPerSample == 16 ){
            if ( channels == 1 )
                Temp.format = AL_FORMAT_MONO16;
            else if ( channels == 2)
                Temp.format = AL_FORMAT_STEREO16;
        }
        if (!Temp.format) exit( 3 );

        alBufferData( Temp.buffer, Temp.format, buf, dataSize, Temp.frequency );
        if( alGetError() != AL_NO_ERROR ) exit( 3 );

        ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
//        ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
        alSourcei( Temp.source, AL_BUFFER, Temp.buffer );
        alSourcef( Temp.source, AL_PITCH, 1.0f );
        alSourcef( Temp.source, AL_GAIN, 1.0f );
        alSourcefv( Temp.source, AL_POSITION, SourcePos );
        alSourcei( Temp.source, AL_LOOPING, AL_FALSE );

        if ( alGetError() != AL_NO_ERROR ) exit( 4 );

        Temp.ID = NextID;
        AudioSystem.push_back( Temp );

        fclose( fp );
        delete[] buf;

        NextID++;

        return( NextID -1 );
    }

    bool FreeSound( long ID ){
        //this will release all sounds and get rid of it
        for ( unsigned int FS=0; FS<AudioSystem.size(); FS++ ) {
            if ( AudioSystem[ FS ].ID == ID ) {
                alDeleteSources( 1, &AudioSystem[ FS ].source );
                alDeleteBuffers( 1, &AudioSystem[ FS ].buffer );
                AudioSystem.erase( AudioSystem.begin() +FS );       //delete the vector entry

                return( true );
            }
        }

        return( false );
    }

    void LoopSound( long ID, bool looped ){
        for ( unsigned int LS=0; LS<AudioSystem.size(); LS++ ) {
            if ( AudioSystem[ LS ].ID == ID ) {
                if ( looped == true ){
                    alSourcei( AudioSystem[ LS ].source, AL_LOOPING, AL_TRUE );
                } else {
                    alSourcei( AudioSystem[ LS ].source, AL_LOOPING, AL_FALSE );
                }
            }
        }
    }

    void PauseSound( long ID ) {
        for ( unsigned int LS=0; LS<AudioSystem.size(); LS++ ) {
            if ( AudioSystem[ LS ].ID == ID )
                alSourcePause( AudioSystem[ LS ].source );
        }
    }

    void ResumeSound( long ID ) {
        for ( unsigned int LS=0; LS<AudioSystem.size(); LS++ ) {
            if ( AudioSystem[ LS ].ID == ID )
                alSourcePlay( AudioSystem[ LS ].source );
        }
    }

    void PlaySound( long ID ) {
        for ( unsigned int LS=0; LS<AudioSystem.size(); LS++ ) {
            if ( AudioSystem[ LS ].ID == ID )
                alSourcePlay( AudioSystem[ LS ].source );
        }
    }

    void StopSound( long ID ) {
        for ( unsigned int LS=0; LS<AudioSystem.size(); LS++ ) {
            if ( AudioSystem[ LS ].ID == ID )
                alSourceStop( AudioSystem[ LS ].source );
        }
    }
};
