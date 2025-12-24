#include "TimeBranch.h"

void TimeBranch::travelTo(const string newLocation){
    if(past.capacity == past.size){
        cout << "Cannot travel to " << newLocation << " in branch " << id << ". Past stack capacity exceeded.\n";
        return;
    }

    past.push(current_location);
    current_location = newLocation;
    while(future.size > 0) future.pop();

    cout << "Traveled to " << newLocation << " in branch " << id << ".\n";
}

void TimeBranch::fastForward(const int k){
    int steps = 0;

    if(k > past.capacity - past.size){
        cout << "Cannot fast forward " << k << " steps in branch " << id << ". Past stack capacity exceeded.\n";
        return;
    }

    for(int i = 0; i < k && future.size > 0; i++){
        past.push(current_location);
        current_location = future.pop();
        steps++;
    }

    cout << "Fast forwarded " << steps << " steps in branch " << id << ".\n";
}

void TimeBranch::rewind(const int k){
    int steps = 0;

    if(k > future.capacity - future.size){
        cout << "Cannot rewind " << k << " steps in branch " << id << ". Future stack capacity exceeded.\n";
        return;
    }

    for(int i = 0; i < k && past.size > 0; i++){
        future.push(current_location);
        current_location = past.pop();
        steps++;
    }

    cout << "Rewound " << steps << " steps in branch " << id << ".\n";
}

void TimeBranch::placeTimeStone(){
    time_stones.push(current_location);
    cout << "Time stone placed at " << current_location << ".\n";
}

void TimeBranch::activateTimeStone(){
    if(time_stones.empty()){
        cout << "Cannot activate time stone. No time stones available.\n";
        return;
    }
    
    string l = time_stones.pop();

    if(current_location == l){
        while(!future.empty())
            future.pop();
        cout << "Time stone activated. The traveler is now at " << l << ".\n";
        return;
    }

    int past_index = stackSearch(past, l);
    int future_index = stackSearch(future, l);

    if((future_index == -1 && past_index != -1) || (past_index <= future_index)){
        for(int i = 0; i < past_index; i++) past.pop();

        current_location = past.pop();

        while(!future.empty()) future.pop();
    }

    else if((future_index != -1 && past_index == -1) || (past_index > future_index)){
        if(past.capacity - past.size <= future_index + 1){
            cout << "Time stone discarded. Past stack capacity exceeded.\n";
            return;
        }
        past.push(current_location);

        for(int i = 0; i < future_index; i++){
            past.push(future.pop());
        }
        current_location = future.pop();

        while(!future.empty()) future.pop();
    }

    else{
        cout << "Time stone discarded. The recorded moment is no longer reachable.\n";
        return;
    }

    cout << "Time stone activated. The traveler is now at " << l << ".\n";
}

void TimeBranch::printTimeBranch() const{
    cout << "Past : " << past;
    cout << "Current: ( " << current_location << " )\n";
    cout << "Future : " << future;
    cout << "Stones : " << time_stones;
}

