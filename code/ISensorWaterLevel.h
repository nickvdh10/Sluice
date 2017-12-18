#ifndef ISENSORWATERLEVEL_H
#define ISENSORWATERLEVEL_H

class ISensorWaterLevel
{
    public:
        ~ISensorWaterLevel() {}
        double GetWaterLevelSluice();
        double GetWaterLevelLow();
        double GetWaterLevelHigh();
    private:
        double waterLevelSluice;
        double waterLevelLow;
        double waterLevelHigh;
};
#endif
