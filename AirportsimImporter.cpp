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
                if (numberofAirport>1){
                    errStream<<inputfilename<<" contains more than one airport"<<endl;
                    return ImportAborted;
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
            errStream<<sim.getAirports()[j]->getName()<<" has no runway or a wrong amount of runway."<<endl;
            errStream<<sim.getAirports()[j]->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            sim.removeAirport(sim.getAirports()[j]);
            return ImportAborted;
        }
    }

    if(errors==0){
        errStream<<inputfilename <<" read no error"<<endl;
    }else{
        errStream<<inputfilename <<" read with " <<errors<< " errors"<<endl;
        //if (importstatus==Success) #condition always true -> direct return on importaborted
        importstatus=PartialImport;
    }
    return importstatus;
}
    return ImportAborted;//returning aborted if there's no root
}

Esucces AirportsimImporter::readAirport(TiXmlElement *airportelement, std::ostream &errStream, Airportsim &sim, Airport *&airport) {

    if (airportelement->FirstChildElement("name")&&airportelement->FirstChildElement("iata")&&airportelement->FirstChildElement("callsign")&&airportelement->FirstChildElement("gates")){
        try{
            string name=airportelement->FirstChildElement("name")->GetText();
            string iata=airportelement->FirstChildElement("iata")->GetText();
            string callsign=airportelement->FirstChildElement("callsign")->GetText();
            int gates;
            try{
                gates=stoi(airportelement->FirstChildElement("gates")->GetText());
            }
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
            for (unsigned int i = 0; i < sim.getAirports().size(); ++i) {
                if(sim.getAirports()[i]->getIata()==iata){
                    errStream<<"airport with iata "<<iata<<" is added on a earlier source, skipping"<<endl;
                    airport=sim.getAirports()[i];
                    return PartialImport;
                }
            }
            airport=new Airport(name,iata,callsign,gates,passenger);
            sim.addAirport(airport);
            return Success;
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
    return ImportAborted;
}

Esucces AirportsimImporter::readRunway(TiXmlElement *runwayelement, std::ostream &errStream, Airportsim &sim, Airport *&airport) {
    string name=runwayelement->FirstChildElement("name")->GetText();
    string airportname=runwayelement->FirstChildElement("airport")->GetText();
    string typerunway=runwayelement->FirstChildElement("type")->GetText();
    int length;
    Taxipoint* pointofthisrunway= NULL;
    Airport* airportofthisrunway;
    try{
        length=stoi(runwayelement->FirstChildElement("length")->GetText());
    }catch (...){
        errStream<<"Runway with name "<<name<< " has a length which is not an integer, skipping this element"<<endl;
        return PartialImport;
    }

    bool airportfound=false;
    for (unsigned int i = 0; i < sim.getAirports().size(); ++i) {
        if(sim.getAirports()[i]->getIata()==airportname){
            for (unsigned int j = 0; j < sim.getAirports()[i]->getRunways().size(); ++j) {
                if(sim.getAirports()[i]->getRunways()[j]->getName()==name){
                    errStream<<"runway with name "<<name<<" is added on a earlier source, skipping"<<endl;
                    return PartialImport;
                }
            }
            airportfound=true;
            airportofthisrunway=sim.getAirports()[i];
        }
    }

    if(!(airportfound)){
        errStream<<"cannot find airpont: "<<airportname<<" for the runway with name:"<<name<<endl;
        errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
        return ImportAborted;
    }
    else{
        Runway* runway=new Runway(name,airportofthisrunway,typerunway,length);


        //**************************************************************************** Taxipoint reading********************************************//
        if (runwayelement->FirstChild("TAXIROUTE")){
            TiXmlElement* routeelement=runwayelement->FirstChildElement("TAXIROUTE");
            if(routeelement->LastChild("taxipoint")){
                pointofthisrunway=new Taxipoint(routeelement->LastChild("taxipoint")->ToElement()->GetText(),runway);
            }
            else{
                errStream<<"TAXIROUTE of runway "<<name<< " doesn't contain any taxipoint!"<<endl;
                delete(runway);
                return PartialImport;
            }
            if (routeelement->FirstChildElement()->GetText()!=pointofthisrunway->getName()){
                for (TiXmlElement* locationElement=routeelement->FirstChildElement(); locationElement !=routeelement->LastChild("taxipoint")->ToElement() ; locationElement=locationElement->NextSiblingElement()) {
                    string elemname=locationElement->Value();
                    if(elemname=="crossing"){
                        Location* location=airportofthisrunway->findRunway(locationElement->GetText());
                        pointofthisrunway->addCrossingToRoute(location);
                    }
                    else if (elemname=="taxipoint"){
                        Location* location=airportofthisrunway->findTaxipoint(locationElement->GetText());
                        pointofthisrunway->addCrossingToRoute(location);
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
    string number=airplaneelement->FirstChildElement("number")->GetText();
    string callsign=airplaneelement->FirstChildElement("callsign")->GetText();
    string model=airplaneelement->FirstChildElement("model")->GetText();
    string status=airplaneelement->FirstChildElement("status")->GetText();
    string type=airplaneelement->FirstChildElement("type")->GetText();
    string engine=airplaneelement->FirstChildElement("engine")->GetText();
    string size=airplaneelement->FirstChildElement("size")->GetText();

    for (unsigned int i = 0; i < sim.getAirplanes().size(); ++i) {
        if(sim.getAirplanes()[i]->getNumber()==number){
            errStream<<"airplane with number "<<number<<" is added on a earlier source, skipping"<<endl;
            return PartialImport;
        }
    }
    if (!(isRightAirplaneCombination(type,engine,size))){
        errStream<<"Airplane with number "<<number<< "has a invalid combination of engine, size and type, check specification for more information"<<endl;
        return PartialImport;
    }
    if(status!="Approaching"&&status!="Standing at gate"){
        errStream<<"Airplane status of " + number+" is not correct"<<endl;
        errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
        return ImportAborted;
    }
    int passengercapacity=10;
    if(airplaneelement->FirstChildElement("passengercapacity")){
        try {
            passengercapacity = stoi(airplaneelement->FirstChildElement("passengercapacity")->GetText());
        }catch (...){
            errStream<<"Airplane with number "+number+" has a passengercapacity attribute which isn't a interger"<<endl;
            return PartialImport;
        }
    }
    int passenger=passengercapacity;

    if(airplaneelement->FirstChildElement("passenger")){
        try {
            passenger = stoi(airplaneelement->FirstChildElement("passenger")->GetText());
        }catch (...){
            errStream<<"Airplane with number "+number+" has a passenger attribute which isn't a interger"<<endl;
            return PartialImport;
        }
    }

    int fuel=100;
    if(airplaneelement->FirstChildElement("fuel")){
        try {
            fuel = stoi(airplaneelement->FirstChildElement("fuel")->GetText());
        }catch (...){
            errStream<<"Airplane with number "+number+" has a fuel attribute which isn't a interger"<<endl;
            return PartialImport;
        }
    }
    Airplane* a=new Airplane(status,number,callsign,model,type,engine,size,passenger,fuel,passengercapacity,airport);
    sim.addAirplane(a);

    if (status=="Standing at gate"){
        Gate* gateforairplane=airport->findFreeGates();
        passenger=0;
        if(gateforairplane==NULL){
            errStream<<airport->getName()<<" has more airplanes at gates than it's gate"<<endl;
            errStream<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            return ImportAborted;
        }
        else{
            airport->parkAirplane(gateforairplane,a);
        }
    }

    return Success;
}

Esucces AirportsimImporter::readTaxiroute(TiXmlElement *routeelement, std::ostream &errStream, Runway &runway,
                                          Airport *&airport) {

    return Success;
}



