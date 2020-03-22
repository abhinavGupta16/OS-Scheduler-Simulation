//
// Created by gupta on 20-03-2020.
//

#include "RoundRobin.h"
#include <bits/stdc++.h>

using namespace std;

RoundRobin::RoundRobin(int quantum){
    this->quantum = quantum;
}

int RoundRobin::getQuantum(){
    return this->quantum;
}

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

void RoundRobin::printRunQueue() {
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