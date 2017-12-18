#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H

class ITrafficLight
{
    public:
        ~ITrafficLight();
        void SetGreen();
        void SetRed();
    private:
        bool LightStatus;
};
#endif
