//
// Created by c6222848 on 4/7/18.
//

#ifndef LUCHTHAVEN_GATE_H
#define LUCHTHAVEN_GATE_H


#include "Location.h"

class Location;
class Airplane;

class Gate:public Location {

private:
public:
    Gate(const string &name);

private:
    Airplane* currentPlane=NULL;
    Airplane* planeNearGate=NULL;
public:
    Airplane *getCurrentPlane() const;

    void setCurrentPlane(Airplane *currentPlane);

    Airplane *getPlaneNearGate() const;

    void setPlaneNearGate(Airplane *planeNearGate);

    bool isGate();

    virtual ~Gate();
};



#endif //LUCHTHAVEN_GATE_H
