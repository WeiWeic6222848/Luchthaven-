//
// Created by c6222848 on 4/3/18.
//

#ifndef LUCHTHAVEN_AIRPORTSIMIMPORTER_H
#define LUCHTHAVEN_AIRPORTSIMIMPORTER_H

#include <ostream>
#include "Airportsim.h"

enum Esucces{ImportAborted,PartialImport,Success};

class AirportsimImporter {
public:

    static Esucces importAirportsim(const char * inputfilename, std::ostream& errStream, Airportsim& game);

};


#endif //LUCHTHAVEN_AIRPORTSIMIMPORTER_H
