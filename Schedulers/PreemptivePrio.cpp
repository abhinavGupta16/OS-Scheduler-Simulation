//
// Created by gupta on 21-03-2020.
//

#include "PreemptivePrio.h"
#include <bits/stdc++.h>

using namespace std;

PreemptivePrio::PreemptivePrio(int quantum, int maxPriority){
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

int PreemptivePrio::getQuantum(){
    return this->quantum;
}

string PreemptivePrio::getName() {
    return "PREPRIO " + to_string(quantum) ;
}

void PreemptivePrio::addProcess(Process *process){
    if(process->dynamicPriority==-1){
        process->dynamicPriority = process->staticPriority-1;
        expiredQueuesPointer->at(process->dynamicPriority).push_back(process);
        expiredProcessCount++;
    } else {
        activeQueuesPointer->at(process->dynamicPriority).push_back(process);
    }
}

Process* PreemptivePrio::findProcess(){
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

Process* PreemptivePrio::getNextProcess(){
    Process *process = findProcess();
    if(expiredProcessCount > 0 && process == nullptr){
        swapQueues();
        return findProcess();
    }
    return process;
}

void PreemptivePrio::swapQueues(){
    vector<deque<Process*>> *temp = activeQueuesPointer;
    activeQueuesPointer = expiredQueuesPointer;
    expiredQueuesPointer = temp;
    expiredProcessCount = 0;
}

int PreemptivePrio::getMaxPriority(){
    return maxPriority;
}

bool PreemptivePrio::isPriority() {
    return true;
}

bool PreemptivePrio::isPreemptivePriority(){
    return true;
}

void PreemptivePrio::printQueueVector(vector<deque<Process*>> *queuesPointer){
    cout<<"{ ";
    for(int i = queuesPointer->size()-1; i >= 0 ; i--){
        deque<Process*> runQueue = queuesPointer->at(i);
        cout<<"[";
        for(int i = 0; i < runQueue.size(); i++){
            if(i+1==runQueue.size()){
                cout << runQueue[i]->pid;
            } else {
                cout << runQueue[i]->pid << ",";
            }
        }
        cout<<"]";
    }
    cout<<"} :";
}

void PreemptivePrio::printRunQueue() {
    printQueueVector(activeQueuesPointer);
    cout<<" ";
    printQueueVector(expiredQueuesPointer);
    cout<<endl;
}