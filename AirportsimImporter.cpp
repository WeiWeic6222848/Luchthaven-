//
// Created by c6222848 on 4/3/18.
//

#include "DesignByContract.h"
#include "AirportUtils.h"

Esucces AirportsimImporter::importAirportsim(const char *inputfilename, std::ostream &errStream, Airportsim &sim) {

    REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling addsourcefile");
    REQUIRE(fileExist(inputfilename),"Giving filename must exist when calling addsourcefile");
    TiXmlDocument XMLfile;
    int errors=0;
    int aprroaching=0;
    XMLfile.LoadFile(inputfilename);
    Airport* airport;
    if(XMLfile.Error()){
        errStream<<"this xml contains syntax error, trying to read as much as possible"<<endl;
        errors++;;
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
                    errStream<< "Airport with name "+name+" has a number of gate which isn't a integer"<<endl;
                    return ImportAborted;
                }
                int passenger=0;
                if (airportelement->FirstChildElement("passenger")) {
                    try {
                        passenger = stoi(airportelement->FirstChildElement("passenger")->GetText());
                    } catch (...) {
                        errStream << "Airport with name " + name + " has a passenger attribute which isn't a interger" << endl;
                        return ImportAborted;
                    }
                }
                airport=new Airport(name,iata,callsign,gates,passenger);
                sim.addAirport(airport);
            }
            catch(...){
                errStream<<"there's a syntax error at airport element";
                return ImportAborted;
            }
        }
        else{
            errStream<<"airport doesn't have the required attributes";
            return ImportAborted;
        }

        for (TiXmlElement* childelement=Root->FirstChildElement();childelement!= NULL;childelement=childelement->NextSiblingElement()){ string Elementname=childelement->Value();
            if(Elementname=="AIRPORT"){}
            else if (Elementname=="RUNWAY"&&childelement->FirstChildElement("name")&&childelement->FirstChildElement("airport")){
                string name=childelement->FirstChildElement("name")->GetText();
                string airportname=childelement->FirstChildElement("airport")->GetText();
                bool airportfound=false;
                for (unsigned int i = 0; i < sim.getAirports().size(); ++i) {
                    if(sim.getAirports()[i]->getIata()==airportname){
                        Runway* runway=new Runway(name,sim.getAirports()[i]);
                        sim.getAirports()[i]->addRunway(runway);
                        airportfound=true;
                    }
                }
                if(!(airportfound)){
                    errStream<<"cannot find airpont: "<<airportname<<" for the runway with name:"<<name<<endl;
                    errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
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
                    errStream<<"Airplane status of " + number+" is not correct"<<endl;
                    errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                    errors++;
                    break;
                }
                int passengercapacity=10;
                if(childelement->FirstChildElement("passengercapacity")){
                    try {
                        passengercapacity = stoi(childelement->FirstChildElement("passengercapacity")->GetText());
                    }catch (...){
                        errStream<<"Airplane with number "+number+" has a passengercapacity attribute which isn't a interger"<<endl;
                        errors++;
                        continue;
                    }
                }
                int passenger=passengercapacity;

                if(childelement->FirstChildElement("passenger")){
                    try {
                        passenger = stoi(childelement->FirstChildElement("passenger")->GetText());
                    }catch (...){
                        errStream<<"Airplane with number "+number+" has a passenger attribute which isn't a interger"<<endl;
                        errors++;
                        continue;
                    }
                }

                int fuel=100;
                if(childelement->FirstChildElement("fuel")){
                    try {
                        fuel = stoi(childelement->FirstChildElement("fuel")->GetText());
                    }catch (...){
                        errStream<<"Airplane with number "+number+" has a fuel attribute which isn't a interger"<<endl;
                        errors++;
                        continue;
                    }
                }
                Airplane* a=new Airplane(status,passenger,fuel,number,callsign,model,passengercapacity);
                sim.addAirplane(a);

                if (status=="standing at gate"){
                    int gateforairplane=airport->findFreeGates();
                    passenger=0;
                    if(gateforairplane==-1){
                        errStream<<airport->getName()<<" has more airplanes at gates than it's gate"<<endl;
                        errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
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
                        errStream<<airport->getName()<<" has more than one airplane approaching"<<endl;
                        errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                        break;
                    }
                }
                airport->addAirplane(a);
            }
            else{
                errStream<<"element "+ Elementname+" is not recongized by the airsim system, skipping"<<endl;
                errors++;
                continue;
            }
        }
}

    Esucces importstatus=Success;
    if(errors==0){
        errStream<<inputfilename <<" read no error"<<endl;
    }else{
        errStream<<inputfilename <<" read with " <<errors<< " errors"<<endl;
        importstatus=PartialImport;
    }
    for (unsigned int j = 0; j < sim.getAirports().size(); ++j) {
        if (sim.getAirports()[j]->getRunways().empty()) {
            errStream<<sim.getAirports()[j]->getName()<<" has no runway or a wrong amount of runway."<<endl;
            errStream<<sim.getAirports()[j]->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            sim.removeAirport(sim.getAirports()[j]);
        }
    }
    return importstatus;
}
