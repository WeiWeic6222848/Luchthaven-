//
// Created by c6222848 on 4/3/18.
//

#ifndef LUCHTHAVEN_AIRPORTSIMIMPORTER_H
#define LUCHTHAVEN_AIRPORTSIMIMPORTER_H

#include <ostream>
#include "tinyxml.h"


enum Esucces{ImportAborted,PartialImport,Success};

class Airportsim;
class Airport;

//why a standalone class needed? its just bunches of codes.
class AirportsimImporter {
public:
    /**
     * REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling importAirportsim");
     * REQUIRE(fileExist(inputfilename),"Giving filename must exist when calling importAirportsim");
     * @param inputfilename
     * @param errStream
     * @param sim
     * @return
     */
    static Esucces importAirportsim(const char * inputfilename, std::ostream& errStream, Airportsim& sim);

    /**
     * REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling readAirport");
     * @param airportelement
     * @param errStream
     * @param sim
     * @param airport
     * @return
     */
    static Esucces readAirport(TiXmlElement* airportelement,std::ostream& errStream,Airportsim& sim,Airport*& airport);

    /**
     * REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling readRunway");
     * REQUIRE(airport->ProperInitialized(),"Airport object wasn't initialized when calling readRunway");
     * @param runwayelement
     * @param errStream
     * @param sim
     * @param airport
     * @return
     */
    static Esucces readRunway(TiXmlElement* runwayelement,std::ostream& errStream,Airportsim& sim,Airport*& airport);

    /**
     * REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling readAirplane");
     * REQUIRE(airport->ProperInitialized(),"Airport object wasn't initialized when calling readAirplane");
     * @param airplaneelement
     * @param errStream
     * @param sim
     * @param airport
     * @return
     */
    static Esucces readAirplane(TiXmlElement* airplaneelement,std::ostream& errStream,Airportsim& sim,Airport*& airport);

};


#endif //LUCHTHAVEN_AIRPORTSIMIMPORTER_H
