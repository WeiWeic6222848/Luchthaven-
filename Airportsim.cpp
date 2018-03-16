//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include <string>
#include "Airportsim.h"
#include "DesignByContract.h"
#include "fstream"

Airportsim::Airportsim(const string& filename) {
    addsourcefile(filename);
}

int stoi(const string &value){
    int temp=atoi(value.c_str());
    if(temp==0&&value!="0"){
        throw "stoi failed beacause the giving string is not a digit";
    }
    return temp;
}


void Airportsim::removeairport(Airport& airport) {
    for (unsigned int i = 0; i < Airports.size(); ++i) {
        if (&airport==&Airports[i]){
            airport.cleanup();
            Airports.erase(Airports.begin()+i);
            break;
        }
    }
}


void Airportsim::addsourcefile(const string &filename) {
    TiXmlDocument XMLfile;
    int errors=0;
    int aprroaching=0;
    XMLfile.LoadFile(filename.c_str());
    Airport airport;
        TiXmlElement *Root = XMLfile.RootElement();
        if (Root) {
            TiXmlElement *airportelement=Root->FirstChildElement("AIRPORT");
            if (airportelement->FirstChildElement("name")&&airportelement->FirstChildElement("iata")&&airportelement->FirstChildElement("callsign")&&airportelement->FirstChildElement("gates")){
                try{
                    string name=airportelement->FirstChildElement("name")->GetText();
                    string iata=airportelement->FirstChildElement("iata")->GetText();
                    string callsign=airportelement->FirstChildElement("callsign")->GetText();
                    int gates;
                    cout<<airportelement->FirstChildElement("gates")->GetText();
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
                    airport=Airport(name,iata,callsign,gates,passenger);
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
                        if(Airports[i].getIata()==airportname){
                            Runway* runway=new Runway(name,&Airports[i]);
                            Airports[i].addrunway(runway);
                            Runways.push_back(runway);
                            airportfound=true;
                        }
                    }
                    if(!(airportfound)){
                        cerr<<"cannot find airpont: "<<airportname<<" for the runway with name:"<<name<<endl;
                        cerr<<airport.getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
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
                        cerr<<airport.getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
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
                    Airplane a(status,passenger,fuel,number,callsign,model,passengercapacity);
                    Airplanes.push_back(a);

                    if (status=="standing at gate"){
                        int gateforairplane=airport.findfreegates();
                        passenger=0;
                        if(gateforairplane==-1){
                            cerr<<airport.getName()<<" has more airplanes at gates than it's gate"<<endl;
                            cerr<<airport.getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                            break;
                        }
                        else{
                            airport.parkAirplane(gateforairplane,&a);
                        }
                    }
                    else{
                        if(aprroaching==0){
                            aprroaching++;
                        }
                        else{
                            cerr<<airport.getName()<<" has more than one airplane approaching"<<endl;
                            cerr<<airport.getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                            break;
                        }
                    }
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
        if (Airports[j].getRunways().empty()) {
            cerr<<Airports[j].getName()<<" has no runway or a wrong amount of runway."<<endl;
            cerr<<Airports[j].getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            removeairport(Airports[j]);
        }
    }
    return;
}

const Airport* Airportsim::findairport(const string &iata) {
    for (unsigned int j = 0; j < Airports.size(); ++j) {
        if(Airports[j].getIata()==iata){
            return &Airports[j];
        }
    }
    cerr<<"no airport found with iata "+iata;
    return NULL;
}

const Airplane *Airportsim::findairplane(const string &number) {
    for (unsigned int j = 0; j < Airplanes.size(); ++j) {
        if(Airplanes[j].getNumber()==number){
            return &Airplanes[j];
        }
    }
    cerr<<"no airplane found with number "+number;
    return NULL;
}

const Runway *Airportsim::findrunway(const string &number, const string &iata) {
    const Airport* air=findairport(iata);
    ENSURE(air!=NULL,"cannot find the giving airport with iata");
    for (unsigned int i = 0; i < air->getRunways().size(); ++i) {
        if (air->getRunways()[i]->getName()==number){
            return air->getRunways()[i];
        }
    }
    cerr<<"no runway found inside "+air->getName();
    return NULL;
}

Airportsim::Airportsim() {}

const vector<Airport> &Airportsim::getAirports() const {
    return Airports;
}

const vector<Airplane> &Airportsim::getAirplanes() const {
    return Airplanes;
}
void Airportsim::landing( Airplane& aproaching, Airport& airport) {
    if(aproaching.getStatus()=="Approaching"){
        ofstream outputfile;
        string filename="../output/"+aproaching.getCallsign()+"_Landing.txt";
        outputfile.open(filename.data(),ios::out);
        outputfile<<aproaching.getCallsign()<<" is approaching "<<airport.getName()<<" at 10.000 ft."<<endl;
        int gate=airport.findfreegates();
        Runway* runway=airport.findfreerunway();
        for(int i=9;i>0;i--){
            outputfile<<aproaching.getCallsign()<<" descended to "<<i<<".000 ft."<<endl;
        }
        runway->setCurrentairplane(&aproaching);
        outputfile<<aproaching.getCallsign()<<" is landing at "<<airport.getName()<<" on runway "<<runway->getName()<<endl;
        outputfile<<aproaching.getCallsign()<<" has landed at "<<airport.getName()<<" on runway "<<runway->getName()<<endl;
        airport.parkAirplane(gate,&aproaching);
        outputfile<<aproaching.getCallsign()<<" is taxiing to Gate "<<gate<<endl;
        runway->setCurrentairplane(NULL);
        outputfile<<aproaching.getCallsign()<<" is standing at Gate "<<gate<<endl;
        aproaching.setStatus("Standing at gate");
        outputfile.close();
    }
}
void Airportsim::takingOff(Airplane& aproaching, Airport& airport){
    if(aproaching.getStatus()=="Standing at gate"){
        ofstream outputfile;
        string filename="../output/"+aproaching.getCallsign()+"_TakingOff.txt";
        outputfile.open(filename.data(),ios::out);
        outputfile<<aproaching.getCallsign()<<" is standing at Gate"<<" gate nummer"<<endl; //nummer huidige gate toegevoegd functie nodig
        Runway* runway=airport.findfreerunway();
        runway->setCurrentairplane(&aproaching);
        //gate moet vrij komen
        outputfile<<aproaching.getCallsign()<<" is taxiing to runway "<<runway->getName()<<endl;
        outputfile<<aproaching.getCallsign()<<" is taking off at "<<airport.getName()<<" on runway "<<runway->getName()<<endl;
        for(int i=1;i<6;i++){
            outputfile<<aproaching.getCallsign()<<" ascended to "<<i<<".000 ft."<<endl;
        }
        runway->setCurrentairplane(NULL);
        aproaching.setStatus("Approaching");
        outputfile<<aproaching.getCallsign()<<" has left "<<airport.getName();
        outputfile.close();


    }
}

