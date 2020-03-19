//
// Created by gupta on 18-03-2020.
//

#include "Helper.h"
#include "Event.h"

#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

void insertSorted(deque<Event*> *eventQueue, Event *event){
    if(eventQueue->size() == 0){
       eventQueue->push_back(event);
    } else {
        for(int i = 0; i < eventQueue->size(); i++){
            if(eventQueue->at(i)->timeStamp >  event->timeStamp){
                eventQueue->insert(eventQueue->begin() + i, event);
                return;
            }
        }
        eventQueue->push_back(event);
    }
}

void readInputFile(string filename, deque<Event*> *eventQueue){
    ifstream input(filename);
    string line;
    vector<string> tokens;
    int i = 0;
    while(getline(input, line)) {
        size_t prev = 0, pos;
        while ((pos = line.find_first_of(" ", prev)) != string::npos) {
            if (pos > prev)
                tokens.push_back(line.substr(prev, pos-prev));
            prev = pos+1;
        }
        if (prev < line.length())
            tokens.push_back(line.substr(prev, string::npos));

        Process *process = new  Process(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
        Event *event = new Event(stoi(tokens[0]), process, i);
        insertSorted(eventQueue, event);
        tokens.clear();
        i++;
    }
}

Event* getEvent(deque<Event*> *eventQueue){
    Event *evt = eventQueue->front();
    return evt;
}

int getNextEventTime(deque<Event*> *eventQueue){
    Event *evt = eventQueue->front();
    return evt->timeStamp;
}

void readRandomFile(string filename, vector<int> *randvals){
    ifstream input(filename);
    string line;
    getline(input, line);
    while(getline(input, line)) {
        randvals->push_back(stoi(line));
    }
}

int myrandom(int burst, vector<int> *randvals, int ofs) {
    return 1 + (randvals->at(ofs) % burst);
}

void printDQueue(deque<Event*> *eventQueue){
    deque <Event*> :: iterator it;
    for (it = eventQueue->begin(); it != eventQueue->end(); ++it)
        cout << "\t" << **it << endl;
    cout << '\n';
}