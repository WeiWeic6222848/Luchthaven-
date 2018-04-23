//
// Created by c6222848 on 4/3/18.
//

#ifndef LUCHTHAVEN_AIRPORTSIMIMPORTER_H
#define LUCHTHAVEN_AIRPORTSIMIMPORTER_H

#include <ostream>
#include "Airportsim.h"
#include "tinyxml.h"

enum Esucces{ImportAborted,PartialImport,Success};
class Airportsim;

class AirportsimImporter {
public:

    static Esucces importAirportsim(const char * inputfilename, std::ostream& errStream, Airportsim& sim);
    static Esucces readAirport(TiXmlElement* airportelement,std::ostream& errStream,Airportsim& sim,Airport*& airport);
    static Esucces readRunway(TiXmlElement* runwayelement,std::ostream& errStream,Airportsim& sim,Airport*& airport);
    static Esucces readAirplane(TiXmlElement* airplaneelement,std::ostream& errStream,Airportsim& sim,Airport*& airport);
    static Esucces readTaxiroute(TiXmlElement* routeelement,std::ostream& errStream, Runway& runway, Airport*&airport);

};


#endif //LUCHTHAVEN_AIRPORTSIMIMPORTER_H
