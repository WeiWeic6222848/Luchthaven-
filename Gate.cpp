//
// Created by c6222848 on 4/7/18.
//

#include "Gate.h"
#include "DesignByContract.h"

Gate::Gate(const string &name) : Location(name) {
    _initCheck=this;
    ENSURE(ProperInitialized(),"Gate object failed to initialize properly");
}

Airplane *Gate::getCurrentPlane() const {
    REQUIRE(ProperInitialized(),"gate must be initialized properly when calling getCurrentPlane");
    return currentPlane;
}

void Gate::setCurrentPlane(Airplane *currentPlane) {
    REQUIRE(ProperInitialized(),"gate must be initialized properly when calling setCurrentPlane");
    Gate::currentPlane = currentPlane;
    if(currentPlane!=NULL){
        setOnuse(true);
    }
    else{
        setOnuse(false);
    }
    ENSURE(getCurrentPlane()==currentPlane,"setCurrentPlane postcondition failed");
}

Airplane *Gate::getPlaneNearGate() const {
    REQUIRE(ProperInitialized(),"gate must be initialized properly when calling getPlaneNearGate");
    return planeNearGate;
}

void Gate::setPlaneNearGate(Airplane *planeNearGate) {
    REQUIRE(ProperInitialized(),"gate must be initialized properly when calling setPlaneNearGate");
    if(planeNearGate!=NULL){
        REQUIRE(getPlaneNearGate()==NULL,"plane shouldnt overwrite other planes");
    }
    Gate::planeNearGate = planeNearGate;
    ENSURE(getPlaneNearGate()==planeNearGate,"setPlaneNearGate postcondition failed");
}

bool Gate::isGate() {
    REQUIRE(ProperInitialized(),"gate must be initialized properly when calling isGate");
    return true;
}

Gate::~Gate() {
    REQUIRE(ProperInitialized(),"gate must be initialized properly when calling destructor");

}

bool Gate::ProperInitialized() const {
    return _initCheck==this;
}
