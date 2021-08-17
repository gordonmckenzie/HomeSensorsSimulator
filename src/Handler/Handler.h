#include <iostream>
#include <ctime>
#include <unistd.h>
#include "../Agent/Checktime.h"

class Handler
{
    private:
        bool started;

    private:
        int update(){
            //std::cout << "Working" << std::endl;
            Checktime check;
            check.checkMovement();
            return(0);
        }

    public:
        void start(){
            started = true;
            while(started)
            {
                std::clock_t start = std::clock();
                update();
                std::clock_t end   = std::clock();
                usleep(10000000 - (end - start)/CLOCKS_PER_SEC);
            }
        }
};