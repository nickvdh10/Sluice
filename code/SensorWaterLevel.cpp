#include "SensorWaterLevel.h"

SensorWaterLevel::SensorWaterLevel(Network* network)
:network(network)
{
}


std::string SensorWaterLevel::CheckCurrentWaterLevel()
{
	network->SendMessage(network->GetSock(), "GetWaterLevel;");
	return network->ReceiveMessage(network->GetSock());
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

