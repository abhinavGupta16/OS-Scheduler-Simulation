//
// Created by gupta on 18-03-2020.
//

#include "Helper.h"
#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

int getCpuBurst(int burst, int &ofs, vector<int> &randvals) {
    if(ofs >= randvals.size())
        ofs = 0;
    int value = 1 + (randvals[ofs] % burst);
    ofs++;
    return value;
}

Event* createEvent(int timestamp, Process* process, process_state_t oldState, process_state_t newState, process_state_t transition){
    Event *event = new Event(timestamp, process, 0, oldState, newState, transition);
    return event;
}

void insertSorted(deque<Event*> *eventQueue, Event *event){
    if(eventQueue->empty()){
       eventQueue->push_back(event);
    } else {
        for(int i = 0; i < eventQueue->size(); i++){
            if(eventQueue->at(i)->timeStamp >  event->timeStamp){
                eventQueue->insert(eventQueue->begin() + i, event);
                return;
            }
        }
        eventQueue->push_back(event);
    }
}

void readInputFile(string filename, deque<Event*> *eventQueue, int &ofs, vector<int> &randvals){
    ifstream input(filename);
    string line;
    vector<string> tokens;
    int pid = 0;
    while(getline(input, line)) {
        size_t prev = 0, pos;
        while ((pos = line.find_first_of(" ", prev)) != string::npos) {
            if (pos > prev)
                tokens.push_back(line.substr(prev, pos-prev));
            prev = pos+1;
        }
        if (prev < line.length())
            tokens.push_back(line.substr(prev, string::npos));
        int priority = getCpuBurst(4, ofs, randvals)-1;
        Process *process = new  Process(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]), pid, priority, stoi(tokens[0]), stoi(tokens[0]));
        Event *event = createEvent(stoi(tokens[0]), process, STATE_CREATED, STATE_CREATED, TRANS_TO_READY);

        insertSorted(eventQueue, event);
        tokens.clear();
        pid++;
    }
}

Event* getEvent(deque<Event*> *eventQueue){
    if(eventQueue->empty()){
        return nullptr;
    }
    Event *evt = eventQueue->front();
    eventQueue->pop_front();
    return evt;
}

int getNextEventTime(deque<Event*> *eventQueue){
    if(eventQueue->empty())
        return -1;
    Event *evt = eventQueue->front();
    return evt->timeStamp;
}

void readRandomFile(string filename, vector<int> *randvals){
    ifstream input(filename);
    string line;
    getline(input, line);
    while(getline(input, line)) {
        randvals->push_back(stoi(line));
    }
}

void printDQueue(deque<Event*> *eventQueue){
    deque <Event*> :: iterator it;
    for (it = eventQueue->begin(); it != eventQueue->end(); ++it)
        cout << "\t" << **it << endl;
    cout << '\n';
}

void runProcess(Process* process, int cpuBurst){
    process->cpuTime -= cpuBurst;
}

string enumStateToString(process_state_t state) {
    switch(state) {
        case STATE_CREATED:
            return "CREATED";
        case STATE_READY:
            return "READY";
        case STATE_RUNNING:
            return "RUNNG";
        case STATE_BLOCKED:
            return "BLOCK";
        case STATE_DONE:
            return "DONE";
        default:
            return "Invalid animal";
    }
}

bool compareInterval(Process* i1, Process* i2)
{
    return (i1->pid < i2->pid);
}

void printResults(vector<Process*> &finishedProcess, Scheduler *scheduler){
    sort(finishedProcess.begin(), finishedProcess.end(), compareInterval);
    double totRunTime = 0;
    double totIOTime = 0;
    double totTurnarime = 0;
    double totCpuWaiting = 0;
    cout<<scheduler->getName()<<endl;
    for(int i = 0; i < finishedProcess.size(); i++){
        Process* process = finishedProcess[i];
        printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n", i, process->arrivalTime, process->reqCpuTime, process->cpuBurst,
                process->ioBurst, process->priority+1, process->finishTime, process->turnarTime, process->ioTime, process->cpuWaiting);
        totRunTime += process->runTime;
        totIOTime += process->ioTime;
        totTurnarime += process->turnarTime;
        totCpuWaiting += process->cpuWaiting;
    }
    cout<<totIOTime<<endl;
    int finishTime = finishedProcess[finishedProcess.size()-1]->finishTime;
    double cpuUtil = (totRunTime/(double)finishTime)*100;
    double ioUtil = (totIOTime/(double)finishTime)*100;
    double avgTurnAr = totTurnarime / finishedProcess.size();
    double avgCpuWaiting = totCpuWaiting / finishedProcess.size();
    double throughPut = (finishedProcess.size() /(double) finishTime) * 100;
    printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n", finishTime, cpuUtil, ioUtil, avgTurnAr, avgCpuWaiting, throughPut);
}