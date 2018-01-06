#ifndef DOORWITHDIFFERENTENGINE_H
#define DOORWITHDIFFERENTENGINE_H

#include "Door.h"

class DoorWithDifferentEngine : public Door
{
	public:
	DoorWithDifferentEngine(Network* network, std::string side);
	//~DoorWithDifferentEngine(){}
};

#endif
