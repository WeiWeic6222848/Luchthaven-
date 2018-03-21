//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include "Airport.h"
#include "DesignByContract.h"
#include "algorithm"

Airport::Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers) : name(name), iata(iata), callsign(callsign),  passengers(passengers)
{
    for (int i = 1; i < gates+1; ++i) {
        Airport::gates[i]= NULL;
    }
    _InitCheck=this;
    ENSURE(ProperInitialized(),"This airport object failed to Initialize properly");
}

void Airport::addrunway(Runway *runway) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addrunway");
    runways.push_back(runway);
    ENSURE(find(runways.begin(),runways.end(),runway)!=runways.end(),"addrunway postcondition failed");
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


Runway *Airport::findfreerunway() {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreerunway");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getCurrentairplane()==NULL){
            return runways[i];
        }
    }
    cout<<"all runways buzy"<<endl;
    return NULL;
}

int Airport::findfreegates() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreegates");
    for (unsigned int i = 1; i < gates.size()+1; ++i) {
        if(gates.at(i)==NULL){
            return i;
        }
    }
    cerr<<"all gates buzy"<<endl;
    return -1;
}

void Airport::parkAirplane(unsigned int gate, Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling parkAirplane");
    REQUIRE(gate<gates.size()&&gate>=1,"The giving gate number must be valid");
    REQUIRE(gates[gate]==NULL,"The giving gate must be empty");
    gates[gate]=airplane;
    ENSURE(gates[gate]==airplane,"parkAirplane postcondition failed");
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

const map<int, Airplane *> &Airport::getGates() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGates");
    return gates;
}

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

int Airport::getGateFromAirplane(Airplane* plane){
    REQUIRE(plane->ProperInitialized(),"Airplane plane wasn't initialized when calling getGateFromAirplane");
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGateFromAirplane");
    for(unsigned int i=1;i<=gates.size();i++){
        if(gates[i]!=NULL){
            if(gates[i]->getNumber()==plane->getNumber()){
                return i;
            }
        }
    }

    return -1;
}

/*
void Airport::setGates(int  gate, Airplane& plane) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling setGates");
    gates[gate]=&plane;
    ENSURE(gates[gate]==&plane,"setGate postcondition failed");
}
 */

void Airport::freeGate(int  gate){
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling freeGate");
    gates[gate]=NULL;
    ENSURE(gates[gate]==NULL,"freeGate postcondition failed");
}

void Airport::addAirplane(Airplane *plane) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addAirplane");
    REQUIRE(find(relatedplanes.begin(),relatedplanes.end(),plane)==relatedplanes.end(),"The giving plane shouldn't be related to the airport already");
    relatedplanes.push_back(plane);
    ENSURE(find(relatedplanes.begin(),relatedplanes.end(),plane)!=relatedplanes.end(),"addAirplanes postcondition failed");
}

const vector<Airplane *> &Airport::getRelatedplanes() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getRelatedplanes");
    return relatedplanes;
}
