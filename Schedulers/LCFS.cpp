//
// Created by gupta on 20-03-2020.
//

#include "LCFS.h"
#include <bits/stdc++.h>

using namespace std;

string LCFS::getName() {
    return "LCFS";
}

void LCFS::addProcess(Process *process){
    runStack.push_back(process);
}

Process* LCFS::getNextProcess(){
    if(runStack.empty())
        return nullptr;
    Process *process = runStack.back();
    runStack.pop_back();
    return process;
}

void LCFS::printRunQueue() {
    cout<<"SCHED ";
    cout << "(" + to_string(runStack.size()) + "):";
    if(runStack.size()!=0){
        cout<< "  ";
    }
    for(int i = 0; i < runStack.size(); i++){
        cout<< *runStack[i];
        if(i+1!=runStack.size()){
            cout << " ";
        }
    }
    cout<<endl;
}