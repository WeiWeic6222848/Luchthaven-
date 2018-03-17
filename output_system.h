//
// Created by tristan on 16/03/18.
//

#ifndef LUCHTHAVEN_OUTPUT_SYSTEM_H
#define LUCHTHAVEN_OUTPUT_SYSTEM_H

#include <fstream>
#include "Airportsim.h"

class output_system {
public:
    void writeToFile(Airportsim& simulator);
};


#endif //LUCHTHAVEN_OUTPUT_SYSTEM_H
