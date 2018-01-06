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
	return lightStatus; //hier moet nog iets anders komen denk ipv lightstatus?
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
	//TODO: iets nuttigers returnen? mby ack/nack
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
	//TODO: iets nuttigers returnen? mby ack/nack
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
