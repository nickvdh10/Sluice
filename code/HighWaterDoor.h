#ifndef HIGHWATERDOOR_H
#define HIGHWATERDOOR_H

#include "Door.h"

class HighWaterDoor : public Door
{
	public:
	HighWaterDoor();
	~HighWaterDoor{}
	void ToHighWaterLevel();
}

#endif
