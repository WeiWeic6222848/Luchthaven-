//
// Created by c6222848 on 4/3/18.
//




#include <fstream>
#include <cstdlib>
#include <sstream>
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
    for (int i = 1; i < argc; ++i) {

        Esucces temp=LoadAirport(argv[i],errStream,sim);
        if (status==Success){
            status=temp;
        }
        else if (status==PartialImport){
            if (temp==ImportAborted){
                status=temp;
                errStream<<"Load has stopped on the file named "<<argv[i]<<endl;
                return status;
            }
        }
    }
    return status;
}

Esucces LoadAirport(int argc, const char **argv, Airportsim &sim, bool testing) {
    Esucces status=Success;
    stringstream test;
    for (int i = 1; i < argc; ++i) {

        Esucces temp=LoadAirport(argv[i],test,sim);
        if (status==Success){
            status=temp;
        }
        else if (status==PartialImport){
            if (temp==ImportAborted){
                status=temp;
            }
        }
        if (status==ImportAborted){
            test<<"Load has stopped on the file named "<<argv[i]<<endl;
            break;
        }
    }
    if(testing){
        ofstream ofile("tester.txt");
        ofile<<test;
    }
    else{
        cout<<test.str();
    }
    return status;
}

bool isRightAirplaneCombination(string type, string engine, string size) {
    if (engine=="propeller"){
        if(size=="small"){
            return type=="emegenry"||type=="private";
        }
        else if (size=="medium"){
            return type=="airline";
        }
        else if (size=="large"){
            return type=="military";
        }
        return false;
    }
    else if (engine=="jet"){
        if(size=="small"){
            return type=="military"||type=="private";
        }
        else if (size=="medium"){
            return type=="airline"||type=="private";
        }
        else if (size=="large"){
            return type=="airline";
        }
        return false;
    }
    else{
        return false;
    }
}

bool airplaneCanLandOnGrass(Airplane *airplane) {
    return airplane->getEngine()=="propeller"&&airplane->getSize()=="small";
}

int requiredLengthOfRunway(Airplane *airplane) {
    string size=airplane->getSize();
    int length=0;
    if(size=="small"){
        length=500;
    }
    else if(size=="medium"){
        length=1000;
    }
    else if (size=="large"){
        length=1500;
    }
    if(airplane->getEngine()=="jet"){
        length*=2;
    }
    return length;
}

