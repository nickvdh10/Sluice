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
		Sluice();
		
		~Sluice();
		
		double GetWaterLevel();
		
		bool GetSluiceStatus();
		
	private:
		IDoor* highWaterDoor;
		IDoor* lowWaterDoor;
		ITrafficLight* one;
		ITrafficLight* two;
		ITrafficLight* three;
		ITrafficLight* four;
		double waterLevel;
		bool sluiceStatus;
}

#endif
