$Processor = Get-WmiObject Win32_Processor
$MaxClockSpeed = $Processor.MaxClockSpeed

$ProcessorPerformance = Get-Counter -Counter "\Processor Information(_Total)\% Processor Performance" | Select-Object -ExpandProperty CounterSamples | Select-Object -ExpandProperty CookedValue

$CurrentClockSpeed = $MaxClockSpeed * ($ProcessorPerformance / 100)

Write-Host $CurrentClockSpeed