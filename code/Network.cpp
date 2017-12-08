#include "Network.h"
#include <iostream>
#include <memory.h>     // for memset()
#include <arpa/inet.h>  // for sockaddr_in and inet_ntoa() 

int CreateConnection(const char * sluiceIP, int portNumber)
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
    echoServAddr.sin_port        = htons(sluicePort); 
    if(connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	{
		std::cout << "failed to connect\n";
		return -1;
	}
	else
	{
		std::cout << "connected with " << sluicePort << std::endl;
    }
    return sock;
}
void CloseConnection(int sock)
{
    if(sock > 0)
	{
		close(sock);
		std::cout << "sock closed\n";
	}
}
void SendMessage(int sock, std::string message)
{
    int echoStringLen = strlen(stringToSend.c_str()); 
	send(sock, stringToSend.c_str(), echoStringLen, 0);
}
char* ReceiveMessage(int sock)
{
    char* receiveString;
    recv(sock, receiveString, 30, 0); //30 is bufsize om te ontvangen.
    receiveString[30]= '\0';
    if(receiveString < 0)
    {
        std::cout << "No message received\n";
    }
    else
    {
        std::out << "message received: " << receiveString << std::endl;

    }
}