#ifndef SLUICE_H
#define SLUICE_H

#include "Network.h"
#include "TrafficLight.h"
#include "SensorWaterLevel.h"
#include "Door.h"
#include "DoorWithDifferentEngine.h"
#include "DoorWithLock.h"


class Sluice
{
	public:
		Sluice(int portNumber);
		~Sluice();
		std::string GetSluiceState() const;
		void SetSluiceState(std::string);
		void ChangeLevel(Door* door);
		int StartSluicing();
		void Sluicing(Door* door1, Door* door2);
		std::string Alarm();
		
	private:
		Door* highWaterDoor;
		Door* lowWaterDoor;
		std::vector<TrafficLight*> trafficLights;
		Network* network;
		SensorWaterLevel* sensorWaterLevel;
		std::string sluiceState;
		
		Sluice(const Sluice&) { /* do nothing */ };
		Sluice& operator= (const Sluice&) { return *this; };   
};

#endif
