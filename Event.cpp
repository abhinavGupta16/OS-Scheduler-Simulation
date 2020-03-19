//
// Created by gupta on 17-03-2020.
//

#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

Event::Event(int timeStamp, Process* process, int val){
    this->timeStamp = timeStamp;
    this->process = process;
    this->val = val;
    this->oldState = STATE_CREATED;
    this->newState = STATE_CREATED;
    this->transition = TRANS_TO_READY;
}

ostream& operator<<(ostream &strm, const Event &event) {
    return strm << "Event(" << event.timeStamp << "," << *event.process << "," << event.val << "," << event.oldState << "," << event.newState << ")";
}