//
// Created by c6222 on 2018/3/8.
//

#include "Runway.h"
#include "DesignByContract.h"



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
    if(currentairplane!=NULL){
        setOnuse(true);
    }
    else{
        setOnuse(false);
        airplanequeueing--;
    }
    ENSURE(getCurrentairplane()==currentairplane,"setCurrentairplane postcondition failed");
}


bool Runway::ProperInitialized() const{
    return _InitCheck==this;
}


Taxipoint *Runway::getTaxipoint() const {
    return taxipoint;
}

void Runway::setTaxipoint(Taxipoint *taxipoint) {
    Runway::taxipoint = taxipoint;
}

Runwaytype Runway::getType() const {
    return type;
}

int Runway::getLength() const {
    return length;
}

Runway::Runway(const string &name, Airport *where, string stringtype, int length) : Location(name), where(where),
                                                                                  length(length) {
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
    airplanequeueing++;
}

int Runway::getAirplanequeueing() const {
    return airplanequeueing;
}

Airplane *Runway::getPlaneAtEnd() const {
    return planeAtEnd;
}

void Runway::setPlaneAtEnd(Airplane *planeAtEnd) {
    Runway::planeAtEnd = planeAtEnd;
}

Airplane *Runway::getPlaneAtbegin() const {
    return planeAtbegin;
}

void Runway::setPlaneAtbegin(Airplane *planeAtbegin) {
    Runway::planeAtbegin = planeAtbegin;
}

bool Runway::isRunway() {
    return true;
}

void Runway::planeLeaved() {
    airplanequeueing--;
}

Runway::~Runway() {

}

