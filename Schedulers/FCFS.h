//
// Created by gupta on 19-03-2020.
//

#ifndef ASSIGNMENT2_FCFS_H
#define ASSIGNMENT2_FCFS_H


#include <bits/stdc++.h>
#include "../Process.h"
#include "Scheduler.h"

using namespace std;

class FCFS : public Scheduler{
private:
    deque<Process*> runQueue;
public:
    void addProcess(Process *process) override;
    Process* getNextProcess() override;
    string getName() override;
    void printRunQueue() override;
};


#endif //ASSIGNMENT2_FCFS_H
