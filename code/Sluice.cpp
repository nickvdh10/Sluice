#include "Sluice.h"
#include <iostream>

const char* standardIp = "127.0.0.1";

Sluice::Sluice(int portNumber)
:portNumber(portNumber)
,waterLevel(0)
,sluiceStatus(false)
,sluiceState("Idle")
{
    //sensorWaterLevel = new ISensorWaterLevel();
    //network = new INetwork();
    //sock = network->CreateConnection(standardIp, portNumber); //werkt zo niet..
}
Sluice::~Sluice()
{
	//delete network;
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
void Sluice::SetSluiceState(std::string state)
{
    sluiceState = state;
}
int Sluice::StartSluicing()
{
    SetSluiceState(""); //sluice state when starting the sluice
    //process of the sluicing
    std::cout << "starting sluicing" << std::endl;
    //check waterlevel 
    //waterLevel = sensorWaterLevel->GetWaterLevelSluice();
    
    //std::cout << "waterLevel = " << waterLevel;
    
    //verschillende methodes voor omhoog en omlaag schutten?

    //if high shutting to low
    //if low shutting to high
    /*if(waterlevel == //highwaterlevel)
    {
        SetSluiceState(""); //sluice state when rising water
        //omlaagschutten
            //close high doors
            //dropping water
            //open low doors
            //wait for release
            //when released back to idle
    }
    else if(waterLevel == //lowWaterLevel)
    {
        SetSluiceState(""); //sluice state when dropping water
        //omhoogschutten
            //close low doors
            //rise water
            //open High doors
            //wait for release
            //when released back to idle
    }*/
    

    SetSluiceState("");//sluice state when ready with sluicing.
    return 0;
}
void Sluice::SendCommand(std::string command)
{
    command = "";
    /*network->SendMessage(sock, command);
    network->ReceiveMessage(sock);*/
}
