#ifndef IVALVE_H
#define IVALVE_H

class IValve
{
	public:
		~IValve(){}
		bool GetValveStatus();
		void OpenValve();
		void CloseValve();
		
	private:
		bool valveStatus;
};

#endif
