//
// Created by gupta on 17-03-2020.
//

#include<iostream>
#include<string>
#include <bits/stdc++.h>

#include "Helper.h"
#include "Schedulers/Scheduler.h"
#include "Schedulers/FCFS.h"
#include "Schedulers/LCFS.h"
#include "Schedulers/SRTF.h"
#include "Schedulers/RoundRobin.h"
#include "Schedulers/PriorityScheduler.h"
#include <unistd.h>

using namespace std;

deque<Event*> eventQueue;
int ofs = 0;
vector<int> randvals;
Scheduler *scheduler;
vector<Process*> finishedProcess;
bool verbose = false;
bool printEvent = false;
bool printRunQueue = false;
int ioTime = 0;

void Simulation();

void parseArguments(int argc, char *argv[]){
    int c, quantum;
    int maxPriority=4;
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
                    case 'L':
                        scheduler = new LCFS();
                        break;
                    case 'S':
                        scheduler = new SRTF();
                        break;
                    case 'R':
                        quantum = atoi(optarg + 1);
                        scheduler = new RoundRobin(quantum);
                        break;
                    case 'P':
                        sscanf(optarg+1, "%d:%d",&quantum,&maxPriority);
                        scheduler = new PriorityScheduler(quantum, maxPriority);
                        break;
                    default:
                        fputs("Error: invalid scheduler "
                              "specified\n\n", stderr);
                        exit(EXIT_FAILURE);
                }
                break;
            case 'e':
                printEvent = true;
                break;
            case 't':
                printRunQueue = true;
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
    readInputFile(inputFilename, &eventQueue, ofs, randvals, scheduler);
    Simulation();
    printResults(finishedProcess, scheduler, ioTime);
}

void Simulation() {
    Event* evt;
    Process* currentRunningProcess = nullptr;
    int conncurrentIOTime = 0;
    int overlap = 0;
    int prevIOTime = 0;
    if(printEvent){
        cout<<"ShowEventQ:  ";
        showEventQ(&eventQueue);
        cout<<endl;
    }
    while( (evt = getEvent(&eventQueue)) ) {
        Process *process = evt->process; // this is the process the event works on
        int currentTime = evt->timeStamp;
        int timeInPrevState = currentTime - process->stateTs;
        int randomBurst = 0;
        int cpuBurst = 0;
        Event *newEvent;
        process_state_t oldState = evt->curState;
        bool callScheduler = false;
        switch(evt->transition) {
            case TRANS_TO_READY:
// must come from BLOCKED or from PREEMPTION
// must add to run queue
                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": "
                         << enumStateToString(evt->curState) << " -> " << "READY" << endl;
                }
                scheduler->addProcess(process);
                process->stateTs = currentTime;
                callScheduler = true; // conditional on whether something is run
                break;
            case TRANS_TO_RUN:

                if(currentRunningProcess->remainingBurst > 0){
                    randomBurst = currentRunningProcess->remainingBurst;
                    currentRunningProcess->remainingBurst = 0;
                } else {
                    randomBurst = getCpuBurst(currentRunningProcess->cpuBurst, ofs, randvals);
                }

                if(randomBurst > currentRunningProcess->cpuTime) {
                    randomBurst = currentRunningProcess->cpuTime;
                }

                newEvent = new Event();
                newEvent->curState = STATE_RUNNING;
                if(scheduler->getQuantum() != -1){
                    if(scheduler->getQuantum() < randomBurst){
                        currentRunningProcess->remainingBurst = randomBurst - scheduler->getQuantum();
                        cpuBurst = scheduler->getQuantum();
                        newEvent->transition = TRANS_TO_PREEMPT;
                    } else {
                        currentRunningProcess->remainingBurst = 0;
                        newEvent->transition = TRANS_TO_BLOCK;
                        cpuBurst = randomBurst;
                    }
                } else {
                    cpuBurst = randomBurst;
                    newEvent->transition = TRANS_TO_BLOCK;
                }

                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": "
                         << enumStateToString(evt->curState) << " -> " << "RUNNG cb=" << randomBurst << " rem="
                         << currentRunningProcess->cpuTime << " prio=" << currentRunningProcess->dynamicPriority << endl;
                }

                currentRunningProcess->runTime += cpuBurst;
                currentRunningProcess->cpuWaiting += timeInPrevState;
                currentRunningProcess = process;
                runProcess(currentRunningProcess, cpuBurst);
                currentRunningProcess->stateTs = currentTime;

                newEvent->process = currentRunningProcess;
                newEvent->timeStamp = currentTime + cpuBurst;
                newEvent->oldState = oldState;
                if(printEvent) {
                    cout << "  AddEvent(" << *newEvent << "):";
                    if(!eventQueue.empty()){
                        cout<<"  ";
                    }
                    printDQueue(&eventQueue);
                }
                insertSorted(&eventQueue, newEvent);
                if(printEvent) {
                    cout << " ==>   ";
                    printDQueue(&eventQueue);
                    cout<<endl;
                }
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
                currentRunningProcess->dynamicPriority = currentRunningProcess->staticPriority-1;
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


                currentRunningProcess->stateTs = currentTime;
                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": "
                         << enumStateToString(evt->curState) << " -> " << "BLOCK  ib=" << randomBurst << " rem="
                         << currentRunningProcess->cpuTime << endl;
                }

                newEvent = new Event();
                newEvent->oldState = STATE_RUNNING;
                newEvent->curState = STATE_BLOCKED;
                newEvent->transition = TRANS_TO_READY;
                newEvent->process = currentRunningProcess;
                newEvent->timeStamp = currentTime + randomBurst;
                if(printEvent) {
                    cout << "  AddEvent(" << *newEvent << "):";
                    if(!eventQueue.empty()){
                        cout<<"  ";
                    }
                    printDQueue(&eventQueue);
                }
                insertSorted(&eventQueue, newEvent);
                if(printEvent) {
                    cout << " ==>   ";
                    printDQueue(&eventQueue);
                    cout<<endl;
                }
                callScheduler = true;
                currentRunningProcess = nullptr;
                break;
            case TRANS_TO_PREEMPT:
// add to runqueue (no event is generated)
                if(verbose) {
                    cout << currentTime << " " << process->pid << " " << timeInPrevState << ": "
                         << enumStateToString(evt->curState) << " -> " << "READY  cb=" << currentRunningProcess->remainingBurst << " rem="
                         << currentRunningProcess->cpuTime << " prio=" << currentRunningProcess->dynamicPriority << endl;
                }
                if(scheduler->isPriority()){
                    process->dynamicPriority--;
                }
                process->stateTs = currentTime;
                scheduler->addProcess(process);
                currentRunningProcess = nullptr;
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

        if(callScheduler) {
            if (getNextEventTime(&eventQueue) == currentTime)
                continue;
            callScheduler = false;
            if (currentRunningProcess == nullptr) {
                if(printRunQueue){
                    cout<<"SCHED ";
                    scheduler->printRunQueue();
                    cout<<endl;
                }
                currentRunningProcess = scheduler->getNextProcess();
                if (currentRunningProcess == nullptr)
                    continue;
                Event *newEventVal = new Event();
                newEventVal->oldState = oldState;
                newEventVal->curState = STATE_READY;
                newEventVal->transition = TRANS_TO_RUN;
                newEventVal->process = currentRunningProcess;
                newEventVal->timeStamp = currentTime;
                if(printEvent) {
                    cout << "  AddEvent(" << *newEventVal << "):";
                    if(!eventQueue.empty()){
                        cout<<"  ";
                    }
                    printDQueue(&eventQueue);
                }
                insertSorted(&eventQueue, newEventVal);
                if(printEvent) {
                    cout << " ==>   ";
                    printDQueue(&eventQueue);
                    cout<<endl;
                }
// create event to make this process runnable for same time.
            }
            delete evt;
            evt = nullptr;
        }
    }
    ioTime += conncurrentIOTime - prevIOTime - overlap;
}

