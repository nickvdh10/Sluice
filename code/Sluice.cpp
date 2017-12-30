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
    for (int i = 0; i < 4; i++)
	{
		// Traffic lights standerd red light???
		trafficLights.push_back(new TrafficLight(false));	
	}
}
Sluice::~Sluice()
{
	// delete memory on the heap
    delete sensorWaterLevel;
    delete network;
    delete lowWaterDoor;
    delete highWaterDoor;
    for (unsigned int i = 0; i < trafficLights.size(); i++)
    {
		delete trafficLights[i];
		trafficLights[i] = NULL;
	}
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
std::string Sluice::ChangeLevel(Door* door)
{
    std::string compareStr;
    if(door->GetDoorSide() == "Right")
    {
        compareStr = "aboveValve2;";
    }
    else
    {
        compareStr = "low;";
    }

    //open valve1
    SendCommand(door->GetValves()[0]->OpenValve());
    
    while(SendCommand(sensorWaterLevel->CheckCurrentWaterLevel()) != compareStr)
    {

    }
    if(door->GetDoorSide() == "Right")
    {    
        //open valve2
        SendCommand(door->GetValves()[1]->OpenValve());
        while(SendCommand(sensorWaterLevel->CheckCurrentWaterLevel()) != "aboveValve3;")
        {
    
        }
        //open valve 3
        SendCommand(door->GetValves()[2]->OpenValve());
        while(SendCommand(sensorWaterLevel->CheckCurrentWaterLevel()) != "high;")
        {
            
        }
    }
    std::cout << "waterlevel is on desired level\n";
    //close all valves
    SendCommand(door->GetValves()[0]->CloseValve());
    SendCommand(door->GetValves()[1]->CloseValve());
    SendCommand(door->GetValves()[2]->CloseValve());

    return "ack;";
}


int Sluice::StartSluicing()
{
    SetSluiceState(""); //sluice state when starting the sluice
    //process of the sluicing
    std::cout << "starting sluicing" << std::endl;
    
    waterLevel = SendCommand(sensorWaterLevel->CheckCurrentWaterLevel());
    
    if(waterLevel == "low;")
    {
        
        
        //wait for release
         SetSluiceState(""); //sluice state when dropping water
         //omhoogschutten
             //close low doors
             if(lowWaterDoor->GetDoorStatus())
             {
                 lowWaterDoor->CloseDoor();
             }

             //rise water
             ChangeLevel(highWaterDoor);
             //open high Doors
             SendCommand(highWaterDoor->OpenDoor());
             //wait for release
             //when released back to idle
    }
    else if(waterLevel == "high;")
    {
        
        //wait for release
        SetSluiceState(""); //sluice state when rising water
        //omlaagschutten
            //close high doors
            //dropping water
            ChangeLevel(lowWaterDoor);
            //open low doors
            SendCommand(lowWaterDoor->OpenDoor());
            //wait for release
            //when released back to idle
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
