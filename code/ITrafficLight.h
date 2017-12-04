#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H

class ITrafficLight
{
    public:
        virtual ~ITrafficLight();
        virtual void SetGreen();
        virtual void SetRed();
    private:
        bool LightStatus;
};
#endif