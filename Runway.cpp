//
// Created by c6222 on 2018/3/8.
//

#include "Runway.h"
#include "DesignByContract.h"

Runway::Runway(const string &name) : name(name) {
    currentairplane= NULL;
    _InitCheck=this;
    ENSURE(ProperInitialized(),"Runway object failed to initialize properly");
}

Runway::Runway(const string &name, Airport *where) : name(name), where(where) {
    currentairplane= NULL;
    _InitCheck=this;
    ENSURE(ProperInitialized(),"Runway object failed to initialize properly");
}

const string &Runway::getName() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getName");
    return name;
}

Airport *Runway::Where() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling Where");
    return where;
}

Airplane *Runway::getCurrentairplane() const {

    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getCurrentairplane");
    return currentairplane;
}

Runway::Runway() {}

void Runway::setCurrentairplane(Airplane *currentairplane) {

    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setCurrentairplane");
    Runway::currentairplane = currentairplane;
    ENSURE(getCurrentairplane()==currentairplane,"setCurrentairplane postcondition failed");
}

Runway::~Runway() {

}

bool Runway::ProperInitialized() const{
    return _InitCheck==this;
}

