#ifndef NETWORK_H
#define NETWORK_H

#include <string>

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

		Network(const Network&) { /* do nothing */ };
		Network& operator= (const Network&) { return *this; };   
};
#endif
