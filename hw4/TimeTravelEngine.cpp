#include "TimeTravelEngine.h"

TimeTravelEngine::TimeTravelEngine(){
    branches = nullptr;
    branches_size = 0;
}

TimeTravelEngine::~TimeTravelEngine(){
    delete [] branches;
    branches_size = 0;
}

int TimeTravelEngine::createTimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId){
    int index = findBranch(branchId);
    int i = 0;

    if(index != -1){
        cout << "Cannot create time branch. A branch with ID " << branchId << " already exists.\n";
        return -1;
    }

    TimeBranch branch(pastCapacity, futureCapacity, startLocation, branchId);
    TimeBranch* new_branches = new TimeBranch[branches_size + 1];

    while(i < branches_size && branches[i].id < branchId){
        new_branches[i] = branches[i];
        i++;
    } 

    new_branches[i] = branch;

    while(i < branches_size){
        new_branches[i + 1] = branches[i];
        i++;
    }

    delete [] branches;
    branches_size++;
    branches = new_branches;

    cout << "Created time branch with ID " << branchId << ".\n";
    return branchId;
}

void TimeTravelEngine::deleteTimeBranch(const int branchId){
    int index = findBranch(branchId);
    int i = 0;

    if(index == -1){
        cout << "Cannot delete branch. There is no branch with ID " << branchId << ".\n";
        return;
    }

    cout << "Deleted time branch " << branchId << ".\n";

    if(branches_size == 1){
        delete [] branches;
        branches = nullptr;
        branches_size--;
        return;
    }
    TimeBranch* new_branches = new TimeBranch[branches_size - 1];

    while(i < index){
        new_branches[i] = branches[i];
        i++; 
    }
    
    while(i < branches_size - 1){
        new_branches[i] = branches[i + 1];
        i++;
    }

    delete [] branches;
    branches_size--;
    branches = new_branches; 
}

void TimeTravelEngine::printAllBranches() const{
    if(branches_size == 0)
        cout << "There are no time branches to show.\n";

    cout << "Time branches in the system:\n";
    for(int i = 0; i < branches_size; i++){
        cout << "Branch " << (branches + i)->id << ":\n";
        (branches + i)->printTimeBranch();
        cout << "\n";
    }
}

void TimeTravelEngine::travelTo(const int branchId, const string newLocation){
    int branch_index = findBranch(branchId);

    if(branch_index == -1){
        cout << "Cannot travel. There is no branch with ID " << branchId << ".\n";
        return;
    }
    
    TimeBranch* branch = branches + branch_index;

    branch->travelTo(newLocation);
}

void TimeTravelEngine::fastForward(const int branchId, const int k){
    int branch_index = findBranch(branchId);
    TimeBranch* branch = branches + branch_index;

    branch->fastForward(k);
}

void TimeTravelEngine::rewind(const int branchId, const int k){
    int branch_index = findBranch(branchId);
    TimeBranch* branch = branches + branch_index;

    branch->rewind(k);
}

void TimeTravelEngine::placeTimeStone(const int branchId){
    int branch_index = findBranch(branchId);
    TimeBranch* branch = branches + branch_index;

    branch->placeTimeStone();
}

void TimeTravelEngine::activateTimeStone(const int branchId){
    int branch_index = findBranch(branchId);
    TimeBranch* branch = branches + branch_index;

    branch->activateTimeStone();
}

void TimeTravelEngine::printTimeBranch(const int branchId) const{
    int branch_index = findBranch(branchId);
    TimeBranch* branch = branches + branch_index;

    branch->printTimeBranch();
}

int TimeTravelEngine::mergeBranches(const int branchId1, const int branchId2, const int newBranchId){
    int index1 = findBranch(branchId1);
    int index2 = findBranch(branchId2);
    int index3 = findBranch(newBranchId);

    if(index1 == -1 || index2 == -1){
        cout << "Cannot merge branches. Missing branch IDs.\n";
        return 0;
    }
    if(index3 != -1){
        cout << "Cannot merge branches. A branch with ID " << newBranchId << " already exists.\n";
        return 0;
    }
    if((branches + index1)->current_location != (branches + index2)->current_location){
        cout << "Cannot merge branches. Current locations do not match.\n";
        return 0;
    }

    createTimeBranch((branches + index1)->past.capacity + (branches + index2)->past.capacity, (branches + index1)->future.capacity + (branches + index2)->future.capacity, (branches + index1)->current_location, newBranchId);

    index1 = findBranch(branchId1);
    index2 = findBranch(branchId2);
    index3 = findBranch(newBranchId);

    Stack<string> new_future;
    Stack<string> new_past;
    Stack<string> new_time_stones;

    while(!(branches + index1)->future.empty())
        new_future.push((branches + index1)->future.pop());
    while(!new_future.empty())
        (branches + index3)->future.push((new_future.pop()));

    while(!(branches + index2)->future.empty())
        new_future.push((branches + index2)->future.pop());
    while(!new_future.empty())
        (branches + index3)->future.push((new_future.pop()));
    

    while(!(branches + index1)->past.empty())
        new_past.push((branches + index1)->past.pop());
    while(!new_past.empty())
        (branches + index3)->past.push((new_past.pop()));

    while(!(branches + index2)->past.empty())
        new_past.push((branches + index2)->past.pop());
    while(!new_past.empty())
        (branches + index3)->past.push((new_past.pop()));


    while(!(branches + index1)->time_stones.empty())
        new_time_stones.push((branches + index1)->time_stones.pop());
    while(!new_time_stones.empty())
        (branches + index3)->time_stones.push((new_time_stones.pop()));

    while(!(branches + index2)->time_stones.empty())
        new_time_stones.push((branches + index2)->time_stones.pop());
    while(!new_time_stones.empty())
        (branches + index3)->time_stones.push((new_time_stones.pop()));
    
    deleteTimeBranch(branchId1);
    deleteTimeBranch(branchId2);

    cout << "Time branches " << branchId1 << " and " << branchId2 << " merged into new branch " << newBranchId <<".\n";
    return 1;
}

int TimeTravelEngine::findBranch(const int branchId) const{
    int high = branches_size - 1;
    int low = 0;
    int mid;

    while(high >= low){
        mid = (high + low) / 2;

        if(branches[mid].id < branchId) 
            low = mid + 1;

        else if(branches[mid].id > branchId)
            high = mid - 1;

        else 
            return mid;
    }

    return -1;
}