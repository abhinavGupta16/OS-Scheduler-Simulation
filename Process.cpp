//
// Created by gupta on 17-03-2020.
//

#include <bits/stdc++.h>

#include "Process.h"

Process::Process(int cpuTime, int cpuBurst, int ioBurst, int pid, int staticPriority, int stateTs, int arrivalTime){
    this->cpuTime = cpuTime;
    this->reqCpuTime = cpuTime;
    this->cpuBurst = cpuBurst;
    this->ioBurst = ioBurst;
    this->pid = pid;
    this->staticPriority = staticPriority;
    this->dynamicPriority = staticPriority-1;
    this->stateTs = stateTs;
    this->arrivalTime = arrivalTime;
    this->ioTime = 0;
    this->runTime = 0;
    this->cpuWaiting = 0;
    this->remainingBurst = 0;
}

ostream& operator<<(ostream &strm, const Process &process) {
    return strm << process.pid << ":" << process.stateTs;
}