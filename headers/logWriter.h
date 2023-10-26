#ifndef LOG_WRITER_H
#define LOG_WRITER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <array>
#include <tuple>


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

        void writeToLog(std::array<std::tuple<std::string, unsigned int>, 8> perfMap, nvmlGetPerf& nvmlObj){
            std::stringstream collectedString;

            collectedString << "| " << nvmlObj.getName() << " | ";

            for(const auto& pair : perfMap){
                std::string key = std::get<0>(pair);
                unsigned int value = std::get<1>(pair);
                collectedString << key << ": " << value << " | ";
            }

            std::string logEntry = collectedString.str();

            writeEntry(logEntry);
        }
        
    private:
        const std::string filename_;
        std::ofstream logFile_;
};

#endif // LOG_WRITER_H