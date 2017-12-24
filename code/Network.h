#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include "INetwork.h"

class Network: public INetwork
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
