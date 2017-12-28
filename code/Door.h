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
		Door(std::string side);
		~Door();
		bool GetDoorStatus();
		std::string OpenDoor();
		std::string CloseDoor();
		std::string CreateDoorMessage(std::string action, bool get);
	private:
		std::vector<Valve> valves;
		bool doorStatus;
		std::string motorType;
		std::string side;
};

#endif
