//
// Created by c6222848 on 4/6/18.
//

#ifndef LUCHTHAVEN_LOCATION_H
#define LUCHTHAVEN_LOCATION_H

#include <vector>
#include "string"
using namespace std;

class Location {
protected:
    bool onuse;
    bool crossing;
    string name;
    vector<Location*> route;

public:
    Location(const string &name);

    bool isOnuse() const;

    bool isCrossing() const;

    void setOnuse(bool onuse);

    void setCrossing(bool crossing);

    void addCrossingToRoute(Location* location);

    const string &getName() const;

    const vector<Location *> &getRoute() const;
};


#endif //LUCHTHAVEN_LOCATION_H
