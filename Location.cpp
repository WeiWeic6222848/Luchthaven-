//
// Created by c6222848 on 4/6/18.
//

#include "Location.h"
#include "DesignByContract.h"

Location::Location(const string &name) : name(name) {
    crossing=false;
    onuse=false;
    _initCheck=this;
    ENSURE(ProperInitialized(),"Location object failed to initialize properly");
}

bool Location::isOnuse() const {
    REQUIRE(ProperInitialized(),"Location must be initialized when calling isOnuse");
    return onuse;
}

bool Location::isCrossing() const {

    REQUIRE(ProperInitialized(),"Location must be initialized when calling isCrossing");
    return crossing;
}

void Location::setOnuse(bool onuse) {

    REQUIRE(ProperInitialized(),"Location must be initialized when calling setOnuse");
    Location::onuse = onuse;
    ENSURE(isOnuse()==onuse,"setOnuser postcondition failed");
}

void Location::setCrossing(bool crossing) {

    REQUIRE(ProperInitialized(),"Location must be initialized when calling setCrossing");
    Location::crossing = crossing;
    ENSURE(isCrossing()==crossing,"setCrossing postcondition failed");
}

void Location::addCrossingToRoute(Location *location) {
    REQUIRE(location!=NULL,"Location can't be NULL");
    REQUIRE(ProperInitialized(),"Location must be initialized when calling addCrossingToRoute");
    route.push_back(location);
    ENSURE(find(route.begin(),route.end(),location)!=route.end(),"addCrossingToRoute postcondition failed");
}

const string &Location::getName() const {

    REQUIRE(ProperInitialized(),"Location must be initialized when calling getName");
    return name;
}

const vector<Location *> &Location::getRoute() const {

    REQUIRE(ProperInitialized(),"Location must be initialized when calling getRoute");
    return route;
}

bool Location::ProperInitialized() const {
    return _initCheck==this;
}

bool Location::isRunway() {
    REQUIRE(ProperInitialized(),"Location must be initialized when calling isRunway");

    return false;
}

bool Location::isGate() {
    REQUIRE(ProperInitialized(),"Location must be initialized when calling isGate");

    return false;
}

bool Location::isTaxipoint() {

    REQUIRE(ProperInitialized(),"Location must be initialized when calling isTaxipoint");
    return false;
}

