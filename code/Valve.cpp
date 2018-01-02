#include "Valve.h"
#include <iostream>
#include <sstream>

Valve::Valve(int valveLevel, std::string side)
:valveLevel(valveLevel)
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

std::string Valve::OpenValve()
{
	if(valveStatus == false)
	{
		valveStatus = true;
		std::string messageToSend = CreateValveMessage("open", false);
		return messageToSend;
	}
	else
	{
		std::cout << "valve already open" << std::endl;
		return "";
	}
}

std::string Valve::CloseValve()
{
	if(valveStatus == true)
	{
		valveStatus = false;
		std::string messageToSend = CreateValveMessage("close", false);
		return messageToSend;
	}
	else
	{
		std::cout << "valve already closed" << std::endl;
		return "";
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
