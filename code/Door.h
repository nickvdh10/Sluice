#ifndef DOOR_H
#define DOOR_H

#include "IDoor.h"
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
		std::string GetDoorSide() const;
		std::string OpenDoor();
		std::string CloseDoor();
		std::string CreateDoorMessage(std::string action, bool get);
		std::vector<Valve*> valves;

	private:
		
		bool doorStatus;
		std::string motorType;
		std::string side;
};

#endif
