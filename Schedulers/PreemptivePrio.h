//
// Created by gupta on 21-03-2020.
//

#ifndef ASSIGNMENT2_PREEMPTIVEPRIO_H
#define ASSIGNMENT2_PREEMPTIVEPRIO_H

#include <bits/stdc++.h>
#include "../Process.h"
#include "Scheduler.h"

using namespace std;

class PreemptivePrio : public Scheduler {
private:
    vector<deque<Process*>> activeQueues, expiredQueues;
    vector<deque<Process*>> *activeQueuesPointer, *expiredQueuesPointer;
    int quantum;
    int maxPriority;
    int expiredProcessCount;
    void swapQueues();
    Process* findProcess();
    void printQueueVector(vector<deque<Process*>> *queuesPointer);
public:
    PreemptivePrio(int quantum, int maxPriority);
    void addProcess(Process *process) override;
    Process* getNextProcess() override;
    string getName() override;
    int getQuantum() override;
    int getMaxPriority() override;
    bool isPriority() override;
    bool isPreemptivePriority() override;
    void printRunQueue() override;
};

#endif //ASSIGNMENT2_PREEMPTIVEPRIO_H
