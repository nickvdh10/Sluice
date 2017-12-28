#ifndef INETWORK_H
#define INETWORK_H


#include <string>

class INetwork
{
    public:
        ~INetwork(){}
        int CreateConnection(const char* sluiceIP, int portNumber);
        void CloseConnection(int sock);
        void SendMessage(int sock, std::string message);
        std::string ReceiveMessage(int sock);
    private:
        int portNumber;
};

#endif