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
    runStack.push(process);
}

Process* LCFS::getNextProcess(){
    if(runStack.empty())
        return nullptr;
    Process *process = runStack.top();
    runStack.pop();
    return process;
}

void LCFS::printRunQueue() {
    cout << "(" + to_string(runStack.size()) + "):";
    if(runStack.size()!=0){
        cout<< "  ";
    }
    stack<Process*> temp = runStack;
    for(int i = 0; i < runStack.size(); i++){
//        cout<< *runStack[i];
        if(i+1!=runStack.size()){
            cout << " ";
        }
    }
}