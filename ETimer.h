//
//	ETimer.h - Copyright (C)EdzUp
//	Programmed by Ed 'EdzUp' Upton
//

#ifndef ETimerClassDef
	#define ETimerClassDef

	#include <stdio.h>
	#include <time.h>
	#include <math.h>
	#include <chrono>
	#include <iostream>
	#include <ctime>
	#include <sys/time.h>
	#include <unistd.h>
	class TimerClass {
		clock_t 	Time;
		double		OldMillisecs;
		long		FPSWanted;
		double		Eachframe;
		double		LastSecond;
		std::string	lastTime;
		double      timetaken;
		std::string CD;

	public:
		std::string CurrentDate( void ) {
			time_t rawtime;
			struct tm * timeinfo;
			char buffer[100];

			time (&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer,100,"%d-%m-%Y %I:%M:%S",timeinfo);
			std::string str(buffer);

			return( str );
		}

		void DesiredFPS( long wantedfps ) {
			//this will set it so the wanted FPS will be the games FPS
			FPSWanted = wantedfps;
		}

		bool RenderFrame( void ) {
			//updates all timers and returns true if a frame should be rendered
			if ( Millisecs() -OldMillisecs >=1000 ) {
				//a second has passed
				timetaken = Millisecs() -LastSecond;
				Eachframe = timetaken /FPSWanted;			//readjust timer
				LastSecond = Millisecs();
			}

			if ( Millisecs() -OldMillisecs >=Eachframe ) {	//check to see if the timer has gone past how long a frame will take
				//render a frame
				OldMillisecs = Millisecs();

				return( true );
			}

			return( false );
		}

		double Millisecs( void ) {
			struct timeval t;
			gettimeofday(&t, NULL);
			return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
			/*
			Time = clock();

			return( ( (long)Time /CLOCKS_PER_SEC ) );*/
		}

		unsigned long long EpochTime( void ) {
			unsigned long long timeSinceEpoch;
			return( timeSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() );
		}
	};
#endif // ETimerClassDef
