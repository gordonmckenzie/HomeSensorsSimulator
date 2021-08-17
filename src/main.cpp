#include "Sensor/Sensor.h"
#include "Agent/GenerateAgents.h"
#include "Handler/Handler.h"
using namespace std;

int main()
{
    cout << "Building agent directory...\n" << endl;
    GenerateAgents generateAgents;
    generateAgents.setup_db();
    generateAgents.createAgents(100);
    cout << "Emulating home sensors...\n" << endl;
    cout << "Press Ctrl + C to exit\n" << endl;
    bool online = true;
    while(online)
    {
        Handler handler;
        handler.start();

    }
    return 0;
}