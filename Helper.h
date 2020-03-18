//
// Created by gupta on 17-03-2020.
//

#ifndef ASSIGNMENT2_HELPER_H
#define ASSIGNMENT2_HELPER_H

#endif //ASSIGNMENT2_HELPER_H

#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

enum process_state_t {
    STATE_CREATED,
    STATE_READY,
    STATE_RUNNING,
    STATE_BLOCKED
};

void readFile(string fileName, deque<Event*>* eventQueue, int i, bool verbose);