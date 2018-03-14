//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_AIRPLANE_H
#define LUCHTHAVEN_AIRPLANE_H

#include "string"
using namespace std;

class Airplane {
public:
    string status;
    int passenger;
    int fuel;

    Airplane(const string &status, const string &number, const string &callsign,
             const string &model, int passengerCapacity=10, int passenger=10, int fuel=100);

    const string &getStatus() const;

    int getPassenger() const;

    int getFuel() const;

    const string &getNumber() const;

    const string &getCallsign() const;

    const string &getModel() const;

    int getPassengerCapacity() const;

private:
    string number;
    string callsign;
    string model;
    int passengerCapacity;
};


#endif //LUCHTHAVEN_AIRPLANE_H
