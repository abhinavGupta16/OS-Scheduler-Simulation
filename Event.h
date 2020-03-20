//
// Created by gupta on 17-03-2020.
//

#ifndef ASSIGNMENT2_EVENT_H
#define ASSIGNMENT2_EVENT_H

#include "Process.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

class Event {
public:
    Event(int timeStamp, Process *process, int val, process_state_t oldState, process_state_t newState, process_state_t transition);
    Event();
    int timeStamp;
    Process *process;
    int val;
    process_state_t oldState;
    process_state_t curState;
    process_state_t transition;
};

ostream& operator<<(ostream &strm, const Event &event);

#endif //ASSIGNMENT2_EVENT_H
