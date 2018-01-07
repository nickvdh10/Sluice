#ifndef IDOOR_H
#define IDOOR_H

#include <string>
#include "Network.h"

class IDoor
{
	public:
		virtual ~IDoor(){}
		virtual bool OpenDoor() = 0;
		virtual bool CloseDoor() = 0;
		virtual void StopDoor() = 0;		
		
};

#endif
