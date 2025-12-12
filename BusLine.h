#ifndef _BUSLINE_H
#define _BUSLINE_H
#include "Bus.h"
#include "Stop.h"
#include "MyList.h"
#include <string>
#include <iostream>

using namespace std;
class BusLine{
public:

    BusLine(int id, string name):id(id), name(name){}
    BusLine():id(0), name(""){}

    int id;
    string name;
    MyList<Bus> busses;
    MyList<Stop> stops;
};

inline bool operator< (const BusLine& lhs, const BusLine& rhs) { return lhs.id < rhs.id; }
inline bool operator> (const BusLine& lhs, const BusLine& rhs) { return rhs < lhs; }
inline bool operator<=(const BusLine& lhs, const BusLine& rhs) { return !(lhs > rhs); }
inline bool operator>=(const BusLine& lhs, const BusLine& rhs) { return !(lhs < rhs); }
inline bool operator==(const BusLine& lhs, const BusLine& rhs) { return !(lhs < rhs) && !(lhs > rhs); }

inline std::ostream& operator<<(ostream& ost, const BusLine busline) { return ost << "Line " << busline.id << " : " << busline.name; }

#endif