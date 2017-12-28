#ifndef SLUICE_H
#define SLUICE_H

#include "Door.h"
#include "Network.h"
#include "ITrafficLight.h"
#include "ISensorWaterLevel.h"
#include "SensorWaterLevel.h"
#include "SluiceControl.h"

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
		int StartSluicing();
		std::string SendCommand(std::string SendCommand);
		
		
	private:
		Door* highWaterDoor;
		Door* lowWaterDoor;
		//ITrafficLight* one;
		//ITrafficLight* two;
		//ITrafficLight* three;
		//ITrafficLight* four;
		Network* network;
		SensorWaterLevel* sensorWaterLevel;
		int portNumber;
		int sock;
		std::string waterLevel;
		bool sluiceStatus;
		std::string sluiceState;
};

#endif
