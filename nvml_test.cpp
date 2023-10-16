#include <iostream>
#include <nvml.h>

// define a macro that returns the errorstring if the nvml call fails
#define NVML_TRY(call)                                                                 \
    do                                                                                 \
    {                                                                                  \
        nvmlReturn_t result = call;                                                    \
        if (result != NVML_SUCCESS)                                                    \
        {                                                                              \
            std::cerr << "NVML call failed: " << nvmlErrorString(result) << std::endl; \
            nvmlShutdown();                                                            \
            return 1;                                                                  \
        }                                                                              \
    } while (0)

int main()
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
    for (unsigned int i = 0; i < deviceCount; i++)
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
    }

    nvmlShutdown();

    return 0;
}
