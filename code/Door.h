#ifndef DOOR_H
#define DOOR_H

#include "IDoor.h"
#include "IValve.h"

class Door: public IDoor
{
	public:
		Door();
		~Door();
		void OpenDoor();
		void CloseDoor();
	private:
		IValve valve1;
		IValve valve2;
		IValve valve3;
		bool doorStatus();
		std::string motorType();
}

#endif
