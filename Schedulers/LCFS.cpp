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