//
// Created by c6222848 on 4/6/18.
//

#include "Taxipoint.h"


Runway *Taxipoint::getRunwayonpoint() const {
    return runwayonpoint;
}

void Taxipoint::setRunwayonpoint(Runway *runwayonpoint) {
    Taxipoint::runwayonpoint = runwayonpoint;
}

Taxipoint::Taxipoint(const string &name, Runway *runwayonpoint) : Location(name), runwayonpoint(runwayonpoint) {}

void Taxipoint::addPlanesWaiting(Airplane *airplane) {
    planesWaitingForRunway.push_back(airplane);
}

const vector<Airplane *> &Taxipoint::getPlanesWaitingForRunway() const {
    return planesWaitingForRunway;
}

