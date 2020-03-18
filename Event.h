//
// Created by gupta on 17-03-2020.
//

#ifndef ASSIGNMENT2_EVENT_H
#define ASSIGNMENT2_EVENT_H

#include "Process.h"
#include "Helper.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

class Event {
public:
    Event(int timeStamp, Process* process, bool verbose, int val);
    int timeStamp;
    Process* process;
    int val;
    process_state_t oldState;
    process_state_t newState;
    boolean verbose;
};


#endif //ASSIGNMENT2_EVENT_H
