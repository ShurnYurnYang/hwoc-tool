#ifndef NVML_GET_PERF_H
#define NVML_GET_PERF_H

#include <iostream>
#include <nvml.h>
#include <array>
#include <tuple>

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

class nvmlGetPerf
{

public:
    nvmlDevice_t device;
    char name[NVML_DEVICE_NAME_V2_BUFFER_SIZE];

    nvmlGetPerf(unsigned int const &deviceIndex)
    {
        NVML_TRY(nvmlInit());

        NVML_TRY(nvmlDeviceGetHandleByIndex(deviceIndex, &device));

        NVML_TRY(nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_V2_BUFFER_SIZE));
    }

    ~nvmlGetPerf()
    {
        nvmlShutdown();
    }

    std::string getName()
    {
        std::string name = this->name;
        return name;
    }

    std::array<std::tuple<std::string, unsigned int>, 8> updatePerfStats()
    {
        _perfMap[0] = std::make_tuple("Graphics Clock (MHz)", getGraphicsClock());
        _perfMap[1] = std::make_tuple("Memory Clock (MHz)", getMemoryClock());
        _perfMap[2] = std::make_tuple("Decoder Clock (MHz)", getDecoderClock());
        //_perfMap[3] = std::make_tuple("fan_speed", getFanSpeed());
        _perfMap[4] = std::make_tuple("Temperature (C)", getTemperature());
        _perfMap[5] = std::make_tuple("Total Memory (MB)", getMemoryTotal());
        _perfMap[6] = std::make_tuple("Used Memory (MB)", getMemoryUsed());
        _perfMap[7] = std::make_tuple("Free Memory (MB)", getMemoryFree());

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
    std::array<std::tuple<std::string, unsigned int>, 8> _perfMap;
};

#endif // NVML_GET_PERF_H