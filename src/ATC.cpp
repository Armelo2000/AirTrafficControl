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


using namespace std;

int main() {

	//Create 5 Aircrafts instances
	Aircraft* Airline1 = new Aircraft(1, 12, 0, 35, 0, 15, 10);
	Aircraft* Airline2 = new Aircraft(2, 20, 10, 44, 120, 15, 72);
	Aircraft* Airline3 = new Aircraft(3, 0, 80, 65, 0, 60, 4);
	Aircraft* Airline4 = new Aircraft(4, 100, 5, 70, 0, 11, 24);
	Aircraft* Airline5 = new Aircraft(5, 24, 125, 8, 0, 105, 18);

	const char* input_file = "/Data/input_flyby.txt";
	   vector<Aircraft> aircraftSchedule;

	   DataParser parser(input_file);
	   aircraftSchedule = parser.getAircraftSchedule();

	   SystemManager SM(&aircraftSchedule);
	   SM.execute();

	cout << "" << endl; // prints 
	return 0;
}
