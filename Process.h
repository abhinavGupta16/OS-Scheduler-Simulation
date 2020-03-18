//
// Created by gupta on 17-03-2020.
//

#ifndef ASSIGNMENT2_PROCESS_H
#define ASSIGNMENT2_PROCESS_H

#include <bits/stdc++.h>


class Process {
public:
    Process(int cpuTime, int cpuBurst, int ioBurst);
    int cpuTime;
    int cpuBurst;
    int ioBurst;
};


#endif //ASSIGNMENT2_PROCESS_H
