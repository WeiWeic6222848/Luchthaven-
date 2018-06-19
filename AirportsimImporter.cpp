//
// Created by c6222848 on 4/3/18.
//

#include "DesignByContract.h"
#include "AirportsimImporter.h"
#include "AirportUtils.h"
#include "Airportsim.h"
#include "Runway.h"
#include "Taxipoint.h"
#include "Gate.h"






Esucces AirportsimImporter::importAirportsim(const char *inputfilename, std::ostream &errStream, Airportsim &sim) {

    REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling importAirportsim");
    REQUIRE(fileExist(inputfilename),"Giving filename must exist when calling importAirportsim");
    TiXmlDocument XMLfile;
    int errors=0;
    int numberofAirport=0;
    Esucces importstatus=Success;
    XMLfile.LoadFile(inputfilename);
    Airport* airport;
    if(XMLfile.Error()){
        errStream<<"this xml contains syntax error, trying to read as much as possible"<<endl;
        errors++;
    }
    TiXmlElement *Root = XMLfile.RootElement();
    if (Root) {
        TiXmlElement *airportelement=Root->FirstChildElement("AIRPORT");
        if(airportelement==NULL){
            errStream<<"this xml doesn't contain any airport!"<<endl;
            return ImportAborted;
        }
        Esucces status=readAirport(airportelement,errStream,sim,airport);
        if(status==ImportAborted){
            return ImportAborted;
        }
        else if(status==PartialImport){
            errors++;
        };



        for (TiXmlElement* childelement=Root->FirstChildElement();childelement!= NULL;childelement=childelement->NextSiblingElement()){
            string Elementname=childelement->Value();
            if(Elementname=="AIRPORT"){
                numberofAirport++;
                if(numberofAirport>1){
                    if(childelement->FirstChildElement("iata")&&childelement->FirstChildElement("iata")->GetText()){
                        if(sim.findAirport(childelement->FirstChildElement("iata")->GetText())!=NULL){
                            errStream<<"airport is added on a earlier source, skipping"<<endl;
                            errors++;
                            numberofAirport--;
                        }
                    }
                    else{
                        if (numberofAirport>1){
                            errStream<<inputfilename<<" contains more than one airport"<<endl;
                            return ImportAborted;
                        }
                    }
                }
            }


            else if (Elementname=="RUNWAY"&&childelement->FirstChildElement("name")&&childelement->FirstChildElement("airport")&&childelement->FirstChildElement("type")&&childelement->FirstChildElement("length")){
                Esucces status=readRunway(childelement,errStream,sim,airport);
                if(status==PartialImport){
                    errors++;
                }
                else if (status==ImportAborted){
                    return ImportAborted;
                };
            }



            else if (Elementname=="AIRPLANE"&&childelement->FirstChildElement("number")&&childelement->FirstChildElement("callsign")
                     &&childelement->FirstChildElement("model")&&childelement->FirstChildElement("status") &&childelement->FirstChildElement("type")
                     &&childelement->FirstChildElement("engine") &&childelement->FirstChildElement("size")){

                Esucces status=readAirplane(childelement,errStream,sim,airport);
                if (status==ImportAborted){
                    return ImportAborted;
                }
                else if (status==PartialImport){
                    errors++;
                }
        }

            else{
                errStream<<"element "+ Elementname+" is not recongized by the airsim system, skipping"<<endl;
                errors++;
            }
}

    for (unsigned int j = 0; j < sim.getAirports().size(); ++j) {
        if (sim.getAirports()[j]->getRunways().empty()) {
            //errStream<<sim.getAirports()[j]->getName()<<" has no runway or a wrong amount of runway."<<endl;
            //errStream<<sim.getAirports()[j]->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            errStream<<"Airport has no runway or a wrong amount of runway."<<endl;
            sim.removeAirport(sim.getAirports()[j]);
            return ImportAborted;
        }
    }


    if(errors==0){
        //errStream<<inputfilename <<" read no error"<<endl;
    }else{
        //errStream<<inputfilename <<" read with " <<errors<< " errors"<<endl;
        //if (importstatus==Success) #condition always true -> direct return on importaborted
        importstatus=PartialImport;
    }
    return importstatus;
}
    return ImportAborted;//returning aborted if there's no root
}

Esucces AirportsimImporter::readAirport(TiXmlElement *airportelement, std::ostream &errStream, Airportsim &sim, Airport *&airport) {
    REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling addsourcefile");


    if (airportelement->FirstChildElement("name")&&airportelement->FirstChildElement("iata")&&airportelement->FirstChildElement("callsign")&&airportelement->FirstChildElement("gates")){
            if(hasEmptyFields(airportelement)){
                errStream<<"Airport contains one or more emptyfields"<<endl;
                return ImportAborted;
            }
            string name=airportelement->FirstChildElement("name")->GetText();
            string iata=airportelement->FirstChildElement("iata")->GetText();
            string callsign=airportelement->FirstChildElement("callsign")->GetText();
            int gates;
            try{
                gates=stoi(airportelement->FirstChildElement("gates")->GetText());
            }
            catch(...){
                //errStream<< "Airport with name "+name+" has a number of gate which isn't a integer"<<endl;
                errStream<< "Airport has a number of gate which isn't a integer"<<endl;
                return ImportAborted;
            }
            int passenger=0;
            if (airportelement->FirstChildElement("passenger")) {
                try {
                    passenger = stoi(airportelement->FirstChildElement("passenger")->GetText());
                } catch (...) {
                    //errStream << "Airport with name " + name + " has a passenger attribute which isn't a interger" << endl;
                    errStream << "Airport has a passenger attribute which isn't a interger" << endl;
                    return ImportAborted;
                }
            }
            for (unsigned int i = 0; i < sim.getAirports().size(); ++i) {
                if(sim.getAirports()[i]->getIata()==iata){
                    //errStream<<"airport with iata "<<iata<<" is added on a earlier source, skipping"<<endl;
                    errStream<<"airport is added on a earlier source, skipping"<<endl;
                    airport=sim.getAirports()[i];
                    return PartialImport;
                }
            }
            airport=new Airport(name,iata,callsign,gates,passenger);
            sim.addAirport(airport);
            return Success;
    }
    else{
        errStream<<"airport doesn't have the required attributes";
        return ImportAborted;
    }
    return ImportAborted;
}

Esucces AirportsimImporter::readRunway(TiXmlElement *runwayelement, std::ostream &errStream, Airportsim &sim, Airport *&airport) {
    REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling readRunway");
    REQUIRE(airport->ProperInitialized(),"Airport object wasn't initialized when calling readRunway");

    if(hasEmptyFields(runwayelement)){
        errStream<<"Runway has one or more empty fields!"<<endl;
        return PartialImport;
    }
    string name=runwayelement->FirstChildElement("name")->GetText();

    string airportname=runwayelement->FirstChildElement("airport")->GetText();

    string typerunway=runwayelement->FirstChildElement("type")->GetText();

    if(typerunway!="asphalt"&&typerunway!="grass"){
        errStream<<"Runway type is wrong"<<endl;
        return PartialImport;
    }


    int length;
    Taxipoint* pointofthisrunway= NULL;
    Airport* airportofthisrunway;

    try{
        length=stoi(runwayelement->FirstChildElement("length")->GetText());
        if(length==0){
            errStream<<"Runway has a length which is not an integer, skipping this element"<<endl;
            return PartialImport;
        }
    }catch (...){
        errStream<<"Runway has a length which is not an integer, skipping this element"<<endl;
        return PartialImport;
    }

    bool airportfound=false;
    for (unsigned int i = 0; i < sim.getAirports().size(); ++i) {
        if(sim.getAirports()[i]->getIata()==airportname){
            for (unsigned int j = 0; j < sim.getAirports()[i]->getRunways().size(); ++j) {
                if(sim.getAirports()[i]->getRunways()[j]->getName()==name){
                    errStream<<"runway is added on a earlier source, skipping"<<endl;
                    return PartialImport;
                }
            }
            airportfound=true;
            airportofthisrunway=sim.getAirports()[i];
        }
    }

    if(!(airportfound)){
        errStream<<"cannot find airport for the runway"<<endl;
        errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
        return ImportAborted;
    }
    else{
        Runway* runway=new Runway(name,airportofthisrunway,typerunway,length);


        //**************************************************************************** Taxipoint reading********************************************//
        if (runwayelement->FirstChild("TAXIROUTE")){
            TiXmlElement* routeelement=runwayelement->FirstChildElement("TAXIROUTE");
            if(routeelement->LastChild("taxipoint")&&routeelement->LastChild("taxipoint")==routeelement->LastChild()){
                if(routeelement->LastChild("taxipoint")->ToElement()->GetText()){
                    if(airport->findTaxipoint(routeelement->LastChild("taxipoint")->ToElement()->GetText())==NULL){
                        pointofthisrunway=new Taxipoint(routeelement->LastChild("taxipoint")->ToElement()->GetText(),runway);
                    }
                    else{
                        errStream<<"unable to read Taxiroute"<<endl;
                        delete(runway);
                        return PartialImport;
                    }
                }
                else{
                    //errStream<<"Empty name"<<endl;
                    errStream<<"unable to read Taxiroute"<<endl;
                    delete(runway);
                    return PartialImport;
                }
            }
            else{
                //errStream<<"TAXIROUTE of runway doesn't contain any taxipoint or it doesnt ends with taxipoint!"<<endl;
                errStream<<"unable to read Taxiroute"<<endl;
                delete(runway);
                return PartialImport;
            }
            if (routeelement->FirstChildElement()->GetText()!=pointofthisrunway->getName()){
                for (TiXmlElement* locationElement=routeelement->FirstChildElement(); locationElement !=routeelement->LastChild("taxipoint")->ToElement() ; locationElement=locationElement) {
                    string elemname=locationElement->Value();
                    if(locationElement->GetText()){
                        if(elemname=="crossing"){
                            Location* location=airportofthisrunway->findRunway(locationElement->GetText());
                            if(location!=NULL){
                                pointofthisrunway->addCrossingToRoute(location);
                                if(locationElement->NextSiblingElement()->Value()){
                                    string a=locationElement->NextSiblingElement()->Value();
                                    if(a=="taxipoint"){
                                        locationElement=locationElement->NextSiblingElement();
                                    }
                                    else{
                                        errStream<<"unable to read Taxiroute"<<endl;
                                        delete(runway);
                                        return PartialImport;
                                    }
                                }
                                else{
                                    errStream<<"unable to read Taxiroute"<<endl;
                                    delete(runway);
                                    return PartialImport;
                                }
                            }
                            else{
                                //errStream<<"Runway contains an unknown runway in the taxi route! "<< endl;
                                errStream<<"unable to read Taxiroute"<<endl;
                                delete(runway);
                                return PartialImport;
                            }
                        }
                        else if (elemname=="taxipoint"){
                            Location* location=airportofthisrunway->findTaxipoint(locationElement->GetText());
                            if(location!=NULL){
                                pointofthisrunway->addCrossingToRoute(location);
                                if(locationElement->NextSiblingElement()->Value()){
                                    string a=locationElement->NextSiblingElement()->Value();
                                    if(a=="crossing"){
                                        locationElement=locationElement->NextSiblingElement();
                                    }
                                    else{
                                        errStream<<"unable to read Taxiroute"<<endl;
                                        delete(runway);
                                        return PartialImport;
                                    }
                                }
                                else{
                                    errStream<<"unable to read Taxiroute"<<endl;
                                    delete(runway);
                                    return PartialImport;
                                }
                            }
                            else{
                                //errStream<<"Runway contains an unreachable taxipoint in the taxi route! "<< endl;
                                errStream<<"unable to read Taxiroute"<<endl;
                                delete(runway);
                                return PartialImport;
                            }
                        }
                        else{
                            errStream<<"unable to read Taxiroute"<<endl;
                            delete(runway);
                            return PartialImport;
                        }
                    }
                    else{
                        //empty name
                        errStream<<"unable to read Taxiroute"<<endl;
                        delete(runway);
                        return PartialImport;
                    }
                }
            }
            pointofthisrunway->setRunwayonpoint(runway);
            airportofthisrunway->addTaxipoints(pointofthisrunway);
            runway->setTaxipoint(pointofthisrunway);
            for (unsigned int i = 0; i < pointofthisrunway->getRoute().size(); ++i) {
                runway->addCrossingToRoute(pointofthisrunway->getRoute()[i]);
            }
            runway->addCrossingToRoute(pointofthisrunway);
        }
        //**************************************************************************** Taxipoint reading********************************************//


        airportofthisrunway->addRunway(runway);
    }
    return Success;
}

Esucces AirportsimImporter::readAirplane(TiXmlElement *airplaneelement, std::ostream &errStream, Airportsim &sim, Airport *&airport) {
    REQUIRE(sim.ProperInitialized(),"Airportsim object wasn't initialized when calling readAirplane");
    REQUIRE(airport->ProperInitialized(),"Airport object wasn't initialized when calling readAirplane");

    if(hasEmptyFields(airplaneelement)){
        errStream<<"Airplane has one or more empty fields!"<<endl;
        return PartialImport;
    }

    string number=airplaneelement->FirstChildElement("number")->GetText();
    string callsign=airplaneelement->FirstChildElement("callsign")->GetText();
    string model=airplaneelement->FirstChildElement("model")->GetText();
    string status=airplaneelement->FirstChildElement("status")->GetText();

    string type=airplaneelement->FirstChildElement("type")->GetText();
    string engine=airplaneelement->FirstChildElement("engine")->GetText();
    string size=airplaneelement->FirstChildElement("size")->GetText();

    for (unsigned int i = 0; i < sim.getAirplanes().size(); ++i) {
        if(sim.getAirplanes()[i]->getNumber()==number){
            //errStream<<"airplane with number "<<number<<" is added on a earlier source, skipping"<<endl;
            errStream<<"airplane is added on a earlier source, skipping"<<endl;
            return PartialImport;
        }
    }

    if (!(isRightAirplaneCombination(type,engine,size))){
        //errStream<<"Airplane with number "<<number<< "has a invalid combination of engine, size and type, check specification for more information"<<endl;
        errStream<<"Airplane with has a invalid combination of engine, size and type, check specification for more information"<<endl;
        return PartialImport;
    }

    if(status!="Approaching"&&status!="Standing at gate"){
        errStream<<"Airplane status is not correct"<<endl;
        //errStream<<"Airplane status of " + number+" is not correct"<<endl;
        //errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
        //return ImportAborted;
        return PartialImport;
    }

    int passengercapacity=10;

    int passenger=-1;

    if(airplaneelement->FirstChildElement("passenger")){
        try {
            passenger = stoi(airplaneelement->FirstChildElement("passenger")->GetText());
        }catch (...){
            //errStream<<"Airplane with number "+number+" has a passenger attribute which isn't a interger"<<endl;
            errStream<<"Airplane has a passenger attribute which isn't a interger or is an negative number"<<endl;
            return PartialImport;
        }
    }

    if(passenger==-1){
        passenger=passengercapacity;
    }

    if(airplaneelement->FirstChildElement("passengercapacity")){
        try {
            passengercapacity = stoi(airplaneelement->FirstChildElement("passengercapacity")->GetText());
        }catch (...){
            //errStream<<"Airplane with number "+number+" has a passengercapacity attribute which isn't a interger"<<endl;
            errStream<<"Airplane has a passengercapacity attribute which isn't a interger or is an negative number"<<endl;
            return PartialImport;
        }
        if(passengercapacity<passenger){
            errStream<<"Airplane has more passenger than it's capacity."<<endl;
            return PartialImport;
        }
    }

    if(passengercapacity<passenger){
        passengercapacity=passenger;
    }

    int fuel=10000;

    if(airplaneelement->FirstChildElement("fuel")){
        try {
            fuel = stoi(airplaneelement->FirstChildElement("fuel")->GetText());
        }catch (...){
            //errStream<<"Airplane with number "+number+" has a fuel attribute which isn't a interger"<<endl;
            errStream<<"Airplane has a fuel attribute which isn't a interger"<<endl;
            return PartialImport;
        }
    }
    Airplane::Airplaneallowedstatus temp=Airplane::Approaching;
    if(status=="Standing at gate"){
        temp=Airplane::Standing_at_gate;
    }
    bool flightplan;
    string destination;
    int departure;
    int arrival;
    int interval;
    if(airplaneelement->FirstChildElement("FLIGHTPLAN")){
        TiXmlElement* planElement = airplaneelement->FirstChildElement("FLIGHTPLAN");
        destination = planElement->FirstChildElement("destination")->GetText();
        departure = stoi(planElement->FirstChildElement("departure")->GetText());
        arrival = stoi(planElement->FirstChildElement("arrival")->GetText());
        interval = stoi(planElement->FirstChildElement("interval")->GetText());
        flightplan=true;
    }
    else{
        errStream<<"plane has no flightplan, when tried to import from .xml file"<<endl;
        flightplan=false;
    }
    Airplane* a;
    if(!flightplan){
        a =new Airplane(temp,number,callsign,model,type,engine,size,passenger,fuel,passengercapacity,airport);
    }
    else {
        a =new Airplane(temp,number,callsign,model,type,engine,size,passenger,fuel,passengercapacity,airport,destination,departure,arrival,interval);
    }
    sim.addAirplane(a);

    if (status=="Standing at gate"){
        Gate* gateforairplane=airport->findFreeGates();
        passenger=0;
        if(gateforairplane==NULL){
            //errStream<<airport->getName()<<" has more airplanes at gates than it's gate"<<endl;
            //errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            errStream<<"airport has more airplanes at gates than it's gate"<<endl;
            return ImportAborted;
        }
        else{
            airport->parkAirplane(gateforairplane,a);
            a->setLocation(gateforairplane);
        }
    }

    return Success;
}


