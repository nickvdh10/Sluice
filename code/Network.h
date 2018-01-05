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
		int GetSock() const;
	private:
		int portNumber;
		int sock;
		// Empty copyconst and assignment operator since we don't want copies to be made (?)
		Network(const Network&) { /* do nothing */ };
		Network& operator= (const Network&) { return *this; };   
};
#endif
