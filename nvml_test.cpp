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
        nvmlDevice_t device;
        NVML_TRY(nvmlDeviceGetHandleByIndex(i, &device));

        char name[NVML_DEVICE_NAME_V2_BUFFER_SIZE];
        NVML_TRY(nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_V2_BUFFER_SIZE));
        std::cout << "GPU number " << i << " name is: " << name << std::endl;
    }

    nvmlShutdown();

    return 0;
}
