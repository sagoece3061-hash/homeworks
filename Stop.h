#ifndef _STOP_H
#define _STOP_H
#include <string>
#include <iostream>

using namespace std;
class Stop{
public:
    Stop(int id, string name):id(id), name(name){}
    Stop():id(0), name(""){}

    int id;
    string name;
};

inline bool operator< (const Stop& lhs, const Stop& rhs) { return lhs.id < rhs.id; }
inline bool operator> (const Stop& lhs, const Stop& rhs) { return rhs < lhs; }
inline bool operator<=(const Stop& lhs, const Stop& rhs) { return !(lhs > rhs); }
inline bool operator>=(const Stop& lhs, const Stop& rhs) { return !(lhs < rhs); }
inline bool operator==(const Stop& lhs, const Stop& rhs) { return !(lhs < rhs) && !(lhs > rhs); }

inline std::ostream& operator<<(ostream& ost, const Stop stop) { return ost << "Stop " << stop.id << " : " << stop.id; }
#endif