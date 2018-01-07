#include "Door.h"
#include <iostream>

Door::Door(Network* network, std::string side)
:network(network)
,doorStatus(false)
,motorType("")
,side(side)
{
	for (int i = 0; i < 3; i++)
	{
		valves.push_back(new Valve(network, i+1, side));
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
/*
bool Door::OpenDoor()
{
	if(doorStatus == false)
	{
		network->SendMessage(network->GetSock(), CreateDoorMessage("open", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			do
			{
				network->SendMessage(network->GetSock(), CreateDoorMessage("", true));
			}
			while(network->ReceiveMessage(network->GetSock()) != "doorOpen;");	
			doorStatus = true;
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "door already open" << std::endl;
		return false;
	}
}*/
/*
bool Door::CloseDoor()
{
	if(doorStatus == true)
	{
		network->SendMessage(network->GetSock(), CreateDoorMessage("close", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			do
			{
				network->SendMessage(network->GetSock(), CreateDoorMessage("", true));
			}
			while(network->ReceiveMessage(network->GetSock()) != "doorClosed;");	
			doorStatus = false;		
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "door already closed" << std::endl;
		return false;
	}
}*/


bool Door::OpenDoor()
{
    if(GetDoorStatus() == false)
	{

		network->SendMessage(network->GetSock(), CreateDoorMessage("open", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			while(CheckDoorState() != "doorOpen;")
			{
        	}
			doorStatus = true;
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "door already open" << std::endl;
		return false;
	}
}

bool Door::CloseDoor()
{
    if(GetDoorStatus() == true)
	{		
		network->SendMessage(network->GetSock(), CreateDoorMessage("close", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
        	while(CheckDoorState() != "doorClosed;")
       	 	{            
			}
			doorStatus = false;		
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "door already closed" << std::endl;
		return false;
	}
}

void Door::StopDoor()
{
	if (CheckDoorState() == "doorOpening;" || CheckDoorState() == "DoorClosing;")
	{
		network->SendMessage(network->GetSock(), CreateDoorMessage("stop", false));
		network->ReceiveMessage(network->GetSock());
	}
}

std::string Door::CheckDoorState()
{
	network->SendMessage(network->GetSock(), CreateDoorMessage("", true));
	return network->ReceiveMessage(network->GetSock());
}

std::vector<Valve*> Door::GetValves()
{
	return valves;
}

std::string Door::CreateDoorMessage(std::string action, bool get)
{
	if (!side.compare("Left") || !side.compare("Right"))
	{
		if (get)
		{
			return "GetDoor" + side + ";";
		}
		if (!action.compare("open") || !action.compare("close") || !action.compare("stop"))
		{
			// Set asked
			return "SetDoor" + side + ":" + action + ";";
		}
	}
	return "";
}

Network* Door::GetNetwork()
{
	return network;
}


