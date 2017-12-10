#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ITrafficLight.h"

class TrafficLight: public ITrafficLight
{
    public:
        TrafficLight(bool lightStatus)
        ~ITrafficLight(){}
        bool GetLightStatus();
        void SetGreen();
        void SetRed();
    private:
        bool lightStatus;
};
#endif
