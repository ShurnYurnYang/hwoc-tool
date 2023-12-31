# HWOC tool
HWOC tool is a set of scripts that monitors hardware level performance of components and provides overclocking related tools and features.

## Features
### Supported Operating Systems:
- Windows
### Supported Hardware:
- CPU:
  - AMD
  - Intel 
- GPU:
  - Nvidia
### Monitoring Features:
- CPU:
  - CPU Name
  - Physical Cores
  - Logical Cores (Threads)
  - Nominal Clock Speed
  - Current Clock Speed
- GPU:
  - GPU Name
  - Clock Speed
  - Memory Clock Speed
  - Video Decoder Clock Speed
  - Temperature
  - Total Memory
  - Used Memory
  - Free Memory
### Data Tracking Features:
- CPU:
   - Console
- GPU:
   - Log in .txt
   - CSV
   - Line Plot
## Examples
### GPU Performance Data Written To Log
![box](examples/nvml_test_log_example.png)
### GPU Performance Data Written To CSV
![box](examples/nvml_test_csv_example.png)
### GPU Performance Data Visualized As Plot
![box](examples/data_to_plot_example.png)
### CPU Performance Data Written To Console
![box](examples/hwoc_tool_cpu_example.png)
## Notes and Limitations:
- CPU Clock Speed related information is currently collected through command line (typeperf)
  - This is very slow and inefficient
## To Do:
- Add Linux support
- Switch from using command line to AMD Ryzen Master Monitoring and Intel Performance Counter Monitor SDKs for CPU Clock Speed
- Add AMD and Intel GPU support using GPUPerfAPI and Metric Discovery, respectively.
