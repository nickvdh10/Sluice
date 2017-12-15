#include "Door.h"


Door::Door()
:doorStatus(true)
,motorType("")
{
	//TODO: initialize vector with 3 valves
}

bool Door::GetDoorStatus()
{
	return doorStatus;
}

void Door::OpenDoor()
{
	doorStatus = true;
}

void Door::CloseDoor()
{
    doorStatus = false;
}

std::string Door::CreateDoorMessage(std::string side, std::string action, bool get)
{
	if (!side.comapre("Left") || !side.comapre("Right"))
	{
		if (!action.compare("open") || !action.compare("close") || !action.compare("stop"))
		{

			if (get)
			{
				return "GetDoor" + side + ":" + action + ";";
			}
			// Set asked
			return "SetDoor" + side + ":" + action + ";";
		}
	}
	return "";
}


