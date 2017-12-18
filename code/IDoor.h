#ifndef IDOOR_H
#define IDOOR_H

#include <string>

class IDoor
{
	public:
		~IDoor(){}
		void OpenDoor();
		void CloseDoor();
		
	private:
		bool doorStatus;
		std::string motorType;
};

#endif
