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
    logWriter(const std::string filename) : filename_(filename)
    {
        logFile_.open(filename_, std::ios::out | std::ios::app);
    }

    ~logWriter()
    {
        logFile_.close();
    }

    void writeToLog(auto perfMap, nvmlGetPerf &nvmlObj)
    { // formats and writes the entire log file given the perfMap
        std::stringstream collectedString;

        collectedString << "| " << nvmlObj.getName() << " | ";

        for (const auto &pair : perfMap)
        {
            std::string key = std::get<0>(pair);
            unsigned int value = std::get<1>(pair);
            collectedString << key << ": " << value << " | ";
        }

        std::string logEntry = collectedString.str();

        writeEntry(logEntry);
    }

private:
    void writeEntry(const std::string entryMessage)
    { // writes a single line entry to the log file
        std::time_t now = std::time(0);
        char timestamp[100];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        logFile_ << timestamp << " " << entryMessage << std::endl;
    }
    const std::string filename_;
    std::ofstream logFile_;
};

#endif // LOG_WRITER_H