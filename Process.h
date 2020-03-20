//
// Created by gupta on 17-03-2020.
//

#ifndef ASSIGNMENT2_PROCESS_H
#define ASSIGNMENT2_PROCESS_H


#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

enum process_state_t {
    STATE_CREATED,
    STATE_READY,
    STATE_RUNNING,
    STATE_BLOCKED,
    STATE_DONE,
    TRANS_TO_READY,
    TRANS_TO_RUN,
    TRANS_TO_BLOCK,
    TRANS_TO_PREEMPT,
    TRANS_TO_DONE
};

class Process {
public:
    int cpuTime;
    int reqCpuTime;
    int cpuBurst;
    int ioBurst;
    int pid;
    int priority;
    int stateTs;
    int arrivalTime;
    Process(int cpuTime, int cpuBurst, int ioBurst, int pid, int priority, int stateTs, int arrivalTime);
    int finishTime;
    int turnarTime;
    int ioTime;
    int runTime;
    int cpuWaiting;
};

ostream& operator<<(ostream &strm, const Process &process);

#endif //ASSIGNMENT2_PROCESS_H
