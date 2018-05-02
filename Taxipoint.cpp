//
// Created by c6222848 on 4/6/18.
//

#include "Taxipoint.h"
#include "DesignByContract.h"

Runway *Taxipoint::getRunwayonpoint() const {
    REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling getRunwayonpoint");
    return runwayonpoint;
}

void Taxipoint::setRunwayonpoint(Runway *runwayonpoint) {
    REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling setRunwayonpoint");
    Taxipoint::runwayonpoint = runwayonpoint;
    ENSURE(getRunwayonpoint()==runwayonpoint,"setRunwayonpoint postcondition failed");
}

Taxipoint::Taxipoint(const string &name, Runway *runwayonpoint) : Location(name), runwayonpoint(runwayonpoint) {
    _initCheck=this;
    ENSURE(ProperInitialized(),"Taxipoint object failed to initialize properly");
}

void Taxipoint::addPlanesWaiting(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling addPlanesWaiting");
    planesWaiting.push_back(airplane);
    ENSURE(find(planesWaiting.begin(),planesWaiting.end(),airplane)!=planesWaiting.end(),"addPlanesWaiting postcondition failed");
}

const vector<Airplane *> &Taxipoint::getPlanesWaiting()const {
    REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling addPlanesWaiting");
    return planesWaiting;
}

bool Taxipoint::isTaxipoint() {
    REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling isTaxipoint");
    return true;
}

Taxipoint::~Taxipoint() {
    REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling destructor");
}

bool Taxipoint::ProperInitialized() const {
    return Location::ProperInitialized();
}

void Taxipoint::removePlanesWaiting(Airplane *aiplane) {
    //we don't really use it as a vector, it's more a counter of how much planes are on the taxipoint right now
    planesWaiting.pop_back();
}

