#include <iostream>
#include <stdio.h>

#include "Sluice.h"


int main()
{

        int portNumber;
        std::cout << "Enter port number:" << std::endln;
        std::cout << "5555 to 5558 ";
        std::cin >> portNumber;
        if(portNumber >= 5555 && portNumber <= 5558)
        {

        }
        else
        {
            cout << "wrong portNumber" << std::endln;
        }
}