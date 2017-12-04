#ifndef ISENSORWATERLEVEL_H
#define ISENSORWATERLEVEL_H

class ISensorWaterLevel
{
    public:
        virtual ~SensorWaterLevel();
        virtual double GetWaterLevelSluice();
        virtual double GetWaterLevelLow();
        virtual double GetWaterLevelHigh();
    private:
        double waterLevelSluice;
        double waterLevelLow;
        double waterLevelHigh;
};
#endif