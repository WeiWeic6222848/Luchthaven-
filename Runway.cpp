//
// Created by c6222 on 2018/3/8.
//

#include "Runway.h"

Runway::Runway(const string &name) : name(name) {currentairplane= nullptr;}

Runway::Runway(const string &name, Airport *where) : name(name), where(where) {}

