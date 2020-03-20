//
// Created by gupta on 17-03-2020.
//

#include <bits/stdc++.h>

#include "Process.h"

Process::Process(int cpuTime, int cpuBurst, int ioBurst, int pid, int priority, int stateTs, int arrivalTime){
    this->cpuTime = cpuTime;
    this->reqCpuTime = cpuTime;
    this->cpuBurst = cpuBurst;
    this->ioBurst = ioBurst;
    this->pid = pid;
    this->priority = priority;
    this->stateTs = stateTs;
    this->arrivalTime = arrivalTime;
    this->ioTime = 0;
    this->runTime = 0;
    this->cpuWaiting = 0;
    this->remainingBurst = 0;
}

ostream& operator<<(ostream &strm, const Process &process) {
    return strm << "Process(" << process.cpuTime << "," << process.cpuBurst << "," << process.ioBurst << ")";
}