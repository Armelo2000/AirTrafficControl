/*
 * Aircraft.cpp
 *
 *  Created on: 02.04.2023
 *      Author: Armel
 */

#include "inc/Aircraft.h"
#include "inc/Airspace.h"

Aircraft::Aircraft(BoundaryTime time, uint32_t id, Coordinate x, Coordinate y, Coordinate z,
			 Speed x_speed, Speed y_speed, Speed z_speed): boundary_time(time),
			 ID(id), xPosition(x), yPosition(y), zPosition(z),
			 xSpeed(x_speed), ySpeed(y_speed), zSpeed(z_speed){

   aircraftCloseToCount = 0;
}

Aircraft::Aircraft(BoundaryTime time, uint32_t id, Coordinate x, Coordinate y, Coordinate z):
			 boundary_time(time), ID(id), xPosition(x), yPosition(y), zPosition(z),
			 xSpeed(0), ySpeed(0), zSpeed(0){

    aircraftCloseToCount = 0;
}


/**********************************************
 * This Function return the ID of the Aircraft
 *********************************************/
uint32_t Aircraft::getAircraftID(){
	return this->ID;
}

/**********************************************
 * This Function return the current x position
 *********************************************/
Coordinate Aircraft::getXCoordinate(){
	return this->xPosition;
}

/**********************************************
 * This Function return the current y position
 *********************************************/
Coordinate Aircraft::getYCoordinate(){
	return this->yPosition;
}

/**********************************************
 * This Function return the current x position
 *********************************************/
Coordinate Aircraft::getZCoordinate(){
	return this->zPosition;
}

/**********************************************
 * This Function return the current speed in
 * the x-axis
 *********************************************/
Speed Aircraft::getXSpeed(){
	return this->xSpeed;
}

/**********************************************
 * This Function return the current speed in
 * the Y-axis
 *********************************************/
Speed Aircraft::getYSpeed(){
	return this->ySpeed;
}

/**********************************************
 * This Function return the current speed in
 * the z-axis
 *********************************************/
Speed Aircraft::getZSpeed(){
	return this->zSpeed;
}

int Aircraft::getTransponderDataChannel() {

   return m_transponderDataChannel;
}

/*********************************************
 * This function set the Channel Id of the
 * transponder
 */
void Aircraft::setTransponderDataChannelId(int channelId){
	this->m_transponderDataChannel = channelId;
}

/**********************************************
 * This Function update the position in the
 * x-axis
 *********************************************/
void Aircraft::updateXCoordinate(){
	this->xPosition += xSpeed;
}

/**********************************************
 * This Function update the position in the
 * y-axis
 *********************************************/
void Aircraft::updateYCoordinate(){
	this->yPosition += ySpeed;
}

/**********************************************
 * This Function update the position in the
 * z-axis
 *********************************************/
void Aircraft::updateZCoordinate(){
	this->zPosition += zSpeed;
}

/************************************************
 * This Function update the Speed of the Aircraft
 * in the x-axis
 ************************************************/
void Aircraft::updateXSpeed(Speed xspeed){
	this->xSpeed = xspeed;
}

/************************************************
 * This Function update the Speed of the Aircraft
 * in the y-axis
 ************************************************/
void Aircraft::updateYSpeed(Speed yspeed){
	this->ySpeed = yspeed;
}

/************************************************
 * This Function update the Speed of the Aircraft
 * in the z-axis
 ************************************************/
void Aircraft::updateZSpeed(Speed zspeed){
	this->zSpeed = zspeed;
}

/***************************************************
 * This function update the position of the Aircraft
 * in all directions (x, y, z)
 ****************************************************/
void Aircraft::updateAircraftPosition(){

    cout<<"The thread for aircraft update position is Executing..."<<endl;

    updateXCoordinate();
    updateYCoordinate();
    updateZCoordinate();

    Airspace::update();

    cout<<"Execution of Update position is finished..."<<endl;

}

/***************************************************
 * This function set the transponder Channel of the
 * Aircraft
 ****************************************************/
void Aircraft::setTransponderDataChannel(int channelId){
	this->m_transponderDataChannel = channelId;
}

//Communication with the IPC (interrogator)
void Aircraft::ServiceInterrogationSignal(){
    TTransponderData reply_msg;
    TInterrogationSignal interrogationSignal;

    cout << "Servicing interrogation signal" << endl;
    // Wait for a message on the channel
    //TODO MsgReceive is removed in Eclipse IDE
    int rcvid = 0; //MsgReceive(transponderDataChannel, &interrogationSignal, sizeof(interrogationSignal), NULL);

    if (rcvid == -1) {
        cout << "Failed to receive message in aircraft. Error Code: " << strerror(errno) << endl;
       exit(EXIT_FAILURE);
    }
    else
    {
       cout<<"Message Received."<<endl;
    }

    // Construct reply message

    reply_msg.flightId    = this->ID;
    reply_msg.positionX   = this->xPosition;
    reply_msg.positionY   = this->yPosition;
    reply_msg.positionZ   = this->zPosition;
    reply_msg.speedX      = this->xSpeed;
    reply_msg.speedY      = this->ySpeed;
    reply_msg.speedZ      = this->zSpeed;

    //TODO MsgReply is removed in Eclipse IDE
   int returnCode = 0; //MsgReply(rcvid, EOK, &reply_msg, sizeof(reply_msg));
   if (returnCode == -1) {
       cout << "Failed to send reply message in ServiceInterrogationSignal. Error Code: " << strerror(errno) << endl;
       exit(EXIT_FAILURE);
   }

   cout << "Finished servicing interrogation signal" << endl;
}

//This function check if an aircraft is closed to another 
bool Aircraft::isCloseTo(Aircraft* anotherAircraft)
{
   if(anotherAircraft == nullptr) return false;

   if(xPosition > anotherAircraft->xPosition){
     if((xPosition - anotherAircraft->xPosition) <= 10000){
       return true;
     }
   }else{
     if((anotherAircraft->xPosition - xPosition) <= 10000){
       return true;
     }
   }

   if(yPosition > anotherAircraft->yPosition){
     if((yPosition - anotherAircraft->yPosition) <= 10000){
       return true;
     }
   }else{
     if((anotherAircraft->yPosition - yPosition) <= 10000){
       return true;
     }
   }

   if(zPosition > anotherAircraft->zPosition){
     if((zPosition - anotherAircraft->zPosition) <= 10000){
       return true;
     }
   }else{
     if((anotherAircraft->zPosition - zPosition) <= 10000){
       return true;
     }
   }
   return false;
}

/********************************************************
 * This function is called until the interrogation
 * arrives. The Interrogation signal move from IPC to
 * Aircraft.
 ********************************************************/
void Aircraft::receiveInterrogationSignal(){

}
