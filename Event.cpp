//
// Created by gupta on 17-03-2020.
//

#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

Event::Event(int timeStamp, Process* process, bool verbose, int val){
    this->timeStamp = timeStamp;
    this->process = process;
    this->verbose = verbose;
    this->val = val;
    this->oldState = STATE_CREATED;
    this->newState = STATE_CREATED;
}