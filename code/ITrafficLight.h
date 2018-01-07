#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H

#include "Network.h"

class ITrafficLight
{
    public:
        virtual ~ITrafficLight(){}
        virtual bool SetGreen() = 0;
        virtual bool SetRed() = 0;
};
#endif
