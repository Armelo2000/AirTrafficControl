/*
 * PSR.cpp
 *
 *  Created on: 05.04.2023
 *      Author: melah
 *
 *      This file serves as the implementation for the PSR (Primary Surveilance Radar)
 *      The PSR will scan the airspace and send an array of illuminated objects to the
 *      SSR.
 *
 */

#include "inc/PSR.h"
#include "inc/SSR.h"
#include <iostream>
#include <math.h>



PSR::PSR(vector<Aircraft> *AircraftSchedule) {

	range = MAX_RANGE;
	reference_angle = REFERENCE_ANGLE;
	scans_per_minute = SCANS_PER_MINUTE;
	pulses_per_degree = PULSES_PER_DEGREE;
	current_angle = CURRENT_ANGLE;
	pulse_speed = PULSE_SPEED;

	this->aircraftList=AircraftSchedule;
	cout << "PSR Aircraft list address: " << aircraftList << endl;
}

PSR::~PSR() {
	// TODO Auto-generated destructor stub
}

void PSR::scan(){

    cout << "Scanning..." << endl;
	while(current_angle <= DEGREES_IN_CIRCLE){

		detectAircraft(current_angle);

		if (current_angle >= DEGREES_IN_CIRCLE){

			// reset the radar
			current_angle = 0;
			break;
		}

		// Rotate the radar 1 degree
		rotateRadar();
	}
}

void PSR::detectAircraft(int angle){

	int aircraftDistance; 			// Distance of the detected aircraft
	double aircraftAngleRads; 		// Angle of the detected aircraft

	for (Aircraft& aircraft : *aircraftList){

		// Get the aircraft angle in radians
		aircraftAngleRads = 0; //TODO (atan2(aircraft.getYCoordinate(), aircraft.getXCoordinate()));

		   // Adjust the aircraft angle to be between 0 and 2*pi
		   if (aircraftAngleRads < 0)
			   aircraftAngleRads += 2 * M_PI;

		   // Adjust the input angle to be between 0 and 2*pi
		   if (angle  < 0)
			   angle += 2 * M_PI;

		// convert to degrees
		int aircraftAngleDegrees = (int) (aircraftAngleRads * 180)/ M_PI;

		   // Check if the aircraft is at the current radar angle
     		   if (aircraftAngleDegrees == angle){
			   // Get the aircraft distance
			   aircraftDistance = 0; // TODO (int) (sqrt(pow(aircraft.getXCoordinate(), 2) + pow(aircraft.getYCoordinate(), 2)));
			   // Add the aircraft object to the array if it is within range
			   if(aircraftDistance < range){

				   cout << "Pushing back with address: " << &aircraft  << endl;
				   illuminatedObjects.push_back(&aircraft);
			   	   cout << illuminatedObjects.size() << endl;
			   }
		   }
	}

}

void PSR::rotateRadar(){

	current_angle++;
}


vector<Aircraft> PSR::sendAircraftPositionsToSSR(){

//	cout << "Sending illuminated objects" << endl;
//
//	for (Aircraft& aircraft : illuminatedObjects){
//
//		cout << "Aircraft: " << aircraft.getFlightID() << endl;
//
//	}


	//return illuminatedObjects;
}


void PSR::execute(){

    cout << "Executing PSR..." << endl;

	scan();
	sendAircraftPositionsToSSR();
	SSR ssr(illuminatedObjects);
	ssr.execute();

	//return illuminatedObjects;

}

void PSR::test(){}

