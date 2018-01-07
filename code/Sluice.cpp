#include "Sluice.h"
#include <iostream>

const char* standardIp = "127.0.0.1";

Sluice::Sluice(int portNumber)
:portNumber(portNumber)
,waterLevel("")
,sluiceStatus(false)
,sluiceState("Idle")
{
	network = new Network();
    sock = network->CreateConnection(standardIp, portNumber);
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
    
    //close all valves
    door->GetValves()[0]->CloseValve();
    door->GetValves()[1]->CloseValve();
    door->GetValves()[2]->CloseValve();
    std::cout << "Valves closed\n";
    
    return "ack;";
}

int Sluice::StartSluicing()
{
	for (size_t i = 0; i < trafficLights.size(); i++)
	{
		trafficLights[i]->SetRed();
	}  
    SetSluiceState(""); //sluice state when starting the sluice
    //process of the sluicing
    std::cout << "starting sluicing" << std::endl;
    waterLevel = sensorWaterLevel->CheckCurrentWaterLevel();
    if(waterLevel == "low;")
    {
        std::cout << "water level = low" << std::endl;
        SetSluiceState("RisingWater");
        Sluicing(highWaterDoor, lowWaterDoor);
    }
    else if(waterLevel == "high;")
    {
        std::cout << "water level = high" << std::endl;
        SetSluiceState("DroppingWater");
		Sluicing(lowWaterDoor, highWaterDoor);
    }
    else //deze laten staan ja? als t goed is kan alleen low of high zijn. 
    {
        std::cout << "water level not high or low" << std::endl;
        std::cout << "water level is: " << waterLevel << std::endl;
        std::cout << "dropping water" << std::endl;
        Sluicing(lowWaterDoor, highWaterDoor);
        /**/
        //Wanneer alarm is geweest kan het water ergens in het midden staan
        //Water level is dan niet high of low wat deze deed was dan automatisch het water weer zakken (dropping water)
        //hieronder geprobeerd om via de states weer na de zelfde functie te gaan. Probleem is dat wanneer hij met risen bezig was
        // hij weer onderaan begint. 


        /*if(sluiceState == "DroppingWater")
        {
            Sluicing(lowWaterDoor, highWaterDoor);
        }
        else if(sluiceState == "RisingWater")
        {
            Sluicing(highWaterDoor, lowWaterDoor);
        }
        else 
        {
            Sluicing(lowWaterDoor, highWaterDoor);
        }*/
        
    }
    SetSluiceState("");//sluice state when ready with sluicing.
    return 0;
}
/*void Sluice::GiveFreeOut(int* trafficlightNumber1, int* trafficlightNumber2)
{
    *trafficlightNumber1 = 2;
    *trafficlightNumber2 = 1;
    if (highWaterDoor->GetDoorSide() == "Right")
    {
        *trafficlightNumber1 = 3;
        *trafficlightNumber2 = 4;
    }
    trafficLights[*trafficlightNumber1 - 1]->SetGreen();
        //[1][2][3][4] in simulator
        //[0][1][2][3] in vector
        //[R][R][G][R]  
}
void Sluice::GiveFreeIn(int* trafficlightNumber1, int* trafficlightNumber2)
{
    trafficLights[*trafficlightNumber1 - 1]->SetRed();
    trafficLights[*trafficlightNumber2 - 1]->SetGreen();
}*/

void Sluice::Sluicing(Door* door1, Door* door2)
{
	std::vector<std::string> doorCommands;
		
    //wait for release
    SetSluiceState(""); //sluice state when dropping water
    //close all doors
    std::cout << "close door1" << std::endl;
    door1->CloseDoor();
    std::cout << "close door2" << std::endl;
    door2->CloseDoor();
    ChangeLevel(door1);
    //open high Doors
    door1->OpenDoor();

    std::cout << "Press g to give free to go out of the sluice" << std::endl;
    // Door side left
    char value = 0;
    std::cin.clear();
    std::cin >> value;
    if(value == 'g')
    {
        int trafficlightNumber1 = 2;
        int trafficlightNumber2 = 1;
        if (door1->GetDoorSide() == "Right")
        {
            trafficlightNumber1 = 3;
            trafficlightNumber2 = 4;
        }
    
        trafficLights[trafficlightNumber1 - 1]->SetGreen();

        std::cout << "Press g to give free to go in to the sluice" << std::endl;
        std::cin.clear();
        std::cin >> value;
        if(value == 'g')
        {
            trafficLights[trafficlightNumber1 - 1]->SetRed();
            trafficLights[trafficlightNumber2 - 1]->SetGreen();
        }
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
    //StartSluicing();
    return "Alarm released";
}
