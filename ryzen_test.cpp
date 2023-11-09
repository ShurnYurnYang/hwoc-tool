//#pragma once
#include <iostream>
#include "ICPUEx.h"
#include "IPlatform.h"
#include "IDeviceManager.h"
#include "IBIOSEx.h"

//#include "Utility.hpp"
#define MAX_LENGTH 50

void callAPI(){
    bool initalizationCode = false;

    IPlatform& rPlatform = GetPlatform();

    initalizationCode = rPlatform.Init();
    if(!initalizationCode){
        std::cerr << "Platform initialization failed" << std::endl;
        return;
    }

    IDeviceManager& rDeviceManager = rPlatform.GetIDeviceManager();
    ICPUEx* obj = (ICPUEx*)rDeviceManager.GetDevice(dtCPU, 0);

    if(obj){

        int iRet = 0;

        std::cout << "CPU device found" << std::endl;

        CPUParameters cpuParams;
    
        iRet = obj->GetCPUParameters(cpuParams);
        if(iRet){
            std::cerr << "GetCPUParameters failed" << std::endl;
            return;
        }else{
            //printCPUParams(cpuParams);
        }

    } else {
        std::cout << "CPU device not found" << std::endl;
    } 
}

void printCPUParams(CPUParameters& cpuParams){
    
}

int main(){
    callAPI();
    return 0;
}