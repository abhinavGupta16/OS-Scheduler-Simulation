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

Event::Event(int timeStamp, Process *process, int val, process_state_t oldState, process_state_t newState, process_state_t transition){
    this->timeStamp = timeStamp;
    this->process = process;
    this->val = val;
    this->oldState = oldState;
    this->curState = newState;
    this->transition = transition;
}

ostream& operator<<(ostream &strm, const Event &event) {
    return strm << event.timeStamp << ":" << event.process->pid << ":" << enumStateToString(event.transition);
}