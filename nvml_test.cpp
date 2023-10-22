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

    std::array<std::tuple<std::string, unsigned int>, 8> perfMap;

    logWriter logWriterObj("nvml_test.log");

    while(true){
        perfMap = nvmlObj.updatePerfStats();

        std::stringstream collectedString;

        collectedString << "| " << nvmlObj.getName() << " | ";

        for(const auto& pair : perfMap){
            std::string key = std::get<0>(pair);
            unsigned int value = std::get<1>(pair);
            collectedString << key << ": " << value << " | ";
        }

        std::string logEntry = collectedString.str();

        logWriterObj.writeEntry(logEntry);

        Sleep(1000);
    }

    return 0;
}
