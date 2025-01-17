//
// Created by gupta on 19-03-2020.
//

#ifndef ASSIGNMENT2_SCHEDULER_H
#define ASSIGNMENT2_SCHEDULER_H


class Scheduler {
public:
    virtual string getName(){
        return "BASE_CLASS";
    };
    virtual void addProcess(Process *process){

    };
    virtual Process* getNextProcess(){
        return nullptr;
    };
    virtual int getQuantum(){
        return -1;
    };
    virtual int getMaxPriority(){
        return 4;
    };
    virtual void printRunQueue(){

    };
    virtual bool isPriority(){
        return false;
    };
    virtual bool isPreemptivePriority(){
        return false;
    };
};


#endif //ASSIGNMENT2_SCHEDULER_H
