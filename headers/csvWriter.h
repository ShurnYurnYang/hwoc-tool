#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <iostream>
#include <fstream>
#include <ctime>

class csvWriter
{

public:
    csvWriter(const std::string filename) : filename_(filename)
    {
        csvFile_.open(filename_, std::ios::out | std::ios::app);
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