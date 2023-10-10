
# DEPRECATED UNTIL FUTURE USE #

<#
$compileCommand = "g++ main.cpp -o main.exe -lole32 -lwbemuuid"
$runCommand = "./main.exe"

Invoke-Expression $compileCommand

if ($LASTEXITCODE -eq 0){
    Invoke-Expression $runCommand
    if ($LASTEXITCODE -ne 0){
        "Runtime Error. Progam has exited."
    }else{
        "Program Successfully Executed."
    }
}else{
    Write-Host "Compilation Failed. Program will not be executed."
}
*/
#>