//
// Created by c6222848 on 4/3/18.
//




#include <fstream>
#include <cstdlib>
#include "string"
#include "AirportUtils.h"
#include "AirportsimImporter.h"
using namespace std;

/**
 *
 * @param filename filename to check wether or not exist
 * @return if the file exists
 */


bool fileExist(const string&filename){
    ifstream a(filename.c_str());
    return a.good();
}


int stoi(const string &value){
    for (unsigned int i = 0; i < value.size(); ++i) {
        if(!(isdigit(value[i]))){
            throw "stoi failed beacause the giving string contains something else that digits\n";
        }
    }
    int temp=atoi(value.c_str());
    if(temp==0&&value!="0"){
        throw "stoi failed beacause the giving string is not a digit\n";
    }
    return temp;
}

Esucces LoadAirport(char const* string, ostream& errStream, Airportsim& sim){
    return AirportsimImporter::importAirportsim(string,errStream,sim);
}

Esucces LoadAirport(int argc,char const* argv[],ostream& errStream,Airportsim& sim){
    Esucces status=Success;
    for (int i = 0; i < argc; ++i) {

        Esucces temp=LoadAirport(argv[i],errStream,sim);
        if (status==Success){
            status=temp;
        }
        else if (status==PartialImport){
            if (temp==ImportAborted){
                status=temp;
            }
        }
    }
    return status;
}

