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

void Sluice::CloseAllDoors(Door* door1, Door* door2)
{
    if(SendCommand(door1->CheckDoorState()) != "doorClosed;")
    {
        door1->SetDoorStatus(true);
        SendCommand(door1->CloseDoor()); 
        while(SendCommand(door1->CheckDoorState()) != "doorClosed;")
        {
        }
    }
    if(SendCommand(door2->CheckDoorState()) != "doorClosed;")
    {
        door2->SetDoorStatus(true);
        SendCommand(door2->CloseDoor()); 
        while(SendCommand(door2->CheckDoorState()) != "doorClosed;")
        {
        }
    }
    
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
    std::cout << "Valves closed\n";
    
    return "ack;";
}


int Sluice::StartSluicing()
{
    SendCommand("SetTrafficLight1Red:on;"); 
    SendCommand("SetTrafficLight1Green:off;");
    SendCommand("SetTrafficLight2Red:on;"); 
    SendCommand("SetTrafficLight2Green:off;"); 
    SendCommand("SetTrafficLight3Red:on;"); 
    SendCommand("SetTrafficLight3Green:off;");
    SendCommand("SetTrafficLight4Red:on;"); 
    SendCommand("SetTrafficLight4Green:off;");  
    SetSluiceState(""); //sluice state when starting the sluice
    //process of the sluicing
    std::cout << "starting sluicing" << std::endl;
    char value;
    waterLevel = SendCommand(sensorWaterLevel->CheckCurrentWaterLevel());
    
    if(waterLevel == "low;")
    {
        
        //wait for release
        SetSluiceState(""); //sluice state when dropping water
        //omhoogschutten
        //close all doors
        CloseAllDoors(lowWaterDoor, highWaterDoor);
        //rise water
        std::cout << "rising water" << std::endl;
        ChangeLevel(highWaterDoor);
        //open high Doors
        SendCommand(highWaterDoor->OpenDoor());
        while(SendCommand(highWaterDoor->CheckDoorState()) != "doorOpen;")
        {}
        //vrijgeven voor uitvaren
        std::cout << "Press g to give free to go out of the sluice" << std::endl;
        std::cin >> value;
        if (value == 'g')
        { 
            //[1][2][3][4] in simulator
            //[0][1][2][3] in vector
            //[R][R][G][R] 
			SendCommand("SetTrafficLight3Red:off;"); 
            SendCommand("SetTrafficLight3Green:on;");
            SendCommand("SetTrafficLight4Red:on;"); 
            SendCommand("SetTrafficLight4Green:off;");  
        }
        std::cout << "Press g to give free to go in to the sluice" << std::endl;
        std::cin >> value;
        if (value == 'g')
        {
            SendCommand("SetTrafficLight3Red:on;"); 
            SendCommand("SetTrafficLight3Green:off;");
            SendCommand("SetTrafficLight4Red:off;"); 
            SendCommand("SetTrafficLight4Green:on;");  
        }
		//SendCommand(highWaterDoor->CloseDoor());
        //wait for release
        //when released back to idle
    }
    else if(waterLevel == "high;")
    {
        //wait for release
        SetSluiceState(""); //sluice state when rising water
        //omlaagschutten
        //close all doors
        CloseAllDoors(lowWaterDoor, highWaterDoor);
        //dropping water    
        std::cout << "dropping water" << std::endl;
        ChangeLevel(lowWaterDoor);
        //open low doors
        SendCommand(lowWaterDoor->OpenDoor());
        while(SendCommand(lowWaterDoor->CheckDoorState()) != "doorOpen;")
        {}
        std::cout << "Press g to give free to go out of the sluice" << std::endl;
        std::cin >> value;
        if (value == 'g')
        {
            //[1][2][3][4] in simulator
            //[0][1][2][3] in vector
            //[R][R][G][R] 
			SendCommand("SetTrafficLight2Red:off;"); 
            SendCommand("SetTrafficLight2Green:on;");
            SendCommand("SetTrafficLight1Red:on;"); 
            SendCommand("SetTrafficLight1Green:off;");  
		}
	    //SendCommand(lowWaterDoor->CloseDoor());
        //wait for release
        std::cout << "Press g to give free to go in to the sluice" << std::endl;
        std::cin >> value;
        if (value == 'g')
        {
            SendCommand("SetTrafficLight2Red:on;"); 
            SendCommand("SetTrafficLight2Green:off;");
            SendCommand("SetTrafficLight1Red:off;"); 
            SendCommand("SetTrafficLight1Green:on;");  
        }
        //when released back to idle
    }
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