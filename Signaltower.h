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
class Time;

class Signaltower {
private:
    vector<Airplane*> approachingAirplanes;
    vector<Airplane*> leavingAirplanes;
    vector<Airplane*> taxiingtogate;
    vector<Airplane*> taxiingtorunway;
    vector<Airplane*> emergency;
    Airport* airport;
    vector<Airplane*> allflyingplanes();
    vector<Airplane*> allgroundplanes();
    ofstream file;
    Time time;
public:
    Signaltower(Airport *airport);

    bool receiveSignal(Airplane* airplane,string signal);
    void regulateApproachingplanes();
    bool permissionLeavingGate(Airplane* airplane);
    void regulateTaxiingtoGate();
    void regulateTaxiingtorunway();

    void makeInstructionToGate(Airplane* airplane);
    void makeInstructionToRunway(Airplane* airplane);
    /*
    void sendSignalPermission5000(Airplane* airplane);
    void sendSignalPermission3000(Airplane* airplane);
    void sendSignalPermissionLanding(Airplane* airplane);
    void sendSignalPermissionLeaving(Airplane* airplane);
    void sendSignalWaiting(Airplane* airplane);
     */
};


#endif //LUCHTHAVEN_SIGNALTOWER_H
