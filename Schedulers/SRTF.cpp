//
// Created by gupta on 20-03-2020.
//

#include "SRTF.h"
#include <bits/stdc++.h>

using namespace std;

string SRTF::getName() {
    return "SRTF";
}

void SRTF::insertSorted(deque<Process*> *runQueue, Process *process){
    if(runQueue->empty()){
        runQueue->push_back(process);
    } else {
        for(int i = 0; i < runQueue->size(); i++){
            if(runQueue->at(i)->cpuTime >  process->cpuTime){
                runQueue->insert(runQueue->begin() + i, process);
                return;
            }
        }
        runQueue->push_back(process);
    }
}

void SRTF::addProcess(Process *process){
    insertSorted(&runQueue, process);
}

Process* SRTF::getNextProcess(){
    if(runQueue.empty())
        return nullptr;
    Process *process = runQueue.front();
    runQueue.pop_front();
    return process;
}

void SRTF::printRunQueue() {
    cout<<"SCHED ";
    cout << "(" + to_string(runQueue.size()) + "):";
    if(runQueue.size()!=0){
        cout<< "  ";
    }
    for(int i = 0; i < runQueue.size(); i++){
        cout<< *runQueue[i];
        if(i+1!=runQueue.size()){
            cout << " ";
        }
    }
    cout<<endl;
}