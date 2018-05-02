//
// Created by c6222848 on 4/6/18.
//

#ifndef LUCHTHAVEN_LOCATION_H
#define LUCHTHAVEN_LOCATION_H

#include <vector>
#include "string"
#include "algorithm"
using namespace std;
class Airplane;

class Location {
protected:
    bool onuse;
    bool crossing;
    string name;
    vector<Location*> route;
    Location* _initCheck=NULL;


public:
    /**
     *    ENSURE(ProperInitialized(),"Location object failed to initialize properly");
     * @param name
     */
    Location(const string &name);

    /**
     *    REQUIRE(ProperInitialized(),"Location must be initialized when calling isOnuse");
     * @return
     */
    bool isOnuse() const;

    /**
     *    REQUIRE(ProperInitialized(),"Location must be initialized when calling isCrossing");

     * @return
     */
    bool isCrossing() const;


    /**
     *    REQUIRE(ProperInitialized(),"Location must be initialized when calling setOnuse");
     *    ENSURE(isOnuse()==onuse,"setOnuser postcondition failed");
     * @param onuse
     */
    void setOnuse(bool onuse);

    /**
     *
     * @param crossing
     */
    void setCrossing(bool crossing);

    /**    REQUIRE(ProperInitialized(),"Location must be initialized when calling addCrossingToRoute");
     *     ENSURE(find(route.begin(),route.end(),location)!=route.end(),"addCrossingToRoute postcondition failed");
     * @param location
     */
    void addCrossingToRoute(Location* location);

    /**
     *    REQUIRE(ProperInitialized(),"Location must be initialized when calling getName");
     * @return
     */
    const string &getName() const;

    /**
     *    REQUIRE(ProperInitialized(),"Location must be initialized when calling getRoute");
     * @return
     */
    const vector<Location *> &getRoute() const;

    /**
     * REQUIRE(ProperInitialized(),"Location must be initialized when calling isRunway");
     * @return
     */
    virtual bool isRunway();

    /**
     * REQUIRE(ProperInitialized(),"Location must be initialized when calling isGate");

     * @return
     */
    virtual bool isGate();

    /**
     * REQUIRE(ProperInitialized(),"Location must be initialized when calling isTaxipoint");
     * @return
     */
    virtual bool isTaxipoint();

    /**
     *
     * @return
     */
    virtual bool ProperInitialized() const;
};


#endif //LUCHTHAVEN_LOCATION_H
