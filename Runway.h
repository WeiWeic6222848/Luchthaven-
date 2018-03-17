//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_RUNWAY_H
#define LUCHTHAVEN_RUNWAY_H

#include "string"
#include "Airplane.h"
#include "Airport.h"
using namespace std;

class Airport;

class Runway {
    string name;
    Airport* where= NULL;
    Airplane* currentairplane= NULL;
    Runway* _InitCheck;
public:
    Runway(const string &name, Airport *where);

    Runway(const string &name);

    Runway();

    const string &getName() const;

    Airport *Where() const;

    Airplane *getCurrentairplane() const;

    void setCurrentairplane(Airplane *currentairplane);

    ~Runway();

    bool ProperInitialized()const;
};


#endif //LUCHTHAVEN_RUNWAY_H
