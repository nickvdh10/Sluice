#include "DoorWithDifferentEngine.h"

DoorWithDifferentEngine::DoorWithDifferentEngine(std::string side, bool hasDifrentEngine)
:Door(side)
,hasDifrentEngine(hasDifrentEngine)
{
}

bool DoorWithDifferentEngine::GetHasDifrentEngine()
{
    return hasDifrentEngine;
}