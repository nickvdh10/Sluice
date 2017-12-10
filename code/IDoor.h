#ifndef IDOOR_H
#define IDOOR_H

#include <string>

class IDoor
{
	public:
		virtual ~IDoor();
		virtual void OpenDoor();
		virtual void CloseDoor();
		
	private:
		bool doorStatus;
		std::string motorType;
};

#endif
