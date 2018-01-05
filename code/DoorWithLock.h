#ifndef DOORWITHLOCK_H
#define DOORWITHLOCK_H

#include "Door.h"

class DoorWithLock : public Door
{
	public:
	DoorWithLock(std::string side);
	~DoorWithLock();
	std::vector<std::string> CreateDoorMessage(std::string action, bool get);

};

#endif
