/*
 * SSR.h
 *
 *  Created on: 05.04.2023
 *      Author: melah
 */

#ifndef INC_SSR_H_
#define INC_SSR_H_

#include "inc/Aircraft.h"
#include "inc/PSR.h"
#include "inc/TransponderData.h"
//#include <sys/neutrino.h> // For QNX message passing API
#include <stdint.h> // For data type uint64_t
#include <unistd.h>
#include <errno.h>

class SSR {

private:
	// Object declaration for Transponder Data object
	TTransponderData TD;
	// Vector declaration for illuminatedObjects vector of type Aircraft
	vector<Aircraft* > illuminatedObjects;


public:
    // Constructors and destructor
    SSR(vector<Aircraft*>illuminatedObjects);
    virtual ~SSR();

    // Functions to interact with Aircraft threads and receive their data
    void interrogateAircraft(Aircraft *targetAircraft);
    void receiveTransponderData(TTransponderData illuminatedObject);

    // Function that will run the two previous functions
    void interrogate(vector<Aircraft*> illuminatedObjects);



    // This function will return the result of interrogate
    vector<TTransponderData> sendTransponderData();

    // This execute will execute all function calls for the SSR
    void execute();


    // Public declaration of transponderDataList vector
    vector<TTransponderData> transponderDataList;


};


#endif /* INC_SSR_H_ */
