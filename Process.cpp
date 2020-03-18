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