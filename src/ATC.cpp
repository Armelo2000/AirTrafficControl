//============================================================================
// Name        : ATC.cpp
// Author      : Armel
// Version     :
// Copyright   : Your copyright notice
// Description : Aircraft traffic control
//============================================================================

#include <iostream>
#include <vector>
#include "inc/Aircraft.h"
#include "inc/SystemManager.h"
#include "inc/DataParser.h"
#include "inc/Airspace.h"

#define AIRCRAFT_COUNT    50

using namespace std;

int main() {

	Airspace* airspace = new Airspace();
        //This function register N aircrafts for the simulation 
        airspace->registerAirCreaft(AIRCRAFT_COUNT);

	   vector<Aircraft*> aircraftSchedule;

	   aircraftSchedule = airspace->getAircraftSchedule();

	   SystemManager SM(&aircraftSchedule);
	   SM.execute();

        //while (1);
	cout << "Finish" << endl;
	return 0;
}
