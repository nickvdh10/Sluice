#ifndef IVALVE_H
#define IVALVE_H

class IValve
{
	public:
		virtual ~IDoor();
		virtual bool GetValveStatus();
		virtual void OpenValve();
		virtual void CloseValve();
		
	private:
		bool valveStatus;
}

#endif
