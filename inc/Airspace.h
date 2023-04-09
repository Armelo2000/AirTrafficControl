/*
 * Airspace.h
 *
 *  Created on: 08.04.2023
 *      Author: melah
 */

#ifndef INC_AIRSPACE_H_
#define INC_AIRSPACE_H_

#include <vector>
#include "inc/Aircraft.h"

//Definition of Parameters for the first aircraft
#define BOUNDARY_TIME_START		100
#define FLIGTH_ID_START			1
#define XPOSITION_START			20000
#define YPOSITION_START			30000
#define ZPOSITION_START			24000
#define XSPEED_START			1000
#define YSPEED_START			800
#define ZSPEED_START			1200

//Parameter for the Increment for the other aircrafts
#define BOUNDARY_TIME_INC		80
#define XPOSITION_INC   		300
#define YPOSITION_INC			260
#define ZPOSITION_INC			600
#define XSPEED_INC				40
#define YSPEED_INC				320
#define ZSPEED_INC				120


class Airspace{

private:
        //This constant variable are the definition
        //of the 3D Airspace 
	static const int AIRSPACE_XFEET			{100000};
	static const int AIRSPACE_YFEET			{100000};
	static const int AIRSPACE_ZFEET			{25000};

	static const int AIRSPACE_MIN_XFEET		{0};
	static const int AIRSPACE_MIN_YFEET		{0};
	static const int AIRSPACE_MIN_ZFEET		{15000};

	//list of all plane
	vector<Aircraft*> m_aircraftSchedule;

	//list of plane in the space
	vector<Aircraft*> m_aircraftInAirspace;

public:
	void registerAirCreaft(unsigned int count);
	void UpdateList();

	vector<Aircraft*> getAircraftSchedule();

	vector<Aircraft*> getAircraftInAirspace();

	void airspaceCheck_XPosition();
	void airspaceCheck_YPosition();
	void airspaceCheck_ZPosition();

        //this function log The aircraft history
        //in a CSV file 
        void log_history(Aircraft*);

        void setAlarm(Aircraft* aircraft, Aircraft* closeTo);


};



#endif /* INC_AIRSPACE_H_ */
