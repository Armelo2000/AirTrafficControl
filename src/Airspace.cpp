/*
 * Airspace.cpp
 *
 *  Created on: 08.04.2023
 *      Author: melah
 */

#include <fstream>
#include "inc/Airspace.h"
#include "inc/Aircraft.h"

Airspace::Airspace(){
   aircraftCount = 0;
}

void Airspace::registerAirCreaft(unsigned int count){
	//register all plane
	for(int i=0; i<count; i++){
		Aircraft* aircraft = new Aircraft(BOUNDARY_TIME_START + (BOUNDARY_TIME_INC * i),
				FLIGTH_ID_START + i,
				XPOSITION_START + (XPOSITION_INC * i), YPOSITION_START + (YPOSITION_INC * i),
				ZPOSITION_START + (ZPOSITION_INC * i), XSPEED_START + (XSPEED_INC * i),
				YSPEED_START + (YSPEED_INC * i), ZSPEED_START + (ZSPEED_INC * i));

		if((aircraft->getXCoordinate() < AIRSPACE_MIN_XFEET)|
				(aircraft->getXCoordinate() > (AIRSPACE_XFEET + AIRSPACE_MIN_XFEET))|
				(aircraft->getYCoordinate() < AIRSPACE_MIN_YFEET)|
				(aircraft->getYCoordinate() > (AIRSPACE_YFEET + AIRSPACE_MIN_YFEET))|
				(aircraft->getZCoordinate() < AIRSPACE_MIN_ZFEET)|
				(aircraft->getZCoordinate() > (AIRSPACE_ZFEET + AIRSPACE_MIN_ZFEET))){

			//The plane is out of airspace
			m_aircraftSchedule.push_back(aircraft);
			cout<<"The registered plane Id: "<<aircraft->getAircraftID()<<
					" is out of airspace. X Position: "<<aircraft->getXCoordinate()<<
					" - Y Position: "<<aircraft->getYCoordinate()<<" - Z Position: "<<
					aircraft->getZCoordinate()<<endl;


		}else{
			//the plane is inside the
			m_aircraftSchedule.push_back(aircraft);
			m_aircraftInAirspace.push_back(aircraft);
			cout<<"The registered plane Id: "<<aircraft->getAircraftID()<<
								" is in the airspace. X Position: "<<aircraft->getXCoordinate()<<
								" - Y Position: "<<aircraft->getYCoordinate()<<" - Z Position: "<<
								aircraft->getZCoordinate()<<endl;
		}
	}
    aircraftCount = count;
}

vector<Aircraft*> Airspace::getAircraftSchedule(){
	return this->m_aircraftSchedule;
}

vector<Aircraft*> Airspace::getAircraftInAirspace(){
	return this->m_aircraftInAirspace;
}

void Airspace::log_history(Aircraft* plane){
    
      if(plane == nullptr) return;
      std::ofstream myfile;
      myfile.open ("history.csv");
      //The history should look like this
      //Aircraft Id, x position, y position, z position,
      //x speed, y speed, z speed

      myfile << plane->getAircraftID() <<",";
      myfile << plane->getXCoordinate()<<",";
      myfile << plane->getYCoordinate()<<",";
      myfile << plane->getZCoordinate()<<",";
      myfile << plane->getXSpeed()<<",";
      myfile << plane->getYSpeed()<<",";
      myfile << plane->getZSpeed()<<"\n";
      
      myfile.close();

}

void Airspace::setAlarm(Aircraft* aircraft, Aircraft* closeTo){

  //set the alarm
  if((aircraft == nullptr) | (closeTo == nullptr)) return;

   cout<<"ALARM IS SET - The aircraft with Id: "<<
       aircraft->getAircraftID()<<" is close to
       the aircraft with the Id: "<<
       closeTo->getAircraftID ()<<end;

}

void Airspace::AirspaceUpdate(){
 
  if(aircraftCount <= 1) return;

  int j = 0;
   // Loop over aircrafts
  for(int i=0; i<aircraftCount-1; i++){
     j=i+1;
     auto aircraft = m_aircraftInAirspace.at(i);
     for(; j<aircraftCount; j++){
       auto next = m_aircraftInAirspace.at(j);
       if(aircraft->isCloseTo(next)){
         //Add to collision list and set alarm 
         setAlarm(aircraft, next);

          if (std::find(aircraft->aircraftCloseTo.begin(), aircraft->aircraftCloseTo.end(), next) != aircraft->aircraftCloseTo.end()) {
             // std::cout << "Element found";
          }
          else {
              //std::cout << "Element not found";
             aircraft->aircraftCloseTo.pushback(next);
             aircraft->aircraftCloseToCount++;
          }

          if (std::find(next->aircraftCloseTo.begin(), next->aircraftCloseTo.end(), aircraft) != next->aircraftCloseTo.end()) {
             // std::cout << "Element found";
          }
          else {
              //std::cout << "Element not found";
             next->aircraftCloseTo.pushback(aircraft);
             next->aircraftCloseToCount++;
          }

       } else {
         //Remove from collision list and reset alarm 
         if (std::find(aircraft->aircraftCloseTo.begin(), aircraft->aircraftCloseTo.end(), next) != aircraft->aircraftCloseTo.end()) {
             //Remove next from the list 
             aircraft->aircraftCloseTo.remove(next);
             aircraft->aircraftCloseToCount--;
          }
          
          if (std::find(next->aircraftCloseTo.begin(), next->aircraftCloseTo.end(), aircraft) != next->aircraftCloseTo.end()) {
             //Remove aircraft from the list 
             next->aircraftCloseTo.remove(aircraft);
             next->aircraftCloseToCount--;
          }

       }

    }

  }


}

