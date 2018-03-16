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

    Airplane(const string &status, int passenger, int fuel, const string &number, const string &callsign,
             const string &model, int passengerCapacity);

    const string &getStatus() const;

    Airplane();

    int getPassenger() const;

    int getFuel() const;

    const string &getNumber() const;

    const string &getCallsign() const;

    const string &getModel() const;

    int getPassengerCapacity() const;

    void setStatus(const string &status);

    friend std::ostream& operator<<(std::ostream& output,Airplane& airport);

private:
    string number;
    string callsign;
    string model;
    int passengerCapacity;
};


#endif //LUCHTHAVEN_AIRPLANE_H
