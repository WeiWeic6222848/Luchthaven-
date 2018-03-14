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


class Airport {
private:
    string name;
    string iata;
    string callsign;
    map<int,Airplane*> gates;
    int passengers=0;
    vector<Runway*> runways;
public:
    Airport();

    Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers);
    void addrunway(Runway* runway);

    const string &getName() const;

    const string &getIata() const;

    const string &getCallsign() const;

    int getPassengers() const;

    const vector<Runway *> &getRunways() const;
};


#endif //LUCHTHAVEN_AIRPORT_H
