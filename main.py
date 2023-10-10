import psutil
import cpuinfo
import time

def get_CPU_info():
    CPU_info = {
        'CPU NAME' : '',
        'PHYSICAL CORES': 0,
        'LOGICAL CORES': 0,
        'CPU FREQUENCY': 0,
    }

    #name_cpu = cpuinfo.get_cpu_info()['brand_raw']
    num_cores = psutil.cpu_count(logical=False)
    num_threads = psutil.cpu_count(logical=True)
    freq_cpu = psutil.cpu_freq().current

    #CPU_info['CPU NAME'] = name_cpu
    CPU_info['PHYSICAL CORES'] = num_cores
    CPU_info['LOGICAL CORES'] = num_threads
    CPU_info['CPU FREQUENCY'] = freq_cpu

    return CPU_info


if __name__ == '__main__':
    start_time = time.time()
    cpu_info = get_CPU_info()
    for key, value in cpu_info.items():
        if key != 'CPU FREQUENCY':
            print(f'{key}: {value}')
        else:
            print(f'{key}: {value}MHz')
    print(f"Execution finished in: {(time.time() - start_time):.3f} seconds")