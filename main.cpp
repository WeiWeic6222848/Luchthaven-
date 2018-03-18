#include <iostream>
#include "Airportsim.h"
#include "output_system.h"
int main(int argc, char const* argv[])
{
    Airportsim airport(argc,argv);
    Airplane* a=airport.getAirplanes()[0];
    Airport* b=airport.getAirports()[0];
    airport.landing(*a,*b);
    airport.AirplaneAtGate(*a,*b);
    airport.takingOff(*a,*b);
    output_system op;
    op.writeToFile(airport);

    return 0;
}