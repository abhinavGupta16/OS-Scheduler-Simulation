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
    TRANS_TO_READY,
    TRANS_TO_RUN,
    TRANS_TO_BLOCK,
    TRANS_TO_PREEMPT
};

class Process {
public:
    int cpuTime;
    int cpuBurst;
    int ioBurst;
    Process(int cpuTime, int cpuBurst, int ioBurst);
};

ostream& operator<<(ostream &strm, const Process &process);

#endif //ASSIGNMENT2_PROCESS_H
