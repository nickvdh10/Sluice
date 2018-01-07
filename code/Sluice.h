#ifndef SLUICE_H
#define SLUICE_H

#include "Door.h"
#include "Network.h"
#include "ITrafficLight.h"
#include "TrafficLight.h"
#include "ISensorWaterLevel.h"
#include "SensorWaterLevel.h"
#include "SluiceControl.h"
#include "DoorWithDifferentEngine.h"
#include "DoorWithLock.h"
#include "IDoor.h"
#include "Door.h"


class Sluice
{
	public:
		Sluice(int portNumber);
		~Sluice();
		std::string GetWaterLevel() const;
		bool GetSluiceStatus() const;
		int GetPortNumber() const;
		int GetSock() const;
		void SetSluiceState(std::string);
		std::string ChangeLevel(Door* door);
		int StartSluicing();
		void GiveFreeOut(int* trafficlightNumber1, int* trafficlightNumber2);
		void GiveFreeIn(int* trafficlightNumber1, int* trafficlightNumber2);
		void Sluicing(Door* door1, Door* door2);
		std::string SendCommand(std::string SendCommand);
		std::string Alarm();
		
		
	private:
		Door* highWaterDoor;
		Door* lowWaterDoor;
		std::vector<TrafficLight*> trafficLights;
		Network* network;
		SensorWaterLevel* sensorWaterLevel;
		int portNumber;
		int sock;
		std::string waterLevel;
		bool sluiceStatus;
		std::string sluiceState;
		
		// Empty copyconst and assignment operator since we don't want copies to be made (?)
		Sluice(const Sluice&) { /* do nothing */ };
		Sluice& operator= (const Sluice&) { return *this; };   
};

#endif
