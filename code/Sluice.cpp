#include "Sluice.h"
#include <iostream>

const char* standardIp = "127.0.0.1";

Sluice::Sluice(int portNumber)
:portNumber(portNumber)
,waterLevel("")
,sluiceStatus(false)
,sluiceState("Idle")
{
    lowWaterDoor = new Door("Left");
    highWaterDoor = new Door("Right");
    sensorWaterLevel = new SensorWaterLevel();
    network = new Network();
    sock = network->CreateConnection(standardIp, portNumber);
}
Sluice::~Sluice()
{
    delete sensorWaterLevel;
    delete network;
}

std::string Sluice::GetWaterLevel() const
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
    
    waterLevel = SendCommand(sensorWaterLevel->CheckCurrentWaterLevel());
    
    if(waterLevel == "low;")
    {
        SendCommand(lowWaterDoor->OpenDoor());
        
        /*//wait for release
         SetSluiceState(""); //sluice state when dropping water
         //omhoogschutten
             //close low doors
             //rise water
             //open High doors
             //wait for release
             //when released back to idle*/
    }
    else if(waterLevel == "high;")
    {
        SendCommand(highWaterDoor->OpenDoor());
        /*//wait for release
        SetSluiceState(""); //sluice state when rising water
        //omlaagschutten
            //close high doors
            //dropping water
            //open low doors
            //wait for release
            //when released back to idle*/
    }
    /*std::cout << "pres y for green light" << std::endl;
    char value;
    std::cin >> value;
    if(value == 'y')
    {
        //set light to green

    }*/
   
    /*std::string stringToSend = lowWaterDoor->OpenDoor();
    std::cout << "stringToSend = " << stringToSend << std::endl;
    SendCommand(stringToSend);*/
    //verschillende methodes voor omhoog en omlaag schutten?

    SetSluiceState("");//sluice state when ready with sluicing.
    return 0;
}
std::string Sluice::SendCommand(std::string command)
{  
    if(command == "")
    {
        return "";
    }
    network->SendMessage(sock, command);
    return network->ReceiveMessage(sock);
}
/*std::string Sluice::SendCommand()
{ 
    return network->ReceiveMessage(sock);
}*/