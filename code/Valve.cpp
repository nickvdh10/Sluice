#include "Valve.h"
#include <iostream>
#include <sstream>

Valve::Valve(Network* network, int valveLevel, std::string side)
:network(network)
,valveLevel(valveLevel)
,side(side)
,valveStatus(false)
{
}

bool Valve::GetValveStatus()
{
	return valveStatus;
}
int Valve::GetValveLevel()
{
	return valveLevel;
}
std::string Valve::GetValveSide()
{
	return side;
}

bool Valve::OpenValve()
{
	if(valveStatus == false)
	{
		valveStatus = true;
		network->SendMessage(network->GetSock(), CreateValveMessage("open", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "valve already open" << std::endl;
		return false;
	}
}

bool Valve::CloseValve()
{
	if(valveStatus == true)
	{
		valveStatus = false;
		network->SendMessage(network->GetSock(), CreateValveMessage("close", false));
		if (network->ReceiveMessage(network->GetSock()) == "ack;")
		{
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "valve already closed" << std::endl;
		return false;
	}
}

std::string Valve::CreateValveMessage(std::string action, bool get)
{
	std::stringstream ss;
	std::cout << valveLevel;
	if (valveLevel == 1 || valveLevel == 2 || valveLevel == 3)
	{
		if (get)
		{
			ss << "GetDoor" << side << "Valve" << valveLevel << ";";
			return ss.str();
		}
		if (!action.compare("open") || !action.compare("close"))
		{
			// Set asked
			ss << "SetDoor" << side << "Valve" << valveLevel << ":" << action << ";";
			std::cout << ss.str() << std::endl;
			return ss.str();
		}
	}
	
	return "FAIL";
}
