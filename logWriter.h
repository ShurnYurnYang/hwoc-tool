#ifndef LOG_WRITER_H
#define LOG_WRITER_H

#include <iostream>
#include <fstream>
#include <ctime>


class logWriter
{
    public:
        logWriter(const std::string filename) : filename_(filename){
            logFile_.open(filename_, std::ios::out | std::ios::app);
        }

        ~logWriter(){
            logFile_.close();
        }

        void writeEntry(const std::string entryMessage){
            std::time_t now = std::time(0);
            char timestamp[100];
            std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            logFile_ << timestamp << " " << entryMessage << std::endl;
        }
    private:
        const std::string filename_;
        std::ofstream logFile_;
}
    
    