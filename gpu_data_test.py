import gpu_data

gpu_data = gpu_data.GPUData("nvml_test.csv")
gpu_data.plot("Local Time", "Graphics Clock (MHz)")