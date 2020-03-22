//
// Created by gupta on 21-03-2020.
//

#ifndef ASSIGNMENT2_PREEMTIVEPRIO_H
#define ASSIGNMENT2_PREEMTIVEPRIO_H

#include <bits/stdc++.h>
#include "../Process.h"
#include "Scheduler.h"

using namespace std;

class PreemtivePrio : public Scheduler {
private:
    vector<deque<Process*>> activeQueues, expiredQueues;
    vector<deque<Process*>> *activeQueuesPointer, *expiredQueuesPointer;
    int quantum;
    int maxPriority;
    int expiredProcessCount;
    void swapQueues();
    Process* findProcess();
public:
    PreemtivePrio(int quantum, int maxPriority);
    void addProcess(Process *process) override;
    Process* getNextProcess() override;
    string getName() override;
    int getQuantum() override;
    int getMaxPriority() override;
    bool isPriority() override;
    bool isPreemptivePriority() override;
};

#endif //ASSIGNMENT2_PREEMTIVEPRIO_H
