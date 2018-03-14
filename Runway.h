//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_RUNWAY_H
#define LUCHTHAVEN_RUNWAY_H

#include "string"
#include "Airplane.h"
using namespace std;

class Airport;

class Runway {
    string name;
    Airport* where= nullptr;
    Airplane* currentairplane= nullptr;
public:
    Runway(const string &name, Airport *where);

    Runway(const string &name);

    const string &getName() const;

    Airport *Where() const;

    Airplane *getCurrentairplane() const;
};


#endif //LUCHTHAVEN_RUNWAY_H
