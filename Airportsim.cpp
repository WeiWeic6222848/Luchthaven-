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
     }

     while (!Airplanes.empty()){
         vector<int> airplanestoremove;
         for (unsigned int j = 0; j < Airplanes.size(); ++j) {
             string status=Airplanes[j]->getStatus();
             Airplanes[j]->time();
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
             else if(status=="jobsdone"){
                 airplanestoremove.push_back(j);
             }
         }
         for (unsigned int i = 0; i < airplanestoremove.size(); ++i) {
             AirplanesFlying.push_back((Airplanes.begin()+airplanestoremove[i]-i).operator*());
             Airplanes.erase(Airplanes.begin()+airplanestoremove[i]-i);
         }
         for (unsigned int k = 0; k < Airports.size(); ++k) {
             Airports[k]->getTower().regulateApproachingplanes();
             Airports[k]->getTower().regulateTaxiingtoGate();
             Airports[k]->getTower().regulateTaxiingtorunway();
         }
     }

}


void Airportsim::landingstep(Airplane &approaching, Airport &airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling landing");
    REQUIRE(approaching.getStatus()=="Approaching","Airplane must has the status of Approaching when calling landing");
    ofstream outputfile;
    string filename="../output/"+approaching.getCallsign()+"_Landing.txt";
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
        outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
        approaching.fall();
    }
    else if(approaching.getHeight()==0&&!approaching.landing()){ ;
        outputfile<<approaching.getCallsign()<<" is landing at "<<airport.getName()<<" on runway "<<approaching.getDestinaterunway()->getName()<<endl;
    }
    else if (approaching.getHeight()==0&&approaching.landing()){
        outputfile<<approaching.getCallsign()<<" has landed at "<<airport.getName()<<" on runway "<<approaching.getDestinaterunway()->getName()<<endl;
        approaching.setLocation(approaching.getDestinaterunway());
        approaching.getDestinaterunway()->setPlaneAtEnd(&approaching);
        outputfile<<approaching.getCallsign()<<" is taxiing to Gates "<<endl;
        approaching.getDestinaterunway()->setCurrentairplane(NULL);
        //ask permission
        approaching.sendSignalTaxiingtoGate();
        approaching.setStatus("Taxiing to gate");
    }
    if (approaching.getHeight()==10000&&approaching.getPermission()!="10000"){
        outputfile<<approaching.getCallsign()<<" is approaching "<<airport.getName()<<" at 10000 ft."<<endl;
        approaching.sendSignalApproaching();
        //initial contact;
    }


}

void Airportsim::airplaneAtGatestep(Airplane &plane, Airport &airport) {
    ofstream outputfile;
    string filename="../output/"+plane.getCallsign()+"_AtGate.txt";
    outputfile.open(filename.data(),ios::app);
    if(plane.getStatus()=="Standing at gate"){
        if(plane.getCheckprocedure()==""){
            airport.addPassenger(plane.getPassenger());
            plane.setPassenger(0);
            outputfile<<plane.getPassenger()<<" passengers exited "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)->getName()<<" of "<<airport.getName()<<endl;
            plane.progressCheck();
        }
        else if(plane.getCheckprocedure()=="Technical control"){
            outputfile<<plane.getCallsign()<<" has been checked for technical malfunctions"<<endl;
            plane.progressCheck();
        }
        else if(plane.getCheckprocedure()=="Refueling"){
            outputfile<<plane.getCallsign()<<" has been refueled"<<endl;
            plane.progressCheck();
        }
        else if(plane.getCheckprocedure()=="Ready to leave"){
            //ask permission to leave gate;
            Gate* gate=airport.getGateFromAirplane(&plane);
            if(gate->getCurrentPlane()==&plane&&plane.sendSignalPushBack()){
                //leave gate at first time, will get a runway assigned if succes, if not then wait one more round.
                outputfile<<plane.getPassenger()<<" passengers boarded "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)->getName()<<" of "<<airport.getName()<<endl;
                plane.setPassenger(plane.getPassengerCapacity());
                gate->setPlaneNearGate(&plane);
                gate->setCurrentPlane(NULL);
            }
            else{
                plane.setDestinaterunway(NULL);
            }
            if(plane.sendSignalTaxiingtoRunway()){

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
    string filename="../output/"+taxiingplane.getCallsign()+"_Landing.txt";
    outputfile.open(filename.c_str(),ios::app);

    taxiingplane.getLocation()->setCrossing(false);
    vector<Location*> instruction=taxiingplane.getInstruction();
    taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());
    //if(taxiingplane.getLocation()==taxiingplane.getInstruction()[taxiingplane.getInstruction().size()-1]){
        //hold short
    //}
    if(taxiingplane.getLocation()->isOnuse()&&taxiingplane.getLocation()->isGate()){
        //only a gate location will be giving under this condition
        outputfile<<taxiingplane.getCallsign()<<" is standing at Gate "<<taxiingplane.getLocation()->getName()<<endl;
        taxiingplane.setStatus("Standing at gate");
    }
}

void Airportsim::taxiingToRunwaystep(Airplane &taxiingplane, Airport &airport) {
    ofstream outputfile;
    string filename="../output/"+taxiingplane.getCallsign()+"_Leaving.txt";
    outputfile.open(filename.c_str(),ios::app);
    Runway* destination=taxiingplane.getDestinaterunway();
    vector<Location*> instruction=taxiingplane.getInstruction();


    if(taxiingplane.getLocation()==destination&&taxiingplane.getDestinaterunway()->getPlaneAtbegin()==&taxiingplane){
        //removing cross marker sinds the plane is no more crossing but at the begin and ready to take off.
        taxiingplane.setStatus("Leaving");
        return;
    }
    else if(taxiingplane.getLocation()==destination){
        instruction.clear();
        instruction.push_back(taxiingplane.getLocation());
        instruction.push_back(taxiingplane.getLocation());
        taxiingplane.setInstruction(instruction);
        return;
    }

    taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());



}

void Airportsim::leavingstep(Airplane &leaving, Airport &airport) {
    ofstream outputfile;
    string filename="../output/"+leaving.getCallsign()+"_Leaving.txt";
    outputfile.open(filename.c_str(),ios::app);
    //ask leaving permission
    if (leaving.getHeight()==0&&leaving.getPermission()!="fly"){
        leaving.sendSignalLeaving();
    }
    else if(leaving.getHeight()==0&&leaving.getPermission()=="fly"&&leaving.takeOff()){
        outputfile<<leaving.getCallsign()<<" is taking off at "<<airport.getName()<<" on runway "<<leaving.getDestinaterunway()->getName()<<endl;
        leaving.rise();
        leaving.getDestinaterunway()->setCurrentairplane(NULL);
        if(leaving.getDestinaterunway()->getPlaneAtbegin()==&leaving){
            leaving.getDestinaterunway()->setPlaneAtbegin(NULL);
        }
        leaving.getDestinaterunway()->planeLeaved();
        leaving.setPermission("");
        leaving.setDestinaterunway(NULL);
    }
    else if(leaving.getHeight()>5000){
        outputfile<<leaving.getCallsign()<<" has left "<<airport.getName()<<endl;
        leaving.setStatus("jobsdone");
    }
    else if(leaving.getHeight()>=1000){
        //don't need permission anymore once it has rised;
        outputfile<<leaving.getCallsign()<<" ascended to "<<leaving.getHeight()<<" ft."<<endl;
        leaving.rise();
    }
}


