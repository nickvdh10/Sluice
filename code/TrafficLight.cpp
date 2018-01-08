#include "TrafficLight.h"
#include <sstream>

TrafficLight::TrafficLight(Network* network, bool lightStatus, int number)
:network(network)
,lightStatus(lightStatus)
,number(number)
{
}

bool TrafficLight::GetLightStatus()
{
	network->SendMessage(network->GetSock() ,CreateTrafficLightMessage("", "Green", number, true));
	std::string greenStatus = network->ReceiveMessage(network->GetSock());
	network->SendMessage(network->GetSock() ,CreateTrafficLightMessage("", "Red", number, true));
	std::string redStatus = network->ReceiveMessage(network->GetSock());
	if (greenStatus == "on" && redStatus == "off")
	{
		return true;
	}
	else if (greenStatus == "off" && redStatus == "on")
	{
		return false;
	}
	return lightStatus;
}

bool TrafficLight::SetGreen()
{
	lightStatus = true;
	std::string message1 = CreateTrafficLightMessage("off", "Red", number, false);
	network->SendMessage(network->GetSock(), message1);
	network->ReceiveMessage(network->GetSock());
	std::string message2 = CreateTrafficLightMessage("on", "Green", number, false);
	network->SendMessage(network->GetSock(), message2);
	network->ReceiveMessage(network->GetSock());
	return lightStatus;
}

bool TrafficLight::SetRed()
{ 
	lightStatus = false;
	std::string message1 = CreateTrafficLightMessage("off", "Green", number, false);
	network->SendMessage(network->GetSock(), message1);
	network->ReceiveMessage(network->GetSock());
	std::string message2 = CreateTrafficLightMessage("on", "Red", number, false);
	network->SendMessage(network->GetSock(), message2);
	network->ReceiveMessage(network->GetSock());
	return lightStatus;
}

std::string TrafficLight::CreateTrafficLightMessage(std::string action, std::string colour, int number, bool get)
{
	std::stringstream ss;
	if (get)
	{
		ss << "GetTrafficLight" << number << colour << ";";
		return ss.str();
	}
	
	if (!action.compare("on") || !action.compare("off"))
	{
		// Set asked
		ss << "SetTrafficLight" << number << colour << ":" << action << ";";
		return ss.str();
	}
	return "FAIL";
}
