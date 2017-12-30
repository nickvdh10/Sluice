#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Sluice.h"


int main()
{
    char choice = '0';
    while(choice != 'q')
    {
        choice = 0;
        std::cout << "Enter port number:" << std::endl;
        std::cout << "1: 5555" << std::endl;
	    std::cout << "2: 5556" << std::endl;
	    std::cout << "3: 5557" << std::endl;
        std::cout << "4: 5558" << std::endl;
        std::cout << "q: exit program" << std::endl;
        std::cin >> choice;
        int port = 0;

        switch(choice)
        {
            case '1':
                port = 5555;
                break;
            case '2':
                port = 5556;
                break;
            case '3':
                port = 5557;
                break;
            case '4':
                port = 5558;
                break;
            case '5':
                std::cout << "exit program" << std::endl;
                exit (0);
                break;
            default:
                    std::cout << "wrong portNumber" << std::endl;
        }
        
        if(port != 0)
        {
            Sluice *sluice = new Sluice(port);
            sluice->SendCommand("GetWaterLevel;");
        
            char value;
            while (value != 'b')
            {
                std::cout << "Press s to start sluicing" << std::endl;
                std::cout << "Press a to activate alarm" << std::endl;
                std::cout << "Press b to go back" << std::endl;
                std::cin >> value;
                switch(value)
                {
                    case 's':
                    sluice->StartSluicing();
                    break;
                    case 'a':
                    //set alarm
                    break;
                    case 'b':
                    //quit program
                    exit (0);
                    break;
                    default:
                    std::cout << "wrong input" << std::endl;
                }
            }
        }
	 }
	 return 0;
}
