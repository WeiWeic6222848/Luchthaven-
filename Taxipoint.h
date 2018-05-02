//
// Created by c6222848 on 4/6/18.
//

#ifndef LUCHTHAVEN_TAXIPOINT_H
#define LUCHTHAVEN_TAXIPOINT_H

#include "Runway.h"
#include "Location.h"
#include "algorithm"

class Runway;

class Taxipoint:public Location{
private:
    Runway* runwayonpoint;
    vector<Airplane*> planesWaiting;
    Taxipoint* _initCheck=NULL;
public:
    /**
     *     ENSURE(ProperInitialized(),"Taxipoint object failed to initialize properly");
     * @param name
     * @param runwayonpoint
     */
    Taxipoint(const string &name, Runway *runwayonpoint);

    /**
     *     REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling getRunwayonpoint");
     * @return
     */
    Runway *getRunwayonpoint() const;

    /**
     *     REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling setRunwayonpoint");
     *     ENSURE(getRunwayonpoint()==runwayonpoint,"setRunwayonpoint postcondition failed");
     * @param runwayonpoint
     */
    void setRunwayonpoint(Runway *runwayonpoint);

    /**
     *     REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling addPlanesWaiting");
     *     ENSURE(find(planesWaiting.begin(),planesWaiting.end(),airplane)!=planesWaiting.end(),"addPlanesWaiting postcondition failed");
     * @param airplane
     */
    void addPlanesWaiting(Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling addPlanesWaiting");
     * @return
     */
  const  vector<Airplane *> &getPlanesWaiting()const;

    /**
     *     REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling isTaxipoint");
     * @return
     */
    bool isTaxipoint();

    /**
     *     REQUIRE(ProperInitialized(),"Taxipoint must be initialized properly when calling destructor");
     */
    virtual ~Taxipoint();

    bool ProperInitialized()const;

    void removePlanesWaiting(Airplane* aiplane);
};

#endif //LUCHTHAVEN_TAXIPOINT_H
