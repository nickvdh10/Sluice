#include "Sluice.h"
#include <iostream>
const char* standardIp = "127.0.0.1";
Sluice::Sluice(int portNumber)
:sluiceState("Idle")
{
	network = new Network();
	int sock = network->CreateConnection(standardIp, portNumber);
	if (sock > 0)
	{
		switch(portNumber)
		{
			case 5557:
				lowWaterDoor = new DoorWithLock(network, "Left");
				highWaterDoor = new DoorWithLock(network, "Right");
				break;
			case 5558:
				lowWaterDoor = new DoorWithDifferentEngine(network, "Left");
				highWaterDoor = new DoorWithDifferentEngine(network, "Right");
				break;
			default:
				lowWaterDoor = new Door(network, "Left");
				highWaterDoor = new Door(network, "Right");
				break;
		}
		sensorWaterLevel = new SensorWaterLevel(network);
		for (int i = 0; i < 4; i++)
		{
			trafficLights.push_back(new TrafficLight(network, false, i+1));
		}
	}
}
Sluice::~Sluice()
{
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

std::string Sluice::GetSluiceState() const
{
	return sluiceState;
}

void Sluice::SetSluiceState(std::string state)
{
	sluiceState = state;
}

void Sluice::ChangeLevel(Door* door)
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
	door->GetValves()[0]->OpenValve();
	
	while(sensorWaterLevel->CheckCurrentWaterLevel() != compareStr)
	{
	}
	
	if(door->GetDoorSide() == "Right")
	{
		//open valve2
		door->GetValves()[1]->OpenValve();
		
		while(sensorWaterLevel->CheckCurrentWaterLevel() != "aboveValve3;")
		{
		}
		
		//open valve 3
		door->GetValves()[2]->OpenValve();
		while(sensorWaterLevel->CheckCurrentWaterLevel() != "high;")
		{
		}
	}
	std::cout << "waterlevel is on desired level\n";
	
	//close all valves
	door->GetValves()[0]->CloseValve();
	door->GetValves()[1]->CloseValve();
	door->GetValves()[2]->CloseValve();
	
	std::cout << "Valves closed\n";
}

int Sluice::StartSluicing()
{
	
	if(network->GetSock() <= 0)
	{
		return -1;
	}
	for (size_t i = 0; i < trafficLights.size(); i++)
	{
		trafficLights[i]->SetRed();
	}
	 //sluice state when starting the sluice
	//process of the sluicing
	std::cout << "starting sluicing" << std::endl;
	SetSluiceState("ChekkingWaterLevel");
	std::string waterLevel = sensorWaterLevel->CheckCurrentWaterLevel();
	if(waterLevel == "low;")
	{
		SetSluiceState("RisingWater");
		Sluicing(highWaterDoor, lowWaterDoor);
	}
	else if(waterLevel == "high;")
	{
		SetSluiceState("DroppingWater");
		Sluicing(lowWaterDoor, highWaterDoor);
	}
	/*
	else
	{
		std::cout << "water level not high or low" << std::endl;
		std::cout << "water level is: " << waterLevel << std::endl;
		std::cout << "dropping water" << std::endl;
		Sluicing(lowWaterDoor, highWaterDoor);
	}*/
	SetSluiceState("");//sluice state when ready with sluicing.
	return 0;
}
void Sluice::Sluicing(Door* door1, Door* door2)
{
	std::vector<std::string> doorCommands;
	char value;
	//wait for release
	 //sluice state when dropping water
	//close all doors
	door1->CloseDoor();
	door2->CloseDoor();
	//change waterlevel
	ChangeLevel(door1);
	//open high Doors
	door1->OpenDoor();
	//give free
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
		trafficLights[trafficlightNumber1 - 1]->SetGreen();
		//[1][2][3][4] in simulator
		//[0][1][2][3] in vector
		//[R][R][G][R]
	}
	std::cout << "Press g to give free to go in to the sluice" << std::endl;
	std::cin >> value;
	if (value == 'g')
	{
		trafficLights[trafficlightNumber1 - 1]->SetRed();
		trafficLights[trafficlightNumber2 - 1]->SetGreen();
	}
	//wait for release
	//when released back to idle
}

std::string Sluice::Alarm()
{    
    std::string historyState;
    historyState = sluiceState;
    sluiceState = "Alarm";
    for(int j = 0; j < 3; j++)
    {    
        highWaterDoor->GetValves()[j]->CloseValve();
        lowWaterDoor->GetValves()[j]->CloseValve();
    }  
	// Stop the doors
	highWaterDoor->StopDoor();
	lowWaterDoor->StopDoor();

    char released;
    std::cout << "press r to release alarm" << std::endl;
    std::cin.clear();
    std::cin >> released;
    sluiceState = historyState;
    return "Alarm released";
}
