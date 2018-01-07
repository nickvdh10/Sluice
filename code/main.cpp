#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Sluice.h"
#include <pthread.h>

void *threadFunc1(void *arg)
{
	Sluice* sluice = static_cast<Sluice*>(arg);
	sluice->StartSluicing();
	return NULL;
}

void *threadFunc2(void *arg)
{
	Sluice* sluice = static_cast<Sluice*>(arg);
	char value = 0;
	do
	{
		std::cin >> value;
	}
	while(value != 'a');
	sluice->Alarm();
	return NULL;
}

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
            //zin hieronder nodig?
            sluice->SendCommand("GetWaterLevel;");
			pthread_t sluiceThread;	
			pthread_t alarmThread;
            char value = 0;
            while (value != 'b')
            {
                std::cout << "Press s to start sluicing" << std::endl;
                std::cout << "(At all times) Press a to activate alarm" << std::endl;
                std::cout << "Press b to go back" << std::endl;
                // Create a thread to check if an alarm has occured
                pthread_create(&alarmThread, NULL, threadFunc2, sluice);
                std::cin >> value;
                switch(value)
                {
                    case 's':
                    // Create a thread to execute the sluicing
                    pthread_create(&sluiceThread, NULL, threadFunc1, sluice);
                    break;
                    case 'a':
                    //set alarm
                    sluice->Alarm();
                    break;
                    case 'b':
                    //back to menu
                    break;
                    default:
                    std::cout << "wrong input" << std::endl;
                }               

				pthread_join(sluiceThread, NULL);
				pthread_join(alarmThread, NULL);
            }
        }
	 }
	 return 0;
}
