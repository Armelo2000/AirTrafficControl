/*
 * Aircraft.h
 *
 *  Created on: 02.04.2023
 *      Author: Armel
 *
 *  This file describes all about an Aircraft
 */

#ifndef INC_AIRCRAFT_H_
#define INC_AIRCRAFT_H_

#include <iostream>
#include <stdint.h>
#include "inc/TransponderData.h"

#include <pthread.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
//#include <sys/neutrino.h> // For QNX message passing API
#include <stdint.h> // For data type uint64_t
//#include <sys/iofunc.h>
//#include <sys/dispatch.h>
#include <unistd.h>
//#include <sys/netmgr.h>
#include <sys/types.h>

typedef int32_t Coordinate, Speed;
typedef uint32_t BoundaryTime;

using namespace std;

class Aircraft{

private:
	/*****************************************
	 * This is the ID of the Aircraft
	 *****************************************/
	uint32_t ID;

protected:
	/*****************************************
	 * This is the position of the Aircraft
	 * in the x-axis
	 *****************************************/
	Coordinate	xPosition;

	/*****************************************
	 * This is the position of the Aircraft
	 * in the y-axis
	 *****************************************/
	Coordinate	yPosition;

	/*****************************************
	 * This is the position of the Aircraft
	 * in the z-axis
	 *****************************************/
	Coordinate	zPosition;

	/*****************************************
	 * This is the speed of the Aircraft
	 * in the x-axis
	 *****************************************/
	Speed xSpeed;

	/*****************************************
	 * This is the speed of the Aircraft
	 * in the y-axis
	 *****************************************/
	Speed ySpeed;

	/*****************************************
	 * This is the speed of the Aircraft
	 * in the z-axis
	 *****************************************/
	Speed zSpeed;

	/*******************************************
	 * Channel of the Aircraft transponder
	 */
	int m_transponderDataChannel;

	/*******************************************
	 * Time at Boundary
	 */
	BoundaryTime boundary_time;

public:
	Aircraft(BoundaryTime time, uint32_t id, Coordinate x, Coordinate y, Coordinate z,
			 Speed x_speed, Speed y_speed, Speed z_speed);

	Aircraft(BoundaryTime time, uint32_t id, Coordinate x, Coordinate y, Coordinate z);

        //List of plane close to
        vector<Aircraft*> aircraftCloseTo;

        //Number of plane close to
        unsigned int aircraftCloseToCount;   

	/**********************************************
	 * This Function return the ID of the Aircraft
	 *********************************************/
	uint32_t getAircraftID();

	/**********************************************
	 * This Function return the current x position
	 *********************************************/
	Coordinate getXCoordinate();

	/**********************************************
	 * This Function return the current y position
	 *********************************************/
	Coordinate getYCoordinate();

	/**********************************************
	 * This Function return the current x position
	 *********************************************/
	Coordinate getZCoordinate();

	/**********************************************
	 * This Function return the current speed in
	 * the x-axis
	 *********************************************/
	Speed getXSpeed();

	/**********************************************
	 * This Function return the current speed in
	 * the Y-axis
	 *********************************************/
	Speed getYSpeed();

	/**********************************************
	 * This Function return the current speed in
	 * the z-axis
	 *********************************************/
	Speed getZSpeed();

	/*********************************************
	 * This function return the Channel of the
	 * transponder
	 */
	int getTransponderDataChannel();

	/*********************************************
	 * This function set the Channel Id of the
	 * transponder
	 */
	void setTransponderDataChannelId(int channelId);

	/**********************************************
	 * This Function update the position in the
	 * x-axis
	 *********************************************/
	void updateXCoordinate();

	/**********************************************
	 * This Function update the position in the
	 * y-axis
	 *********************************************/
	void updateYCoordinate();

	/**********************************************
	 * This Function update the position in the
	 * z-axis
	 *********************************************/
	void updateZCoordinate();

	/************************************************
	 * This Function update the Speed of the Aircraft
	 * in the x-axis
	 ************************************************/
	void updateXSpeed(Speed xspeed);

	/************************************************
	 * This Function update the Speed of the Aircraft
	 * in the y-axis
	 ************************************************/
	void updateYSpeed(Speed yspeed);

	/************************************************
	 * This Function update the Speed of the Aircraft
	 * in the z-axis
	 ************************************************/
	void updateZSpeed(Speed zspeed);

	/***************************************************
	 * This function update the position of the Aircraft
	 * in all directions (x, y, z)
	 ****************************************************/
	void updateAircraftPosition();

	/***************************************************
	 * This function set the transponder Channel of the
	 * Aircraft
	 ****************************************************/
	void setTransponderDataChannel(int channelId);

	//Communication with the IPC (interrogator)
	void ServiceInterrogationSignal();

	/********************************************************
	 * This function is called until the interrogation
	 * arrives. The Interrogation signal move from IPC to
	 * Aircraft.
	 ********************************************************/
	void receiveInterrogationSignal();

        // This function check if two aircraft are
        // closed. If it is closed to another aircraft
        // the function return true otherwise false
        bool isCloseTo(Aircraft* anotherAircraft);


};





#endif /* INC_AIRCRAFT_H_ */
