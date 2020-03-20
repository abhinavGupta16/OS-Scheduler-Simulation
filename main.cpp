//
// Created by gupta on 17-03-2020.
//

#include<iostream>
#include<string>
#include <bits/stdc++.h>

#include "Helper.h"
#include "Schedulers/Scheduler.h"
#include "Schedulers/FCFS.h"
#include <unistd.h>

using namespace std;

deque<Event*> eventQueue;
int ofs = 0;
vector<int> randvals;
Scheduler *scheduler;
vector<Process*> finishedProcess;
bool verbose = false;
int ioTime = 0;

void Simulation();

void parseArguments(int argc, char *argv[]){
    int c;
    bool schedulerInitialized = false;
    while ((c = getopt (argc, argv, "vtes:")) != -1)
        switch (c)
        {
            case 'v':
                verbose = true;
                break;
            case 's':
                schedulerInitialized = true;
                switch(optarg[0]) {
                    case 'F':
                        scheduler = new FCFS();
                        break;
//                    case 'L':
//                        scheduler = new LCFS();
//                        break;
//                    case 'S':
//                        scheduler = new SJF();
//                        break;
                    default:
                        fputs("Error: invalid scheduler "
                              "specified\n\n", stderr);
                        exit(EXIT_FAILURE);
                }
                break;
            default:
                abort ();
        }

    if(!schedulerInitialized)
        scheduler = new FCFS();
}

int main(int argc, char *argv[]){
    parseArguments(argc, argv);
    string inputFilename  = argv[optind];
    string randomFilename = argv[optind+1];
//    string inputFilename = "D:\\NYU_assignment\\Spring_2020\\OS\\Assignment2\\files\\lab2_assign\\input0";
//    string randomFilename = "D:\\NYU_assignment\\Spring_2020\\OS\\Assignment2\\files\\lab2_assign\\rFile";
    readRandomFile(randomFilename, &randvals);
    readInputFile(inputFilename, &eventQueue, ofs, randvals);
    Simulation();
    printResults(finishedProcess, scheduler, ioTime);
}

void Simulation() {
    Event* evt;
    Process* currentRunningProcess = nullptr;
    int conncurrentIOTime = 0;
    int overlap = 0;
    int prevIOTime = 0;
    while( (evt = getEvent(&eventQueue)) ) {
        Process *process = evt->process; // this is the process the event works on
        int currentTime = evt->timeStamp;
        int timeInPrevState = currentTime - process->stateTs;
        int randomBurst = 0;
        Event *newEvent;
        process_state_t oldState = evt->curState;
        process_state_t curState;
        process_state_t transition;
        bool callScheduler = false;
        switch(evt->transition) { // which state to transition to?
            case TRANS_TO_READY:
// must come from BLOCKED or from PREEMPTION
// must add to run queue
                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": "
                         << enumStateToString(evt->curState) << " -> " << "READY" << endl;
                }
                scheduler->addProcess(process);
                process->stateTs = currentTime;
                curState = STATE_READY;
                transition = TRANS_TO_RUN;
                callScheduler = true; // conditional on whether something is run
                break;
            case TRANS_TO_RUN:
                randomBurst = getCpuBurst(currentRunningProcess->cpuBurst, ofs, randvals);
                if(randomBurst > currentRunningProcess->cpuTime) randomBurst = currentRunningProcess->cpuTime;
                currentRunningProcess->runTime += randomBurst;
                currentRunningProcess->cpuWaiting += timeInPrevState;
                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": "
                         << enumStateToString(evt->curState) << " -> " << "RUNNG cb=" << randomBurst << " rem="
                         << currentRunningProcess->cpuTime << " prio=" << currentRunningProcess->priority << endl;
                }


                currentRunningProcess = process;
                runProcess(currentRunningProcess, randomBurst);
                currentRunningProcess->stateTs = currentTime;
                newEvent = new Event();
                newEvent->curState = STATE_RUNNING;
                newEvent->transition = TRANS_TO_BLOCK;
                newEvent->process = currentRunningProcess;
                newEvent->timeStamp = currentTime + randomBurst;
                newEvent->oldState = oldState;
                insertSorted(&eventQueue, newEvent);
// create event for either preemption or blocking
                break;
            case TRANS_TO_BLOCK:
//create an event for when process becomes READY again
                if(currentRunningProcess->cpuTime == 0){
                    newEvent = new Event();
                    newEvent->timeStamp = evt->timeStamp;
                    newEvent->process = process;
                    newEvent->transition = TRANS_TO_DONE;
                    eventQueue.insert(eventQueue.begin(), newEvent);
                    currentRunningProcess = nullptr;
                    break;
                }
                randomBurst = getCpuBurst(currentRunningProcess->ioBurst, ofs, randvals);
                currentRunningProcess->ioTime += randomBurst;

                if(currentTime + randomBurst > conncurrentIOTime){
                    ioTime += conncurrentIOTime - prevIOTime - overlap;
                    if(conncurrentIOTime!=0) {
                        overlap = conncurrentIOTime - currentTime;
                        if(overlap < 0) {
                            overlap = 0;
                        }
                    }
                    conncurrentIOTime = randomBurst + currentTime;
                    prevIOTime = currentTime;
                }
                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": "
                         << enumStateToString(evt->curState) << " -> " << "BLOCK  ib=" << randomBurst << " rem="
                         << currentRunningProcess->cpuTime << endl;
                }
                currentRunningProcess->stateTs = currentTime;
                newEvent = new Event();
                newEvent->oldState = STATE_RUNNING;
                newEvent->curState = STATE_BLOCKED;
                newEvent->transition = TRANS_TO_READY;
                newEvent->process = currentRunningProcess;
                newEvent->timeStamp = currentTime + randomBurst;
                insertSorted(&eventQueue, newEvent);
                callScheduler = true;
                currentRunningProcess = nullptr;
                break;
            case TRANS_TO_PREEMPT:
// add to runqueue (no event is generated)
                callScheduler = true;
                break;
            case TRANS_TO_DONE:
                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": Done" << endl;
                }
                Process *doneProcess = evt->process;
                doneProcess->finishTime = currentTime;
                doneProcess->turnarTime = currentTime - process->arrivalTime;
                finishedProcess.push_back(evt->process);
                callScheduler = true;
                break;

        }
// remove current event object from Memory
        delete evt;
        evt = nullptr;
        if(callScheduler) {
            if (getNextEventTime(&eventQueue) == currentTime)
                continue; //process next event from Event queue
            callScheduler = false; // reset global flag
            if (currentRunningProcess == nullptr) {
                currentRunningProcess = scheduler->getNextProcess();
                if (currentRunningProcess == nullptr)
                    continue;
                Event *newEventVal = new Event();
                newEventVal->oldState = oldState;
                newEventVal->curState = STATE_READY;
                newEventVal->transition = TRANS_TO_RUN;
                newEventVal->process = currentRunningProcess;
                newEventVal->timeStamp = currentTime;
                insertSorted(&eventQueue, newEventVal);
// create event to make this process runnable for same time.
            }

        }
    }
    ioTime += conncurrentIOTime - prevIOTime - overlap;
}

