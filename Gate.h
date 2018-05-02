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
    Airplane* currentPlane=NULL;
    Airplane* planeNearGate=NULL;
    Gate* _initCheck=NULL;


public:
    /**
     *     ENSURE(ProperInitialized(),"Gate object failed to initialize properly");
     * @param name
     */
    Gate(const string &name);
    /**
     *     REQUIRE(ProperInitialized(),"gate must be initialized properly when calling getCurrentPlane");

     * @return
     */
    Airplane *getCurrentPlane() const;

    /**
     *     REQUIRE(ProperInitialized(),"gate must be initialized properly when calling setCurrentPlane");
     *     ENSURE(getCurrentPlane()==currentPlane,"setCurrentPlane postcondition failed");
     * @param currentPlane
     */
    void setCurrentPlane(Airplane *currentPlane);

    /**
     *     REQUIRE(ProperInitialized(),"gate must be initialized properly when calling getPlaneNearGate");
     * @return
     */
    Airplane *getPlaneNearGate() const;

    /**
     *     REQUIRE(ProperInitialized(),"gate must be initialized properly when calling setPlaneNearGate");
     *     REQUIRE(getPlaneNearGate()==NULL,"plane shouldnt overwrite other planes");
     *     ENSURE(getPlaneNearGate()==planeNearGate,"setPlaneNearGate postcondition failed");
     * @param planeNearGate
     */
    void setPlaneNearGate(Airplane *planeNearGate);

    /**
     *     REQUIRE(ProperInitialized(),"gate must be initialized properly when calling isGate");
     * @return
     */
    bool isGate();

    /**
     *     REQUIRE(ProperInitialized(),"gate must be initialized properly when calling destructor");
     */
    virtual ~Gate();

    /**
     *
     * @return
     */
    bool ProperInitialized() const ;
};



#endif //LUCHTHAVEN_GATE_H
