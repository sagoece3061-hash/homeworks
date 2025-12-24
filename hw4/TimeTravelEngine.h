#ifndef _TIMETRAVELENGINE_H
#define _TIMETRAVELENGINE_H
#include <string>
#include "TimeBranch.h"

using namespace std;
class TimeTravelEngine
{
    TimeBranch* branches;
    int branches_size;
public:
    TimeTravelEngine();
    ~TimeTravelEngine();

    int createTimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId);
        
    void deleteTimeBranch(const int branchId);
    void printAllBranches() const;
        
    void travelTo(const int branchId, const string newLocation);
        
    void fastForward(const int branchId, const int k);
    void rewind(const int branchId, const int k);
        
    void placeTimeStone(const int branchId);
    void activateTimeStone(const int branchId);
        
    void printTimeBranch(const int branchId) const;
        
    int mergeBranches(const int branchId1, const int branchId2, const int newBranchId);
    int findBranch(const int branchId) const;
 };
#endif