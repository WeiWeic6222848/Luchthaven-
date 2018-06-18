//
// Created by c6222848 on 4/3/18.
//

#ifndef LUCHTHAVEN_AIRPORTUTILS_H
#define LUCHTHAVEN_AIRPORTUTILS_H

#include "string"
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "AirportsimImporter.h"
#include "tinyxml.h"

using namespace std;

class Airplane;

/**
 *
 * @param dirname
 * @return
 */
bool DirectoryExists(const std::string dirname);
/**
 *
 * @param filename
 * @return
 */
bool fileExist(const string&filename);

/**
 *
 * @param value
 * @return
 */
int stoi(const string&value);

/**
 *     REQUIRE(fileExist(string),"input file doesnt exist when calling LoadAirport");
 *     REQUIRE(sim.ProperInitialized(),"Airportsim must be initialized in order to load");
 * @param string
 * @param errStream
 * @param sim
 * @return
 */
Esucces LoadAirport(char const* string, ostream& errStream, Airportsim& sim);

/**
 *     REQUIRE(sim.ProperInitialized(),"Airportsim must be initialized in order to load");
 * @param argc
 * @param argv
 * @param errStream
 * @param sim
 * @return
 */
Esucces LoadAirport(int argc,char const* argv[],ostream& errStream,Airportsim& sim);

/**
 *     REQUIRE(sim.ProperInitialized(),"Airportsim must be initialized in order to load");
 * @param argc
 * @param argv
 * @param sim
 * @param testing
 * @return
 */
Esucces LoadAirport(int argc,char const* argv[],Airportsim& sim,bool testing=false);

/**
 *  soft require
 *   //REQUIRE(type=="private"||type=="emergency"||type=="military"||type=="airline","airplane has a wrong type");
 *   //REQUIRE(size=="small"||size=="medium"||size=="large","airplane has a wrong size");
 *   //REQUIRE(engine=="jet"||engine=="propeller","airplane has a wrong engine type");
 * @param type
 * @param engine
 * @param size
 * @return
 */
bool isRightAirplaneCombination(string type, string engine, string size);

/**
 *     REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized when calling isRightAirplaneCombination!");
 * @param airplane
 * @return
 */
bool isRightAirplaneCombination(Airplane* airplane);

/**
 * REQUIRE(airplane->ProperInitialized(),"airplane must be initialized properly when calling airplane can load on grass")
 * @param airplane
 * @return
 */
bool airplaneCanLandOnGrass(Airplane* airplane);

/**
 * REQUIRE(airplane->ProperInitialized(),"airplane must be initialized properly when calling airplane can load on grass");
 * @param airplane
 * @return
 */
int requiredLengthOfRunway(Airplane* airplane);

/**
 *
 * @param integer
 * @return
 */
string to_string(int integer);

/**
 * REQUIRE(fileExist(leftFileName)&&fileExist(rightFileName),"Both file must exist when calling FileCompare");
 * @param leftFileName
 * @param rightFileName
 * @return
 */
bool FileCompare(const std::string leftFileName, const std::string rightFileName);

/**
 *
 * @param element
 * @return
 */
bool hasEmptyFields(TiXmlElement* element);

/**
 *    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized when calling getBasesqwakcode");
 *    REQUIRE(isRightAirplaneCombination(airplane),"airplane must be the right combination!");
 * @param airplane
 * @return
 */
int getBasesqwakcode(Airplane* airplane);

/**
 *    REQUIRE(extendtodigit>0,"you must enter a positive digit to extend!");
 * @param numer
 * @param extendtodigit
 * @return
 */
string fillingintegergap(int numer,int extendtodigit);

/**
 *
 * @param code
 * @return
 */
bool validSquawkcode(int code);

/**
 *
 * @return
 */
int generatevalidRandomcode();
#endif //LUCHTHAVEN_AIRPORTUTILS_H
