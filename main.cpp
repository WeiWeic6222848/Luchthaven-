#include "fstream"
#include "Airportsim.h"
#include "output_system.h"
#include "AirportUtils.h"

using namespace std;
int main(int argc, char const* argv[])
{
    Airportsim* airport=new Airportsim();
    ofstream cerrr;
    cerrr.open("tester.txt");
    LoadAirport(argc,argv,cerrr,*airport);
    Airplane* a=airport->getAirplanes()[0];
    Airport* b=airport->getAirports()[0];
    airport->landing(*a,*b);
    airport->airplaneAtGate(*a,*b);
    airport->takingOff(*a,*b);
    output_system op;
    op.writeToFile(*airport);

    return 0;
}