//
// Created by tristan on 16/03/18.
//

#include "output_system.h"
#include "DesignByContract.h"

bool fileExist(const string&filename);

void output_system::writeToFile(Airportsim &simulator) {
    REQUIRE(simulator.ProperInitialized(),"airportsimulator wasn't initialized when calling writeToFile");
    ofstream outputfile;
    outputfile.open("../output/Info.txt",ios::out);
    for(unsigned int i=0;i<simulator.getAirports().size();i++){
        Airport* airport=simulator.getAirports()[i];
        outputfile<<*airport<<endl;
    }
    for(unsigned int i=0;i<simulator.getAirplanes().size();i++){
        Airplane* airplane=simulator.getAirplanes()[i];
        outputfile<<*airplane<<endl;
    }
    outputfile.close();
    ENSURE(fileExist("../output/Info.txt"),"writeToFile postcondition failed");
}

