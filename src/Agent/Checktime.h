#include <iostream>
#include <ctime>
#include <sqlite3.h>
#include "../Sensor/Sensor.h"

class Checktime
{
    private:
        sqlite3 *db;
        char *zErrMsg;
        int rc;

    static std::string mapRoom(std::string agent_time)
    {
        if (agent_time == "wake_up_time"){
            return "bedroom";
        } else if (agent_time == "breakfast_time"){
            return "kitchen";
        } else if (agent_time == "lunch_time"){
            return "kitchen";
        } else if (agent_time == "dinner_time"){
            return "kitchen";
        } else if (agent_time == "bed_time"){
            return "bedroom";
        } else {
            return NULL;
        }
    }

    static int callback(void *data, int argc, char **argv, char **azColName) 
    {
        //int i;
        //std::string argS = argv[i] ? argv[i] : "NULL";
        Sensor sensor;
        Checktime checktime;
        sensor.trigger(argv[0], checktime.mapRoom(azColName[1]), "PIR");
        //std::cout << azColName[i] << argS << "\n" << std::endl;
        //std::cout << "\n" << std::endl;
        return 0;
    }

    public:
        int checkMovement(){
            zErrMsg = 0;
            rc = sqlite3_open("agents.db", &db);
            const char* data;

            time_t currentTime;
            struct tm *localTime;

            time(&currentTime);
            localTime = localtime(&currentTime);

            int hour = localTime->tm_hour;
            int minutes = localTime->tm_min;

            if(rc) {
                std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
                return(0);
            } else {
                char *sql;
                std::cout << "Time now is " << hour << ":" << minutes << std::endl;
                if (hour >= 7 && hour <= 8){
                    sql = (char *)"SELECT uuid, wake_up_time FROM agents WHERE wake_up_time > TIME('NOW', '-2 second', 'localtime') AND wake_up_time < TIME('NOW', '+2 second', 'localtime')";
                } else if (hour >= 8 && hour <= 10){
                    sql = (char *)"SELECT uuid, breakfast_time FROM agents WHERE breakfast_time > TIME('NOW', '-2 second', 'localtime') AND breakfast_time < TIME('NOW', '+2 second', 'localtime')";
                } else if (hour >= 11 && hour <= 14){
                    sql = (char *)"SELECT uuid, lunch_time FROM agents WHERE lunch_time > TIME('NOW', '-2 second', 'localtime') AND lunch_time < TIME('NOW', '+2 second', 'localtime')";
                } else if (hour >= 16 && hour <= 18){
                    sql = (char *)"SELECT uuid, dinner_time FROM agents WHERE dinner_time > TIME('NOW', '-2 second', 'localtime') AND dinner_time < TIME('NOW', '+2 second', 'localtime')";
                } else if (hour >= 20 && hour <= 22){
                    sql = (char *)"SELECT uuid, bed_time FROM agents WHERE bed_time > TIME('NOW', '-2 second', 'localtime') AND bed_time < TIME('NOW', '+2 second', 'localtime')";
                }
                if (sql) {
                    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                    if( rc != SQLITE_OK ){
                        std::cout << "SQL error: \n" << zErrMsg << std::endl;
                        sqlite3_free(zErrMsg);
                    }
                }
            }
            sqlite3_close(db);
            return(0);
            }

};