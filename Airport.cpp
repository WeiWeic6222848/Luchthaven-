//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include "Airport.h"

Airport::Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers) : name(name), iata(iata), callsign(callsign),  passengers(passengers)
{
    for (int i = 1; i < gates+1; ++i) {
        Airport::gates[i]= NULL;
    }
}

void Airport::addrunway(Runway *runway) {
    runways.push_back(runway);
}

const string &Airport::getName() const {
    return name;
}

const string &Airport::getIata() const {
    return iata;
}

const string &Airport::getCallsign() const {
    return callsign;
}

int Airport::getPassengers() const {
    return passengers;
}

const vector<Runway *> &Airport::getRunways() const {
    return runways;
}

Airport::Airport() {}

Runway *Airport::findfreerunway() {
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getCurrentairplane()==NULL){
            return runways[i];
        }
    }
    cout<<"all runways buzy"<<endl;
    return NULL;
}

int Airport::findfreegates() const {
    for (unsigned int i = 1; i < gates.size()+1; ++i) {
        if(gates.at(i)==NULL){
            return i;
        }
    }
    cerr<<"all gates buzy"<<endl;
    return -1;
}

void Airport::parkAirplane(int gate, Airplane *airplane) {
    if(gate<1||gate>(int)gates.size()){
        cerr<<"invalid gate assigned";
        return;
    }
    gates[gate]=airplane;
}

Airport::~Airport() {
    for (unsigned int i = 0; i < runways.size(); ++i) {
        delete(runways[i]);
    }
}

void Airport::cleanup() {
    for (unsigned int i = 0; i < runways.size(); ++i) {
        delete(runways[i]);
    }
}
