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


using namespace std;

int main() {

	Airspace* airspace = new Airspace();
        //This function register aircraft for the simulation 
	airspace->registerAirCreaft();
	const char* input_file = "./Data/input_flyby.txt";
	   vector<Aircraft*> aircraftSchedule;

	   DataParser parser(input_file);
	   aircraftSchedule = parser.getAircraftSchedule();

	   SystemManager SM(&aircraftSchedule);
	   SM.execute();

	cout << "Finish" << endl;
	return 0;
}
