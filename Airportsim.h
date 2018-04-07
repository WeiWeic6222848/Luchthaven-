//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_Airportsim_H
#define LUCHTHAVEN_Airportsim_H

#include "vector"
#include "Airport.h"

class AirportsimImporter;

using namespace std;

class Airportsim{
    vector<Airport*> Airports;
    vector<Airplane*> Airplanes;
    vector<Airplane*> AirplanesFlying;
    vector<Airplane*> Allplanes;
    Airportsim* _InitCheck;

public:

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling removeairport");
 * ENSURE(find(Airports.begin(),Airports.end(),airport)==Airports.end(),"removeairport postcondition failed");
 * @param airport airport to remove from airportslist
 */
    void removeAirport(Airport* airport);

/**
 * ENSURE(ProperInitialized(),"Airportsim object failed to initialize properly");
 * @param argc terminal input
 * @param argv terminal input, multiple name of xmll files to read
 */
    Airportsim(int argc,char const* argv[]);

/**
 * ENSURE(ProperInitialized(),"This airportsim object failed to initialize properly");
 * @param filename xmlfile to read while initializing
 */
    Airportsim(const string& filename);

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addsourcefile");
 * REQUIRE(fileExist(filename),"Giving filename must exist when calling addsourcefile");
 * @param filename xmlfilename to read
 */
    void addSourcefile(const string &filename);

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairport");
 * @param iata unique iata of the airport to find
 * @return the found airport or NULL if not found
 */
    Airport* findAirport(const string& iata);

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairplane");
 * @param number unique number of the airplane to find
 * @return the found airplane or NULL if not found
 */
    Airplane* findAirplane(const string& number);

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findrunway");
 * @param number unique number of runway
 * @param iata unique iata of the airport that the runway is at;
 * @return the found runway or NULL if either airport or runway is not found
 */

    Runway* findRunway(const string&number,const string& iata);

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirports");
 * @return vector of all Airports
 */
    const vector<Airport*> &getAirports() const;

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirplanes");
 * @return vector of all Airplanes
 */
    const vector<Airplane*> &getAirplanes() const;

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling landing");
 * REQUIRE(aproaching.getStatus()=="Approaching","Airplane must has the status of Approaching when calling landing");
 * ENSURE(fileExist(filename),"landing postcondition failed");
 * @param aproaching the landing airplane
 * @param airport the airport to land
 */
    void landing(Airplane& approaching, Airport& airport);

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling takingOff");
 * REQUIRE(aproaching.getStatus()=="Standing at gate","Airplane must has the status of Standing at gate when calling taking off");
 * ENSURE(fileExist(filename),"takingOff postcondition failed");
 * @param aproaching the leaving airplane
 * @param airport the airport to leave
 */
    void takingOff(Airplane& leaving, Airport& airport);

/**
 *
 * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
 */
    bool ProperInitialized()const;

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling AirplaneAtGate");
 * ENSURE(fileExist(filename),"AirplaneAtGate postcondition failed");
 * @param plane plane to get prepared
 * @param airport where is this airplane standing.
 */
    void airplaneAtGate(Airplane& plane,Airport& airport);

/**
 * REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling Destructor");
 */
    virtual ~Airportsim();

    void addAirport(Airport* airport);

    void addAirplane(Airplane* airplane);

    Airportsim();
    //future functions
    void Simulate();

    void landingstep(Airplane& approaching, Airport& airport);

    void airplaneAtGatestep(Airplane& plane,Airport& airport);

    void taxiingToGatestep(Airplane& taxiingplane,Airport& airport);

    void taxiingToRunwaystep(Airplane& taxiingplane,Airport& airport);

    void leavingstep(Airplane& leaving, Airport& airport);

};


#endif //LUCHTHAVEN_Airportsim_H
