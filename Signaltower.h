//
// Created by c6222848 on 4/6/18.
//

#ifndef LUCHTHAVEN_SIGNALTOWER_H
#define LUCHTHAVEN_SIGNALTOWER_H


#include "Airplane.h"
#include "vector"
#include "Airport.h"
#include "fstream"
#include "Time.h"
#include "string"
#include "algorithm"
using namespace std;


static string allowedSignalprepare[]={"Approaching","Leaving","ApproachingtoGate","LeavingtoRunway","Emergency","Push back","IFR clearancy","Crossing runway","At runway"};
static vector<string> allowedSignal(allowedSignalprepare, allowedSignalprepare+sizeof(allowedSignalprepare)/ sizeof(allowedSignalprepare[0]));


class Airplane;
class Airport;
class Runway;
class Location;


class Signaltower {
private:
    vector<Airplane*> approachingAirplanes;
    vector<Airplane*> leavingAirplanes;
    vector<Airplane*> emergency;
    vector<pair<Airplane*,string> > incomingSignal;
    vector<pair<Airplane*,string> > regulateSignal;
    Airport* airport;
    vector<Airplane*> allflyingplanes();
    ofstream file;
    Time currentTime;
    bool doingNothing;
    vector<Location*> makeInstructionToGate(Airplane* airplane);
    vector<Location*> makeInstructionToRunway(Airplane* airplane);
    Signaltower* _initCheck=NULL;
public:
    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling getCurrentTime");
     * @return
     */
    const Time &getCurrentTime() const;

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling setCurrentTime");
     *    ENSURE(getCurrentTime()==currentTime,"setCurrentTime postcondition failed");
     * @param currentTime
     */
    void setCurrentTime(const Time &currentTime);

    /**
     *     REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling getFile");
     * @return
     */
    ofstream &getFile();

    /**
     *    REQUIRE(airport->ProperInitialized(),"airport must be initialized properly when calling constructor");
     *    ENSURE(ProperInitialized(),"Signal tower object failed to initialize properly");
     * @param airport
     */
    Signaltower(Airport *airport);

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling receiveSignal");
     *    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling receiveSignal");
     *    REQUIRE(find(allowedSignal.begin(),allowedSignal.end(),signal)!=allowedSignal.end(),"Signal tower received a signal that it doesnt reconizes");
     * @param airplane
     * @param signal
     * @return
     */
    bool receiveSignal(Airplane* airplane,string signal);

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling regulateApproachingplanes");
     */
    void regulateApproachingplanes();

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling regulateLeavingplanes");
     */
    void regulateLeavingplanes();

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignal");
     * @return
     */
    bool sendSignal();


//unused, replaced by regulateleavingplanes;
    /**
     *
     * @param airplane
     * @return
     */
    bool permissionLeavingGate(Airplane* airplane);

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPermission5000");
     *    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPermission5000");
     * @param airplane
     */
    void sendSignalPermission5000(Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPermission3000");
     *     REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPermission3000");
     * @param airplane
     */
    void sendSignalPermission3000(Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPermissionLanding");
     *     REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPermissionLanding");
     * @param airplane
     * @param runway
     */
    void sendSignalPermissionLanding(Airplane* airplane,Runway* runway);

    /**
     *     REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalWaiting");
     *     REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalWaiting");
     * @param airplane
     * @return
     */
    bool sendSignalWaiting(Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalClearedToCross");
     *     REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalClearedToCross");
     * @param airplane
     */
    void sendSignalClearedToCross(Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalHoldPosition");
     *     REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalHoldPosition");
     *
     * @param airplane
     */
    void sendSignalHoldPosition(Airplane* airplane);

    /**
     *     REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalLineup");
     *     REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalLineup");
     * @param airplane
     * @param takeoff
     */
    void sendSignalLineup(Airplane* airplane,bool takeoff=false);

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendInstruction");
     *    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalInstruction");
     * @param airplane
     * @param Instruction
     * @param adding
     */
    void sendInstruction(Airplane*airplane, vector<Location*> Instruction,bool adding=false);

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalIFRclear");
     *    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalIFRclear");
     * @param airplane
     */
    void sendSignalIFRclear(Airplane* airplane);

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPushBack");
     *    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPushBack");
     * @param airplane
     * @param runway
     */
    void sendSignalPushBack(Airplane* airplane,Runway* runway);

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling timeRuns");
     */
    void timeRuns();

    /**
     *    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling isDoingNothing");
     * @return
     */
    bool isDoingNothing();

    bool ProperInitialized() const;
};


#endif //LUCHTHAVEN_SIGNALTOWER_H
