//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPLANE_H
#define LUCHTHAVEN_AIRPLANE_H

#include "string"
#include <iostream>
using namespace std;


class Airplane {
public:
    string status;
    int passenger;
    int fuel;
    Airplane* _initcheck=NULL;
    int height;


/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getStatus");
 */
    const string &getStatus() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassenger");
 */
    int getPassenger() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuel");
 */
    int getFuel() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getNumber");
 */
    const string &getNumber() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCallsign");
 */
    const string &getCallsign() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getModel")
 */
    const string &getModel() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassengerCapacity");
 */
    int getPassengerCapacity() const;

/**
 * REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
 * ENSURE(getStatus()==status,"setStatus Postcondition failed");
 * @param status string with a certain restriction.
 * Status can only be either Flying, Approaching(landing), Standing at Gate, Just landed or Leaving.
 */
    void setStatus(const string &status);
/**
 * REQUIRE(airplane.ProperInitialized(),"Airplane wasn't initialized when getting output");
 * @param output the outputstream that this function has to edit
 * @param airport airplane reference to output
 * @return an edited outputstream
 */
    friend std::ostream& operator<<(std::ostream& output,Airplane& airport);

/**
 *
 * @return Boolean value of whether or not this object is being initialized and not being copied from other object;
 */
    bool ProperInitialized() const;

    bool dalen();

    bool stijgen();



/**
 * ENSURE(ProperInitialized(),"this airplane object failed to Initialize properly");
 * @param status the status of airplane in string.
 * @param passenger amount of passenger aboard
 * @param fuel percentage of fuel remaining in integer
 * @param number uniek number of airplane
 * @param callsign callsign of an airplane
 * @param model model of an airplane
 * @param passengerCapacity Maximum amount of passenger aboard
 */
    Airplane(const string &status, int passenger, int fuel, int height, const string &number, const string &callsign,
             const string &model, const string &type, const string &engine, const string &size, int passengerCapacity);

private:
    string number;
    string callsign;
    string model;
    string type;
    string engine;
    string size;

private:
public:
    Airplane(const string &status, int passenger, int fuel, const string &number, const string &callsign,
             const string &model, const string &type, const string &engine, const string &size, int passengerCapacity);

private:
    int passengerCapacity;
};


#endif //LUCHTHAVEN_AIRPLANE_H
