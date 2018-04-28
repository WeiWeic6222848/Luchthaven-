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

using namespace std;

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
public:
    const Time &getCurrentTime() const;

    void setCurrentTime(const Time &currentTime);

    ofstream &getFile();

public:

    Signaltower(Airport *airport);

    bool receiveSignal(Airplane* airplane,string signal);
    void regulateApproachingplanes();
    void regulateLeavingplanes();
    bool permissionLeavingGate(Airplane* airplane);
    bool sendSignal();



    void sendSignalPermission5000(Airplane* airplane);
    void sendSignalPermission3000(Airplane* airplane);
    void sendSignalPermissionLanding(Airplane* airplane,Runway* runway);
    bool sendSignalWaiting(Airplane* airplane);
    void sendSignalClearedToCross(Airplane* airplane);
    void sendSignalHoldPosition(Airplane* airplane);
    void sendSignalLineup(Airplane* airplane,bool takeoff=false);
    void sendInstruction(Airplane*airplane, vector<Location*> Instruction,bool adding=false);
    void sendSignalIFRclear(Airplane* airplane);
    void sendSignalPushBack(Airplane* airplane,Runway* runway);


    void timeRuns();
    bool isDoingNothing();
};


#endif //LUCHTHAVEN_SIGNALTOWER_H
