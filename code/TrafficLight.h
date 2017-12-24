#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ITrafficLight.h"
#include "INetwork.h"

class TrafficLight: public ITrafficLight
{
    public:
        TrafficLight(bool lightStatus);
        ~TrafficLight(){}
        bool GetLightStatus();
        void SetGreen();
        void SetRed();
    private:
        bool lightStatus;
};
#endif
