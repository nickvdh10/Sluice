#include "TrafficLight.h"
#include <iostream>
#include <sstream>

TrafficLight::TrafficLight(Network* network, bool lightStatus, int number)
:network(network)
,lightStatus(lightStatus)
,number(number)
{
}

bool TrafficLight::GetLightStatus()
{
	return lightStatus;
}

std::string TrafficLight::SetGreenOn()
{
	lightStatus = true;
	std::string messageToSend = CreateTrafficLightMessage("on", "Green", number, false);
	return messageToSend;
}
std::string TrafficLight::SetGreenOff()
{
	lightStatus = true;
	std::string messageToSend = CreateTrafficLightMessage("off", "Green", number, false);
	return messageToSend;
}
std::string TrafficLight::SetRedOn()
{
	lightStatus = false;
	std::string messageToSend = CreateTrafficLightMessage("on", "Red", number, false);
	return messageToSend;
}
std::string TrafficLight::SetRedOff()
{
	lightStatus = false;
	std::string messageToSend = CreateTrafficLightMessage("off", "Red", number, false);
	return messageToSend;
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
	lightStatus = true;
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
	//SetTrafficLight[1..4][Red|Green]:[on|off]
	//GetTrafficLight[1..4][Red|Green]
	// TODO: replace first "colour" with a number propperty
	std::stringstream ss;
	//std::string colour = lightStatus ? "Green" : "Red";
	if (get)
	{
		ss << "SetTrafficLight" << number << colour << ";";
		return ss.str();
	}
	
	if (!action.compare("on") || !action.compare("off"))
	{
		// Set asked
		ss << "SetTrafficLight" << number << colour << ":" << action << ";";
		std::cout << ss.str() << std::endl;
		return ss.str();
	}
	return "FAIL";
}
