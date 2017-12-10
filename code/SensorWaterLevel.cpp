#include "SensorWaterLevel.h"

SensorWaterLevel::SensorWaterLevel()
{
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
