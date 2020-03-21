//
// Created by gupta on 20-03-2020.
//

#ifndef ASSIGNMENT2_ROUNDROBIN_H
#define ASSIGNMENT2_ROUNDROBIN_H

#include <bits/stdc++.h>
#include "../Process.h"
#include "Scheduler.h"

using namespace std;

class RoundRobin : public Scheduler {
private:
    deque<Process*> runQueue;
    int quantum;
public:
    RoundRobin(int quantum);
    void addProcess(Process *process) override;
    Process* getNextProcess() override;
    string getName() override;
    int getQuantum() override;
};


#endif //ASSIGNMENT2_ROUNDROBIN_H
