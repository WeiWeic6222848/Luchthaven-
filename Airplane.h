//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPLANE_H
#define LUCHTHAVEN_AIRPLANE_H

#include "string"
#include <iostream>
#include <vector>
#include "list"
#include "Time.h"
#include "algorithm"

class Airport;
class Location;
class Runway;
class Time;
class Airportsim;
class Signaltower;

using namespace std;


class Airplane {
public:

    enum Airplaneallowedstatus{Standing_at_gate,Approaching,Leaving,Taxiing_to_runway,Taxiing_to_gate,jobsdone,Landed,Emergency};
    enum AirplaneallowedSignal{Keep_flying,threeThousand,fiveThousand,Cleared_to_cross,Hold_position,Line_up,Fly,IFR_clearancy,Push_back,EmergencySignal};
    enum AirplaneallowedPermission{empty,tenThousandPermission,threeThousandPermission,fiveThousandPermission,LandingPermission,FlyPermission,LineupPermission,Push_backPermission,IFR_clearancyPermission,TaxiingPermission,Cleared_to_crossPermission};
    enum AirplaneCheckProcedure{Just_landed,Technical_control,Refueling,Boarding,Ready_to_leave};

private:
    Airplane* _initcheck=NULL;
    Airplaneallowedstatus status;
    string number;
    string callsign;
    string model;
    string type;
    string engine;
    string size;
    int passenger;
    int squawkcode;

    int fuel;
    int fuelCapacity;
    int height;
    int passengerCapacity;



    AirplaneallowedPermission permission;
    Airport* destination=NULL;
    string des;
    int departure;
    int arrival;
    int interval;
    Airport* nextDestination=NULL;//for flightplan. unused now
    Location* location=NULL;
    vector<Location*> instruction;
    Time currentTime;
    Time actionDone;
    bool doingNothing;
    Runway* destinaterunway=NULL;
    AirplaneCheckProcedure checkprocedure;

    friend Airportsim;
    friend Airport;
    friend Signaltower;

public:



    //all the getters------------------------------------------------------------------------

    /**
     *    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getSquawkcode");
     * @return squawkcode as integer
     */
    int getSquawkcode() const;
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getStatus");
     * @return status
     */
    const Airplaneallowedstatus &getStatus() const;


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
    const AirplaneallowedPermission &getPermission() const;

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
    const AirplaneCheckProcedure &getCheckProcedure() const;


    /**
     *
     * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
     */
    bool ProperInitialized() const;

    /**
     *      REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDes");
     * @return
     */
    const string &getDes() const;

    /**
     *      REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDeparture")
     * @return
     */
    int getDeparture() const;

    /**
     *      REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getArrival")
     * @return
     */
    int getArrival() const;

    /**
     *      REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getInterval")
     * @return
     */
    int getInterval() const;

    //all the getters------------------------------------------------------------------------





    //all the setters------------------------------------------------------------------------
    /**
     *    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setSquawkcode");
     *    REQUIRE(validSquawkcode(squawkcode),"the squawkcode that has been giving is not valid");//function in AirportUtils.h
     *    ENSURE(getSquawkcode()==squawkcode,"setSquawkcode postcondition failed");
     * @param squawkcode squawkcode 0000-7777
     */
    void setSquawkcode(int squawkcode);
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
     *     ENSURE(getStatus()==status,"setStatus Postcondition failed");
     * @param status a certain status.
     */
    void setStatus(const Airplaneallowedstatus &status);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
     *     REQUIRE(passenger>=0,"passenger must be bigger than zero!");
     *     REQUIRE(passenger<=getPassengerCapacity(),"passenger must be lesser than capacity!");
     *     ENSURE(getPassenger()==passenger,"setPassenger postcondition failed");
     * @param passenger
     */
    void setPassenger(int passenger);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setFuel");
     *     REQUIRE(fuel>=0,"fuel must be bigger than zero!");
     *     REQUIRE(fuel<=getFuelCapacity(),"fuel must be lesser than capacity!");
     *     ENSURE(getFuel()==fuel,"setFuel postcondition failed");
     * @param fuel
     */
    void setFuel(int fuel);//not using atm.

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
     *     REQUIRE(fuel>=0,"fuelcapacity must be bigger than zero!");
     *     REQUIRE(fuel>=getFuel(),"fuelcapacity must be bigger than fuel!");
     *     ENSURE(getFuelCapacity()==fuel,"setFuelCapacity postcondition failed");
     * @param fuel
     */
    void setFuelCapacity(int fuel);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPermission");
     *     ENSURE(getPermission()==descendingpermission,"setPermission postcondition failed");
     * @param descendingpermission
     */
    void setPermission(AirplaneallowedPermission descendingpermission);//planning to remove this part

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
     *     REQUIRE(airplane.ProperInitialized(),"Airplane wasn't initialized when getting output");
     * @param output the outputstream that this function has to edit
     * @param airplane airplane reference to output
     * @return an edited outputstream
     */
    friend std::ostream& operator<<(std::ostream& output,Airplane& airplane);






    //constructor
    /**
     *    ENSURE(ProperInitialized(),"this airplane object failed to Initialize properly");
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
    Airplane(const Airplaneallowedstatus &status, const string &number, const string &callsign, const string &model,
             const string &type, const string &engine, const string &size, int passenger, int fuel,
             int passengerCapacity, Airport *destination, const string &des="",int departure=0, int arrival=0, int interval=0);

    void fuelReduction();

private:
    //all valid signals--------------------------------------------------------------------------
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Approaching");
     *     REQUIRE(getStatus()==Approaching&&getHeight()==10000,"Airplane can only contact tower if it's approaching at height 10000");
     * @return
     */
    bool sendSignalApproaching();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Leaving");
     *     REQUIRE(getStatus()==Leaving&&getPermission()!=FlyPermission,"Leaving signal should only be sent when airplane is leaving and already standing at runway");
     *     REQUIRE(getLocation()==getDestinateRunway()&&getDestinateRunway()->getCurrentairplane()==this,"Leaving signal should only be sent when runway are set properly");
     * @return
     */
    bool sendSignalLeaving();//not really used anymore but ill leave it here

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoGate");
     *     REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane can only taxi to gate if it just landed on the runway");
     *     REQUIRE(getStatus()==Landed,"Airplane can only taxi to gate if its just landed");
     * @return
     */
    bool sendSignalTaxiingtoGate();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoRunway");
     *     REQUIRE(getCheckProcedure()==Ready_to_leave,"Airplane should only be able to taxi to runway after technical check");
     *     REQUIRE(getStatus()==Standing_at_gate,"Airplane should only be able to taxi to runway if its at gate right now");
     *     REQUIRE(getPermission()==Push_backPermission,"Airplane should only be able to taxi to runway after push back");
     * @return
     */
    bool sendSignalTaxiingtoRunway();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Emergency");
     *     REQUIRE(getStatus()==Emergency,"Airplane shouldnt request emergency if it's not in emergency");
     *     REQUIRE(getType()=="Emergency","Airplane shouldnt request emergency if it's not in emergency");
     * @return
     */
    bool sendSignalEmergency();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal PushBack");
     *     REQUIRE(getCheckProcedure()==Ready_to_leave,"Airplane should only be able to push back after technical check");
     *     REQUIRE(getPermission()==IFR_clearancyPermission,"Airplane shouldnt request push back when IFR are not cleared");
     *     REQUIRE(getStatus()==Standing_at_gate,"Airplane shouldnt request push back if it's not at gate");
     * @return
     */
    bool sendSignalPushBack();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal CrossingRunway");
     *     REQUIRE(getLocation()->isRunway()&&getLocation()!=getDestinateRunway(),"Airplane must be at an runway that isn't its destination");
     *     REQUIRE(getPermission()==TaxiingPermission,"Airplane must have the permission to taxi");
     * @return
     */
    bool sendSignalCrossingRunway();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal AtRunway");
     *     REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane must be at its destinate runway");
     *     REQUIRE(getStatus()==Taxiing_to_runway,"Airplane must be taxiing to runway");
     *     REQUIRE(getPermission()==TaxiingPermission,"Airplane must have the permission to taxi");
     * @return
     */
    bool sendSignalAtRunway();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal IFR");
     *     REQUIRE(getLocation()->isGate()&&getLocation()->isOnuse(),"Airplane must be standing at gate while asking IFR clearancy");
     *     REQUIRE(getStatus()==Standing_at_gate,"Airplane shouldnt request IFR clearancy if it's not at gate");
     *     REQUIRE(getCheckProcedure()==Ready_to_leave,"Airplane should only be able to ask for IFR clearancy after technical check");
     * @return
     */
    bool sendSignalIFR();
    //all valid signals--------------------------------------------------------------------------


    //all valid receive signals------------------------------------------------------------------
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a normal signal");
     *     ENSURE(signal==Keep_flying||isDoingNothing(),"receiveSignal postcondition failed");
     * @param signal
     * @return
     */
    bool receiveSignal(AirplaneallowedSignal signal);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a landing signal");
     *     REQUIRE(runway!=NULL,"Airplane has received a runway which is NULL, to land");
     *     REQUIRE(getStatus()==Approaching&&height==3000&&getPermission()==threeThousandPermission,"Airplane should only gets a landing signal when its at height 3000 and approaching");
     *     ENSURE(getPermission()==LandingPermission&&isDoingNothing(),"receiveLandingSignal postcondition failed");
     * @param runway
     * @return
     */
    bool receiveLandingSignal(Runway* runway);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving an instruction");
     *     REQUIRE(Instruction.size()>1,"Airplane has received an instruction which has only one or less location");
     *     REQUIRE(find(Instruction.begin(),Instruction.end(),location)!=getInstruction().end(),"Airplane must have a correct taxi instruction with its own location");
     *     ENSURE((getPermission()==TaxiingPermission||getPermission()==Cleared_to_crossPermission)&&isDoingNothing(),"receiveLandingSignal postcondition failed");
     * @param Instruction
     * @param adding
     * @return
     */
    bool receiveInstruction(vector<Location*> Instruction,bool adding=false);

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling receiveSquawkcode");
     *     REQUIRE(validSquawkcode(squawkcode),"the squawkcode that has been giving is not valid");
     *     ENSURE(getSquawkcode()==squawkcode,"receiveSquawkcode postcondition failed");
     * @param squawkcode
     * @return
     */
    bool receiveSquawkcode(int squawkcode);
    //all valid receive signals------------------------------------------------------------------


    //time
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when time flies");
     */
    void timeRuns();


    //all actions to be done by aieplane---------------------------------------------------------
    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving doing the technical check");
     *     REQUIRE(getStatus()==Standing_at_gate,"Airplane must be standing at gate while doing the technical check");
     */
    void progressCheck();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when resetting the technical check status");
     *     ENSURE(getCheckProcedure()==Just_landed,"reset checkprocedure failed");
     */
    void resetCheckProcedure();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when falling");
     *     REQUIRE(getHeight() >= 1000, "airplane is too low to fall!! Its lower than 1000 meter");
     *     REQUIRE(getStatus()==Approaching||getStatus()==Emergency,"Airplane can only fall if it's approaching or having emergency");
     * @return
     */
    bool fall();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when rising");
     *     REQUIRE(getStatus()==Leaving,"Airplane can only rise if it's leaving");
     *     REQUIRE(getPermission()==FlyPermission,"Airplane can only rise if it has the flying permission");
     * @return
     */
    bool rise();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when landing");
     *     REQUIRE(getStatus()==Approaching||getStatus()==Emergency,"Airplane can only land if it's approaching");
     *     REQUIRE(getPermission()==LandingPermission,"Airplane can only land if it got the permission of landing");
     *     REQUIRE(getDestinateRunway()!=NULL,"Airplane can only land if it knows which runway to land");
     *     ENSURE(!isDoingNothing()||getStatus()==Landed,"status must be landed when landing has been finished!");
     * @return
     */
    bool landing();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when takingOff");
     *     REQUIRE(getStatus()==Leaving,"Airplane can only takeOff if it is leaving");
     *     REQUIRE(getPermission()==FlyPermission,"Airplane can only takeOff if it has the fly permission");
     * @return
     */
    bool takeOff();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when pushing back");
     *     REQUIRE(getStatus()==Standing_at_gate&&getLocation()->isGate(),"Airplane can only push back if it is standing at an gate");
     *     REQUIRE(getPermission()==Push_backPermission,"Airplane must get the permission to push back");
     * @return
     */
    bool pushBack();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when taxiing");
     *     REQUIRE(getStatus()==Taxiing_to_runway||getStatus()==Taxiing_to_gate,"Airplane can only taxi if it is taxiing to a gate or a runway");
     *     REQUIRE(getPermission()==TaxiingPermission,"Airplane must get the permission to taxi");
     *     REQUIRE(!getInstruction().empty(),"Airplane doesnt have any instruction yet!");
     *     REQUIRE(find(getInstruction().begin(),getInstruction().end(),location)!=getInstruction().end(),"Airplane must have a correct taxi instruction with its own location");
     *     REQUIRE(find(getInstruction().begin(),getInstruction().end(),location)!=getInstruction().end()-1,"Airplane already finished taxi");
     * @return
     */
    bool taxiing();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when liningUp");
     *     REQUIRE(getStatus()==Taxiing_to_runway,"Airplane can only lineup if it is taxiing to a runway");
     *     REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane can only lineUp if it's at the destinate runway");
     *     REQUIRE(getPermission()==LineupPermission||getPermission()==FlyPermission,"Airplane must get permission to line up");
     *     ENSURE(!isDoingNothing()||getDestinateRunway()->getPlaneAtbegin()==this,"lining up postcondition failed");
     * @return
     */
    bool liningUp();

    /**
     *     REQUIRE(ProperInitialized(),"Airplane wasn't initialized when crossing runway");
     *     REQUIRE(getStatus()==Taxiing_to_runway||getStatus()==Taxiing_to_gate,"Airplane can only taxi if it is taxiing to a runway");
     *     REQUIRE(getPermission()==Cleared_to_crossPermission,"Airplane must get permission to cross runway");
     *     REQUIRE(getLocation()->isRunway()&&getLocation()!=getDestinateRunway(),"Airplane shouldnt cross its destinate runway");
     *     ENSURE((isDoingNothing()&&!getLocation()->isCrossing())||(!isDoingNothing()&&getLocation()->isCrossing()),"crossingRunway postcondition failed");
     * @return
     */
    bool crossingRunway();
    /**
     *      REQUIRE(ProperInitialized(),"Airplane wasn't initalized when calling flightPlanActivated");
     * @return
     */
    bool flightPlanActivated();
    //all actions to be done by aieplane---------------------------------------------------------

private:
    void setHeight(int height);

    void setCurrentTime(const Time &currentTime);
};


#endif //LUCHTHAVEN_AIRPLANE_H
