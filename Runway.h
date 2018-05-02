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
    Airplane* currentairplane = NULL;
    Airplane* planeAtEnd = NULL;
    Airplane* planeAtbegin = NULL;
    Runwaytype type;
    int length;
    Taxipoint* taxipoint=NULL;
    int airplanequeueing;
public:

    /**
     *
     * @param name
     * @param where
     * @param stringtype
     * @param length
     *     ENSURE(ProperInitialized(),"Runway object failed to initialize properly");
     */
    Runway(const string &name, Airport *where, string stringtype, int length);

    /**
     * REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling Where");
     * @return the pointer to where this runway is at
     */
    Airport *getAirport() const;

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

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getTaxipoint");

     * @return
     */
    Taxipoint *getTaxipoint() const;

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setTaxipoint");
     *    ENSURE(getTaxipoint()==taxipoint,"setTaxipoint postcondition failed");
     * @param taxipoint
     */
    void setTaxipoint(Taxipoint *taxipoint);

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getType");

     * @return
     */
    Runwaytype getType() const;

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getPlaneAtEnd");

     * @return
     */
    Airplane *getPlaneAtEnd() const;

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setPlaneAtEnd");
     *    ENSURE(getPlaneAtEnd()==planeAtEnd,"setPlaneAtEnd postcondition failed");
     * @param planeAtEnd
     */
    void setPlaneAtEnd(Airplane *planeAtEnd);

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getPlaneAtbegin");
     * @return
     */
    Airplane *getPlaneAtbegin() const;

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling setPlaneAtbegin");
     *    ENSURE(getPlaneAtbegin()==planeAtbegin,"setPlaneAtbegin postcondition failed");
     * @param planeAtbegin
     */
    void setPlaneAtbegin(Airplane *planeAtbegin);

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getLength");
     * @return
     */
    int getLength() const;

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling planeQueued");
     */
    void planeQueued();

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling getAirplanequeueing");
     * @return
     */
    int getAirplanequeueing() const;

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling isRunway");
     * @return
     */
    bool isRunway();

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling planeLeaved");
     */
    void planeLeaved();

    /**
     *    REQUIRE(ProperInitialized(),"Runway object wasn't initialized when calling destructor");
     */
    virtual ~Runway();
};


#endif //LUCHTHAVEN_RUNWAY_H
