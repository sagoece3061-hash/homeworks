#ifndef _BUS
#define _BUS
#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>

using namespace std;

class Bus{
public:
    Bus(int id, string driver): id(id), driver(driver){}
    Bus(): id(0), driver(""){}
    int id;
    string driver;
};

inline bool operator< (const Bus& lhs, const Bus& rhs) { return lhs.id < rhs.id; }
inline bool operator> (const Bus& lhs, const Bus& rhs) { return rhs < lhs; }
inline bool operator<=(const Bus& lhs, const Bus& rhs) { return !(lhs > rhs); }
inline bool operator>=(const Bus& lhs, const Bus& rhs) { return !(lhs < rhs); }
inline bool operator==(const Bus& lhs, const Bus& rhs) { return !(lhs < rhs) && !(lhs > rhs); }

inline std::ostream& operator<<(ostream& ost, const Bus busline) { return ost << "Bus"; }


#endif