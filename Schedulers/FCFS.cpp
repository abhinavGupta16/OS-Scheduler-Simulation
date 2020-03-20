//
// Created by gupta on 19-03-2020.
//

#include "FCFS.h"
#include <bits/stdc++.h>

using namespace std;

string FCFS::getName() {
    return "FCFS";
}

void FCFS::addProcess(Process *process){
//    runQueue.insert(runQueue.begin(), process);
    runQueue.push_back(process);
}

Process* FCFS::getNextProcess(){
    if(runQueue.empty())
        return nullptr;
    Process *process = runQueue.front();
    runQueue.pop_front();
    return process;
}