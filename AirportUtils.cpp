//
// Created by c6222848 on 4/3/18.
//




#include <sys/stat.h>
#include "AirportUtils.h"
#include "DesignByContract.h"
#include "Airportsim.h"
#include "Runway.h"
#include "Taxipoint.h"
#include "Gate.h"

using namespace std;

bool DirectoryExists(const std::string dirname) {
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

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
    REQUIRE(fileExist(string),"input file doesnt exist when calling LoadAirport");
    REQUIRE(sim.ProperInitialized(),"Airportsim must be initialized in order to load");
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
    //soft requirement
    //REQUIRE(type=="private"||type=="emergency"||type=="military"||type=="airline","airplane has a wrong type");
    //REQUIRE(size=="small"||size=="medium"||size=="large","airplane has a wrong size");
    //REQUIRE(engine=="jet"||engine=="propeller","airplane has a wrong engine type");

    if (engine=="propeller"){
        if(size=="small"){
            return type=="emergency"||type=="private";
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
    REQUIRE(airplane->ProperInitialized(),"airplane must be initialized properly when calling airplane can load on grass");
    return airplane->getEngine()=="propeller"&&airplane->getSize()=="small";
}

int requiredLengthOfRunway(Airplane *airplane) {
    REQUIRE(airplane->ProperInitialized(),"airplane must be initialized properly when calling airplane can load on grass");
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

string to_string(int integer) {
    string finalString;
    if(integer==0){
        return "0";
    }
    while(integer!=0){
        int lastdigit=integer-integer/10*10;//using the integer devide rule, e.a. 105/10*10=100.
        finalString.insert(finalString.begin(),'0'+lastdigit);
        integer=integer/10;
    }
    return finalString;
}

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
    REQUIRE(fileExist(leftFileName)&&fileExist(rightFileName),"Both file must exist when calling FileCompare");
    ifstream leftFile, rightFile;
    char leftRead, rightRead;
    bool result;

    // Open the two files.
    leftFile.open(leftFileName.c_str());
    if (!leftFile.is_open()) {
        return false;
    };
    rightFile.open(rightFileName.c_str());
    if (!rightFile.is_open()) {
        leftFile.close();
        return false;
    };

    result = true; // files exist and are open; assume equality unless a counterexamples shows up.
    while (result && leftFile.good() && rightFile.good()) {
        leftFile.get(leftRead);
        rightFile.get(rightRead);
        result = (leftRead == rightRead);
    };
    if (result) {
        // last read was still equal; are we at the end of both files ?
        result = (!leftFile.good()) && (!rightFile.good());
    };

    leftFile.close();
    rightFile.close();
    return result;
}

bool hasEmptyFields(TiXmlElement *element) {
    if(element->FirstChildElement()==NULL&&element->GetText()==NULL){
        return true;
    }
    for (TiXmlElement* childelement = element->FirstChildElement(); childelement!=NULL ; childelement=childelement->NextSiblingElement()) {
        if(childelement->GetText()==NULL&&hasEmptyFields(childelement)){
            return true;
        }
    }
    return false;
}

int getBasesqwakcode(Airplane *airplane) {
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized when calling getBasesqwakcode");
    REQUIRE(isRightAirplaneCombination(airplane),"airplane must be the right combination!");
    string engine=airplane->getEngine();
    string size=airplane->getSize();
    string type=airplane->getType();
    int basecode=0;
    if(type=="private"){
        if(size=="medium"){
            return basecode+1000;
        }
    }
    else if(type=="airline"){
        basecode+=2000;
        if(engine=="jet"){
            basecode+=1000;
        }
        if(size=="large"){
            basecode+=1000;
        }
        return basecode;
    }
    else if(type=="military"){
        basecode+=5000;
        return basecode;
    }
    else if(type=="emergency"){
        basecode+=6000;
        return basecode;
    }
    return 0;
}

string fillingintegergap(int numer, int extendtodigit) {
    REQUIRE(extendtodigit>0,"you must enter a positive digit to extend!");
    string a="";
    for (int i = extendtodigit-1; i >0 ; --i) {
        if(numer<pow(10,i)){
            a+="0";
        }
        else{
            break;
        }
    }
    a+=to_string(numer);
    return a;
}

bool validSquawkcode(int code) {
    if(code>7777){
        return false;
    }
    else if(code<0){
        return false;
    }
    while(code>0){
        int lastdigit=code-code/10*10;
        if(lastdigit>7){
            return false;
        }
        code=code/10;
    }
    return true;
}

int generatevalidRandomcode() {
    int hunderd=rand()%8;
    int ten=rand()%8;
    int one=rand()%8;
    return hunderd*100+ten*10+one;
}

bool isRightAirplaneCombination(Airplane *airplane) {
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized when calling isRightAirplaneCombination!");
    string engine=airplane->getEngine();
    string size=airplane->getSize();
    string type=airplane->getType();
    if (engine=="propeller"){
        if(size=="small"){
            return type=="emergency"||type=="private";
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
