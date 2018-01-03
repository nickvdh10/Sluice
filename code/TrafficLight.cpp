#include "TrafficLight.h"
#include <iostream>
#include <sstream>

TrafficLight::TrafficLight(bool lightStatus)
:lightStatus(lightStatus)
{
}

bool TrafficLight::GetLightStatus()
{
	return lightStatus;
}

std::string TrafficLight::SetGreen()
{
	lightStatus = true;
	return "";
}

std::string TrafficLight::SetRed()
{
	lightStatus = false;
	return "";
}

std::string TrafficLight::CreateTrafficLightMessage(std::string action, int number, bool get)
{
	//SetTrafficLight[1..4][Red|Green]:[on|off]
	//GetTrafficLight[1..4][Red|Green]
	// TODO: replace first "colour" with a number propperty
	std::stringstream ss;
	std::string colour = lightStatus ? "Green" : "Red";
	if (get)
	{

		ss << "SetTrafficLight" << number << colour << ";";
		return ss.str();
	}
	
	if (!action.compare("on") || !action.compare("off"))
	{
		// Set asked
		ss << "SetTrafficLight" << number << colour << ";";
		std::cout << ss.str() << std::endl;
		return ss.str();
	}
	return "FAIL";
}
