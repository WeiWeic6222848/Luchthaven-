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
    vector<Airport*> Airports;
    vector<Airplane*> Airplanes;
    void removeairport(Airport* airport);
    Airportsim* _InitCheck;
public:
    Airportsim(int argc,char const* argv[]);

    Airportsim(const string& filename);
    void addsourcefile(const string &filename);
    const Airport* findairport(const string& iata);
    const Airplane* findairplane(const string& number);
    const Runway* findrunway(const string&number,const string& iata);

    const vector<Airport*> &getAirports() const;
    const vector<Airplane*> &getAirplanes() const;

    void landing(Airplane& aproaching, Airport& airport);
    void takingOff(Airplane& aproaching, Airport& airport);
    bool ProperInitialized()const;
};


#endif //LUCHTHAVEN_Airportsim_H
