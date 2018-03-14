//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPORT_H
#define LUCHTHAVEN_AIRPORT_H

#include <vector>
#include "string"
#include "Runway.h"
using namespace std;

class Airport {
private:
    string number;
    string iata;
    string callsign;
    int gates;
    int passengers=0;
    vector<Runway*> runways;
public:
    Airport();

    Airport(const string &number, const string &iata, const string &callsign, int gates, int passengers);
    void addrunway(Runway* runway);

    const string &getNumber() const;

    const string &getIata() const;

    const string &getCallsign() const;

    int getGates() const;

    int getPassengers() const;

    const vector<Runway *> &getRunways() const;
};


#endif //LUCHTHAVEN_AIRPORT_H
