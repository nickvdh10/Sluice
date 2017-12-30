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
		int GetValveLevel();
		std::string GetValveSide();
		std::string OpenValve();
		std::string CloseValve();
		std::string CreateValveMessage(std::string action, bool get);
		 //naar private ff public voor test
		 // deze ^ en comment hieronder kenne weg denk fnie?
	private:
		int valveLevel; //naar private ff public voor test
		std::string side;
		bool valveStatus;
		
		// Empty copyconst and assignment operator since we don't want copies to be made (?)
		Valve(const Valve&) { /* do nothing */ };
		Valve& operator= (const Valve&) { return *this; };   
};

#endif
