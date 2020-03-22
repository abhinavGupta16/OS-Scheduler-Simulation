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

enum process_state_t {
    STATE_CREATED,
    STATE_READY,
    STATE_RUNNING,
    STATE_BLOCKED,
    TRANS_TO_READY,
    TRANS_TO_RUN,
    TRANS_TO_BLOCK,
    TRANS_TO_PREEMPT,
    TRANS_TO_DONE
};

class Event {
public:
    Event(int timeStamp, Process *process, process_state_t oldState, process_state_t newState, process_state_t transition);
    Event();
    string enumStateToString(process_state_t state);
    int timeStamp;
    Process *process;
    process_state_t oldState;
    process_state_t curState;
    process_state_t transition;
};

ostream& operator<<(ostream &strm, Event &event);

#endif //ASSIGNMENT2_EVENT_H
