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

/**
 * ENSURE(ProperInitialized(),"Runway object failed to initialize properly");
 * @param name unique name of the runway
 * @param where at which airport is this runway
 */
    Runway(const string &name, Airport *where);

/**
 * REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getName");
 * @return the name of this runway
 */
    const string &getName() const;

/**
 * REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling Where");
 * @return the pointer to where this runway is at
 */
    Airport *Where() const;

/**
 * REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getCurrentairplane");
 * @return the pointer to the airplane on this runway
 */
    Airplane *getCurrentairplane() const;

/**
 * REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setCurrentairplane");
 * ENSURE(getCurrentairplane()==currentairplane,"setCurrentairplane postcondition failed");
 * @param currentairplane the airplane to be set on this runway
 */
    void setCurrentairplane(Airplane *currentairplane);

/**
 *
 * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
 */
    bool ProperInitialized()const;
};


#endif //LUCHTHAVEN_RUNWAY_H
