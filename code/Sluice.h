#ifndef SLUICE_H
#define SLUICE_H

#include "IDoor.h"
#include "INetwork.h"
#include "ITrafficLight.h"
#include "ISensorWaterLevel.h"
#include "SluiceControl.h"

class Sluice
{
	public:
		Sluice(int portNumber);
		~Sluice();
		double GetWaterLevel() const;
		bool GetSluiceStatus() const;
		int GetPortNumber() const;
		int GetSock() const;
		void SetSluiceState(std::string);
		int StartSluicing();
		void SendCommand(std::string SendCommand);
		
		
	private:
		IDoor* highWaterDoor;
		IDoor* lowWaterDoor;
		ITrafficLight* one;
		ITrafficLight* two;
		ITrafficLight* three;
		ITrafficLight* four;
		INetwork* network;
		ISensorWaterLevel* sensorWaterLevel;
		int portNumber;
		int sock;
		double waterLevel;
		bool sluiceStatus;
		std::string sluiceState;
};

#endif
