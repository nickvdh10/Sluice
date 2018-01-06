#ifndef DOORWITHLOCK_H
#define DOORWITHLOCK_H

#include "Door.h"

class DoorWithLock : public Door
{
	public:
	DoorWithLock(Network* network, std::string side);
	~DoorWithLock();
	bool OpenDoor();
	bool CloseDoor();
	//std::vector<std::string> CreateDoorMessage(std::string action, bool get);

};

#endif
