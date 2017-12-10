#ifndef VALVE_H
#define VALVE_H

#include "IValve.h"

class Valve : public IValve
{
	public:
		Valve();
		~Valve(){}
		bool GetValveStatus();
		void OpenValve();
		void CloseValve();
		
	private:
		bool valveStatus;
};

#endif
