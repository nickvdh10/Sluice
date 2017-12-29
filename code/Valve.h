#ifndef VALVE_H
#define VALVE_H

#include "IValve.h"
#include "Network.h"

class Valve : public IValve
{
	public:
		Valve(int valveLevel, std::string side);
		~Valve(){}
		bool GetValveStatus();
		char GetValveLevel();
		std::string GetValveSide();
		std::string OpenValve();
		std::string CloseValve();
		std::string CreateValveMessage(std::string action, bool get);
		 //naar private ff public voor test

	private:
		char valveLevel; //naar private ff public voor test
		std::string side;
		bool valveStatus;
		
};

#endif
