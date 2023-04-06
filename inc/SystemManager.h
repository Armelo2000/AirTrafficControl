/*
 * SystemManager.h
 *
 *  Created on: 05.04.2023
 *      Author: melah
 */

#ifndef INC_SYSTEMMANAGER_H_
#define INC_SYSTEMMANAGER_H_

#include "inc/Aircraft.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>


using namespace std;

class SystemManager{

public:
    // Constructors and destructor
	SystemManager();
	SystemManager(vector<Aircraft> *AircraftArr);
    virtual ~SystemManager();

    // Initialization functions
    void initDataDisplay();
    void initComputerSystem();
    void initCommunicationSystem();
    void initOperatorConsole();
    void initRadar();
    void initPSR();
    void initSSR();

    // Process management functions
    void createAircraftThreads();
    void createATCSSubsystems();
    void storeAircraftProcessId(int pid);
    void storeATCSProcessId(int pid);
    int createAircraftTransponderDataChannel();

    // Thread execution functions
    static void * threadUpdateAircraftPosition(void * aircraft);
    static void * threadServiceInterrogationSignal(void * aircraft);
    static void * threadExecutionToPSR(void * psr);
    static void * threadExecutionToSSR(void * ssr);

    // Simulation functions
    void execute();
    void configureSimulation();
    void runSimulation();
    void spawnNewAircraftThreads(Aircraft& nextAircraft);

private:
    vector<int> aircraft_pids;
    vector<int> ATCS_pids;
    vector<Aircraft> *AircraftSchedule;

};



#endif /* INC_SYSTEMMANAGER_H_ */
