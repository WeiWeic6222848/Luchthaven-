//
// Created by c6222 on 2018/3/8.
//

#include "Airport.h"

Airport::Airport(const string &number, const string &iata, const string &callsign, int gates, int passengers) : number(
        number), iata(iata), callsign(callsign), gates(gates), passengers(passengers) {}

void Airport::addrunway(Runway *runway) {
    runways.push_back(runway);
}

const string &Airport::getNumber() const {
    return number;
}

const string &Airport::getIata() const {
    return iata;
}

const string &Airport::getCallsign() const {
    return callsign;
}

int Airport::getGates() const {
    return gates;
}

int Airport::getPassengers() const {
    return passengers;
}

const vector<Runway *> &Airport::getRunways() const {
    return runways;
}

Airport::Airport() {}

