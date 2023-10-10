import psutil
import time
import subprocess

def get_CPU_info():
    CPU_info = {
        'CPU NAME' : '',
        'PHYSICAL CORES': 0,
        'LOGICAL CORES': 0,
        'CPU FREQUENCY': 0,
    }

    name_cpu_raw = subprocess.run(['wmic', 'CPU', 'get', 'name'], capture_output=True, text=True)
    output_lines = name_cpu_raw.stdout.split('\n')[2:] #[2:] such that the list begins from the third elemnt of the split list i.e. the second line is now the first and only element of the list | raw stdout as follows"Name\n\n*CPUNAME*\n" | split into ['Name', '', 'CPUNAME'...]
    name_cpu = output_lines[0]
    num_cores = psutil.cpu_count(logical=False)
    num_threads = psutil.cpu_count(logical=True)
    freq_cpu = psutil.cpu_freq().current

    CPU_info['CPU NAME'] = name_cpu
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
    
    #Load testing code | NOT FOR PROD
    while True:
        start_time = time.time()
        cpu_info = get_CPU_info()
        for key, value in cpu_info.items():
            if key != 'CPU FREQUENCY':
                print(f'{key}: {value}')
            else:
                print(f'{key}: {value}MHz')
        print(f"Execution finished in: {(time.time() - start_time):.3f} seconds")
        time.sleep(1)