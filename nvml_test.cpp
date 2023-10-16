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

    nvmlClass(int const &deviceIndex)
    {
        NVML_TRY(nvmlnit());

        NVML_TRY(nvmlDeviceGetHandleByIndex(deviceIndex, &device));

        NVML_TRY(nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_V2_BUFFER_SIZE));
    }

    ~nvmlClass()
    {
        nvmlShutdown();
    }

    char[] getName()
    {
        return name;
    }

    std::map<std::string, unsigned int> updatePerfStats()
    {
        _perfMap["graphics_clock"] = getGraphicsClock();
        _perfMap["memory_clock"] = getMemoryClock();
        _perfMap["decoder_clock"] = getDecoderClock();
        _perfMap["fan_speed"] = getFanSpeed();
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

    int getFanSpeed()
    {
        unsigned int fan_speed;
        NVML_TRY(nvmlDeviceGetFanSpeed(device, &fan_speed));
        return fan_speed;
    }

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
    NVML_TRY(nvmlInit());

    unsigned int deviceCount; // Change the data type to unsigned int

    NVML_TRY(nvmlDeviceGetCount(&deviceCount));
    if (deviceCount == 0)
    {
        std::cerr << "No GPU devices found." << std::endl;
        nvmlShutdown();
        return 1;
    }

    // Loop through the number of devices and print the name for each
    while (true)
    {
        for (unsigned int i = 0; i < deviceCount; i++)
        {
            nvmlDevice_t device;
            NVML_TRY(nvmlDeviceGetHandleByIndex(i, &device));

            char name[NVML_DEVICE_NAME_V2_BUFFER_SIZE];
            NVML_TRY(nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_V2_BUFFER_SIZE));
            std::cout << "GPU number " << i << " name is: " << name << std::endl;

            unsigned int graphics_clock;
            NVML_TRY(nvmlDeviceGetClockInfo(device, NVML_CLOCK_GRAPHICS, &graphics_clock));
            std::cout << "GPU number " << i << " graphics clock is: " << graphics_clock << " MHz" << std::endl;

            unsigned int memory_clock;
            NVML_TRY(nvmlDeviceGetClockInfo(device, NVML_CLOCK_MEM, &memory_clock));
            std::cout << "GPU number " << i << " memory clock is: " << memory_clock << " MHz" << std::endl;

            unsigned int decoder_clock;
            NVML_TRY(nvmlDeviceGetClockInfo(device, NVML_CLOCK_VIDEO, &decoder_clock));
            std::cout << "GPU number " << i << " decoder clock is: " << decoder_clock << " MHz" << std::endl;

            /*unsigned int fan_speed;
            NVML_TRY(nvmlDeviceGetFanSpeed(device, &fan_speed));
            std::cout << "GPU number " << i << " fan speed is: " << fan_speed << " %" << std::endl;
            */

            unsigned int temperature;
            NVML_TRY(nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature));
            std::cout << "GPU number " << i << " temperature is: " << temperature << " C" << std::endl;

            nvmlMemory_t memory;
            NVML_TRY(nvmlDeviceGetMemoryInfo(device, &memory));
            std::cout << "GPU number " << i << " memory total is: " << memory.total / 1024 / 1024 << " MB" << std::endl;
            std::cout << "GPU number " << i << " memory used is: " << memory.used / 1024 / 1024 << " MB" << std::endl;
            std::cout << "GPU number " << i << " memory free is: " << memory.free / 1024 / 1024 << " MB" << std::endl;
        }

        Sleep(1000);
    }

    nvmlShutdown();

    return 0;
}
