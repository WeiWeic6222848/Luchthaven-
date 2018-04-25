//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPORT_H
#define LUCHTHAVEN_AIRPORT_H

#include <vector>
#include <map>
#include "string"
#include "Runway.h"
#include "Signaltower.h"
#include "Taxipoint.h"
#include "Gate.h"

using namespace std;

class Airplane;
class Runway;
class Signaltower;
class Taxipoint;
class Gate;





class Airport {
private:
    string name;
    string iata;
    string callsign;
    vector<Gate*> gates;
    int passengers;
    vector<Runway*> runways;
    vector<Taxipoint*> taxipoints;
    Airport* _InitCheck;
    vector<Airplane*> catched_airplane;
    Signaltower* tower;
public:
    Signaltower &getTower() ;

    friend std::ostream& operator<<(std::ostream& output,Airport& airport);

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
    void addRunway(Runway* runway);

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
    //const map<int, Airplane *> &getGates() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getRunways");
 * @return all the runways information
 */
    const vector<Runway *> &getRunways() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreerunway");
 * @return a runway pointer which doesn't have any airplanes
 */
    Runway* findFreeRunway();

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreegates");
 * @return a number of gate which doesn't have any airplanes
 */
    Gate* findFreeGates() const;

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling parkAirplane");
 * REQUIRE(gate<gates.size()&&gate>=1,"The giving gate number must be valid");
 * REQUIRE(gates[gate]==NULL,"The giving gate must be empty");
 * ENSURE(gates[gate]==airplane,"parkAirplane postcondition failed");
 * @param gate the number of gate to park
 * @param airplane the airplane to park
 */
    void parkAirplane(Gate* gate,Airplane* airplane);

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
    Gate* getGateFromAirplane(Airplane* plane);

/**
 * REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling freeGate");
 * ENSURE(gates[gate]==NULL,"freeGate postcondition failed");
 * @param gate gate to free
 */
    void freeGate(Gate*  gate);

    Runway* findRunway (const string& name);

    Taxipoint* findTaxipoint (const string& name);

    Runway* findFreeRunway (Airplane* airplane);

    void addTaxipoints(Taxipoint* taxipoint);

    const vector<Taxipoint*> &getTaxipoints() const;

    bool receiveSignal(Airplane* airplane,string signal);

    void addPassenger(int a);

    void removePassenger(int a);

    const vector<Gate *> &getGates() const;
};


#endif //LUCHTHAVEN_AIRPORT_H
