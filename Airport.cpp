//
// Created by c6222 on 2018/3/8.
//

#include "Airport.h"

Airport::Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers) : name(name), iata(iata), callsign(callsign),  passengers(passengers)
{
    for (int i = 1; i < gates+1; ++i) {
        Airport::gates[i]= nullptr;
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

