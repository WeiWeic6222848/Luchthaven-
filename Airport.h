//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPORT_H
#define LUCHTHAVEN_AIRPORT_H

#include <vector>
#include <map>
#include "string"
#include "Runway.h"
using namespace std;

class Airplane;
class Runway;

class Airport {
private:
    string name;
    string iata;
    string callsign;
    map<int,Airplane*> gates;
    int passengers;
    vector<Runway*> runways;
    vector<Airplane*> relatedplanes;
    Airport* _InitCheck;

/**
 * REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when getting output");
 * @param output the outputstream that this function has to edit
 * @param airport reference to output
 * @return an edited outputstream
 */
    friend std::ostream& operator<<(std::ostream& output,Airport& airport);

public:

/**
 * ENSURE(ProperInitialized(),"This airport object failed to Initialize properly");
 * @param name name of an airport
 * @param iata unique iata of an airport
 * @param callsign name of the airport tower
 * @param gates amount of gates of this airport, it will be numbered from one to this amount.
 * @param passengers passengers currently on airport
 */
    Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addrunway");
 * ENSURE(find(runways.begin(),runways.end(),runway)!=runways.end(),"addrunway postcondition failed");
 * @param runway the pointer to a pre-initialized runway which will be added to addrunway
 */
    void addrunway(Runway* runway);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getName");
 * @return the name of this airport
 */
    const string &getName() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getIata");
 * @return the iata of this airport
 */
    const string &getIata() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getCallsign");
 * @return the callsign of this airport
 */
    const string &getCallsign() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getPassenger");
 * @return the passengers of this airport;
 */
    int getPassengers() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGates");
 * @return all the gates information with the current airplane on the gate information
 */
    const map<int, Airplane *> &getGates() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getRunways");
 * @return all the runways information
 */
    const vector<Runway *> &getRunways() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreerunway");
 * @return a runway pointer which doesn't have any airplanes
 */
    Runway* findfreerunway();

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreegates");
 * @return a number of gate which doesn't have any airplanes
 */
    int findfreegates() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling parkAirplane");
 * REQUIRE(gate<gates.size()&&gate>=1,"The giving gate number must be valid");
 * REQUIRE(gates[gate]==NULL,"The giving gate must be empty");
 * ENSURE(gates[gate]==airplane,"parkAirplane postcondition failed");
 * @param gate the number of gate to park
 * @param airplane the airplane to park
 */
    void parkAirplane(unsigned int gate,Airplane* airplane);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling destructor");
 */
    virtual ~Airport();

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling cleanup");
 * ENSURE(runways.empty(),"cleanup postcondition failed");
 */
    void cleanup();

/**
 *
 * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
 */
    bool ProperInitialized() const;

/**
 *
 * REQUIRE(plane->ProperInitialized(),"Airplane plane wasn't initialized when calling getGateFromAirplane");
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGateFromAirplane");
 * @param plane the plane to search
 * @return the gate which this plane is at
 */
    int getGateFromAirplane(Airplane* plane);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling setGates");
 * ENSURE(gates[gate]==&plane,"setGate postcondition failed");
 * has the same functionality as parkAirplaneso it has never been used;
 */
//   void setGates(int gate,Airplane& plane);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling freeGate");
 * ENSURE(gates[gate]==NULL,"freeGate postcondition failed");
 * @param gate gate to free
 */
    void freeGate(int  gate);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addAirplane");
 * REQUIRE(find(relatedplanes.begin(),relatedplanes.end(),plane)==relatedplanes.end(),"The giving plane shouldn't be related to the airport already");
 * ENSURE(find(relatedplanes.begin(),relatedplanes.end(),plane)!=relatedplanes.end(),"addAirplanes postcondition failed");
 * @param plane plane to add
 */
    void addAirplane(Airplane* plane);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getRelatedplanes");
 * @return vector of airplanes related to this airport, needed to simulate
 */
    const vector<Airplane *> &getRelatedplanes() const;
};


#endif //LUCHTHAVEN_AIRPORT_H
