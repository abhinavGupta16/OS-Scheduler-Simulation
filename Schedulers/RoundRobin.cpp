//
// Created by gupta on 20-03-2020.
//

#include "RoundRobin.h"
#include <bits/stdc++.h>

using namespace std;

RoundRobin::RoundRobin(int quantum){
    this->quantum = quantum;
    this->remainingBurst = 0;
}

int RoundRobin::getQuantum(){
    return this->quantum;
}

//int RoundRobin::getRemainingCpuBurst(){
//    return remainingBurst;
//}
//
//void RoundRobin::setRemainingCpuBurst(int remainingCpuBurst){
//    this->remainingBurst = remainingCpuBurst;
//}

string RoundRobin::getName() {
    return "RR " + to_string(quantum) ;
}

void RoundRobin::addProcess(Process *process){
    runQueue.push_back(process);
}

Process* RoundRobin::getNextProcess(){
    if(runQueue.empty())
        return nullptr;
    Process *process = runQueue.front();
    runQueue.pop_front();
    return process;
}