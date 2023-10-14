#include <iostream>
#include <nvml.h>

int main() {
    nvmlReturn_t result;
    result = nvmlInit();
    if (result != NVML_SUCCESS) {
        std::cerr << "NVML initialization failed: " << nvmlErrorString(result) << std::endl;
        return 1;
    }
    unsigned int deviceCount; // Change the data type to unsigned int
    result = nvmlDeviceGetCount(&deviceCount);
    if (result != NVML_SUCCESS) {
        std::cerr << "Failed to get the number of GPU devices: " << nvmlErrorString(result) << std::endl;
        nvmlShutdown();
        return 1;
    }

    if (deviceCount == 0) {
        std::cerr << "No GPU devices found." << std::endl;
        nvmlShutdown();
        return 1;
    }

    for (unsigned int i = 0; i < deviceCount; i++) { // Change the data type to unsigned int
        nvmlDevice_t device;
        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (result != NVML_SUCCESS) {
            std::cerr << "Failed to get the handle for GPU device " << i << ": " << nvmlErrorString(result) << std::endl;
            continue;
        }

        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        result = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);
        if (result != NVML_SUCCESS) {
            std::cerr << "Failed to get the name of GPU device " << i << ": " << nvmlErrorString(result) << std::endl;
        } else {
            std::cout << "GPU " << i << " Name: " << name << std::endl;
        }
    }

    nvmlShutdown();

    return 0;
}
