#ifndef SLUICECONTROL_H
#define SLUICECONTROL_H

class SluiceControl
{
public:
    void Start();
    void Alarm();
    void ReleasAlarm();
    bool GiveFree();

private:
    bool alarmStatus;
};

#endif