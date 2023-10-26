#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <iostream>
#include <fstream>
#include <ctime>

class csvWriter{

    public:
        csvWriter(const std::string filename) : filename_(filename){
            csvFile_.open(filename_, std::ios::out | std::ios::app);
        }

        ~csvWriter(){
            csvFile_.close();
        }

        void writeEntry(const std::string entryMessage){
            std::time_t now = std::time(0);
            char timestamp[100];
            std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            csvFile_ << timestamp << "," << entryMessage << std::endl;
        }

    private:
        const std::string filename_;
        std::ofstream csvFile_;

}

#endif // CSV_WRITER_H