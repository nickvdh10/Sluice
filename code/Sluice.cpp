#include "Sluice.h"

const char* standardIp = "127.0.0.1";

Sluice::Sluice(int portNumber)
:portNumber(portNumber)
,waterLevel(waterLevel)
,sluiceStatus(sluiceStatus)
{
    Network* network;
    sock = network->CreateConnection(standardIp, portNumber);
}
Sluice::~Sluice()
{

}

double Sluice::GetWaterLevel()
{
    return waterLevel
}

bool Sluice::GetSluiceStatus()
{
    return sluiceStatus;
}
int GetPortNumber()
{
    return portNumber;
}
void SendCommand(std::string command)
{
    Network* network;
    network->SendMessage(sock, command);
}