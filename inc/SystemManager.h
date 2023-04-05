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

    // Constructors and destructor
	SystemManager();
	SystemManager(vector<Aircraft> *AircraftArr);
    virtual ~SystemManager();



};



#endif /* INC_SYSTEMMANAGER_H_ */
