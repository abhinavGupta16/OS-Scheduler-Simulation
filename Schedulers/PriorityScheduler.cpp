//
// Created by gupta on 20-03-2020.
//

#include "PriorityScheduler.h"
#include <bits/stdc++.h>

using namespace std;

PriorityScheduler::PriorityScheduler(int quantum, int maxPriority){
    this->quantum = quantum;
    this->maxPriority = maxPriority;
    for(int i = 0; i < maxPriority; i++){
        deque<Process*> activeQueue, expiredQueue;
        activeQueues.push_back(activeQueue);
        expiredQueues.push_back(expiredQueue);
    }
    activeQueuesPointer = &activeQueues;
    expiredQueuesPointer = &expiredQueues;
    this->expiredProcessCount = 0;
}

int PriorityScheduler::getQuantum(){
    return this->quantum;
}

string PriorityScheduler::getName() {
    return "PRIO " + to_string(quantum) ;
}

void PriorityScheduler::addProcess(Process *process){
    if(process->dynamicPriority==-1){
        process->dynamicPriority = process->staticPriority-1;
        expiredQueuesPointer->at(process->dynamicPriority).push_back(process);
        expiredProcessCount++;
    } else {
        activeQueuesPointer->at(process->dynamicPriority).push_back(process);
    }
}

Process* PriorityScheduler::findProcess(){
    Process *process = nullptr;
    deque<Process*> curQueue;
    for(int i = activeQueuesPointer->size()-1; i >= 0; i--){
        if(!activeQueuesPointer->at(i).empty()){
            process = activeQueuesPointer->at(i).front();
            activeQueuesPointer->at(i).pop_front();
            return process;
        }
    }
    return process;
}

Process* PriorityScheduler::getNextProcess(){
    Process *process = findProcess();
    if(expiredProcessCount > 0 && process == nullptr){
        swapQueues();
        return findProcess();
    }
    return process;
}

void PriorityScheduler::swapQueues(){
    vector<deque<Process*>> *temp = activeQueuesPointer;
    activeQueuesPointer = expiredQueuesPointer;
    expiredQueuesPointer = temp;
    expiredProcessCount = 0;
}

int PriorityScheduler::getMaxPriority(){
    return maxPriority;
}

bool PriorityScheduler::isPriority() {
    return true;
}