import subprocess
import re
import time

time_now = time.time()

# Define the combined PowerShell script
ps_script = r"""
$Processor = Get-WmiObject Win32_Processor;
$MaxClockSpeed = $Processor.MaxClockSpeed;
$ProcessorPerformance = Get-Counter -Counter "\Processor Information(_Total)\% Processor Performance" | Select-Object -ExpandProperty CounterSamples | Select-Object -ExpandProperty CookedValue;
$CurrentClockSpeed = $MaxClockSpeed * ($ProcessorPerformance / 100);
Write-Host $CurrentClockSpeed;
"""

clock_speed_script = r"""
$Processor = Get-WmiObject Win32_Processor;
$MaxClockSpeed = $Processor.MaxClockSpeed;
$MaxClockSPeed;
"""

perf_speed_script = r"""
//$Processor = Get-WmiObject Win32_Processor;
$ProcessorPerformance = (Get-Counter -Counter "\Processor Information(_Total)\% Processor Performance").CounterSamples[0].CookedValue
$ProcessorPerformance
"""

typerf_command = (
    r'typeperf "\Processor Information(_Total)\% Processor Performance" -sc 1'
)
output = subprocess.check_output(typerf_command)
match = re.search(r'"(\d+\.\d+)"', output.decode("utf-8")) ## This regex argument looks for a string of digits and a decimal point, followed by more digits. The parentheses capture the digits and decimal point, but not the quotes.
result = match.group(1) if match else "No match found"
print(result)


"""
max_clock_speed = int(
    subprocess.run(
        ["powershell", "-Command", clock_speed_script],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    ).stdout
)
"""

# print(max_clock_speed)

MAX_CLOCK_SPEED = 2112

# Run PowerShell script using subprocess.run

"""
#while True:
perf_speed = float(
    subprocess.run(
        ["powershell", "-Command", perf_speed_script],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    ).stdout
)
"""

# print(f"Current clock speed is {(MAX_CLOCK_SPEED * (perf_speed / 100)):.0f} MHz")

# Capture and display the output
print(f"Execution time: {(time.time() - time_now):.3f} seconds")
