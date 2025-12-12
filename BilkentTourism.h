#ifndef _BILKENTTOURISM_H
#define _BILKENTTOURISM_H
#include "MyList.h"
#include "BusLine.h"

class BilkentTourism {
public:
    BilkentTourism();
    ~BilkentTourism();

    void addBusLine( const int lineId, const string lineName );
    void removeBusLine( const int lineId );
    void printBusLines() const;

    void addStop( const int stopId, const string stopName );
    void removeStop( const int stopId );
    void addStopToLine( const int stopId, const int lineId );
    void removeStopFromLine( const int stopId, const int lineId );
    void printStops( const int lineId ) const;

    void assignBus( const int busId, const string driverName, const int lineId);
    void unassignBus( const int busId );
    void printBussesInLine( const int lineId ) const;
    void printBussesPassingStop( const int stopId ) const;

    MyList<BusLine> buslines;
    MyList<Stop> stops;
    MyList<Bus> buses;

 };
 #endif