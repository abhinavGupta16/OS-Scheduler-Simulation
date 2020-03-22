//
// Created by gupta on 18-03-2020.
//

#ifndef ASSIGNMENT2_HELPER_H
#define ASSIGNMENT2_HELPER_H

#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>
#include "Schedulers/Scheduler.h"

using namespace std;

void insertSorted(deque<Event*> *eventQueue, Event *event, bool printEvent);
void readInputFile(string fileName, deque<Event*> *eventQueue, int &ofs, vector<int> &randvals, Scheduler *scheduler);
Event* getEvent(deque<Event*> *eventQueue);
void readRandomFile(string filename, vector<int> *randvals);
int getNextEventTime(deque<Event*> *eventQueue);
void printDQueue(deque<Event*> *eventQueue);
Event* createEvent(int timestamp, Process* process, process_state_t oldState, process_state_t newState, process_state_t transition);
int getCpuBurst(int burst, int &ofs, vector<int> &randvals);
void printResults(vector<Process*> &finishedProcess, Scheduler *scheduler, int ioTime);
void showEventQ(deque<Event*> *eventQueue);
deque <Event*> :: iterator findEvent(deque<Event*> *eventQueue, Process *process);
void printQForRemoveEvent(deque<Event*> *eventQueue);

#endif //ASSIGNMENT2_HELPER_H