//
// Created by tristan on 16/03/18.
//

#ifndef LUCHTHAVEN_OUTPUT_SYSTEM_H
#define LUCHTHAVEN_OUTPUT_SYSTEM_H

#include <fstream>

class Airportsim;

class output_system {
public:
/**
 * REQUIRE(simulator.ProperInitialized(),"airportsimulator wasn't initialized when calling writeToFile");
 * ENSURE(fileExist("../output/Info.txt"),"writeToFile postcondition failed");
 * @param simulator the airsim to output
 */
   static void writeToFile(Airportsim& simulator);
};


#endif //LUCHTHAVEN_OUTPUT_SYSTEM_H
