#ifndef ISENSORWATERLEVEL_H
#define ISENSORWATERLEVEL_H

#include "Network.h"

class ISensorWaterLevel
{
    public:
        virtual ~ISensorWaterLevel() {}
        virtual std::string CheckCurrentWaterLevel() = 0;

};
#endif
