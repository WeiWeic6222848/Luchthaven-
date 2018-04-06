//
// Created by c6222848 on 4/3/18.
//

#ifndef LUCHTHAVEN_AIRPORTUTILS_H
#define LUCHTHAVEN_AIRPORTUTILS_H

#include "string"
#include "AirportsimImporter.h"
using namespace std;


bool fileExist(const string&filename);
int stoi(const string&value);
Esucces LoadAirport(char const* string, ostream& errStream, Airportsim& sim);
Esucces LoadAirport(int argc,char const* argv[],ostream& errStream,Airportsim& sim);
Esucces LoadAirport(int argc,char const* argv[],Airportsim& sim,bool testing=false);
bool isRightAirplaneCombination(string type, string engine, string size);
bool airplaneCanLandOnGrass(Airplane* airplane);
int requiredLengthOfRunway(Airplane* airplane);
#endif //LUCHTHAVEN_AIRPORTUTILS_H
