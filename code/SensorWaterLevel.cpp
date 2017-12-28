#include "SensorWaterLevel.h"
#include "Network.h"

SensorWaterLevel::SensorWaterLevel()
{
}


std::string SensorWaterLevel::CheckCurrentWaterLevel()
{
	return "GetWaterLevel;";
}

double SensorWaterLevel::GetWaterLevelSluice()
{
	return waterLevelSluice;
}

double SensorWaterLevel::GetWaterLevelLow()
{
	return waterLevelLow;
}

double SensorWaterLevel::GetWaterLevelHigh()
{
	return waterLevelHigh;
}

