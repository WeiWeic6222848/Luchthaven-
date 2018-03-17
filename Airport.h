//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPORT_H
#define LUCHTHAVEN_AIRPORT_H

#include <vector>
#include <map>
#include "string"
#include "Runway.h"
using namespace std;

class Airplane;
class Runway;

class Airport {
private:
    string name;
    string iata;
    string callsign;
    map<int,Airplane*> gates;
    int passengers;
    vector<Runway*> runways;
    vector<Airplane*> approachingplanes;
    vector<Airplane*> leavingplanes;
    Airport* _InitCheck;


    friend std::ostream& operator<<(std::ostream& output,Airport& airport);

public:
    Airport();

    Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers);
    void addrunway(Runway* runway);

    const string &getName() const;

    const string &getIata() const;

    const string &getCallsign() const;

    int getPassengers() const;

    const map<int, Airplane *> &getGates() const;

    const vector<Runway *> &getRunways() const;

    Runway* findfreerunway();

    int findfreegates() const;

    void parkAirplane(int gate,Airplane* airplane);

    virtual ~Airport();

    void cleanup();

    bool ProperInitialized() const;

    bool operator==(const Airport &rhs) const;

    bool operator!=(const Airport &rhs) const;
};


#endif //LUCHTHAVEN_AIRPORT_H
