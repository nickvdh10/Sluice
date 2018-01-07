#include "DoorWithLock.h"
#include <iostream>

DoorWithLock::DoorWithLock(Network* network, std::string side)
:Door(network, side)
{
	
}

DoorWithLock::~DoorWithLock()
{
	
}

bool DoorWithLock::OpenDoor()
{
	Network* network = GetNetwork();
	if (GetDoorStatus() == false)
	{
		std::string openLock = "SetDoorLock" + GetDoorSide() + ":" + "off" + ";";
		std::string closeLock = "SetDoorLock" + GetDoorSide() + ":" + "on" + ";";
		network->SendMessage(network->GetSock(), openLock);
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			Door::OpenDoor();
			return true;
		}
	}
	return false;
}

bool DoorWithLock::CloseDoor()
{
	Network* network = GetNetwork();
	if (GetDoorStatus() == true)
	{
		std::string openLock = "SetDoorLock" + GetDoorSide() + ":" + "off" + ";";
		std::string closeLock = "SetDoorLock" + GetDoorSide() + ":" + "on" + ";";
		Door::CloseDoor();
		network->SendMessage(network->GetSock(), closeLock);
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			while(CheckDoorState() != "doorLocked;")
			{
			}
			return true;
		}
	}
	return false;	
}
