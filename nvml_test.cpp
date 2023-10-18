#include <iostream>
#include <nvml.h>
#include <nvmlGetPerf.h>
#include <windows.h>

int
main()
{
    unsigned int deviceIndex{0};

    nvmlGetPerf nvmlObj(deviceIndex);

    while(true){
        std::cout << "The GPU name is: " << nvmlObj.getName() << std::endl;
        nvmlObj.updatePerfStats();
        std::cout << "The GPU graphics clock is: " << nvmlObj.getGraphicsClock() << " MHz" << std::endl;
        std::cout << "The GPU memory clock is: " << nvmlObj.getMemoryClock() << " MHz" << std::endl;
        std::cout << "The GPU decoder clock is: " << nvmlObj.getDecoderClock() << " MHz" << std::endl;
        //std::cout << "The GPU fan speed is: " << nvmlObj.getFanSpeed() << " %" << std::endl;
        std::cout << "The GPU temperature is: " << nvmlObj.getTemperature() << " C" << std::endl;
        std::cout << "The GPU memory total is: " << nvmlObj.getMemoryTotal() << " MB" << std::endl;
        std::cout << "The GPU memory used is: " << nvmlObj.getMemoryUsed() << " MB" << std::endl;
        std::cout << "The GPU memory free is: " << nvmlObj.getMemoryFree() << " MB" << std::endl;
        std::cout << std::endl;
        Sleep(1000);
    }

    return 0;
}
