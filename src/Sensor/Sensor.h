#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

class Sensor 
{
    // private:
    //     std::string type;
    //     std::string room;
    //     float sensitivity;
    
    // public:
    //     void set(
    //         std::string _type, 
    //         std::string _room, 
    //         float _sensitivity
    //     ) 
    //     {
    //         type = _type;
    //         room = _room;
    //         sensitivity = _sensitivity;
    //     }
    public:
        int trigger(
            std::string uuid,
            std::string room,
            std::string type
        ) 
        {
            std::string filename("data/stream.csv");
            std::fstream file_out;
            std::stringstream ss;
            std::time_t time = std::time(nullptr);
            file_out.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
            if (!file_out)
            {
                file_out.open(filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
                file_out << "";
                file_out.close();
            } 
            else 
            {
                ss << uuid << "," << room << "," << type << "," << time;
                file_out << ss.str() << std::endl;
                file_out.close();
            }
            return 0;
        }
};