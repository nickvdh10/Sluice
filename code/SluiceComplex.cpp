#include <iostream>
#include <stdio.h>

#include "Sluice.h"


int main()
{
    int choice = 0;
    while(choice != 5)
    {
        std::cout << "Enter port number:" << std::endln;
        std::cout << "1: 5555" << std::endl;
		std::cout << "2: 5556" << std::endl;
		std::cout << "3: 5557" << std::endl;
        std::cout << "4: 5558" << std::endl;
        std::cout << "5: exit program" << std::endl;
        std::cin >> choice;
        int port = 0;
        switch(choice)
        {
            case 1:
                port = 5555;
            break;
            case 2:
                port = 5556;
            break;
            case 3:
                port = 5557;
            break;
            case 4:
                port = 5558;
            break;
            case 5:
                std::cout << "exit program" << std::endln;
            break;
            default:
                std::cout << "wrong portNumber" << std::endln;
        }
        if(port != 0)
        {
            Sluice sluice = new Sluice(port);
        }
    }
}
