#include "Door.h"


Door::Door()
:doorStatus(true)
,motorType("")
{
	//TODO: initialize vector with 3 valves
}

void Door::OpenDoor()
{
	doorStatus = true;
}

void Door::CloseDoor()
{
    doorStatus = false;
}
