#include "TrafficLight.h"

TrafficLight::TrafficLight(bool lightStatus)
:lightStatus(lightStatus)
{
}

bool TrafficLight::GetLightStatus()
{
	return lightStatus;
}

void TrafficLight::SetGreen()
{
	lightStatus = true;
}

void TrafficLight::SetRed()
{
	lightStatus = false;
}
