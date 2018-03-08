//
// Created by c6222 on 2018/3/8.
//

#include "Airport.h"

Airport::Airport(const string &number, const string &iata, const string &callsign, int gates, int passengers) : number(
        number), iata(iata), callsign(callsign), gates(gates), passengers(passengers) {}
