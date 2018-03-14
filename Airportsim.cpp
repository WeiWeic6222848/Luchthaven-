//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include "Airportsim.h"

Airportsim::Airportsim(const string& filename) {
    addsourcefile(filename);
}

void Airportsim::addsourcefile(const string &filename) {

    TiXmlDocument XMLfile(filename.c_str());
    if (XMLfile.LoadFile()) {
        TiXmlElement *Root = XMLfile.RootElement();
        if (Root) {
            for (TiXmlElement* childelement=Root->FirstChildElement();childelement!= nullptr;childelement=childelement->NextSiblingElement()){
                string Elementname=childelement->Value();
                if (Elementname=="AIRPORT"){
                    string name=childelement->FirstChildElement("name")->GetText();
                    string iata=childelement->FirstChildElement("iata")->GetText();
                    string callsign=childelement->FirstChildElement("callsign")->GetText();
                    int gates;
                    try{gates=stoi(childelement->FirstChildElement("gates")->GetText());}
                    catch(...){
                        cerr<<"Airport with name "+name+" has a number of gate which isn't a integer"<<endl;
                        continue;
                    }
                    int passenger=0;
                    if (childelement->FirstChildElement("passenger")){
                        try {
                            passenger = stoi(childelement->FirstChildElement("passenger")->GetText());
                        }catch (...){
                            cerr<<"Airport with name "+name+" has a passenger attribute which isn't a interger"<<endl;
                            continue;
                        }
                    }
                    cout<<name<<iata<<callsign<<gates<<passenger<<endl;
                    Airport tempair(name,iata,callsign,gates,passenger);
                    Airports.push_back(tempair);
                }
                else if (Elementname=="RUNWAY"){
                    string name=childelement->FirstChildElement("name")->GetText();
                    string airport=childelement->FirstChildElement("airport")->GetText();
                    cout<<name<<airport;
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
                        continue;
                    }
                }
                else if (Elementname=="AIRPLANE"){
                    string number=childelement->FirstChildElement("number")->GetText();
                    string callsign=childelement->FirstChildElement("callsign")->GetText();
                    string model=childelement->FirstChildElement("model")->GetText();
                    string status=childelement->FirstChildElement("status")->GetText();
                    int passengercapacity=10;
                    if(childelement->FirstChildElement("passengercapacity")){
                        try {
                            passengercapacity = stoi(childelement->FirstChildElement("passengercapacity")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a passengercapacity attribute which isn't a interger"<<endl;
                            continue;
                        }
                    }
                    int passenger=passengercapacity;
                    if (status=="standing at gate"){
                        passenger=0;
                    }

                    if(childelement->FirstChildElement("passenger")){
                        try {
                            passenger = stoi(childelement->FirstChildElement("passenger")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a passenger attribute which isn't a interger"<<endl;
                            continue;
                        }
                    }

                    int fuel=100;
                    if(childelement->FirstChildElement("fuel")){
                        try {
                            fuel = stoi(childelement->FirstChildElement("fuel")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a fuel attribute which isn't a interger"<<endl;
                            continue;
                        }
                    }
                    Airplane a(status,number,callsign,model,passengercapacity,passenger,fuel);
                    Airplanes.push_back(a);
                }
                else{
                    cerr<<"element "+ Elementname+" is not recongized by the airsim system, skipping"<<endl;
                    continue;
                }
            }
        }
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
    return nullptr;
}

const Airplane &Airportsim::findairplane(const string &number) {
    for (Airplane plane:Airplanes){
        if(plane.getNumber()==number){
            return plane;
        }
    }
    cerr<<"no airplane found with number "+number;
    return nullptr;
}

const Runway &Airportsim::findrunway(const string &number, const string &iata) {
    const Airport air=findairport(iata);
    for (Runway* run:air.getRunways()) {
        if(run->getName()==number){
            return *run;
        }
    }
    cerr<<"no runway found inside "+air.getName();
    return nullptr;
}
