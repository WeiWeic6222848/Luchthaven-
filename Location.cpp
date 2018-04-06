//
// Created by c6222848 on 4/6/18.
//

#include "Location.h"

Location::Location(const string &name) : name(name) {
    crossing=false;
    onuse=false;
}

bool Location::isOnuse() const {
    return onuse;
}

bool Location::isCrossing() const {
    return crossing;
}

void Location::setOnuse(bool onuse) {
    Location::onuse = onuse;
}

void Location::setCrossing(bool crossing) {
    Location::crossing = crossing;
}

void Location::addCrossingToRoute(Location *location) {
    route.push_back(location);
}

const string &Location::getName() const {
    return name;
}

const vector<Location *> &Location::getRoute() const {
    return route;
}

