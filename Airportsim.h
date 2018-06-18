//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_Airportsim_H
#define LUCHTHAVEN_Airportsim_H

#include "vector"
#include "Airport.h"
#include <iostream>
#include <cmath>

class AirportsimImporter;
class Airport;
class Airplane;
class Runway;

using namespace std;

class Airportsim{
    vector<Airport*> Airports;
    vector<Airplane*> Airplanes;
    vector<Airplane*> AirplanesFlying;
    vector<Airplane*> Allplanes;
    Airportsim* _InitCheck;
    Time currentTime;
    friend AirportsimImporter;
public:

    //constructor
    Airportsim();

    /**
    *      ENSURE(ProperInitialized(),"Airportsim object failed to initialize properly");
    * @param argc terminal input
    * @param argv terminal input, multiple name of xmll files to read.
    */
    Airportsim(int argc,char const* argv[]);

    /**
     *     ENSURE(ProperInitialized(),"This airportsim object failed to initialize properly");
     * @param filename xmlfile to read while initializing.
     */
    Airportsim(const string& filename);


    //all getters----------------------------------------------------------------------------------------
    /**
     *
     * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
     */
    bool ProperInitialized()const;

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirports");
     * @return vector of all Airports
     */
    const vector<Airport*> &getAirports() const;

    /**
    *      REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairport");
    * @param iata unique iata of the airport to find
    * @return the found airport or NULL if not found
    */
    Airport* findAirport(const string& iata);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirplanes");
     * @return vector of all Airplanes
     */
    const vector<Airplane*> &getAirplanes() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairplane");
     * @param number unique number of the airplane to find
     * @return the found airplane or NULL if not found
     */
    Airplane* findAirplane(const string& number);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findrunway");
     * @param number unique number of runway
     * @param iata unique iata of the airport that the runway is at;
     * @return the found runway or NULL if either airport or runway is not found
     */

    Runway* findRunway(const string&number,const string& iata);

    /**
    *     REQUIRE(ProperInitialized(), "airportsim wasn't initialized when calling getCurrentTime");
    * @return
    */
    const Time &getCurrentTime() const;


    //all setter/changers--------------------------------------------------------------------------------
    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addAirport");
     *     ENSURE(findAirport(airport->getIata())!=NULL,"addAirport postcondition failed");
     * @param airport
     */
    void addAirport(Airport* airport);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling removeairport");
     *     ENSURE(find(Airports.begin(),Airports.end(),airport)==Airports.end(),"removeairport postcondition failed");
     * @param airport airport to remove from airportslist.
     */
    void removeAirport(Airport* airport);


    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addAirplane");
     *     ENSURE(find(Airplanes.begin(),Airplanes.end(),airplane)!=Airplanes.end()&&find(Allplanes.begin(),Allplanes.end(),airplane)!=Allplanes.end(),"addAirplane postcondition failed");
     * @param airplane
     */
    void addAirplane(Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addsourcefile");
     *     REQUIRE(fileExist(filename),"Giving filename must exist when calling addsourcefile");
     * @param filename xmlfilename to read.
     */
    void addSourcefile(const string &filename);
    //use loadairportsim from airportutils;


    /**
     *     REQUIRE(ProperInitialized(), "airportsim wasn't initialized when calling setCurrentTime");
     *     ENSURE(getCurrentTime()==currentTime,"setCurrenTime postcondition failed");
     * @param currentTime
     */
    void setCurrentTime(const Time &currentTime);

    //all setter/changers--------------------------------------------------------------------------------











    //destroyer
    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling Destructor");
     */
    virtual ~Airportsim();

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling Simulate");
     */
    void Simulate();

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling simulate_Onetime");
     */
    void simulate_Onetime();

private:
    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling landingstep");
     *     REQUIRE(approaching.ProperInitialized(),"Airplane wasn't initialized when calling landingstep");
     *     REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling landingstep");
     *     REQUIRE(approaching.getStatus()==Airplane::Approaching||approaching.getStatus()==Airplane::Landed,"Airplane must has the status of Approaching when calling landingstep");
     *
     * @param approaching
     * @param airport
     */
    void landingstep(Airplane& approaching, Airport& airport);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling airplaneAtGatestep");
     *     REQUIRE(plane.ProperInitialized(),"Airplane wasn't initialized when calling airplaneAtGatestep");
     *     REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling airplaneAtGatestep");
     *     REQUIRE(plane.getStatus()==Airplane::Standing_at_gate,"Airplane must has the status of Standing at gate when calling airplaneAtGate");
     * @param plane
     * @param airport
     */
    void airplaneAtGatestep(Airplane& plane,Airport& airport);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling taxiingToGatestep");
     *     REQUIRE(taxiingplane.ProperInitialized(),"Airplane wasn't initialized when calling taxiingToGatestep");
     *     REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling taxiingToGatestep");
     *     REQUIRE(taxiingplane.getStatus()==Airplane::Taxiing_to_gate,"Airplane must has the status of Taxiing to gate when calling taxiingToGatestep");
     * @param taxiingplane
     * @param airport
     */
    void taxiingToGatestep(Airplane& taxiingplane,Airport& airport);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling taxiingToRunwaystep");
     *     REQUIRE(taxiingplane.ProperInitialized(),"Airplane wasn't initialized when calling taxiingToRunwaystep");
     *     REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling taxiingToRunwaystep");
     *     REQUIRE(taxiingplane.getStatus()==Airplane::Taxiing_to_runway,"Airplane must has the status of Taxiing to runway when calling taxiingToRunwaystep");
     * @param taxiingplane
     * @param airport
     */
    void taxiingToRunwaystep(Airplane& taxiingplane,Airport& airport);

    /**
     *     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling leavingstep");
     *     REQUIRE(leaving.ProperInitialized(),"Airplane wasn't initialized when calling leavingstep");
     *     REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling leavingstep");
     *     REQUIRE(leaving.getStatus()==Airplane::Leaving,"Airplane must has the status of Leaving when calling leavingstep");
     * @param leaving
     * @param airport
     */
    void leavingstep(Airplane& leaving, Airport& airport);

    /**
     *     REQUIRE(vlieghaven.ProperInitialized(), "airport wasn't initialized when calling generateFloorPlan");
     * @param vlieghaven
     */
    void generateFloorPlan(Airport& vlieghaven);

    /**
     *     REQUIRE(airport.ProperInitialized(), "airport wasn't initialized when calling writeIni");
     * @param airport
     */
    void writeIni(Airport& airport);

    /**
     *     REQUIRE(airport.ProperInitialized(), "airport wasn't initialized when calling createVisual");
     * @param airport
     */
    void createVisual(Airport& airport);

};


#endif //LUCHTHAVEN_Airportsim_H
