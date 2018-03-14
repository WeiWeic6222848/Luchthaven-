//
// Created by c6222 on 2018/3/8.
//

#ifndef LUCHTHAVEN_LUCHTHAVENXML_H
#define LUCHTHAVEN_LUCHTHAVENXML_H

#include "vector"
#include "Airport.h"
#include "tinyxml.h"

using namespace std;

class LuchthavenXML:private TiXmlDocument {
    vector<Airport> Airports;
public:
    LuchthavenXML(const string& filename);
};


#endif //LUCHTHAVEN_LUCHTHAVENXML_H
