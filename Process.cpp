//
// Created by gupta on 17-03-2020.
//

#include <bits/stdc++.h>

#include "Process.h"

Process::Process(int cpuTime, int cpuBurst, int ioBurst){
    this->cpuTime = cpuTime;
    this->cpuBurst = cpuBurst;
    this->ioBurst = ioBurst;
}

ostream& operator<<(ostream &strm, const Process &process) {
    return strm << "Process(" << process.cpuTime << "," << process.cpuBurst << "," << process.ioBurst << ")";
}