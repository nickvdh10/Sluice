#include "Network.h"
#include <stdexcept>
#include <iostream>
#include <memory.h>     // for memset()
#include <arpa/inet.h>  // for sockaddr_in and inet_ntoa() 
#include <unistd.h> // for close()

Network::Network()
{
	
}

Network::~Network()
{
	
}

int Network::CreateConnection(const char * sluiceIP, int portNumber)
{
    std::cout << sluiceIP << " " << portNumber << "\n";
	int sock = 0;
	struct sockaddr_in  echoServAddr;
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		return -1;
    }
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family      = AF_INET;            
    echoServAddr.sin_addr.s_addr = inet_addr(sluiceIP);   
    echoServAddr.sin_port        = htons(portNumber); 
    if(connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	{
		std::cout << "failed to connect\n";
		return -1;
	}
	else
	{
		std::cout << "connected with " << portNumber << std::endl;
    }
    return sock;
}

void Network::CloseConnection(int sock)
{
    if(sock > 0)
	{
		close(sock);
		std::cout << "sock closed\n";
	}
}

void Network::SendMessage(int sock, std::string message)
{
    int echoStringLen = strlen(message.c_str()); 
	send(sock, message.c_str(), echoStringLen, 0);
}

std::string Network::ReceiveMessage(int sock)
{
    char receiveString[30];
    int bytesRcvd = recv(sock, receiveString, 30, 0); //30 is bufsize om te ontvangen.
    receiveString[bytesRcvd]= '\0';
   
    if(bytesRcvd > 0 && receiveString != NULL && receiveString[0] == '\0')
    {
        //throw std::invalid_argument("String is empty or NULL");  
        std::cout << "No message received:.. " << std::endl;
        return "noMessage";  
    }
    else
    {
        //std::cout << "message received: " << receiveString << std::endl;
        return receiveString;
    }
}

int Network::GetSock() const
{
	return sock;
}
