#include "Sluice.h"



Sluice::Sluice()
:waterLevel(waterLevel)
,sluiceStatus(sluiceStatus)
{
    
}
Sluice::~Sluice()
{

}

double Sluice::GetWaterLevel()
{
    return waterLevel
}

bool Sluice::GetSluiceStatus()
{
    return sluiceStatus;
}