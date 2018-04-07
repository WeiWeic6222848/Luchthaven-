//
// Created by c6222848 on 4/7/18.
//

#include "Gate.h"

Gate::Gate(const string &name) : Location(name) {}

Airplane *Gate::getCurrentPlane() const {
    return currentPlane;
}

void Gate::setCurrentPlane(Airplane *currentPlane) {
    Gate::currentPlane = currentPlane;
    if(currentPlane!=NULL){
        setOnuse(true);
    }
    else{
        setOnuse(false);
    }
}

Airplane *Gate::getPlaneNearGate() const {
    return planeNearGate;
}

void Gate::setPlaneNearGate(Airplane *planeNearGate) {
    Gate::planeNearGate = planeNearGate;
}

bool Gate::isGate() {
    return true;
}

Gate::~Gate() {

}
