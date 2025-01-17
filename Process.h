//
// Created by gupta on 17-03-2020.
//

#ifndef ASSIGNMENT2_PROCESS_H
#define ASSIGNMENT2_PROCESS_H


#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

class Process {
public:
    int cpuTime;
    int reqCpuTime;
    int cpuBurst;
    int ioBurst;
    int pid;
    int staticPriority;
    int dynamicPriority;
    int stateTs;
    int arrivalTime;
    Process(int cpuTime, int cpuBurst, int ioBurst, int pid, int staticPriority, int stateTs, int arrivalTime);
    void runProcess(int cpuBurst);
    int finishTime;
    int turnarTime;
    int ioTime;
    int runTime;
    int cpuWaiting;
    int remainingBurst;
};

ostream& operator<<(ostream &strm, const Process &process);

#endif //ASSIGNMENT2_PROCESS_H
