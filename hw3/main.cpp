#include "MyList.h"
#include <string>
#include "BilkentTourism.h"

using namespace std;

int main() {
    BilkentTourism bilkentTourism;
    bilkentTourism.printBusLines(); // No bus to show
    cout<<endl;
    bilkentTourism.addBusLine(25, "T10");
    bilkentTourism.addBusLine(22, "G14");
    bilkentTourism.addBusLine(25, "C16"); // Cannot add. Already added
    bilkentTourism.addBusLine(28, "C16");
    bilkentTourism.addBusLine(26, "T43");
    cout<<endl;
    bilkentTourism.removeBusLine(15); // //Cannot remove. No Line.
    bilkentTourism.removeBusLine(26);
    cout<<endl;
    bilkentTourism.printBusLines();
    cout<<endl;
}