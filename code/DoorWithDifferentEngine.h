#ifndef DOORWITHDIFFERENTENGINE_H
#define DOORWITHDIFFERENTENGINE_H

#include "Door.h"

class DoorWithDifferentEngine : public Door
{
	public:
	DoorWithDifferentEngine(std::string side, bool hasDifrentEngine);
	//~DoorWithDifferentEngine(){}
	bool GetHasDifrentEngine();
	private:
		bool hasDifrentEngine;
};

#endif
