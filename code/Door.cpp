#include "Door.h"
#include <iostream>

Door::Door(std::string side)
:doorStatus(false)
,motorType("")
,side(side)
{
	//TODO: initialize vector with 3 valves
	for (int i = 0; i < 3; i++)
	{
		valves.push_back(new Valve(i+1, side));
		
	}
	for (int i = 0; i < 3; i++)//test loop
	{
		std::cout << valves[i]->GetValveLevel() << std::endl << valves[i]->GetValveSide() << std::endl;
	}
}

Door::~Door()
{
}

bool Door::GetDoorStatus()
{
	return doorStatus;
}

std::string Door::GetDoorSide() const
{
	return side;
}

std::string Door::OpenDoor()
{
	if(doorStatus == false)
	{
		doorStatus = true;
		std::string messageToSend = CreateDoorMessage("open", false);
		return messageToSend;
	}
	else
	{
		std::cout << "door already open" << std::endl;
		return "";
	}
}

std::string Door::CloseDoor()
{
	if(doorStatus == true)
	{
		doorStatus = false;
		std::string messageToSend = CreateDoorMessage("close", false);
		return messageToSend;
	}
	else
	{
		std::cout << "door already closed" << std::endl;
		return "";
	}
	
	
}

std::string Door::CreateDoorMessage(std::string action, bool get)
{
	if (!side.compare("Left") || !side.compare("Right"))
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


