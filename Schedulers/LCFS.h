//
// Created by gupta on 20-03-2020.
//

#ifndef ASSIGNMENT2_LCFS_H
#define ASSIGNMENT2_LCFS_H

#include <bits/stdc++.h>
#include "../Process.h"
#include "Scheduler.h"

using namespace std;

class LCFS : public Scheduler{
private:
    stack<Process*> runStack;
public:
    void addProcess(Process *process) override;
    Process* getNextProcess() override;
    string getName() override;
    void printRunQueue() override;
};


#endif //ASSIGNMENT2_LCFS_H
