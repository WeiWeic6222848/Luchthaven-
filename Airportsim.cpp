//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include <string>
#include "Airportsim.h"

Airportsim::Airportsim(const string& filename) {
    addsourcefile(filename);
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

            for (TiXmlElement* childelement=Root->FirstChildElement();childelement!= nullptr;childelement=childelement->NextSiblingElement()){ string Elementname=childelement->Value();
                if(Elementname=="AIRPORT"){}
                else if (Elementname=="RUNWAY"&&childelement->FirstChildElement("name")&&childelement->FirstChildElement("airport")){
                    string name=childelement->FirstChildElement("name")->GetText();
                    string airport=childelement->FirstChildElement("airport")->GetText();
                    bool airportfound=false;
                    for (Airport air:Airports) {
                        if(air.getIata()==airport){
                            Runway* runway=new Runway(name,&air);
                            air.addrunway(runway);
                            Runways.push_back(runway);
                            airportfound=true;
                        }
                    }
                    if(!(airportfound)){
                        cerr<<"cannot find airpont:"<<airport<<" for the runway with name:"<<name<<endl;
                        errors++;
                        break;
                    }
                }
                else if (Elementname=="AIRPLANE"&&childelement->FirstChildElement("number")&&childelement->FirstChildElement("callsign")&&childelement->FirstChildElement("model")&&childelement->FirstChildElement("status")){
                    string number=childelement->FirstChildElement("number")->GetText();
                    string callsign=childelement->FirstChildElement("callsign")->GetText();
                    string model=childelement->FirstChildElement("model")->GetText();
                    string status=childelement->FirstChildElement("status")->GetText();
                    if(status!="approaching "&&status!="stand at gate"){
                        cerr<<"Airplane status of " + number+" is not correct"<<endl;
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
                    Airplane a(status,number,callsign,model,passengercapacity,passenger,fuel);
                    Airplanes.push_back(a);

                    if (status=="standing at gate"){
                        int gateforairplane=airport.findfreegates();
                        passenger=0;
                        if(gateforairplane==-1){
                            cerr<<"Airport not consistent"<<endl;
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
        cout<<filename +" read with "+ to_string(errors) +" errors"<<endl;
    }
    return;
}

const Airport &Airportsim::findairport(const string &iata) {
    for(Airport air:Airports){
        if(air.getIata()==iata){
            return air;
        }
    }
    cerr<<"no airport found with iata "+iata;
    return Airport();
}

const Airplane &Airportsim::findairplane(const string &number) {
    for (Airplane plane:Airplanes){
        if(plane.getNumber()==number){
            return plane;
        }
    }
    cerr<<"no airplane found with number "+number;
    return Airplane();
}

const Runway &Airportsim::findrunway(const string &number, const string &iata) {
    const Airport air=findairport(iata);
    for (Runway* run:air.getRunways()) {
        if(run->getName()==number){
            return *run;
        }
    }
    cerr<<"no runway found inside "+air.getName();
    return Runway();
}

Airportsim::Airportsim() {}
