#include <iostream>
#include <nvml.h>
#include <windows.h>
#include <map>

// define a macro that returns the errorstring if the nvml call fails
#define NVML_TRY(call)                                                                 \
    do                                                                                 \
    {                                                                                  \
        nvmlReturn_t result = call;                                                    \
        if (result != NVML_SUCCESS)                                                    \
        {                                                                              \
            std::cerr << "NVML call failed: " << nvmlErrorString(result) << std::endl; \
            nvmlShutdown();                                                            \
            throw std::runtime_error("An errorwhile calling NVML");                    \
        }                                                                              \
    } while (0)

class nvmlClass
{

public:
    nvmlDevice_t device;
    char name[NVML_DEVICE_NAME_V2_BUFFER_SIZE];

    nvmlClass(unsigned int const &deviceIndex)
    {
        NVML_TRY(nvmlInit());

        NVML_TRY(nvmlDeviceGetHandleByIndex(deviceIndex, &device));

        NVML_TRY(nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_V2_BUFFER_SIZE));
    }

    ~nvmlClass()
    {
        nvmlShutdown();
    }

    std::string getName()
    {
        std::string name = this->name;
        return name;
    }

    std::map<std::string, unsigned int> updatePerfStats()
    {
        _perfMap["graphics_clock"] = getGraphicsClock();
        _perfMap["memory_clock"] = getMemoryClock();
        _perfMap["decoder_clock"] = getDecoderClock();
        //_perfMap["fan_speed"] = getFanSpeed();
        _perfMap["temperature"] = getTemperature();
        _perfMap["memory_total"] = getMemoryTotal();
        _perfMap["memory_used"] = getMemoryUsed();
        _perfMap["memory_free"] = getMemoryFree();

        return _perfMap;
    }

    int getGraphicsClock()
    {
        unsigned int graphics_clock;
        NVML_TRY(nvmlDeviceGetClockInfo(device, NVML_CLOCK_GRAPHICS, &graphics_clock));
        return graphics_clock;
    }

    int getMemoryClock()
    {
        unsigned int memory_clock;
        NVML_TRY(nvmlDeviceGetClockInfo(device, NVML_CLOCK_MEM, &memory_clock));
        return memory_clock;
    }

    int getDecoderClock()
    {
        unsigned int decoder_clock;
        NVML_TRY(nvmlDeviceGetClockInfo(device, NVML_CLOCK_VIDEO, &decoder_clock));
        return decoder_clock;
    }

    /*int getFanSpeed()
    {
        unsigned int fan_speed;
        NVML_TRY(nvmlDeviceGetFanSpeed(device, &fan_speed));
        return fan_speed;
    }
    */

    int getTemperature()
    {
        unsigned int temperature;
        NVML_TRY(nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature));
        return temperature;
    }

    int getMemoryTotal()
    {
        nvmlMemory_t memory;
        NVML_TRY(nvmlDeviceGetMemoryInfo(device, &memory));
        return memory.total / 1024 / 1024;
    }

    int getMemoryUsed()
    {
        nvmlMemory_t memory;
        NVML_TRY(nvmlDeviceGetMemoryInfo(device, &memory));
        return memory.used / 1024 / 1024;
    }

    int getMemoryFree()
    {
        nvmlMemory_t memory;
        NVML_TRY(nvmlDeviceGetMemoryInfo(device, &memory));
        return memory.free / 1024 / 1024;
    }

private:
    std::map<std::string, unsigned int> _perfMap;

};

int
main()
{
    unsigned int deviceIndex{0};

    nvmlClass nvmlObj(deviceIndex);

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
