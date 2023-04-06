/*
 * PSR.h
 *
 *  Created on: 05.04.2023
 *      Author: melah
 *
 *      This class is related for the Primary Surveillance Radar
 */

#ifndef INC_PSR_H_
#define INC_PSR_H_

#define MAX_RANGE 100000
#define REFERENCE_ANGLE 0
#define SCANS_PER_MINUTE 12
#define PULSES_PER_DEGREE 1
#define CURRENT_ANGLE 0
#define PULSE_SPEED 1
#define DEGREES_IN_CIRCLE 360

#include "inc/Aircraft.h"
#include <vector>

using namespace std;

class PSR {
public:
	PSR(vector<Aircraft> *aircraftSchedule);

	void execute();
	void test();
	void scan();
	void detectAircraft(int angle);
	void rotateRadar();
	bool receiveEchoes(int echoes[]);
	Aircraft* determineDistances(int echoes[]);

	vector<Aircraft> sendAircraftPositionsToSSR();

	virtual ~PSR();



private:

	int range;
	int reference_angle;
	int scans_per_minute;
	int pulses_per_degree;
	int current_angle;
	int pulse_speed;

	vector<Aircraft> *aircraftList;
	vector<Aircraft*> illuminatedObjects;

};



#endif /* INC_PSR_H_ */
