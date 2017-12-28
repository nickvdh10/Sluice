#ifndef DOOR_H
#define DOOR_H

#include "IDoor.h"
#include "IValve.h"
#include "Valve.h"
#include "Network.h"
#include <vector>
#include <string>

class Door: public IDoor
{
	public:
		Door();
		~Door();
		bool GetDoorStatus();
		void OpenDoor();
		void CloseDoor();
		std::string CreateDoorMessage(std::string side, std::string action, bool get);
	private:
		std::vector<Valve> valves;
		bool doorStatus;
		std::string motorType;
};

#endif
