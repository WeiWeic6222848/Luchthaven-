//
// Created by c6222848 on 4/6/18.
//

#ifndef LUCHTHAVEN_TAXIPOINT_H
#define LUCHTHAVEN_TAXIPOINT_H

#include "Runway.h"
#include "Location.h"

class Runway;

class Taxipoint:public Location{
private:
    Runway* runwayonpoint;
    vector<Airplane*> planesWaitingForRunway;
public:
    Taxipoint(const string &name, Runway *runwayonpoint);

    Runway *getRunwayonpoint() const;

    void setRunwayonpoint(Runway *runwayonpoint);

    void addPlanesWaiting(Airplane* airplane);

    const vector<Airplane *> &getPlanesWaitingForRunway() const;
};

#endif //LUCHTHAVEN_TAXIPOINT_H
