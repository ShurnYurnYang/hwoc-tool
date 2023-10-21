#include <iostream>
#include <nvml.h>
#include <nvmlGetPerf.h>
#include <windows.h>
#include <stdlib.h>
#include <logWriter.h>
#include <sstream>

int
main()
{
    unsigned int deviceIndex{0};

    nvmlGetPerf nvmlObj(deviceIndex);

    std::map<std::string, unsigned int> perfMap;

    logWriter logWriterObj("nvml_test.log");

    while(true){
        perfMap = nvmlObj.updatePerfStats();

        std::stringstream collectedString;

        collectedString << nvmlObj.getName() << " | ";

        for(const auto& pair : perfMap){
            std::string key = pair.first;
            unsigned int value = pair.second;
            collectedString << key << ": " << value << " | ";
        }

        std::string logEntry = collectedString.str();

        logWriterObj.writeEntry(logEntry);

        Sleep(1000);
    }

    return 0;
}
