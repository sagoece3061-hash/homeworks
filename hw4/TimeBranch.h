#ifndef _TIMEBRANCH_H
#define _TIMEBRANCH_H
#include <iostream>
#include "Stack.h"

using namespace std;

class TimeBranch{
public:
    string current_location;
    Stack<string> time_stones;
    Stack<string> past;
    Stack<string> future;
    int id;

    TimeBranch(): past(), future(), time_stones(), current_location(""), id(0){}

    TimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId): past(), future(), time_stones(){
        past.capacity = pastCapacity;
        future.capacity = futureCapacity;
        current_location = startLocation;
        id = branchId;
    }

    void travelTo(const string newLocation);
    void fastForward(const int k);
    void rewind(const int k);
    void placeTimeStone();
    void activateTimeStone();
    void printTimeBranch() const;
};

#endif