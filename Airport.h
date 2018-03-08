//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPORT_H
#define LUCHTHAVEN_AIRPORT_H

#include "string"
using namespace std;

class Airport {
private:
    string number;
    string iata;
    string callsign;
    int gates;
    int passengers=0;
public:
    Airport(const string &number, const string &iata, const string &callsign, int gates, int passengers);
};


#endif //LUCHTHAVEN_AIRPORT_H
