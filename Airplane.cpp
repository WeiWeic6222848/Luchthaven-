//
// Created by c6222 on 2018/3/8.
//

#include "Airplane.h"

const string &Airplane::getStatus() const {
    return status;
}

int Airplane::getPassenger() const {
    return passenger;
}

int Airplane::getFuel() const {
    return fuel;
}

const string &Airplane::getNumber() const {
    return number;
}

const string &Airplane::getCallsign() const {
    return callsign;
}

const string &Airplane::getModel() const {
    return model;
}

int Airplane::getPassengerCapacity() const {
    return passengerCapacity;
}

Airplane::Airplane() {}

Airplane::Airplane(const string &status, int passenger, int fuel, const string &number, const string &callsign,
                   const string &model, int passengerCapacity) : status(status), passenger(passenger), fuel(fuel),
                                                                 number(number), callsign(callsign), model(model),
                                                                 passengerCapacity(passengerCapacity) {}
