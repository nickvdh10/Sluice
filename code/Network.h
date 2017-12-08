#ifndef NETWORK_H
#define NETWORK_H

class Network
{
	public:
		Network();
		~Network();
		int CreateConnection(const char * sluiceIP, int portNumber);
		void CloseConnection(int sock);
		void SendMessage(int sock, std::string message);
		char* ReceiveMessage(int sock);
	private:
		int portNumber;
};
#endif
