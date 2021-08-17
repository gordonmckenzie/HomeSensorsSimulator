#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <sqlite3.h>
#include <cctype>
#include <random>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using u32    = uint_least32_t; 
using engine = std::mt19937;

class GenerateAgents 
{
    private:
        boost::uuids::uuid uuid;
        std::string wake_up_time;
        std::string breakfast_time;
        int kitchen_visits;
        std::string lunch_time;
        std::string dinner_time;
        std::string bed_time;

        sqlite3 *db;
        char *zErrMsg;
        int rc;

    private:
        static int callback(void *NotUsed, int argc, char **argv, char **azColName) 
        {
            int i;
            for(i = 0; i<argc; i++) {
                std::string argS = argv[i] ? argv[i] : "NULL";
                std::cout << azColName[i] << argS << "\n" << std::endl;
            }
            std::cout << "\n" << std::endl;
            return 0;
        }

    public:
        int setup_db()
        {
            zErrMsg = 0;
            rc = sqlite3_open("agents.db", &db);

            if(rc) {
                std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
                return(0);
            } else {
                // Cast string to char for compatibilty with SQLite API
                char *sql = (char *)"CREATE TABLE IF NOT EXISTS agents("  \
                    "id                 INTEGER PRIMARY KEY AUTOINCREMENT," \
                    "uuid               VARCHAR(36)," \
                    "wake_up_time       TEXT," \
                    "breakfast_time     TEXT," \
                    "kitchen_visits     INT," \
                    "lunch_time         TEXT," \
                    "dinner_time        TEXT," \
                    "bed_time           TEXT);";
                rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
                if( rc != SQLITE_OK ){
                    std::cout << "SQL error: \n" << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                }
            }
            sqlite3_close(db);
            return(0);
        }
    
    private:
        void set(
            std::string _wake_up_time, 
            std::string _breakfast_time,
            int _kitchen_visits,
            std::string _lunch_time,
            std::string _dinner_time,
            std::string _bed_time
        ) {
            uuid = boost::uuids::random_generator()();
            wake_up_time = _wake_up_time;
            breakfast_time = _breakfast_time;
            kitchen_visits = _kitchen_visits;
            lunch_time = _lunch_time;
            dinner_time = _dinner_time;
            bed_time = _bed_time;
            
            zErrMsg = 0;
            rc = sqlite3_open("agents.db", &db);
            
            char sql[167] = 
                "INSERT INTO agents (uuid, wake_up_time, breakfast_time, kitchen_visits, lunch_time, dinner_time, bed_time)" \
                "VALUES (?, time(?), time(?), ?, time(?), time(?), time(?));";
            
            sqlite3_stmt* stmt;
            
            rc = sqlite3_prepare(
                db,
                sql,
                -1,
                &stmt,
                NULL
            );

            char * str = (char *)boost::lexical_cast<std::string>(uuid).c_str();

            sqlite3_bind_text(
                stmt, 
                1,
                str,
                strlen(str),
                SQLITE_TRANSIENT
            );

            rc = sqlite3_bind_text(
                stmt, 
                2,
                (char *)wake_up_time.c_str(),
                wake_up_time.length(),
                SQLITE_STATIC
            );
            
            rc = sqlite3_bind_text(
                stmt, 
                3,
                (char *)breakfast_time.c_str(),
                breakfast_time.length(),
                SQLITE_STATIC
            );

            rc = sqlite3_bind_int(
                stmt, 
                4,
                kitchen_visits
            );

            rc = sqlite3_bind_text(
                stmt, 
                5,
                (char *)lunch_time.c_str(),
                lunch_time.length(),
                SQLITE_STATIC
            );

            rc = sqlite3_bind_text(
                stmt, 
                6,
                (char *)dinner_time.c_str(),
                dinner_time.length(),
                SQLITE_STATIC
            );

            rc = sqlite3_bind_text(
                stmt, 
                7,
                (char *)bed_time.c_str(),
                bed_time.length(),
                SQLITE_STATIC
            );
            rc = sqlite3_step(stmt);
            rc = sqlite3_clear_bindings(stmt);
            rc = sqlite3_reset(stmt);

            rc = sqlite3_finalize(stmt);
            if( rc != SQLITE_OK ){
                std::cout << "SQL error: \n" << zErrMsg << std::endl;
                sqlite3_free(zErrMsg);
            }
            rc = sqlite3_close(db);
        }

        private:
            std::string minutesConverter(int m) {
                if (m < 10){
                    return "0" + std::to_string(m); 
                } else {
                    return std::to_string(m);
                }
            }

        public: 
            int createAgents(int n){
                std::random_device os_seed;
                const u32 seed = os_seed();

                engine generator( seed );
                std::uniform_int_distribution< u32 > wake_up_dist(7,8);
                std::uniform_int_distribution< u32 > kitchen_visits_dist(1,6);
                std::uniform_int_distribution< u32 > lunch_time_dist(11,14);
                std::uniform_int_distribution< u32 > dinner_time_dist(16,18);
                std::uniform_int_distribution< u32 > bed_time_dist(20,22);
                std::uniform_int_distribution< u32 > minutes_dist(0,59);
                
                for (int i = 0; i < n; i++) {
                    int wake_up = wake_up_dist(generator);
                    int kitchen_visits = kitchen_visits_dist(generator);
                    std::string lunch_time = std::to_string(lunch_time_dist(generator)) + ":" + minutesConverter(minutes_dist(generator));
                    std::string dinner_time = std::to_string(dinner_time_dist(generator)) + ":" + minutesConverter(minutes_dist(generator));
                    std::string bed_time = std::to_string(bed_time_dist(generator)) + ":" + minutesConverter(minutes_dist(generator));
                    std::string _wake_up = "0" + std::to_string(wake_up) + ":" + minutesConverter(minutes_dist(generator));
                    int breakfast_time;
                    std::string _breakfast_time;

                    breakfast_time = wake_up + 1;
                    
                    if (breakfast_time < 10){
                        _breakfast_time = "0" + std::to_string(breakfast_time) + ":" + minutesConverter(minutes_dist(generator));
                    } else {
                        _breakfast_time = std::to_string(breakfast_time) + ":" + minutesConverter(minutes_dist(generator));
                    }

                    set(_wake_up, _breakfast_time, kitchen_visits, lunch_time, dinner_time, bed_time);
                }

                return 0;
            }
};