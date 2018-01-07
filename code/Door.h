#ifndef DOOR_H
#define DOOR_H

#include "IDoor.h"
#include "Valve.h"
#include "Network.h"
#include <vector>
#include <string>

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
		std::vector<Valve*> GetValves();
		std::string CreateDoorMessage(std::string action, bool get);
		Network* GetNetwork();

	private:
		Network* network;
		std::vector<Valve*> valves;
		bool doorStatus;
		std::string motorType;
		std::string side;
		
		// Empty copyconst and assignment operator since we don't want copies to be made (?)
		//Door(const Door&) { /* do nothing */ };
		//Door& operator= (const Door&) { return *this; };   
};

#endif
