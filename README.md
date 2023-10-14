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
## Notes and Limitations:
- CPU Clock Speed related information is currently collected through command line (typeperf)
  - This is very slow and inefficient
## To Do:
- Add Linux support
- Switch from command line to AMD and Intel SDKs for CPU Clock Speed
- Add AMD and Intel GPU support using their respective SDKs
- Implement more GPU monitoring features
