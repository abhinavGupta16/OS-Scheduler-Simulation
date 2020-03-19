//
// Created by gupta on 17-03-2020.
//

#include<iostream>
#include<string>
#include <bits/stdc++.h>

#include "Helper.h"
#include "Schedulers/Scheduler.h"
#include "Schedulers/FCFS.h"

using namespace std;

deque<Event*> eventQueue;
int ofs = 0;
vector<int> randvals;
Scheduler *scheduler;

int main(){
    string inputFilename = "D:\\NYU_assignment\\Spring_2020\\OS\\Assignment2\\files\\lab2_assign\\input0";
    string randomFilename = "D:\\NYU_assignment\\Spring_2020\\OS\\Assignment2\\files\\lab2_assign\\rFile";
    readInputFile(inputFilename, &eventQueue);
    readRandomFile(randomFilename, &randvals);
    scheduler = new FCFS();
    printDQueue(&eventQueue);
}

void Simulation() {
    Event* evt;
    while( (evt = getEvent(&eventQueue)) ) {
        Process *proc = evt->process; // this is the process the event works on
        int currentTime = evt->timeStamp;
        int timeInPrevState = currentTime - proc->cpuTime;
        bool callScheduler = false;
        switch(evt->transition) { // which state to transition to?
            case TRANS_TO_READY:
// must come from BLOCKED or from PREEMPTION
// must add to run queue
                insertSorted(&eventQueue, evt);
                callScheduler = true; // conditional on whether something is run
                break;
            case TRANS_TO_RUN:
// create event for either preemption or blocking
                break;
            case TRANS_TO_BLOCK:
//create an event for when process becomes READY again
                callScheduler = true;
                break;
            case TRANS_TO_PREEMPT:
// add to runqueue (no event is generated)
                callScheduler = true;
                break;
        }
// remove current event object from Memory
        delete evt;
        if(callScheduler) {
            if (getNextEventTime(&eventQueue) == currentTime)
                continue; //process next event from Event queue
            callScheduler = false; // reset global flag
//            if (CURRENT_RUNNING_PROCESS == nullptr) {
//                CURRENT_RUNNING_PROCESS = THE_SCHEDULER->get_next_process();
//                if (CURRENT_RUNNING_PROCESS == nullptr)
//                    continue;
//// create event to make this process runnable for same time.
//            }
        }
    }
}