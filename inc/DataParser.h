/*
 * DataParser.h
 *
 *  Created on: 05.04.2023
 *      Author: melah
 */

#ifndef INC_DATAPARSER_H_
#define INC_DATAPARSER_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "inc/Aircraft.h"

using namespace std;

class DataParser {
public:
	DataParser(const char* AircraftDataFile);
    vector<Aircraft*> getAircraftSchedule();
    int parse();
    virtual ~DataParser();

private:

    const char * m_aircraftDataFile;
    vector<Aircraft*> m_aircraftSchedule;
};


#endif /* INC_DATAPARSER_H_ */
