#ifndef DOORWITHLOCKS_H
#define DOORWITHLOCKS_H

#include "Door.h"

class DoorWithLocks : public Door
{
	public:
	DoorWithLocks(std::string side, bool hasLockers);
	//~DoorWithLocks(){}
	bool GetHasLockers();
	private:
		bool hasLockers;
};

#endif
