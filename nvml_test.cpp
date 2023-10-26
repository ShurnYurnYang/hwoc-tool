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

    auto perfMap = nvmlObj.updatePerfStats();

    logWriter logWriterObj("nvml_test.log");

    while(true){
        perfMap = nvmlObj.updatePerfStats();

        logWriterObj.writeToLog(perfMap, nvmlObj);

        Sleep(1000);
    }

    return 0;
}
