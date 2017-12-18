#include "Sluice.h"

const char* standardIp = "127.0.0.1";

Sluice::Sluice(int portNumber)
:portNumber(portNumber)
,waterLevel(0)
,sluiceStatus(false)
{
    network = new Network();
    sock = network->CreateConnection(standardIp, portNumber);
}
Sluice::~Sluice()
{
	delete network;
}

double Sluice::GetWaterLevel() const
{
    return waterLevel;
}

bool Sluice::GetSluiceStatus() const
{
    return sluiceStatus;
}

int Sluice::GetPortNumber() const
{
    return portNumber;
}

int Sluice::GetSock() const
{
	return sock;
}

void Sluice::SendCommand(std::string command)
{
    network->SendMessage(sock, command);
    network->ReceiveMessage(sock);
}
