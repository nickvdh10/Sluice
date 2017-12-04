#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include TrafficLight.h

class TrafficLight: public ITrafficLight
{
    public:
        TrafficLight(bool lightStatus)
        ~ITrafficLight();
        void SetGreen();
        void SetRed();
    private:
        bool LightStatus;
};
#endif