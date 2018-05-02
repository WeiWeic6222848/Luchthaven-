//
// Created by c6222 on 2018/3/8.
//

#include "Runway.h"
#include "DesignByContract.h"



Airport *Runway::getAirport() const {
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
    if(currentairplane!=NULL){
        setOnuse(true);
    }
    else{
        setOnuse(false);
    }
    ENSURE(getCurrentairplane()==currentairplane,"setCurrentairplane postcondition failed");
}


bool Runway::ProperInitialized() const{
    return _InitCheck==this;
}


Taxipoint *Runway::getTaxipoint() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getTaxipoint");
    return taxipoint;
}

void Runway::setTaxipoint(Taxipoint *taxipoint) {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setTaxipoint");
    Runway::taxipoint = taxipoint;
    ENSURE(getTaxipoint()==taxipoint,"setTaxipoint postcondition failed");
}

Runwaytype Runway::getType() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getType");
    return type;
}

int Runway::getLength() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getLength");
    return length;
}

Runway::Runway(const string &name, Airport *where, string stringtype, int length) : Location(name), where(where),
                                                                                  length(length) {
    REQUIRE((stringtype=="asphalt"||stringtype=="grass"),"Runwaytype were wrong");
    currentairplane= NULL;
    _InitCheck=this;
    if (stringtype=="asphalt"){
        type=asphalt;
    }
    else if (stringtype=="grass"){
        type=grass;
    }
    airplanequeueing=0;
    ENSURE(ProperInitialized(),"Runway object failed to initialize properly");
}

void Runway::planeQueued() {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling planeQueued");
    airplanequeueing++;
}

int Runway::getAirplanequeueing() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getAirplanequeueing");
    return airplanequeueing;
}

Airplane *Runway::getPlaneAtEnd() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getPlaneAtEnd");
    return planeAtEnd;
}

void Runway::setPlaneAtEnd(Airplane *planeAtEnd) {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setPlaneAtEnd");
    Runway::planeAtEnd = planeAtEnd;
    ENSURE(getPlaneAtEnd()==planeAtEnd,"setPlaneAtEnd postcondition failed");
}

Airplane *Runway::getPlaneAtbegin() const {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getPlaneAtbegin");
    return planeAtbegin;
}

void Runway::setPlaneAtbegin(Airplane *planeAtbegin) {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setPlaneAtbegin");
    Runway::planeAtbegin = planeAtbegin;
    ENSURE(getPlaneAtbegin()==planeAtbegin,"setPlaneAtbegin postcondition failed");

}

bool Runway::isRunway() {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling isRunway");
    return true;
}

void Runway::planeLeaved() {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling planeLeaved");
    airplanequeueing--;
}

Runway::~Runway() {
    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling destructor");

}

