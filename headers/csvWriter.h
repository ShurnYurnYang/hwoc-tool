#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <iostream>
#include <fstream>
#include <ctime>

class csvWriter
{

public:
    csvWriter(const std::string filename, auto perfMap) : filename_(filename)
    {

        std::ifstream fileExistsCheck(filename_);

        if (fileExistsCheck)
        {
            // The file exists, so you can open it for appending
            csvFile_.open(filename_, std::ios::out | std::ios::app);
        }
        else
        {
            // The file doesn't exist, so you can create and open it
            csvFile_.open(filename_, std::ios::out);
            std::stringstream collectedHeaders;
            collectedHeaders << "Local Time,"
                             << "Device Name,";

            for (const auto &pair : perfMap)
            {
                std::string key = std::get<0>(pair);
                collectedHeaders << key << ",";
            }
            std::string csvHeader = collectedHeaders.str();
            csvHeader.pop_back(); // remove trailing comma
            csvFile_ << csvHeader << std::endl;
        }
    }

    ~csvWriter()
    {
        csvFile_.close();
    }

    void writeCSVToLog(auto perfMap, nvmlGetPerf &nvmlObj)
    { // formats and writes the entire csv file given the perfMap
        std::stringstream collectedString;

        collectedString << "," << nvmlObj.getName() << ",";

        for (const auto &pair : perfMap)
        {
            unsigned int value = std::get<1>(pair);
            collectedString << value << ",";
        }

        std::string csvEntry = collectedString.str();
        csvEntry.pop_back(); // remove trailing comma

        writeEntry(csvEntry);
    }

private:
    void writeEntry(const std::string entryMessage)
    { // writes a single line entry to the csv file
        std::time_t now = std::time(0);
        char timestamp[100];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        csvFile_ << timestamp << entryMessage << std::endl;
    }
    const std::string filename_;
    std::ofstream csvFile_;
};

#endif // CSV_WRITER_H