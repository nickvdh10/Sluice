#ifndef NETWORK_H
#define NETWORK_H

class Network
{
	public:
		Network();
		~Network();
		void CreateConnection(int portNumber);
		void SendMessage(std::string message);
		std::string ReceiveMessage();
	private:
		int portNumber;
}

#endif
