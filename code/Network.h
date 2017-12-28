#ifndef NETWORK_H
#define NETWORK_H

#include <string>
//#include "INetwork.h"
//: public INetwork
class Network
{
	public:
		Network();
		~Network();
		int CreateConnection(const char * sluiceIP, int portNumber);
		void CloseConnection(int sock);
		void SendMessage(int sock, std::string message);
		std::string ReceiveMessage(int sock);
	private:
		int portNumber;
};
#endif
