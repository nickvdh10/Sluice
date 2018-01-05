#include "Sluice.h"
#include <iostream>

const char* standardIp = "127.0.0.1";

Sluice::Sluice(int portNumber)
:portNumber(portNumber)
,waterLevel("")
,sluiceStatus(false)
,sluiceState("Idle")
{
	switch(portNumber)
	{
		case 5557:
			lowWaterDoor = new DoorWithLock("Left");
			highWaterDoor = new DoorWithLock("Right");
			break;
		case 5558:
			lowWaterDoor = new DoorWithDifferentEngine("Left");
			highWaterDoor = new DoorWithDifferentEngine("Right");
			break;
		default:
			lowWaterDoor = new Door("Left");
			highWaterDoor = new Door("Right");
			break;
	}
    sensorWaterLevel = new SensorWaterLevel();
    network = new Network();
    sock = network->CreateConnection(standardIp, portNumber);
    for (int i = 0; i < 4; i++)
	{
		trafficLights.push_back(new TrafficLight(network, false, i+1));	
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
	std::vector<std::string> doorCommands;
	doorCommands = door1->CheckDoorState();
    if(SendCommand(doorCommands[0]) != "doorClosed;")
    {
        door1->SetDoorStatus(true);
        door1->CloseDoor();
        std::string action = door1->GetDoorStatus() ? "open" : "close";
        doorCommands = door1->CreateDoorMessage(action, false);
        for(size_t i = 0; i < doorCommands.size(); i++)
        {
			SendCommand(doorCommands[i]);
			std::cout << doorCommands[i] << std::endl;
		}
		//TODO: while loop
    }
    doorCommands = door2->CheckDoorState();
    if(SendCommand(doorCommands[0]) != "doorClosed;")
    {
        door2->SetDoorStatus(true);
        door2->CloseDoor();
        std::string action = door2->GetDoorStatus() ? "open" : "close";
        doorCommands = door2->CreateDoorMessage(action, false);
        for(size_t i = 0; i < doorCommands.size(); i++)
        {
			SendCommand(doorCommands[i]);
			std::cout << doorCommands[i] << std::endl;
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
	for (size_t i = 0; i < trafficLights.size(); i++)
	{
		SendCommand(trafficLights[i]->SetRedOn());
		SendCommand(trafficLights[i]->SetGreenOff());
	}  
    SetSluiceState(""); //sluice state when starting the sluice
    //process of the sluicing
    std::cout << "starting sluicing" << std::endl;
    waterLevel = SendCommand(sensorWaterLevel->CheckCurrentWaterLevel());
    if(waterLevel == "low;")
    {
        Sluicing(highWaterDoor, lowWaterDoor);
    }
    else if(waterLevel == "high;")
    {
		Sluicing(lowWaterDoor, highWaterDoor);
    }
    //verschillende methodes voor omhoog en omlaag schutten?
    SetSluiceState("");//sluice state when ready with sluicing.
    return 0;
}

void Sluice::Sluicing(Door* door1, Door* door2)
{
		std::vector<std::string> doorCommands;
		char value;
        //wait for release
        SetSluiceState(""); //sluice state when dropping water
        //omhoogschutten
        //close all doors
        CloseAllDoors(door1, door2);
        //rise water
        std::cout << "rising water" << std::endl;
        ChangeLevel(door1);
        //open high Doors
        door1->OpenDoor();
        std::string action = door1->GetDoorStatus() ? "open" : "close";
        std::cout << action << std::endl;
        doorCommands = door1->CreateDoorMessage(action, false);
        for(size_t i = 0; i < doorCommands.size(); i++)
        {
			SendCommand(doorCommands[i]);
			std::cout << doorCommands[i] << std::endl;
		}
        doorCommands = door1->CreateDoorMessage("", true);
        while(SendCommand(doorCommands[0]) != "doorOpen;")
        {}
        //vrijgeven voor uitvaren
        std::cout << "Press g to give free to go out of the sluice" << std::endl;
        std::cin >> value;
        // Door side left
        int trafficlightNumber1 = 2;
        int trafficlightNumber2 = 1;
        if (door1->GetDoorSide() == "Right")
		{
			trafficlightNumber1 = 3;
			trafficlightNumber2 = 4;
		}

        if (value == 'g')
        { 
			SendCommand(trafficLights[trafficlightNumber1 - 1]->SetRedOff());
			SendCommand(trafficLights[trafficlightNumber1 - 1]->SetGreenOn());
            //[1][2][3][4] in simulator
            //[0][1][2][3] in vector
            //[R][R][G][R]   
        }
        std::cout << "Press g to give free to go in to the sluice" << std::endl;
        std::cin >> value;
        if (value == 'g')
        {
			SendCommand(trafficLights[trafficlightNumber1 - 1]->SetRedOn());
			SendCommand(trafficLights[trafficlightNumber1 - 1]->SetGreenOff());
			SendCommand(trafficLights[trafficlightNumber2 - 1]->SetGreenOn());
			SendCommand(trafficLights[trafficlightNumber2 - 1]->SetRedOff());
        }
        //wait for release
        //when released back to idle
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
