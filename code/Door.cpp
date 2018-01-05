#include "Door.h"
#include <iostream>

Door::Door(std::string side)
:doorStatus(false)
,motorType("")
,side(side)
{
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
	for (unsigned int i = 0; i < valves.size(); i++)
    {
		delete valves[i];
		valves[i] = NULL;
	}
}
void Door::SetDoorStatus(bool status)
{
	doorStatus = status;
}
bool Door::GetDoorStatus()
{
	return doorStatus;
}

std::string Door::GetDoorSide() const
{
	return side;
}

void Door::OpenDoor()
{
	/*std::vector<std::string> messageToSend;
	if(doorStatus == false)
	{
		doorStatus = true;
		messageToSend = CreateDoorMessage("open", false);
		std::cout << messageToSend[0] << std::endl;
		return messageToSend;
	}
	std::cout << "door already closed" << std::endl;
	return messageToSend;*/
	if(doorStatus == false)
	{
		doorStatus = true;
	}
}

void Door::CloseDoor()
{
	/*std::vector<std::string> messageToSend;
	if(doorStatus == true)
	{
		doorStatus = false;
		messageToSend = CreateDoorMessage("close", false);
	}

	std::cout << "door already closed" << std::endl;
	return messageToSend;*/
	if(doorStatus == true)
	{
		doorStatus = false;
	}
}
std::vector<std::string> Door::CheckDoorState()
{
	std::vector<std::string> doorState = CreateDoorMessage("", true);
	return doorState;
}

std::vector<Valve*> Door::GetValves()
{
	return valves;
}

std::vector<std::string> Door::CreateDoorMessage(std::string action, bool get)
{
	std::vector<std::string> messages;
	std::string message;
	if (!side.compare("Left") || !side.compare("Right"))
	{
		if (get)
		{
			//return "GetDoor" + side + ";";
			message = "GetDoor" + side + ";";
			messages.push_back(message);
			return messages;
		}
		if (!action.compare("open") || !action.compare("close") || !action.compare("stop"))
		{
			// Set asked
			//return "SetDoor" + side + ":" + action + ";";
			message = "SetDoor" + side + ":" + action + ";";
			messages.push_back(message);
		}
	}
	return messages;
}


