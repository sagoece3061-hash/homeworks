#include "BilkentTourism.h"

using namespace std;
BilkentTourism::BilkentTourism(){}
BilkentTourism::~BilkentTourism(){}
void BilkentTourism::addBusLine( const int lineId, const string lineName ){
    BusLine busline(lineId, lineName);

    if(buslines.find(busline) != -1){
        cout << "Cannot add line. There is already a bus line with ID " << lineId << ".\n";
        return;
    }
    
    buslines.insert_sorted(busline);
    cout << "Added bus line " << lineId << ".\n";
}
void BilkentTourism::removeBusLine( const int lineId ){
    BusLine busline(lineId, "");

    if(buslines.find(busline) == -1){
        cout << "Cannot remove bus line. There is no bus line with ID " << lineId << ".\n";
        return;
    }

    buslines.remove(busline);
    cout << "Removed bus line " << lineId << ".\n";
}
void BilkentTourism::printBusLines() const{
    if(buslines.size == 0){
        cout << "There are no bus lines to show.\n";
        return;
    }

    cout << "Bus lines in the system:\n";
    buslines.print_list();
}

void BilkentTourism::addStop( const int stopId, const string stopName ){
    Stop stop(stopId, stopName);
    
    if(stops.find(stop) != -1){
        cout << "Cannot add stop. BilkentTourism already contains stop " << stopId << ".\n";
        return;
    }

    cout << "Added stop " << stopId << ".\n";
    stops.insert_sorted(stop);
}
void BilkentTourism::removeStop( const int stopId ){
    Stop stop(stopId, "");
    int index;

    if(stops.find(stop) == -1){
        cout << "Cannot remove stop " << stopId << ". There is no bus stop with ID " << stopId << ".\n";
        return;
    }

    for(int i = 0; i < buslines.size; i++){
        BusLine& busline_ref2 = buslines[i];
        index = busline_ref2.stops.find(stop);
        
        if(index != -1){
            cout << "Cannot remove stop " << stopId << ". The stop is currently in use.\n";
            return;
        }
    }

    stops.remove(stop);
    cout << "Removed stop " << stopId << ".\n";
}
void BilkentTourism::addStopToLine( const int stopId, const int lineId ){
    Stop stop(stopId, "");
    BusLine busline(lineId, "");
    int line_index = buslines.find(busline);
    int stop_index = stops.find(stop);

    if(line_index == -1){
        cout << "Cannot add stop. There is no line with ID " << lineId << ".\n";
        return;
    }
    if(stop_index == -1){
        cout << "Cannot add stop. There is no stop with ID " << lineId << ".\n";
        return;
    }
    busline = buslines[line_index];
    stop = stops[stop_index];

    if(busline.stops.find(stop) == -1){
        cout << "Cannot add stop. Line " << lineId << " already contains stop " << stopId << ".\n";
        return;
    }

    busline.stops.insert_sorted(stop);
    buslines[line_index] = busline;
    cout << "Added stop " << stopId << " to line " << lineId << "(" << busline.name << ").\n";
}
void BilkentTourism::removeStopFromLine( const int stopId, const int lineId ){
    BusLine busline(lineId, "");
    Stop stop(stopId, "");
    int line_index = buslines.find(busline);
    int stop_index;

    if(line_index == -1){
        cout << "Cannot remove stop. There is no line with ID " << lineId << ".\n";
        return;
    }
    busline = buslines[line_index];
    stop_index = busline.stops.find(stop);

    if(stop_index == -1){
        cout << "Cannot remove stop. Line " << lineId << " does not have stop " << stopId << ".\n";
        return;
    }

    busline.stops.remove(stop);
    buslines[line_index] = busline;
    cout << "Removed stop " << stopId << " from line " << lineId << ".\n";
}
void BilkentTourism::printStops( const int lineId ) const{
    BusLine busline(lineId, "");
    int index = buslines.find(busline);

    if(index == -1){
        cout << "Cannot print stops. There is no line with ID " << lineId << ".\n";
        return;
    }
    const BusLine& busline_ref = buslines[index];

    if(busline_ref.stops.size == 0){
        cout << "Cannot print stops. There is no stop to show.\n";
        return;
    }

    cout << "Stops in bus line " << lineId << "(" << busline.name << ") :\n";
    busline_ref.stops.print_list();
}

void BilkentTourism::assignBus( const int busId, const string driverName, const int lineId){
    BusLine busline(lineId, "");
    Bus bus(busId, driverName);
    int line_index = buslines.find(busline);
    int index;

    if(line_index == -1){
        cout << "Cannot assign bus. There is no line with ID " << lineId << ".\n";
        return;
    }
    BusLine& busline_ref1 = buslines[line_index];

    for(int i = 0; i < buslines.size; i++){
        BusLine& busline_ref2 = buslines[i];
        index = busline_ref2.busses.find(bus);
        
        if(index != -1){
            cout << "Cannot assign bus. Bus " << busId << " is already assigned to a line.\n";
            return;
        }
    }
    
    busline_ref1.busses.insert_sorted(bus);
    buses.insert_sorted(bus);
    cout << "Bus " << busId << " with driver " << driverName << " is assigned to line " << lineId << " (" << busline_ref1.name << ")" << ".\n";
}
void BilkentTourism::unassignBus( const int busId ){
    Bus bus(busId, "");
    int bus_index = buses.find(bus);
    int index;

    if(bus_index == -1){
        cout << "Cannot unassign bus. There is no bus with ID " << busId << ".\n";
        return;
    }

    for(int i = 0; i < buslines.size; i++){
        BusLine& busline_ref = buslines[i];
        index = busline_ref.busses.find(bus);
        
        if(index != -1){
            busline_ref.busses.remove(index);
            cout << "Bus " << busId << " is unassigned from line " << busline_ref.id << " (" << busline_ref.name << ").\n";
            return;
        }
    }
}
void BilkentTourism::printBussesInLine( const int lineId ) const{
    BusLine busline(lineId, "");
    int line_index = buslines.find(busline);

    if(line_index == -1){
        cout << "Cannot print busses. There is no line with ID " << lineId << ".\n";
        return;
    }
    const BusLine& busline_ref = buslines[line_index];
    
    if(busline_ref.stops.size == 0){
        cout << "There are no bus to show in line " << lineId << " (" << busline.name << ").\n";
        return;
    }
    
    cout << "Busses and their drivers assigned to the line " << lineId << " (" << busline.name << "):\n";
    busline_ref.busses.print_list();
}
void BilkentTourism::printBussesPassingStop( const int stopId ) const{
    Stop stop_temp(stopId, "");
    int stop_index = stops.find(stop_temp);
    bool flag = false;

    if(stop_index == -1){
        cout << "Cannot print buses. There is no stop with ID " << stopId << ".\n";
        return;
    }

    const Stop& stop_full = stops[stop_index]; 
    
    cout << "Buses and their assigned lines passing the stop " << stopId << " (" << stop_full.name << "):\n";

    for(int i = 0; i < buslines.size; i++){
        const BusLine& busline_ref2 = buslines[i];
        int index = busline_ref2.stops.find(stop_temp);
        
        if(index != -1){
            flag = true;
            cout << "Line " << busline_ref2.id << " (" << busline_ref2.name << ") : ";
            
            if(busline_ref2.busses.size == 0){
                cout <<  "None\n"; 
            } 
            else{
                cout << "[";
                cout << busline_ref2.busses[0].id;
                for(int j = 1; j < busline_ref2.busses.size; j++){
                    cout << ", ";
                    cout << busline_ref2.busses[j].id;
                }
                cout <<"]\n";
 
            }
        }
    }
    
    if(!flag)
        cout << "Cannot print buses. No lines pass through the stop.\n";
}