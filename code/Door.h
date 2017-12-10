#ifndef DOOR_H
#define DOOR_H

#include "IDoor.h"
#include "IValve.h"
#include <vector>
#include <string>

class Door: public IDoor
{
	public:
		Door();
		~Door(){}
		void OpenDoor();
		void CloseDoor();
	private:
		std::vector<IValve> valves;
		bool doorStatus;
		std::string motorType;
};

#endif
