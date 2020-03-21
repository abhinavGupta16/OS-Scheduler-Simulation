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
    runQueue.push_back(process);
}

Process* FCFS::getNextProcess(){
    if(runQueue.empty())
        return nullptr;
    Process *process = runQueue.front();
    runQueue.pop_front();
    return process;
}

void FCFS::printRunQueue() {
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
}