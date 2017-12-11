#ifndef LOWWATERDOOR_H
#define LOWWATERDOOR_H

#include "Door.h"

class LowWaterDoor : public Door
{
	public:
	LowWaterDoor();
	~LowWaterDoor{}
	void ToLowWaterLevel();
};

#endif
