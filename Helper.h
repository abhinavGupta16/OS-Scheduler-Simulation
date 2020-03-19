//
// Created by gupta on 18-03-2020.
//

#ifndef ASSIGNMENT2_HELPER_H
#define ASSIGNMENT2_HELPER_H

#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

void insertSorted(deque<Event*> *eventQueue, Event *event);
void readInputFile(string fileName, deque<Event*> *eventQueue);
Event* getEvent(deque<Event*> *eventQueue);
void readRandomFile(string filename, vector<int> *randvals);
int getNextEventTime(deque<Event*> *eventQueue);
void printDQueue(deque<Event*> *eventQueue);

#endif //ASSIGNMENT2_HELPER_H