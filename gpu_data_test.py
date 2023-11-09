import gpu_data

gpu_data = gpu_data.GPUData("nvml_test.csv")
for header in gpu_data.dataframe.columns[2:]:
    gpu_data.plot("Local Time", str(header))