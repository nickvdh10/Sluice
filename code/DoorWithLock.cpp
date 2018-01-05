#include "DoorWithLock.h"
#include <iostream>
DoorWithLock::DoorWithLock(std::string side)
:Door(side)
{
	
}

DoorWithLock::~DoorWithLock()
{
	
}

std::vector<std::string> DoorWithLock::CreateDoorMessage(std::string action, bool get)
{
	std::vector<std::string> messages;
	std::string message;
	if (!GetDoorSide().compare("Left") || !GetDoorSide().compare("Right"))
	{
		if (get)
		{
			//return "GetDoor" + side + ";";
			message = "GetDoor" + GetDoorSide() + ";";
			messages.push_back(message);
			return messages;
		}
		if (!action.compare("open") || !action.compare("close") || !action.compare("stop"))
		{
			// Set asked
			//return "SetDoor" + side + ":" + action + ";";
			message = "SetDoorLock" + GetDoorSide() + ":" + "off" + ";";
			messages.push_back(message);
			message = "SetDoor" + GetDoorSide() + ":" + action + ";";
			messages.push_back(message);
			message = "SetDoorLock" + GetDoorSide() + ":" + "on" + ";";
			messages.push_back(message);
		}
	}
	return messages;
}
