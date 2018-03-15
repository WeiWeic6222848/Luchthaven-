#include <iostream>
#include "Airportsim.h"
int main(int argc, char const* argv[])
{
    Airportsim airport=Airportsim();
    for (int i = 1; i < argc; ++i) {
        airport.addsourcefile(argv[i]);
    };
}