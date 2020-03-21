//
// Created by gupta on 20-03-2020.
//

#ifndef ASSIGNMENT2_SRTF_H
#define ASSIGNMENT2_SRTF_H

#include <bits/stdc++.h>
#include "../Process.h"
#include "Scheduler.h"

using namespace std;

class SRTF : public Scheduler{
private:
    deque<Process*> runQueue;
    void insertSorted(deque<Process*> *runQueue, Process *process);
public:
    void addProcess(Process *process) override;
    Process* getNextProcess() override;
    string getName() override;
    void printRunQueue() override ;
};


#endif //ASSIGNMENT2_SRTF_H
