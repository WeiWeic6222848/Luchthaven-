//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include <string>
#include "Airportsim.h"
#include "DesignByContract.h"
#include "fstream"
#include "algorithm"
#include "AirportUtils.h"


Airportsim::Airportsim(const string& filename) {
    _InitCheck=this;
    addSourcefile(filename);
    ENSURE(ProperInitialized(),"This airportsim object failed to initialize properly");
}


/**
 * @param value a string of only digits
 * @return the int value of that string, logically
 */

void Airportsim::removeAirport(Airport* airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling removeairport");
    for (unsigned int i = 0; i < Airports.size(); ++i) {
        if (airport==Airports[i]){
            airport->cleanup();
            Airports.erase(Airports.begin()+i);
            break;
        }
    }
    ENSURE(find(Airports.begin(),Airports.end(),airport)==Airports.end(),"removeairport postcondition failed");
}


void Airportsim::addSourcefile(const string &filename) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addsourcefile");
    REQUIRE(fileExist(filename),"Giving filename must exist when calling addsourcefile");
    /*TiXmlDocument XMLfile;
    int errors=0;
    int aprroaching=0;
    XMLfile.LoadFile(filename.c_str());
    Airport* airport;
    if(XMLfile.Error()){
        cerr<<"this xml contains syntax error, trying to read as much as possible"<<endl;
    }
        TiXmlElement *Root = XMLfile.RootElement();
        if (Root) {
            TiXmlElement *airportelement=Root->FirstChildElement("AIRPORT");
            if (airportelement->FirstChildElement("name")&&airportelement->FirstChildElement("iata")&&airportelement->FirstChildElement("callsign")&&airportelement->FirstChildElement("gates")){
                try{
                    string name=airportelement->FirstChildElement("name")->GetText();
                    string iata=airportelement->FirstChildElement("iata")->GetText();
                    string callsign=airportelement->FirstChildElement("callsign")->GetText();
                    int gates;
                    try{gates=stoi(airportelement->FirstChildElement("gates")->GetText());}
                    catch(...){
                        cerr<< "Airport with name "+name+" has a number of gate which isn't a integer"<<endl;
                        return;
                    }
                    int passenger=0;
                    if (airportelement->FirstChildElement("passenger")) {
                        try {
                            passenger = stoi(airportelement->FirstChildElement("passenger")->GetText());
                        } catch (...) {
                            cerr << "Airport with name " + name + " has a passenger attribute which isn't a interger" << endl;
                            return;
                        }
                    }
                    airport=new Airport(name,iata,callsign,gates,passenger);
                    Airports.push_back(airport);
                }
                catch(...){
                    cerr<<"there's a syntax error at airport element";
                    return;
                }
            }
            else{
                cerr<<"airport doesn't have the required attributes";
                return;
            }

            for (TiXmlElement* childelement=Root->FirstChildElement();childelement!= NULL;childelement=childelement->NextSiblingElement()){ string Elementname=childelement->Value();
                if(Elementname=="AIRPORT"){}
                else if (Elementname=="RUNWAY"&&childelement->FirstChildElement("name")&&childelement->FirstChildElement("airport")){
                    string name=childelement->FirstChildElement("name")->GetText();
                    string airportname=childelement->FirstChildElement("airport")->GetText();
                    bool airportfound=false;
                    for (unsigned int i = 0; i < Airports.size(); ++i) {
                        if(Airports[i]->getIata()==airportname){
                            Runway* runway=new Runway(name,Airports[i]);
                            Airports[i]->addRunway(runway);
                            airportfound=true;
                        }
                    }
                    if(!(airportfound)){
                        cerr<<"cannot find airpont: "<<airportname<<" for the runway with name:"<<name<<endl;
                        cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                        errors++;
                        break;
                    }
                }
                else if (Elementname=="AIRPLANE"&&childelement->FirstChildElement("number")&&childelement->FirstChildElement("callsign")&&childelement->FirstChildElement("model")&&childelement->FirstChildElement("status")){
                    string number=childelement->FirstChildElement("number")->GetText();
                    string callsign=childelement->FirstChildElement("callsign")->GetText();
                    string model=childelement->FirstChildElement("model")->GetText();
                    string status=childelement->FirstChildElement("status")->GetText();
                    if(status!="Approaching"&&status!="Stand at gate"){
                        cerr<<"Airplane status of " + number+" is not correct"<<endl;
                        cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                        errors++;
                        break;
                    }
                    int passengercapacity=10;
                    if(childelement->FirstChildElement("passengercapacity")){
                        try {
                            passengercapacity = stoi(childelement->FirstChildElement("passengercapacity")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a passengercapacity attribute which isn't a interger"<<endl;
                            errors++;
                            continue;
                        }
                    }
                    int passenger=passengercapacity;

                    if(childelement->FirstChildElement("passenger")){
                        try {
                            passenger = stoi(childelement->FirstChildElement("passenger")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a passenger attribute which isn't a interger"<<endl;
                            errors++;
                            continue;
                        }
                    }

                    int fuel=100;
                    if(childelement->FirstChildElement("fuel")){
                        try {
                            fuel = stoi(childelement->FirstChildElement("fuel")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a fuel attribute which isn't a interger"<<endl;
                            errors++;
                            continue;
                        }
                    }
                    Airplane* a=new Airplane(status,passenger,fuel,number,callsign,model,passengercapacity);
                    Airplanes.push_back(a);

                    if (status=="standing at gate"){
                        int gateforairplane=airport->findFreeGates();
                        passenger=0;
                        if(gateforairplane==-1){
                            cerr<<airport->getName()<<" has more airplanes at gates than it's gate"<<endl;
                            cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                            break;
                        }
                        else{
                            airport->parkAirplane(gateforairplane,a);
                        }
                    }
                    else{
                        if(aprroaching==0){
                            aprroaching++;
                        }
                        else{
                            cerr<<airport->getName()<<" has more than one airplane approaching"<<endl;
                            cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                            break;
                        }
                    }
                    airport->addAirplane(a);
                }
                else{
                    cerr<<"element "+ Elementname+" is not recongized by the airsim system, skipping"<<endl;
                    errors++;
                    continue;
                }
            }
        }
    if(errors==0){
        cout<<filename +" read no error"<<endl;
    }else{
        cout<<filename +" read with " <<errors<< " errors"<<endl;
    }
    for (unsigned int j = 0; j < Airports.size(); ++j) {
        if (Airports[j]->getRunways().empty()) {
            cerr<<Airports[j]->getName()<<" has no runway or a wrong amount of runway."<<endl;
            cerr<<Airports[j]->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            removeAirport(Airports[j]);
        }
    }
    return;*/
    ofstream a;
    AirportsimImporter::importAirportsim(filename.c_str(),a,*this);
    cout<<a;
}

Airport* Airportsim::findAirport(const string &iata) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairport");
    for (unsigned int j = 0; j < Airports.size(); ++j) {
        if(Airports[j]->getIata()==iata){
            return Airports[j];
        }
    }
    cerr<<"no airport found with iata "+iata;
    return NULL;
}

Airplane *Airportsim::findAirplane(const string &number) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairplane");
    for (unsigned int j = 0; j < Airplanes.size(); ++j) {
        if(Airplanes[j]->getNumber()==number){
            return Airplanes[j];
        }
    }
    cerr<<"no airplane found with number "+number;
    return NULL;
}

Runway *Airportsim::findRunway(const string &number, const string &iata) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findrunway");
    Airport* air=findAirport(iata);
    if (air==NULL){
        cerr<<"cannot find the giving airport with iata "+iata;
        return NULL;
    }
    return air->findRunway(number);
}


const vector<Airport*> &Airportsim::getAirports() const {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirports");
    return Airports;
}

const vector<Airplane*> &Airportsim::getAirplanes() const {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirplanes");
    return Allplanes;
}
void Airportsim::landing(Airplane& approaching,Airport& airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling landing");
    REQUIRE(approaching.getStatus()=="Approaching","Airplane must has the status of Approaching when calling landing");
    ofstream outputfile;
    string filename="../output/"+approaching.getCallsign()+"_Landing.txt";
    outputfile.open(filename.data(),ios::out);
    outputfile<<approaching.getCallsign()<<" is approaching "<<airport.getName()<<" at 10.000 ft."<<endl;
    Gate* gate=airport.findFreeGates();
    Runway* runway=airport.findFreeRunway(&approaching);
    while (approaching.getHeight()>1000){
        approaching.fall();
        outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
    }
    approaching.fall();
    outputfile<<approaching.getCallsign()<<" is landing at "<<airport.getName()<<" on runway "<<runway->getName()<<endl;
    runway->setCurrentairplane(&approaching);
    outputfile<<approaching.getCallsign()<<" has landed at "<<airport.getName()<<" on runway "<<runway->getName()<<endl;
    airport.parkAirplane(gate,&approaching);
    outputfile<<approaching.getCallsign()<<" is taxiing to Gate "<<gate->getName()<<endl;
    runway->setCurrentairplane(NULL);
    outputfile<<approaching.getCallsign()<<" is standing at Gate "<<gate->getName()<<endl;
    approaching.setStatus("Standing at gate");
    outputfile.close();
    ENSURE(fileExist(filename),"landing postcondition failed");
}


void Airportsim::takingOff(Airplane& leaving, Airport& airport){
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling takingOff");
    REQUIRE(leaving.getStatus()=="Standing at gate","Airplane must has the status of Standing at gate when calling taking off");
    ofstream outputfile;
    string filename="../output/"+leaving.getCallsign()+"_TakingOff.txt";
    outputfile.open(filename.data(),ios::out);
    Gate* gate=airport.getGateFromAirplane(&leaving);
    outputfile<<leaving.getCallsign()<<" is standing at Gate "<<gate->getName()<<endl;
    Runway* runway=airport.findFreeRunway(&leaving);
    runway->setCurrentairplane(&leaving);
    airport.freeGate(gate);
    outputfile<<leaving.getCallsign()<<" is taxiing to runway "<<runway->getName()<<endl;
    outputfile<<leaving.getCallsign()<<" is taking off at "<<airport.getName()<<" on runway "<<runway->getName()<<endl;
    for(int i=1;i<6;i++){
        outputfile<<leaving.getCallsign()<<" ascended to "<<i<<".000 ft."<<endl;
    }
    runway->setCurrentairplane(NULL);
    leaving.setStatus("Approaching");
    outputfile<<leaving.getCallsign()<<" has left "<<airport.getName();
    outputfile.close();
    ENSURE(fileExist(filename),"takingOff postcondition failed");
}

void Airportsim::airplaneAtGate(Airplane& plane,Airport& airport){
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling AirplaneAtGate");
    ofstream outputfile;
    string filename="../output/"+plane.getCallsign()+"_AtGate.txt";
    outputfile.open(filename.data(),ios::out);
    if(plane.getStatus()=="Standing at gate"){
        outputfile<<plane.getPassenger()<<" passengers exited "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)<<" of "<<airport.getName()<<endl;
        outputfile<<plane.getCallsign()<<" has been checked for technical malfunctions"<<endl;
        outputfile<<plane.getCallsign()<<" has been refueled"<<endl;
        outputfile<<plane.getPassenger()<<" passengers boarded "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)<<" of "<<airport.getName()<<endl;
    }
    ENSURE(fileExist(filename),"AirplaneAtGate postcondition failed");
}

bool Airportsim::ProperInitialized() const{
    return _InitCheck==this;
}

Airportsim::Airportsim(int argc, const char **argv) {
    _InitCheck=this;
    for (int i = 1; i < argc; ++i) {
        addSourcefile(argv[i]);
    };
    ENSURE(ProperInitialized(),"Airportsim object failed to initialize properly");
}

Airportsim::~Airportsim() {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling Destructor");
    for (unsigned int i = 0; i < Airports.size(); ++i) {
        delete Airports[i];
    }
    for (unsigned int j = 0; j < Airplanes.size(); ++j) {
        delete Airplanes[j];
    }
}

void Airportsim::addAirport(Airport *airport) {
    Airports.push_back(airport);
}

void Airportsim::addAirplane(Airplane *airplane) {
    Airplanes.push_back(airplane);
    Allplanes.push_back(airplane);
}

Airportsim::Airportsim() {_InitCheck=this;}



 //future functions
void Airportsim::Simulate() {

    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling Destructor");
     ofstream file;
     for (unsigned int k = 0; k < Airports.size(); ++k) {
         string filename="../output/"+Airports[k]->getIata()+"_Tower.txt";
         file.open(filename.c_str(),ios::out);
         file.close();
     }

     for (unsigned int l = 0; l < Airplanes.size(); ++l) {
         string filename="../output/"+Airplanes[l]->getCallsign()+".txt";
         file.open(filename.c_str(),ios::out);
         file.close();
     }
     vector<int> airplanestoremove;
     bool  alreadypushed=false;
     int chillingcounter=0;

     while (!Airplanes.empty()){
         airplanestoremove.clear();
         string status;
         //while still plane with action = current time;
         //loop through all those planes to get them something to do;

         for (unsigned int j = 0; j < Airplanes.size(); ++j) {
             alreadypushed=false;
             chillingcounter=0;
             do{
                 status=Airplanes[j]->getStatus();
                 chillingcounter++;
                 if(status=="Approaching"||status=="Landed"){
                     landingstep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Standing at gate"){
                     airplaneAtGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Taxiing to gate"){
                     taxiingToGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Leaving"){
                     leavingstep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Taxiing to runway"){
                     taxiingToRunwaystep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="jobsdone"&&!alreadypushed){
                     airplanestoremove.push_back(j);
                     alreadypushed=true;
                 }
             }while(Airplanes[j]->isDoingNothing()&&chillingcounter<3);
             Airplanes[j]->timeRuns();

/*
             if(Airplanes[j]->isDoingNothing()){
                 //reruns code to get new job.
                 if(status=="Approaching"){
                     landingstep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Standing at gate"){
                     airplaneAtGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Taxiing to gate"){
                     taxiingToGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Leaving"){
                     leavingstep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="Taxiing to runway"){
                     taxiingToRunwaystep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status=="jobsdone"&&!alreadypushed){
                     airplanestoremove.push_back(j);
                 }
                 */
             }
         for (unsigned int k = 0; k < Airports.size(); ++k) {
             chillingcounter=0;
             do{
                 chillingcounter++;
                 bool doingnothing=Airports[k]->getTower().isDoingNothing();
                 Airports[k]->getTower().sendSignal();
                 if(Airports[k]->getTower().isDoingNothing()!=doingnothing){
                     if(doingnothing==true){
                         break;
                     }
                 }
                 Airports[k]->getTower().regulateApproachingplanes();
                 if(Airports[k]->getTower().isDoingNothing()!=doingnothing){
                     if(doingnothing==true){
                         break;
                     }
                 }
                 Airports[k]->getTower().regulateLeavingplanes();
                 if(Airports[k]->getTower().isDoingNothing()!=doingnothing){
                     if(doingnothing==true){
                         break;
                     }
                 }
             }while(Airports[k]->getTower().isDoingNothing()&&chillingcounter<3);

             Airports[k]->getTower().timeRuns();
             /*
             bool doingsth=!Airports[k]->getTower().isDoingNothing();
             if(doingsth){
                     Airports[k]->getTower().sendSignal();
                     if(Airports[k]->getTower().isDoingNothing()){
                         goto HELP;
                     }
                     Airports[k]->getTower().regulateApproachingplanes();
                     if(Airports[k]->getTower().isDoingNothing()){
                         goto HELP;
                     }
                     Airports[k]->getTower().regulateLeavingplanes();
             }
             HELP:
             if(Airports[k]->getTower().isDoingNothing()){
                 chillingcounter=0;
                 do{
                     chillingcounter++;
                     Airports[k]->getTower().sendSignal();
                 }while(Airports[k]->getTower().isDoingNothing()&&chillingcounter<3);
                 chillingcounter=0;
                 if(!Airports[k]->getTower().isDoingNothing()){
                     Airports[k]->getTower().timeRuns();
                     continue;
                 }
                 do{
                     chillingcounter++;
                     Airports[k]->getTower().regulateApproachingplanes();
                 }while(Airports[k]->getTower().isDoingNothing()&&chillingcounter<3);
                 chillingcounter=0;
                 if(!Airports[k]->getTower().isDoingNothing()){
                     Airports[k]->getTower().timeRuns();
                     continue;
                 }
                 do{
                     chillingcounter++;
                     Airports[k]->getTower().regulateLeavingplanes();
                 }while(Airports[k]->getTower().isDoingNothing()&&chillingcounter<3);
             }

             Airports[k]->getTower().timeRuns();*/

/*

             if(Airports[k]->getTower().isDoingNothing()){

                 Airports[k]->getTower().regulateApproachingplanes();
                 Airports[k]->getTower().sendSignal();
                 Airports[k]->getTower().regulateLeavingplanes();
             }
*/
         }


/*
     //rerun code for seeking jobs;
         for (unsigned int j = 0; j < Airplanes.size(); ++j) {
             if (Airplanes[j]->isDoingNothing()) {
                 status = Airplanes[j]->getStatus();
                 //reruns code to get new job.
                 if (status == "Approaching") {
                     landingstep(*Airplanes[j], *Airplanes[j]->getDestination());
                 } else if (status == "Standing at gate") {
                     airplaneAtGatestep(*Airplanes[j], *Airplanes[j]->getDestination());
                 } else if (status == "Taxiing to gate") {
                     taxiingToGatestep(*Airplanes[j], *Airplanes[j]->getDestination());
                 } else if (status == "Leaving") {
                     leavingstep(*Airplanes[j], *Airplanes[j]->getDestination());
                 } else if (status == "Taxiing to runway") {
                     taxiingToRunwaystep(*Airplanes[j], *Airplanes[j]->getDestination());
                 } else if (status == "jobsdone" && !alreadypushed) {
                     airplanestoremove.push_back(j);
                 }
             }
         }
         for (unsigned int k = 0; k < Airports.size(); ++k) {
             if (Airports[k]->getTower().isDoingNothing()) {
                 Airports[k]->getTower().regulateApproachingplanes();
                 Airports[k]->getTower().sendSignal();
                 Airports[k]->getTower().regulateLeavingplanes();
             }
         }*/

         for (unsigned int i = 0; i < airplanestoremove.size(); ++i) {
             AirplanesFlying.push_back((Airplanes.begin() + airplanestoremove[i] - i).operator*());
             Airplanes.erase(Airplanes.begin() + airplanestoremove[i] - i);
         }
         currentTime=currentTime++;
     }

}


void Airportsim::landingstep(Airplane &approaching, Airport &airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling landing");
    REQUIRE(approaching.getStatus()=="Approaching"||approaching.getStatus()=="Landed","Airplane must has the status of Approaching when calling landing");
    ofstream outputfile;

    string filename="../output/"+approaching.getCallsign()+".txt";

    outputfile.open(filename.c_str(),ios::app);

    if (approaching.getHeight()>5000&&approaching.getPermission()=="5000"){//getting permission
        approaching.fall();
        outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
    }

    else if(approaching.getHeight()>3000&&approaching.getPermission()=="3000"){
        approaching.fall();
        outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
    }

    else if(approaching.getHeight()>=1000&&approaching.getPermission()=="0"){
        //on getting permission landing, a runway will be on use
        approaching.fall();
        if(approaching.getHeight()!=0&&approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
        }
    }



    else if (approaching.getHeight()==0&&approaching.getStatus()!="Landed"){
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" is landing at "<<airport.getName()<<" on runway "<<approaching.getDestinaterunway()->getName()<<endl;
        }
        approaching.landing();
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" has landed at "<<airport.getName()<<" on runway "<<approaching.getDestinaterunway()->getName()<<endl;
            approaching.setLocation(approaching.getDestinaterunway());
            approaching.getDestinaterunway()->setPlaneAtEnd(&approaching);
        }
        //ask permission
    }
    else if(approaching.getStatus()=="Landed"){
        approaching.sendSignalTaxiingtoGate();
        if(approaching.getPermission()=="Taxiing"){
            outputfile<<approaching.getCallsign()<<" is taxiing to Gates "<<endl;
            approaching.getDestinaterunway()->setCurrentairplane(NULL);
            approaching.setStatus("Taxiing to gate");
        };
    }
    if (approaching.getHeight()==10000&&approaching.getPermission()!="10000"){
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" is approaching "<<airport.getName()<<" at 10000 ft."<<endl;
        }
        approaching.sendSignalApproaching();
        //initial contact;
    }


}

void Airportsim::airplaneAtGatestep(Airplane &plane, Airport &airport) {
    ofstream outputfile;
    string filename="../output/"+plane.getCallsign()+".txt";
    outputfile.open(filename.data(),ios::app);
    if(plane.getStatus()=="Standing at gate"){
        if(plane.getCheckprocedure()=="Just landed"){
            plane.progressCheck();
            if(plane.isDoingNothing()){
                airport.addPassenger(plane.getPassenger());
                outputfile<<plane.getPassenger()<<" passengers exited "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)->getName()<<" of "<<airport.getName()<<endl;
                plane.setPassenger(0);
            }
        }

        else if(plane.getCheckprocedure()=="Technical control"){
            plane.progressCheck();
            if(plane.isDoingNothing()){
                outputfile<<plane.getCallsign()<<" has been checked for technical malfunctions"<<endl;
            }
        }
        else if(plane.getCheckprocedure()=="Refueling"){
            plane.progressCheck();
            if(plane.isDoingNothing()) {
                outputfile << plane.getCallsign() << " has been refueled" << endl;
            }
        }
        else if(plane.getCheckprocedure()=="Boarding"){
            plane.progressCheck();
            if(plane.isDoingNothing()) {
                plane.setPassenger(plane.getPassengerCapacity());
                outputfile<<plane.getPassenger()<<" passengers boarded "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)->getName()<<" of "<<airport.getName()<<endl;
            }
        }
        else if(plane.getCheckprocedure()=="Ready to leave"){
            //ask permission to leave gate;
            Gate* gate=airport.getGateFromAirplane(&plane);
            if(plane.getPermission()!="IFR clearancy"&&plane.getPermission()!="Push back"&&plane.getPermission()!="Taxiing"){
                plane.sendSignalIFR();
            }
            else if(plane.getPermission()!="Push back"&&plane.getPermission()!="Taxiing"){
                plane.sendSignalPushBack();
            }
            else if(gate->getCurrentPlane()==&plane&&plane.getPermission()=="Push back"){
                    if(plane.pushBack()){
                        //leave gate at first time, will get a runway assigned if succes, if not then wait one more round.
                        gate->setPlaneNearGate(&plane);
                        gate->setCurrentPlane(NULL);
                    }//care, maybe syntax problems. idk?
                }
            else if(plane.getPermission()!="Taxiing"){
                plane.sendSignalTaxiingtoRunway();
            }
            else if(plane.getPermission()=="Taxiing"){
                plane.resetCheckProcedure();
                //ask permission, if there is a runway available just go there.
                plane.setStatus("Taxiing to runway");
                gate->setPlaneNearGate(NULL);
                outputfile<<plane.getCallsign()<<" is standing at Gate "<<gate->getName()<<endl;
                outputfile<<plane.getCallsign()<<" is taxiing to runway "<<plane.getDestinaterunway()->getName()<<endl;//add here
            }
        }
    }
}

void Airportsim::taxiingToGatestep(Airplane &taxiingplane, Airport &airport) {
        ofstream outputfile;
        string filename="../output/"+taxiingplane.getCallsign()+".txt";
        outputfile.open(filename.c_str(),ios::app);
        vector<Location*> instruction=taxiingplane.getInstruction();

        if(taxiingplane.getLocation()->isOnuse()&&taxiingplane.getLocation()->isGate()){
            //only a gate location will be giving under this condition
            outputfile<<taxiingplane.getCallsign()<<" is standing at Gate "<<taxiingplane.getLocation()->getName()<<endl;
            taxiingplane.setStatus("Standing at gate");
        }
        else if(taxiingplane.getLocation()==taxiingplane.getDestinaterunway()){
            if(taxiingplane.crossingRunway()){
                taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());
                taxiingplane.getDestinaterunway()->setPlaneAtEnd(NULL);
                taxiingplane.setDestinaterunway(NULL);
            }
        }
        else if(!taxiingplane.getLocation()->isRunway()){
            if(taxiingplane.taxiing()){
                taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());
            }
        }
        else if(taxiingplane.getLocation()->isRunway()&&taxiingplane.getPermission()!="Cleared to cross"){
            taxiingplane.sendSignalCrossingRunway();
        }
        else if(taxiingplane.getPermission()=="Cleared to cross"&&taxiingplane.getLocation()->isRunway()){
            if(taxiingplane.crossingRunway()){
                taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());
            }
        }
    //if(taxiingplane.getLocation()==taxiingplane.getInstruction()[taxiingplane.getInstruction().size()-1]){
        //hold short
        //}


}

void Airportsim::taxiingToRunwaystep(Airplane &taxiingplane, Airport &airport) {
        ofstream outputfile;
        string filename = "../output/" + taxiingplane.getCallsign() + ".txt";
        outputfile.open(filename.c_str(), ios::app);
        Runway *destination = taxiingplane.getDestinaterunway();
        vector<Location *> instruction = taxiingplane.getInstruction();

        if (taxiingplane.getLocation() == destination && (taxiingplane.getPermission()=="Line up"||taxiingplane.getPermission()=="Fly")) {
            if(taxiingplane.liningUp()){
                /*
                destination->setPlaneAtbegin(&taxiingplane);
                if(taxiingplane.getPermission()=="Fly"){
                    destination->setCurrentairplane(&taxiingplane);
                }
                 */
                taxiingplane.setStatus("Leaving");
            }
        }
        else if (taxiingplane.getLocation() == destination&&!(taxiingplane.getPermission()=="Line up"||taxiingplane.getPermission()=="Fly")) {
            taxiingplane.sendSignalAtRunway();
        }
        else if (!taxiingplane.getLocation()->isRunway()) {
            if(taxiingplane.taxiing()){
                taxiingplane.setLocation((find(instruction.begin(), instruction.end(), taxiingplane.getLocation()) + 1).operator*());
            }
        }
        else if (taxiingplane.getLocation()->isRunway()&&taxiingplane.getPermission()!="Cleared to cross"){
            taxiingplane.sendSignalCrossingRunway();
        }
        else if(taxiingplane.getLocation()->isRunway()&&taxiingplane.getPermission()=="Cleared to cross"){
            if(taxiingplane.crossingRunway()){
                taxiingplane.setLocation((find(instruction.begin(), instruction.end(), taxiingplane.getLocation()) + 1).operator*());
            }
        }
}

void Airportsim::leavingstep(Airplane &leaving, Airport &airport) {
    ofstream outputfile;
    string filename="../output/"+leaving.getCallsign()+".txt";
    outputfile.open(filename.c_str(),ios::app);
    //ask leaving permission

    if(leaving.getHeight()==0&&leaving.getPermission()=="Fly"&&leaving.getDestinaterunway()==NULL){
        leaving.rise();
    }
    else if(leaving.getHeight()==0&&leaving.getPermission()=="Fly"){
        if(leaving.isDoingNothing()){
            outputfile<<leaving.getCallsign()<<" is taking off at "<<airport.getName()<<" on runway "<<leaving.getDestinaterunway()->getName()<<endl;
        }
        if(leaving.takeOff()){
            leaving.getDestinaterunway()->planeLeaved();
            leaving.getDestinaterunway()->setCurrentairplane(NULL);
            if(leaving.getDestinaterunway()->getPlaneAtbegin()==&leaving){
                leaving.getDestinaterunway()->setPlaneAtbegin(NULL);
            }
            leaving.setDestinaterunway(NULL);
            airport.getTower().getFile()<<"airplane "<<leaving.getCallsign()<< " left"<<currentTime<<endl;
        }
        //test purpose
    }
    else if(leaving.getHeight()>5000&&leaving.getPermission()=="Fly"){
        outputfile<<leaving.getCallsign()<<" has left "<<airport.getName()<<endl;
        leaving.setPermission("");
        leaving.setStatus("jobsdone");
    }
    else if(leaving.getHeight()>=1000&&leaving.getPermission()=="Fly"){
        //don't need permission anymore once it has rised;
        if(leaving.isDoingNothing()){
            outputfile<<leaving.getCallsign()<<" ascended to "<<leaving.getHeight()<<" ft."<<endl;
        }
        leaving.rise();
    }
    else if (leaving.getHeight()==0&&leaving.getPermission()!="Fly"){
        //await for signal;
    }
}

const Time &Airportsim::getCurrentTime() const {
    return currentTime;
}

void Airportsim::setCurrentTime(const Time &currentTime) {
    Airportsim::currentTime = currentTime;
}

void Airportsim::generateFloorPlan(Airport &vlieghaven, int i) {
    REQUIRE(vlieghaven.ProperInitialized(), "airport wasn't initialized when calling writeToFile");
    ofstream outputfile;
    string filename = "../output/floormap_state_airport[" + vlieghaven.getIata() + "]v"+to_string(i)+".txt";
    outputfile.open(filename.c_str(), ios::out);
    for (unsigned int i = 0; i < vlieghaven.getRunways().size(); i++) {
        Runway *runway = vlieghaven.getRunways()[vlieghaven.getRunways().size() - 1 - i];
        outputfile << runway->getName() << " | ";
        if (runway->isOnuse()) {
            outputfile << "====V=====" << endl;
        } else {
            outputfile << "==========" << endl;
        }
        outputfile << "TP" << runway->getTaxipoint()->getName()[0] << " | " << endl;
    }
    outputfile << "Gates [";
    for (unsigned int i = 0; i < vlieghaven.getGates().size(); i++) {
        Gate *gate = vlieghaven.getGates()[i];
        if (gate->isOnuse()) {
            outputfile << "V";
        } else {
            outputfile << " ";
        }
    }
    outputfile << "]" << endl;
    outputfile.close();
    ENSURE(fileExist(filename.c_str()), "writeToFile postcondition failed");
}


