#include "Valve.h"

Valve::Valve()
:valveStatus(false)
{
}

bool Valve::GetValveStatus()
{
	return valveStatus;
}
void Valve::OpenValve()
{
	valveStatus = true;
}

void Valve::CloseValve()
{
	valveStatus = false;
}
