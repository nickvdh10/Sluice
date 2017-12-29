#include "Valve.h"
#include <iostream>

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
char Valve::GetValveLevel()
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
	if(valveStatus == false)
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
	std::cout << valveLevel;
	if (valveLevel == 1 || valveLevel == 2 || valveLevel == 3)
	{
		if (!action.compare("open") || !action.compare("close") || !action.compare("stop"))
		{
			if (get)
			{
				return "GetDoor" + side + ":" + action + ";";
			}
			// Set asked
			//std::cout << "SetDoor" << side << ":" << action << ";";
			return "SetDoor" + side + "Valve" + valveLevel + ":" + action + ";";
		}
	}
	
	return "FAIL";
}
//TODO: add private copy const
