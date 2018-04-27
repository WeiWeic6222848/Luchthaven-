//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPLANE_H
#define LUCHTHAVEN_AIRPLANE_H

#include "string"
#include <iostream>
#include <vector>
#include "list"
#include "Airport.h"
#include "Time.h"

class Airport;
class Location;
class Runway;
class Time;

using namespace std;


static string allowedstatusprepare[]={"Standing at gate","Approaching","Leaving","Taxiing to runway","Taxiing to gate","jobsdone","Landed"};
static vector<string> allowedstatus(allowedstatusprepare, allowedstatusprepare+sizeof(allowedstatusprepare)/ sizeof(allowedstatusprepare[0]));

class Airplane {
private:
    Airplane* _initcheck=NULL;
    string status;
    string number;
    string callsign;
    string model;
    string type;
    string engine;
    string size;
    int passenger;
    int fuelCapacity;
    int height;
    int passengerCapacity;
    string permission;
    Airport* destination=NULL;
    Airport* nextDestination=NULL;
public:
    Airport *getNextDestination() const;

    void setNextDestination(Airport *nextDestination);

private:
    Location* location=NULL;
    vector<Location*> instruction;
    Time currentTime;
    Time actionDone;
    bool doingNothing;
public:
    const Time &getCurrentTime() const;

    void setCurrentTime(const Time &currentTime);

public:
    const vector<Location *> &getInstruction() const;

    void setInstruction(const vector<Location *> &instruction);

private:
    Runway* destinaterunway=NULL;
    string checkprocedure;
public:
    Runway *getDestinaterunway() const;

    void setDestinaterunway(Runway *destinaterunway);

public:
/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getStatus");
 */
    const string &getStatus() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassenger");
 */
    int getPassenger() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuelCapacity");
 */
    int getFuelCapacity() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getNumber");
 */
    const string &getNumber() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCallsign");
 */
    const string &getCallsign() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getModel")
 */
    const string &getModel() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassengerCapacity");
 */
    int getPassengerCapacity() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
 * ENSURE(getStatus()==status,"setStatus Postcondition failed");
 * @param status string with a certain restriction.
 * Status can only be either Flying, Approaching(landing), Standing at Gate, Just landed or Leaving.
 */
    void setStatus(const string &status);
/**
 * REQUIRE(airplane.ProperInitialized(),"Airplane wasn't initialized when getting output");
 * @param output the outputstream that this function has to edit
 * @param airport airplane reference to output
 * @return an edited outputstream
 */
    friend std::ostream& operator<<(std::ostream& output,Airplane& airport);

/**
 *
 * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
 */
    bool ProperInitialized() const;

    bool fall();

    bool rise();

    int getHeight() const;

    const string &getType() const;

    const string &getEngine() const;

    const string &getSize() const;

    void setPermission(string descendingpermission);

    void setPassenger(int passenger);

    void setFuelCapacity(int fuel);

    Airplane(const string &status, const string &number, const string &callsign, const string &model,
             const string &type, const string &engine, const string &size, int passenger, int fuel,
             int passengerCapacity, Airport *destination);

    Airport *getDestination() const;

    const string &getPermission() const;

    Location *getLocation() const;

    void setDestination(Airport *destination);

    void setLocation(Location *location);

    bool sendSignalApproaching();

    bool sendSignalLeaving();

    bool sendSignalTaxiingtoGate();

    bool sendSignalTaxiingtoRunway();

    bool sendSignalEmergency();

    bool sendSignalPushBack();

    bool sendSignalCrossingRunway();

    bool sendSignalAtRunway();

    bool sendSignalIFR();

    void progressCheck();

    const string &getCheckprocedure() const;

    void resetCheckProcedure();

    bool landing();

    bool takeOff();

    bool isDoingNothing();

    bool pushBack();

    void timeRuns();

    bool taxiing();

    bool liningUp();

    bool crossingRunway();

    bool receiveSignal(string signal);

    bool receiveLandingSignal(Runway* runway);

    bool receiveInstruction(vector<Location*> Instruction,bool adding=false);

};


#endif //LUCHTHAVEN_AIRPLANE_H
