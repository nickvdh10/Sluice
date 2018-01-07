#ifndef IVALVE_H
#define IVALVE_H

#include "Network.h"

class IValve
{
	public:
		virtual ~IValve(){}
		virtual bool OpenValve() = 0;
		virtual bool CloseValve() = 0;
		
};

#endif
