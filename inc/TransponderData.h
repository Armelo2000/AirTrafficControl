/*******************************************************
 * TransponderData.h
 *
 *  Created on: 04-04-2023
 *      Author: Armel
 *
 *  This file define the Datatyp for the data that are
 *  transmitted from Aircraft (Transponder data) to the
 *  Interrogator and from interrogator to the Aircraft
 **********************************************************/

#ifndef INC_TRANSPONDERDATA_H_
#define INC_TRANSPONDERDATA_H_

typedef struct
{
    int flightId;
    int positionX;
    int positionY;
    int positionZ;
    int speedX;
    int speedY;
    int speedZ;

 } TTransponderData;

 typedef struct
 {
     int code;
 } TInterrogationSignal;


#endif /* INC_TRANSPONDERDATA_H_ */
