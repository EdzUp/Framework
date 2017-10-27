/*
    ERandom.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef _ERANDOM_
    #define _ERANDOM_ 1

	#include <stdio.h>
	#include <time.h>
	#include <math.h>
	#include <chrono>
	#include <iostream>
	#include <ctime>
	#include <sys/time.h>
	#include <unistd.h>

class RNDGenerator {
    static const int               iSLIP = 27;
    static const int               i31BITSIGN = 0x7FFFFFFF;
    static const int               iSCANUPSTART =1;

    public:
    int                     iScanUp;
    int                     iSeed;
    int                     iValue;

    void Initialise( void ) {
        iScanUp = iSCANUPSTART;
        iSeed = 0;
        iValue = 0;
    }

    //seed the random number generator
    void Seed( long iRNDSeed, long iStartScanUp = 1 ) {
        if ( iStartScanUp == 1 ) iStartScanUp = iSCANUPSTART;
		iValue = ( iRNDSeed & i31BITSIGN );
		iSeed = ( iRNDSeed & i31BITSIGN );
		iScanUp = ( iStartScanUp & i31BITSIGN );
    }

    void Randomize( void ) {
		struct timeval t;
		gettimeofday(&t, NULL);
		Seed( (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0 );
    }

    long Generate( long iMaxValue ) {
		//Step up
		if ( iMaxValue ==0 ) return( 0 );			//if the values is 0-0 then just return 0

		iScanUp = (iScanUp + 1);                        //Increase by one
		iScanUp = (iScanUp & i31BITSIGN);               //Make sure the sign value does Not get used (wraps it)
		//Re-seed self with new value
		iSeed = ((iSeed+(iSeed >> 8))-(iSLIP ^iScanUp) ) & i31BITSIGN; //Calculate new seed for next time
		//Wrap to get correct value
		iValue = (iSeed % iMaxValue);  //Just in case we need it
		return( iValue );
    }
};
#endif // _ERANDOM_
