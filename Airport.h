//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPORT_H
#define LUCHTHAVEN_AIRPORT_H

#include <vector>
#include "string"
#include "Time.h"
#include <iostream>
#include <limits>
#include "algorithm"
#include "Signaltower.h"


using namespace std;

class Airplane;
class Runway;
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
    Signaltower* tower;
    friend std::ostream& operator<<(std::ostream& output,Airport& airport);
    friend class AirportDomeinTest;
    //test purpose
    void setName(const string &name);

    void setIata(const string &iata);

    void setCallsign(const string &callsign);

    void setGates(const vector<Gate *> &gates);

    void setPassengers(int passengers);

    void setRunways(const vector<Runway *> &runways);

    void setTaxipoints(const vector<Taxipoint *> &taxipoints);

    void setTower(Signaltower *tower);
    //test purpose
    
    friend Signaltower;

public:

    //constructor
    /**
     *     ENSURE(ProperInitialized(),"This airport object failed to Initialize properly");
     * @param name name of an airport
     * @param iata unique iata of an airport
     * @param callsign name of the airport tower
     * @param gates amount of gates of this airport, it will be numbered from one to this amount.
     * @param passengers passengers currently on airport
     */
    Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers);



//all getters-----------------------------------------------------------------------------------------


    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getName");
     * @return the name of this airport
     */
    const string &getName() const;


    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getIata");
     * @return the iata of this airport
     */
    const string &getIata() const;


    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getCallsign");
     * @return the callsign of this airport
     */
    const string &getCallsign() const;


    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGates");
     * @return all the gates information with the current airplane on the gate information
     */
    const vector<Gate *> &getGates() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getPassenger");
     * @return the passengers of this airport;
     */
    int getPassengers() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getRunways");
     * @return all the runways information
     */
    const vector<Runway *> &getRunways() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getTaxipoints");
     * @return
     */
    const vector<Taxipoint*> &getTaxipoints() const;

    /**
     * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
     */
    bool ProperInitialized() const;


    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getTower");
     * @return
     */
    Signaltower &getTower() ;

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreegates");
     * @return a number of gate which doesn't have any airplanes
     */
    Gate* findFreeGates() const;


    /**
     *     REQUIRE(plane->ProperInitialized(),"Airplane plane wasn't initialized when calling getGateFromAirplane");
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGateFromAirplane");
     * @param plane the plane to search
     * @return the gate which this plane is at
     */
    Gate* getGateFromAirplane(Airplane* plane);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findRunway");
     * @param name
     * @return
     */
    Runway* findRunway (const string& name);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findFreeRunway");
     *     REQUIRE(airplane->ProperInitialized(),"Airplane wasn't initialized when calling findFreeRunway");
     *     REQUIRE(isRightAirplaneCombination(airplane),"Airplane is not correct");
     * @param airplane
     * @param emergency
     * @return
     */
    Runway* findFreeRunway (Airplane* airplane,bool emergency=false);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findTaxipoint");
     * @param name
     * @return
     */
    Taxipoint* findTaxipoint (const string& name);
//all getters----------------------------------------------------------------------------------------------------



//all setters/changers-------------------------------------------------------------------------------------------


    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addPassenger");
     * @param a
     */
    void addPassenger(int a);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling removePassenger");
     * @param a
     */
    void removePassenger(int a);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling freeGate");
     *     ENSURE(gate->getCurrentPlane()==NULL&&!gate->isOnuse(),"freeGate postcondition failed");
     * @param gate
     */
    void freeGate(Gate*  gate);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addrunway");
     *     REQUIRE(findRunway(runway->getName())==NULL,"there is already a runway with the same name!!");
     *     ENSURE(findRunway(runway->getName())!=NULL,"addrunway postcondition failed");
     * @param runway the pointer to a pre-initialized runway which will be added to addrunway
     */
    void addRunway(Runway* runway);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling parkAirplane");
     *     REQUIRE((unsigned int)stoi(gate->getName())<=gates.size(),"The giving gate number must be valid");
     *     REQUIRE(gate->getCurrentPlane()==NULL,"The giving gate must be empty");
     *     ENSURE(gate->getCurrentPlane()==airplane,"parkAirplane postcondition failed");
     * @param gate the number of gate to park
     * @param airplane the airplane to park
     */
    void parkAirplane(Gate* gate,Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addTaxipoint");
     *     REQUIRE(findTaxipoint(taxipoint->getName())==NULL,"The giving Taxipoint shouldn't be added already");
     *     ENSURE(findTaxipoint(taxipoint->getName())!=NULL,"addTaxipoints postcondition failed");
     * @param taxipoint
     */
    void addTaxipoints(Taxipoint* taxipoint);




//destroyer
    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling destructor");
     */
    virtual ~Airport();

    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling cleanup");
     *     ENSURE(getRunways().empty(),"cleanup postcondition failed");
     */
    void cleanup();


//transmitter
    /**
     *     REQUIRE(ProperInitialized(),"Airport wasn't initialized when transmitting signal");
     * @param airplane
     * @param signal
     * @return
     */
    bool receiveSignal(Airplane* airplane,Signaltower::SignaltowerallowedSignal signal);


};


#endif //LUCHTHAVEN_AIRPORT_H
