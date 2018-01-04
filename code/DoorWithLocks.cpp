#include "DoorWithLocks.h"

DoorWithLocks::DoorWithLocks(std::string side, bool hasLockers)
:Door(side)
,hasLockers(hasLockers)
{
	
}

bool DoorWithLocks::GetHasLockers()
{
    return hasLockers;
}