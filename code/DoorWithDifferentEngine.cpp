#include "DoorWithDifferentEngine.h"
#include <iostream>

DoorWithDifferentEngine::DoorWithDifferentEngine(Network* network, std::string side)
:Door(network, side)
{
}

DoorWithDifferentEngine::~DoorWithDifferentEngine()
{
}

bool DoorWithDifferentEngine::OpenDoor()
{
	Network* network = GetNetwork();
    if(GetDoorStatus() == false)
	{

		network->SendMessage(network->GetSock(), CreateDoorMessage("open", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			while(CheckDoorState() != "doorOpen;")
			{
                network->SendMessage(network->GetSock(), CreateDoorMessage("open", false));
                network->ReceiveMessage(network->GetSock());   
        	}
			SetDoorStatus(true);
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

bool DoorWithDifferentEngine::CloseDoor()
{
	Network* network = GetNetwork();
    if(GetDoorStatus() == true)
	{		
        network->SendMessage(network->GetSock(), CreateDoorMessage("close", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
        	while(CheckDoorState() != "doorClosed;")
       	 	{
                network->SendMessage(network->GetSock(), CreateDoorMessage("close", false));  
                network->ReceiveMessage(network->GetSock());          
			}
            SetDoorStatus(false);		
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
