/*
 * SystemManager.cpp
 *
 *  Created on: 05.04.2023
 *      Author: melah
 */

#include "inc/SystemManager.h"
#include "inc/PSR.h"
#include "inc/SSR.h"

/* -----------------------------------------------------------------------------
 * This is the constructor of the SystemManager class, which
 *              initializes the object.
 * -----------------------------------------------------------------------------
 */
SystemManager::SystemManager() {
}

/* -----------------------------------------------------------------------------
 * Name:        SystemManager
 * Input:       vector of Aircraft objects
 * Output:      None
 * Description: This is a constructor of the SystemManager class that
 *              initializes the AircraftSchedule vector.
 * -----------------------------------------------------------------------------
 */
SystemManager::SystemManager(vector<Aircraft> *AircraftArr) {

    this->AircraftSchedule = AircraftArr;

    cout << "Aircraft schedule: " << AircraftSchedule << endl;

    cout << "Aircraft a1: " << &AircraftSchedule[0] << endl;
    cout << "Aircraft a2: " << &AircraftSchedule[1] << endl;

}

/* -----------------------------------------------------------------------------
 * Name:        ~SystemManager
 * Input:       None
 * Output:      None
 * Description: Destructor for the SystemManager class.
 * -----------------------------------------------------------------------------
 */
SystemManager::~SystemManager() {
    // TODO Auto-generated destructor stub
}


/* -----------------------------------------------------------------------------
 * Name:        initDataDisplay
 * Input:       None
 * Output:      None
 * Description: This function initializes the Data Display subsystem.
 * -----------------------------------------------------------------------------
 */
void SystemManager::initDataDisplay() {

    cout << "Initializing Data Display..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initComputerSystem
 * Input:       None
 * Output:      None
 * Description: This function initializes the Computer System subsystem.
 * -----------------------------------------------------------------------------
 */
void SystemManager::initComputerSystem() {

    cout << "Initializing Computer System..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initCommunicationSystem
 * Input:       None
 * Output:      None
 * Description: This function initializes the Communication System subsystem.
 * -----------------------------------------------------------------------------
 */
void SystemManager::initCommunicationSystem() {

    cout << "Initializing Communication System..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initOperatorConsole
 * Input:       None
 * Output:      None
 * Description: This function initializes the Operator Console subsystem.
 * -----------------------------------------------------------------------------
 */
void SystemManager::initOperatorConsole() {

    cout << "Initializing Operator Console..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initRadar
 * Input:       None
 * Output:      None
 * Description: This function initializes the Radar subsystem and calls the
 *              initPSR() function.
 *
 * -----------------------------------------------------------------------------
 */
void SystemManager::initRadar() {

    cout << "Initializing Radar..." << endl;

    initPSR();

}

/* -----------------------------------------------------------------------------
 * Name:        initPSR
 * Input:       None
 * Output:      None
 * Description: This function creates a dynamic instance of the PSR class and
 *              creates a new thread to execute it using the threadExecutionToPSR()
 *              function.
 * -----------------------------------------------------------------------------
 */
void SystemManager::initPSR() {

    int err_no;
    pthread_t PSR_thread_id;

    // Create a dynamic instance of the PSR class
    PSR *psr = new PSR(AircraftSchedule);

    err_no = pthread_create(&PSR_thread_id,
                            NULL,
                            &threadExecutionToPSR,
                           psr);
    if (err_no != 0) {
       // cout << "ERROR when creating PSR thread: " << err_no << endl;
    } else {
       // cout << " PSR with thread ID: " << PSR_thread_id << " created" << endl;
    }

}

/* -----------------------------------------------------------------------------
 * Name:
 * Input:
 * Output:
 * Description:
 * -----------------------------------------------------------------------------
 */
void SystemManager::initSSR() {

}
/* -----------------------------------------------------------------------------
 * Name:        createAircraftThreads
 * Input:       None
 * Output:      None
 * Description: This function creates threads for each Aircraft object in the
 *              AircraftSchedule vector by calling spawnNewAircraftThread().
 * -----------------------------------------------------------------------------
 */
void SystemManager::createAircraftThreads() {

    cout << "Creating Aircraft threads" << endl;

    for (Aircraft &nextAircraft : *AircraftSchedule) {


        cout << &nextAircraft << endl;
        int chid = createAircraftTransponderDataChannel();
        nextAircraft.setTransponderDataChannel(chid);
        spawnNewAircraftThreads(nextAircraft);
    }
}

/* -----------------------------------------------------------------------------
 * Name:        createATCSSubsystems
 * Input:       None
 * Output:      None
 * Description: This function initializes the ATCS subsystems by calling the
 *              initialize functions for the Data Display, Computer System,
 *              Communication System, Operator Console, and Radar.
 * -----------------------------------------------------------------------------
 */
void SystemManager::createATCSSubsystems() {

    cout << "Initializing ATCS subsystems..." << endl;
    initDataDisplay();
    initComputerSystem();
    initCommunicationSystem();
    initOperatorConsole();
    initRadar();
}
/* -----------------------------------------------------------------------------
 * Name:        threadExecutionToAircraft
 * Input:       void pointer to an Aircraft object
 * Output:      void pointer
 * Description: This function forwards execution to an Aircraft object to update
 *              its position.
 * -----------------------------------------------------------------------------
 */
void* SystemManager::threadUpdateAircraftPosition(void *aircraft) {
    static_cast<Aircraft*>(aircraft)->updateAircraftPosition();

    return NULL;
}
/* -----------------------------------------------------------------------------
 * Name:        threadExecutionToPSR
 * Input:       void pointer to a PSR object
 * Output:      void pointer
 * Description: This function forwards execution to a PSR object to execute.
 * -----------------------------------------------------------------------------
 */
void* SystemManager::threadExecutionToPSR(void *psr) {

    static_cast<PSR*>(psr)->execute();

    return NULL;
}

/* -----------------------------------------------------------------------------
 * Name:        threadExecutionToSSR
 * Input:       void pointer to an SSR object
 * Output:      void pointer
 * Description: This function forwards execution to an SSR object.
 * -----------------------------------------------------------------------------
 */

void* SystemManager::threadExecutionToSSR(void *ssr) {

    static_cast<PSR*>(ssr)->execute();
    return NULL;
    //pthread_exit(NULL);
}
/* -----------------------------------------------------------------------------
 * Name:		execute
 * Input:		None
 * Output:		None
 * Description: This function executes the ATCS simulation by first configuring
 *              the simulation through the configureSimulation() function.
 *              then, the user is prompted to start the simulation by pressing
 *              'R' and the runSimulation() function is executed if the input
 *              is 'R'.
 * -----------------------------------------------------------------------------
 */
void SystemManager::execute() {

    char input;

    configureSimulation();

    // Execute the ATCS simulation
    cout << "All systems ready, press 'R' to run the simulation." << endl;
    cin >> input;
    if (input == 'R')
        runSimulation();

}
/* -----------------------------------------------------------------------------
 * Name:		configureSimulation
 * Input: 		None
 * Output:		None
 * Description: This function is responsible for configuring the simulation by
 *              creating threads for each aircraft in the AircraftSchedule
 	 	 	 	initializing the ATCS subsystems. It calls
 	 	 	 	createAircraftThreads() and createATCSSubsystems() functions.
 * -----------------------------------------------------------------------------
 */
void SystemManager::configureSimulation() {


    createAircraftThreads();
    createATCSSubsystems();
}

/* -----------------------------------------------------------------------------
 * Name:        runSimulation
 * Input:       None
 * Output:      None
 * Description: This function runs the simulation by printing "Begin of
 *              simulation" to the console.
 * -----------------------------------------------------------------------------
 */
void SystemManager::runSimulation() {

    cout << "Begin of simulation" << endl;

}

int SystemManager::createAircraftTransponderDataChannel() {

    // Create message passing channel

        int chid = 0; //ChannelCreate(0);
        if (chid == -1) {
            //cout << "Error: ChannelCreate failed. Error ID: "<< strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }

    return chid;
}

void* SystemManager::threadServiceInterrogationSignal(void *aircraft) {

    static_cast<Aircraft*>(aircraft)->ServiceInterrogationSignal();

        return NULL;
}

/* -----------------------------------------------------------------------------
 * Name:        spawnNewAircraftThread
 * Input:       reference to an Aircraft object
 * Output:      None
 * Description: This function creates a new thread for an Aircraft object passed
 *              in as an argument, using the fwdExecutionToAircraft() function
 *              to forward execution to the object. If there is an error
 *              creating the thread, an error message is printed.
 * -----------------------------------------------------------------------------
 */
void SystemManager::spawnNewAircraftThreads(Aircraft &nextAircraft) {

    int err_no;
    pthread_t thread_id;

    err_no = pthread_create(&thread_id,
    NULL, &threadUpdateAircraftPosition, &nextAircraft);
    if (err_no != 0) {
        cout << "ERROR when creating thread: " << err_no << endl;
    } else {
        cout << " Aircraft Update position thread created with ID: " << thread_id << endl;
    }

    err_no = pthread_create(&thread_id,
       NULL, &threadServiceInterrogationSignal, &nextAircraft);
       if (err_no != 0) {
           cout << "ERROR when creating thread: " << err_no << endl;
       } else {
           cout << " Aircraft service interrogation signal thread created with ID: " << thread_id << endl;
       }

}
