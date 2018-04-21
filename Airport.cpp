//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include <limits>
#include "Airport.h"
#include "DesignByContract.h"
#include "algorithm"
#include "AirportUtils.h"

Airport::Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers) : name(name), iata(iata), callsign(callsign),  passengers(passengers)
{
    _InitCheck=this;
    for (int i = 1; i < gates+1; ++i) {
        Airport::gates.push_back(new Gate(to_string(i))) ;
    }
    tower= new Signaltower(this);
    ENSURE(ProperInitialized(),"This airport object failed to Initialize properly");
}

void Airport::addRunway(Runway* runway) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addrunway");
    REQUIRE(findRunway(runway->getName())==NULL,"there is already a runway with the same name!!");
    runways.push_back(runway);
    ENSURE(findRunway(runway->getName())!=NULL,"addrunway postcondition failed");
}

const string &Airport::getName() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getName");
    return name;
}

const string &Airport::getIata() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getIata");
    return iata;
}

const string &Airport::getCallsign() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getCallsign");
    return callsign;
}

int Airport::getPassengers() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getPassenger");
    return passengers;
}

const vector<Runway *> &Airport::getRunways() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getRunways");
    return runways;
}


Runway *Airport::findFreeRunway(){

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreerunway");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getCurrentairplane()==NULL){
            return runways[i];
        }
    }
    cout<<"all runways buzy"<<endl;
    return NULL;
}

Gate* Airport::findFreeGates() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreegates");
    for (unsigned int i = 0; i < gates.size(); ++i) {
        if(!(gates[i]->isOnuse())){
            return gates[i];
        }
    }
    cerr<<"all gates buzy"<<endl;
    return NULL;
}

void Airport::parkAirplane(Gate* gate, Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling parkAirplane");
    REQUIRE((unsigned int)stoi(gate->getName())<=gates.size(),"The giving gate number must be valid");
    REQUIRE(gate->getCurrentPlane()==NULL,"The giving gate must be empty");
    gate->setCurrentPlane(airplane);
    ENSURE(gate->getCurrentPlane(),"parkAirplane postcondition failed");
}

Airport::~Airport() {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling destructor");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        delete(runways[i]);
    }
}

void Airport::cleanup() {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling cleanup");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        delete(runways[i]);
    }
    runways.clear();
    ENSURE(runways.empty(),"cleanup postcondition failed");
}

/*const map<int, Airplane *> &Airport::getGates() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGates");
    return gates;
}*/

std::ostream& operator<<(std::ostream& output,Airport& airport){
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when getting output");
    output<<"Airport: "<<airport.getName()<<" ("<<airport.getIata()<<")"<<endl;
    output<<" -> gates: "<<airport.gates.size()<<endl;
    output<<" -> runways: "<<airport.runways.size()<<endl;
    return output;
}

bool Airport::ProperInitialized() const {
    return _InitCheck==this;
}

Gate* Airport::getGateFromAirplane(Airplane* plane){
    REQUIRE(plane->ProperInitialized(),"Airplane plane wasn't initialized when calling getGateFromAirplane");
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGateFromAirplane");
    for(unsigned int i=0;i<gates.size();i++){
        if(gates[i]->getCurrentPlane()!=NULL){
            if(gates[i]->getCurrentPlane()->getNumber()==plane->getNumber()){
                return gates[i];
            }
        }
    }
    return NULL;
}


void Airport::freeGate(Gate*  gate){
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling freeGate");
    gate->setCurrentPlane(NULL);
    ENSURE(gate->getCurrentPlane()==NULL,"freeGate postcondition failed");
}


const vector<Taxipoint*> &Airport::getTaxipoints() const {
    return taxipoints;
}

void Airport::addTaxipoints(Taxipoint* taxipoint) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addAirplane");
    REQUIRE(findTaxipoint(taxipoint->getName())==NULL,"The giving plane shouldn't be related to the airport already");
    taxipoints.push_back(taxipoint);
    ENSURE(findTaxipoint(taxipoint->getName())!=NULL,"addTaxipoints postcondition failed");
}

Runway *Airport::findRunway(const string&name) {
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getName()==name){
            return runways[i];
        }
    }
    return NULL;
}

Taxipoint *Airport::findTaxipoint(const string &name) {
    for (unsigned int i = 0; i < taxipoints.size(); ++i) {
        if(taxipoints[i]->getName()==name){
            return taxipoints[i];
        }
    }
    return NULL;
}


Runway *Airport::findFreeRunway(Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreerunway");
    bool grassallowed=airplaneCanLandOnGrass(airplane);
    int required=requiredLengthOfRunway(airplane);
    int queueingplane=2147483647;//initialize the number to max
    Runway* leastplane=NULL;
    if (grassallowed){
        //always using grass first if possible.
        for (unsigned int i = 0; i < runways.size(); ++i) {
            if(!(runways[i]->isCrossing())&&!(runways[i]->isOnuse())&&runways[i]->getType()==grass&&runways[i]->getLength()>=required&&runways[i]->getAirplanequeueing()<queueingplane){
                queueingplane=runways[i]->getAirplanequeueing();
                leastplane=runways[i];
            }
        }
    }
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(!(runways[i]->isCrossing())&&!(runways[i]->isOnuse())&&runways[i]->getType()!=grass&&runways[i]->getLength()>=required&&runways[i]->getAirplanequeueing()<queueingplane){
            queueingplane=runways[i]->getAirplanequeueing();
            leastplane=runways[i];
        }
    }
    if (leastplane==NULL){
        cout<<"no free runway are suitable for this plane"<<endl;
    }
    //always find the runway with the least plane queuing
    return leastplane;
}

Signaltower &Airport::getTower(){
    return *tower;
}

bool Airport::receiveSignal(Airplane *airplane, string signal) {
    return tower->receiveSignal(airplane,signal);
}

void Airport::addPassenger(int a) {
    passengers+=a;
}

void Airport::removePassenger(int a) {
    passengers-=a;
}

