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

    int fuel;
    int fuelCapacity;
    int height;
    int passengerCapacity;
    string permission;
    Airport* destination=NULL;
    Airport* nextDestination=NULL;//for flightplan. unused now
    Location* location=NULL;
    vector<Location*> instruction;
    Time currentTime;
    Time actionDone;
    bool doingNothing;
    Runway* destinaterunway=NULL;
    string checkprocedure;


public:

    //all the getters------------------------------------------------------------------------

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getStatus");
     * @return status
     */
    const string &getStatus() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getNumber");
     * @return number
     */
    const string &getNumber() const;


    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getModel")
     * @return model
     */
    const string &getModel() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCallsign");
     * @return callsign
     */
    const string &getCallsign() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getType");
     * @return type
     */
    const string &getType() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getEngine");
     * @return engine
     */
    const string &getEngine() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getSize");
     * @return size
     */
    const string &getSize() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassenger");
     * @return current passenger on airplane
     */
    int getPassenger() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuel");
     * @return remaining fuel
     */
    int getFuel() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuelCapacity");
     * @return fuelCapacity
     */
    int getFuelCapacity() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getHeight");
     * @return
     */
    int getHeight() const;


    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassengerCapacity");
     * @return
     */
    int getPassengerCapacity() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPermission");
     * @return
     */
    const string &getPermission() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDestination");
     * @return
     */
    Airport *getDestination() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getNextDestination");
     * @return
     */
    Airport *getNextDestination() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getLocation");
     * @return
     */
    Location *getLocation() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getInstruction");
     * @return
     */
    const vector<Location *> &getInstruction() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCurrentTime");
     * @return
     */
    const Time &getCurrentTime() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling isDoingNothing");
     * @return
     */
    bool isDoingNothing();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDestinateRunway");
     * @return
     */
    Runway *getDestinateRunway() const;

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCheckProcedure");
     * @return
     */
    const string &getCheckProcedure() const;


    /**
     *
     * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
     */
    bool ProperInitialized() const;

    //all the getters------------------------------------------------------------------------



    //all the setters------------------------------------------------------------------------
    /**
     * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
     * ENSURE(getStatus()==status,"setStatus Postcondition failed");
     * @param status string with a certain restriction.
     * Status can only be either Flying, Approaching(landing), Standing at Gate, Just landed or Leaving.
     */
    void setStatus(const string &status);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
     *     ENSURE(getPassenger()==passenger,"setPassenger postcondition failed");
     * @param passenger
     */
    void setPassenger(int passenger);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setFuel");
     *     ENSURE(getFuel()==fuel,"setFuel postcondition failed");
     * @param fuel
     */
    void setFuel(int fuel);//not using atm.

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
     *     ENSURE(getFuelCapacity()==fuel,"setFuelCapacity postcondition failed");
     * @param fuel
     */
    void setFuelCapacity(int fuel);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPermission");
     *     ENSURE(getPermission()==descendingpermission,"setFuelCapacity postcondition failed");
     * @param descendingpermission
     */
    void setPermission(string descendingpermission);//planning to remove this part

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setDestination");
     *     ENSURE(getDestination()==destination,"setDestination postcondition failed");
     * @param destination
     */
    void setDestination(Airport *destination);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setNextDestination");
     *     ENSURE(getNextDestination()==nextDestination,"setNextDestination postcondition failed");
     * @param nextDestination
     */
    void setNextDestination(Airport *nextDestination);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setLocation");
     *     ENSURE(getLocation()==location,"setLocation postcondition failed");
     * @param location
     */
    void setLocation(Location *location);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setInstruction");
     *     ENSURE(getInstruction()==instruction,"setInstruction postcondition failed");
     * @param instruction
     */
    void setInstruction(const vector<Location *> &instruction);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setDestinateRunway");
     *     ENSURE(getDestinateRunway()==destinaterunway,"setDestinateRunway postcondition failed");
     * @param destinaterunway
     */
    void setDestinateRunway(Runway *destinaterunway);

    //remove as much as possible
    //all the setters--------------------------------------------------------------------------


    //outputter
    /**
     * REQUIRE(airplane.ProperInitialized(),"Airplane wasn't initialized when getting output");
     * @param output the outputstream that this function has to edit
     * @param airplane airplane reference to output
     * @return an edited outputstream
     */
    friend std::ostream& operator<<(std::ostream& output,Airplane& airplane);






    //constructor
    /**
     *
     * @param status
     * @param number
     * @param callsign
     * @param model
     * @param type
     * @param engine
     * @param size
     * @param passenger
     * @param fuel
     * @param passengerCapacity
     * @param destination
     */
    Airplane(const string &status, const string &number, const string &callsign, const string &model,
             const string &type, const string &engine, const string &size, int passenger, int fuel,
             int passengerCapacity, Airport *destination);





    //all valid signals--------------------------------------------------------------------------
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Approaching");
     *     ENSURE(received==true,"Tower didnt receive the signal Approaching");
     * @return
     */
    bool sendSignalApproaching();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Leaving");
     *     ENSURE(received==true,"Tower didnt receive the signal Leaving");
     * @return
     */
    bool sendSignalLeaving();//not really used anymore but ill leave it here

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoGate");
     *     ENSURE(received==true,"Tower didnt receive the signal ApproachingtoGate");
     * @return
     */
    bool sendSignalTaxiingtoGate();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoRunway");
     *     ENSURE(received==true,"Tower didnt receive the signal LeavingtoRunway");
     * @return
     */
    bool sendSignalTaxiingtoRunway();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Emergency");
     *     ENSURE(received==true,"Tower didnt receive the signal Emergency");
     * @return
     */
    bool sendSignalEmergency();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal PushBack");
     *     ENSURE(received==true,"Tower didnt receive the signal Push back");
     * @return
     */
    bool sendSignalPushBack();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal CrossingRunway");
     *     ENSURE(received==true,"Tower didnt receive the signal Crossing runway");
     * @return
     */
    bool sendSignalCrossingRunway();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal AtRunway");
     *     ENSURE(received==true,"Tower didnt receive the signal At runway");
     * @return
     */
    bool sendSignalAtRunway();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal IFR");
     *     ENSURE(received==true,"Tower didnt receive the signal IFR clearancy");
     * @return
     */
    bool sendSignalIFR();
    //all valid signals--------------------------------------------------------------------------


    //all valid receive signals------------------------------------------------------------------
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a normal signal");
     * @param signal
     * @return
     */
    bool receiveSignal(string signal);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a landing signal");
     * @param runway
     * @return
     */
    bool receiveLandingSignal(Runway* runway);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving an instruction");
     * @param Instruction
     * @param adding
     * @return
     */
    bool receiveInstruction(vector<Location*> Instruction,bool adding=false);
    //all valid receive signals------------------------------------------------------------------


    //time
    void timeRuns();

    //all actions to be done by aieplane---------------------------------------------------------
    void progressCheck();

    void resetCheckProcedure();

    bool fall();

    bool rise();

    bool landing();

    bool takeOff();

    bool pushBack();

    bool taxiing();

    bool liningUp();

    bool crossingRunway();
    //all actions to be done by aieplane---------------------------------------------------------


};


#endif //LUCHTHAVEN_AIRPLANE_H
