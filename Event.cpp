//
// Created by gupta on 17-03-2020.
//

#include "Event.h"
#include "Helper.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

Event::Event(){};

Event::Event(int timeStamp, Process *process, process_state_t oldState, process_state_t newState, process_state_t transition){
    this->timeStamp = timeStamp;
    this->process = process;
    this->oldState = oldState;
    this->curState = newState;
    this->transition = transition;
}

string Event::enumStateToString(process_state_t state) {
    switch(state) {
        case STATE_CREATED:
            return "CREATED";
        case STATE_READY:
            return "READY";
        case STATE_RUNNING:
            return "RUNNG";
        case STATE_BLOCKED:
            return "BLOCK";
        case TRANS_TO_RUN:
            return "RUNNG";
        case TRANS_TO_BLOCK:
            return "BLOCK";
        case TRANS_TO_PREEMPT:
            return "PREEMPT";
        case TRANS_TO_READY:
            return "READY";
        default:
            return "Invalid animal";
    }
}

ostream& operator<<(ostream &strm, Event &event) {
    return strm << event.timeStamp << ":" << event.process->pid << ":" << event.enumStateToString(event.transition);
}