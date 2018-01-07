#ifndef DOOR_H
#define DOOR_H

#include "IDoor.h"
#include "Valve.h"
#include <vector>

class Door: public IDoor
{
	public:
		Door(Network* network, std::string side);
		virtual ~Door();
		bool GetDoorStatus();
		void SetDoorStatus(bool status);
		std::string GetDoorSide() const;
		virtual bool OpenDoor();
		virtual bool CloseDoor();
		virtual void StopDoor();
		std::string CheckDoorState();
		std::vector<Valve*> GetValves() const;
		std::string CreateDoorMessage(std::string action, bool get);
		Network* GetNetwork();

	private:
		Network* network;
		std::vector<Valve*> valves;
		std::string side;
		bool doorStatus;
		
		Door(const Door&) { /* do nothing */ };
		Door& operator= (const Door&) { return *this; };   
};

#endif
