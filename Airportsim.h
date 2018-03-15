//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_Airportsim_H
#define LUCHTHAVEN_Airportsim_H

#include "vector"
#include "Airport.h"
#include "tinyxml.h"

using namespace std;

class Airportsim{
    vector<Airport> Airports;
    vector<Airplane> Airplanes;
    vector<Runway*> Runways;
public:
    Airportsim();

    Airportsim(const string& filename);
    void addsourcefile(const string &filename);
    const Airport& findairport(const string& iata);
    const Airplane& findairplane(const string& number);
    const Runway& findrunway(const string&number,const string& iata);
};


#endif //LUCHTHAVEN_Airportsim_H
