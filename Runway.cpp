//
// Created by c6222 on 2018/3/8.
//

#include "Runway.h"
#include "DesignByContract.h"


Runway::Runway(const string &name, Airport *where) : name(name), where(where) {
}

const string &Runway::getName() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getName");
    return name;
}

Airport *Runway::location() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling Where");
    return where;
}

Airplane *Runway::getCurrentairplane() const {

    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getCurrentairplane");
    return currentairplane;
}


void Runway::setCurrentairplane(Airplane *currentairplane) {

    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setCurrentairplane");
    Runway::currentairplane = currentairplane;
    ENSURE(getCurrentairplane()==currentairplane,"setCurrentairplane postcondition failed");
}


bool Runway::ProperInitialized() const{
    return _InitCheck==this;
}

Runway::Runway(const string &name, Airport *where, const string& stringtype, int length,Taxiroute route) : name(name), where(where),
                                                                                  length(length), taxiroute(route){
    currentairplane= NULL;
    _InitCheck=this;
    if (stringtype=="asphalt"){
        type=asphalt;
    }
    else if (stringtype=="grass"){
        type=grass;
    }
    ENSURE(ProperInitialized(),"Runway object failed to initialize properly");

}

