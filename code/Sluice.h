#ifndef SLUICE_H
#define SLUICE_H

#include "IDoor.h"
#include "Network.h"
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
		void SendCommand(std::string SendCommand);
		
	private:
		IDoor* highWaterDoor;
		IDoor* lowWaterDoor;
		ITrafficLight* one;
		ITrafficLight* two;
		ITrafficLight* three;
		ITrafficLight* four;
		Network* network;
		int portNumber;
		int sock;
		double waterLevel;
		bool sluiceStatus;
};

#endif
