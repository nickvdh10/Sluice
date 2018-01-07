#ifndef VALVE_H
#define VALVE_H

#include "IValve.h"

class Valve : public IValve
{
	public:
		Valve(Network* network, int valveLevel, std::string side);
		~Valve(){}
		bool GetValveStatus();
		int GetValveLevel();
		std::string GetValveSide();
		bool OpenValve();
		bool CloseValve();
		std::string CreateValveMessage(std::string action, bool get);
		
	private:
		Network* network;
		int valveLevel; 
		std::string side;
		bool valveStatus;
		
		Valve(const Valve&) { /* do nothing */ };
		Valve& operator= (const Valve&) { return *this; };   
};

#endif
