#include <iostream>
#include <nvml.h>
#include <nvmlGetPerf.h>
#include <windows.h>
#include <stdlib.h>
#include <logWriter.h>
#include <sstream>
#include <csvWriter.h>

int
main()
{
    unsigned int deviceIndex{0};

    nvmlGetPerf nvmlObj(deviceIndex);

    auto perfMap = nvmlObj.updatePerfStats();

    logWriter logWriterObj("nvml_test.log");

    csvWriter csvWriterObj("nvml_test.csv");

    while(true){
        perfMap = nvmlObj.updatePerfStats();

        logWriterObj.writeToLog(perfMap, nvmlObj);

        csvWriterObj.writeCSVToLog(perfMap, nvmlObj);

        Sleep(1000);
    }

    return 0;
}
