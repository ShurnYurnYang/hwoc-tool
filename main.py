import psutil
import time
import subprocess
import re


def first_run():
    CPU_info = {
        "CPU NAME": "",
        "PHYSICAL CORES": 0,
        "LOGICAL CORES": 0,
        "MAX SPEED": 0,
        "CURRENT SPEED": 0,
    }

    name_cpu_raw = subprocess.run(
        ["wmic", "CPU", "get", "name"], capture_output=True, text=True
    )
    output_lines = name_cpu_raw.stdout.split("\n")[2:]  # [2:] such that the list begins from the third elemnt of the split list i.e. the second line is now the first and only element of the list | raw stdout as follows"Name\n\n*CPUNAME*\n" | split into ['Name', '', 'CPUNAME'...]
    name_cpu = output_lines[0]

    num_cores = psutil.cpu_count(logical=False)

    num_threads = psutil.cpu_count(logical=True)

    clock_speed_script = r"""
    $MaxClockSpeed = (Get-CimInstance Win32_Processor).MaxClockSpeed;
    $MaxClockSpeed;
    """

    max_clock_speed = int(
        subprocess.run(
            ["powershell", "-Command", clock_speed_script],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        ).stdout
    )

    CPU_info["CPU NAME"] = name_cpu
    CPU_info["PHYSICAL CORES"] = num_cores
    CPU_info["LOGICAL CORES"] = num_threads
    CPU_info["MAX SPEED"] = max_clock_speed

    return CPU_info


def get_CPU_freq():
    typerf_command = (
        r'typeperf "\Processor Information(_Total)\% Processor Performance" -sc 1'
    )
    output = subprocess.check_output(typerf_command)
    match = re.search(
        r'"(\d+\.\d+)"', output.decode("utf-8")
    )  ## This regex argument looks for a string of digits and a decimal point, followed by more digits. The parentheses capture the digits and decimal point, but not the quotes.
    result = match.group(1) if match else "No match found"
    
    return float(result)

def update_CPU_info(cpu_info):
    cpu_info["CURRENT SPEED"] = cpu_info["MAX SPEED"] * (get_CPU_freq() / 100)
    return cpu_info

if __name__ == "__main__":

    average = 0
    count = 0

    cpu_info = first_run()

    # Performance testing code | NOT FOR PROD
    while True:
        start_time = time.time()
        cpu_info = update_CPU_info(cpu_info)
        for key, value in cpu_info.items():
            if key != "CURRENT SPEED":
                print(f"{key}: {value}")
            else:
                print(f"{key}: {value:.0f} MHz")
        time_diff = time.time() - start_time
        average += time_diff
        count += 1
        print(f"Execution finished in: {time_diff:.3f} seconds\n")
        print(f"Average execution time: {(average/count):.3f} seconds\n")
