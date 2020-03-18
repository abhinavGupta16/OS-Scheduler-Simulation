//
// Created by gupta on 17-03-2020.
//

#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

void readFile(string fileName, deque<Event*>* eventQueue, int i, bool verbose){
    stringstream input(fileName);
    string line;
    vector<string> tokens;

    while(getline(input, line)) {
        size_t prev = 0, pos;
        while ((pos = line.find_first_of(" ", prev)) != string::npos) {
            if (pos > prev)
                tokens.push_back(line.substr(prev, pos-prev));
            prev = pos+1;
        }
        if (prev < line.length())
            tokens.push_back(line.substr(prev, string::npos));
    }

    Process process(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
    Event event(stoi(tokens[0]), &process, i, verbose);
    eventQueue->push_back(&event);
}

void printDQueue(deque<Event*> eventQueue){
    deque <Event*> :: iterator it;
    for (it = eventQueue.begin(); it != eventQueue.end(); ++it)
        cout << "\t";
    cout << '\n';
}