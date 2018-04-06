//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_RUNWAY_H
#define LUCHTHAVEN_RUNWAY_H

#include "string"
#include "Airplane.h"
#include "Location.h"
using namespace std;

class Airplane;
class Airport;
class Taxipoint;

enum Runwaytype{ asphalt,grass};


class Runway: public Location {
    Runway* _InitCheck;
    Airport* where= NULL;
    Airplane* currentairplane= NULL;
    Runwaytype type;
    int length;
    Taxipoint* taxipoint=NULL;
    int airplanequeueing;
public:
    Runway(const string &name, Airport *where, string stringtype, int length);
/**
 * REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling Where");
 * @return the pointer to where this runway is at
 */
    Airport *location() const;

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

    Taxipoint *getTaxipoint() const;

    void setTaxipoint(Taxipoint *taxipoint);

    Runwaytype getType() const;

    int getLength() const;

    void planeQueued();

    int getAirplanequeueing() const;
};


#endif //LUCHTHAVEN_RUNWAY_H
