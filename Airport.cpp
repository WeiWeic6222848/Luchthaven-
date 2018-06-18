//
// Created by c6222 on 2018/3/8.
//


#include "Airport.h"
#include "DesignByContract.h"
#include "AirportUtils.h"
#include "Runway.h"
#include "Taxipoint.h"
#include "Gate.h"

//constructor
Airport::Airport(const string &name, const string &iata, const string &callsign, int gates, int passengers) : name(name), iata(iata), callsign(callsign),  passengers(passengers)
{
    _InitCheck=this;
    for (int i = 1; i < gates+1; ++i) {
        Airport::gates.push_back(new Gate(to_string(i))) ;
    }
    tower= new Signaltower(this);
    ENSURE(ProperInitialized(),"This airport object failed to Initialize properly");
}


//all getters--------------------------
const string &Airport::getName() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getName");
    return name;
}


const string &Airport::getIata() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getIata");
    return iata;
}



const string &Airport::getCallsign() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getCallsign");
    return callsign;
}

const vector<Gate *> &Airport::getGates() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGates");
    return gates;
}

int Airport::getPassengers() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getPassenger");
    return passengers;
}

const vector<Runway *> &Airport::getRunways() const {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getRunways");
    return runways;
}

const vector<Taxipoint*> &Airport::getTaxipoints() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getTaxipoints");
    return taxipoints;
}

bool Airport::ProperInitialized() const {
    return _InitCheck==this;
}

Signaltower &Airport::getTower(){
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getTower");
    return *tower;
}

Gate* Airport::findFreeGates() const {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findfreegates");
    for (unsigned int i = 0; i < gates.size(); ++i) {
        if(!(gates[i]->isOnuse())){
            return gates[i];
        }
    }
    //cerr<<"all gates buzy"<<endl;
    return NULL;
}

Gate* Airport::getGateFromAirplane(Airplane* plane){
    REQUIRE(plane->ProperInitialized(),"Airplane plane wasn't initialized when calling getGateFromAirplane");
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling getGateFromAirplane");
    for(unsigned int i=0;i<gates.size();i++){
        if(gates[i]->getCurrentPlane()!=NULL){
            if(gates[i]->getCurrentPlane()->getNumber()==plane->getNumber()){
                return gates[i];
            }
        }
        if(gates[i]->getPlaneNearGate()!=NULL){
            if(gates[i]->getPlaneNearGate()->getNumber()==plane->getNumber()){
                return gates[i];
            }
        }
    }
    return NULL;
}


Runway *Airport::findRunway(const string&name) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findRunway");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getName()==name){
            return runways[i];
        }
    }
    return NULL;
}


Runway *Airport::findFreeRunway(Airplane *airplane,bool emergency) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findFreeRunway");
    REQUIRE(airplane->ProperInitialized(),"Airplane wasn't initialized when calling findFreeRunway");
    REQUIRE(isRightAirplaneCombination(airplane),"Airplane is not correct");
    bool grassallowed=airplaneCanLandOnGrass(airplane);
    int required=requiredLengthOfRunway(airplane);
    int queueingplane=2147483647;//initialize the number to max
    unsigned int taxiroutelength=0;
    Runway* result=NULL;
    vector<Runway*> leastplane;
    if (grassallowed){
        //always using grass first if possible.
        //emergency is not done
        for (unsigned int i = 0; i < runways.size(); ++i) {
            if(!emergency){
                if(/*!(runways[i]->isCrossing())&&!(runways[i]->isOnuse())&&*/runways[i]->getType()==grass&&runways[i]->getLength()>=required&&runways[i]->getAirplanequeueing()<=queueingplane){
                    queueingplane=runways[i]->getAirplanequeueing();
                    leastplane.push_back(runways[i]);
                }
            }
            else{
                if(/*!(runways[i]->isCrossing())&&!(runways[i]->isOnuse())&&*/runways[i]->getType()==grass&&runways[i]->getLength()>=required&&runways[i]->getAirplanequeueing()<=queueingplane){
                    queueingplane=runways[i]->getAirplanequeueing();
                    leastplane.push_back(runways[i]);
                }
            }
        }
    }
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(!emergency){

            if(/*!(runways[i]->isCrossing())&&!(runways[i]->isOnuse())&&*/runways[i]->getType()!=grass&&runways[i]->getLength()>=required&&runways[i]->getAirplanequeueing()<=queueingplane){
                queueingplane=runways[i]->getAirplanequeueing();
                leastplane.push_back(runways[i]);
            }
        }
        else{
            if(/*!(runways[i]->isCrossing())&&!(runways[i]->isOnuse())&&*/runways[i]->getType()!=grass&&runways[i]->getLength()>=required&&runways[i]->getAirplanequeueing()<=queueingplane){
                queueingplane=runways[i]->getAirplanequeueing();
                leastplane.push_back(runways[i]);
            }
        }
    }
    if (leastplane.empty()){
        cout<<"no free runway are suitable for this plane"<<endl;
        return NULL;
    }
    else{
            for (unsigned int i = 0; i <leastplane.size() ; ++i) {
                if(leastplane[i]->getRoute().size()>taxiroutelength){
                    result=leastplane[i];
                    taxiroutelength=leastplane[i]->getRoute().size();
                }
            }
    }
    //always find the runway with the least plane queuing and always returning the most far runway.
    return result;
}

Taxipoint *Airport::findTaxipoint(const string &name) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling findTaxipoint");
    for (unsigned int i = 0; i < taxipoints.size(); ++i) {
        if(taxipoints[i]->getName()==name){
            return taxipoints[i];
        }
    }
    return NULL;
}



// all changers-----------------------------------------------------------------------------

void Airport::addPassenger(int a) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addPassenger");
    passengers+=a;
}



void Airport::removePassenger(int a) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling removePassenger");
    passengers-=a;
}


void Airport::freeGate(Gate*  gate){
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling freeGate");
    gate->setCurrentPlane(NULL);
    ENSURE(gate->getCurrentPlane()==NULL&&!gate->isOnuse(),"freeGate postcondition failed");
}


void Airport::addRunway(Runway* runway) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addRunway");
    REQUIRE(findRunway(runway->getName())==NULL,"there is already a runway with the same name!!");
    runways.push_back(runway);
    ENSURE(findRunway(runway->getName())!=NULL,"addrunway postcondition failed");
}

void Airport::parkAirplane(Gate* gate, Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling parkAirplane");
    REQUIRE((unsigned int)stoi(gate->getName())<=gates.size(),"The giving gate number must be valid");
    REQUIRE(gate->getCurrentPlane()==NULL,"The giving gate must be empty");
    gate->setCurrentPlane(airplane);
    ENSURE(gate->getCurrentPlane()==airplane,"parkAirplane postcondition failed");
}

void Airport::addTaxipoints(Taxipoint* taxipoint) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling addTaxipoint");
    REQUIRE(findTaxipoint(taxipoint->getName())==NULL,"The giving Taxipoint shouldn't be added already");
    taxipoints.push_back(taxipoint);
    ENSURE(findTaxipoint(taxipoint->getName())!=NULL,"addTaxipoints postcondition failed");
}








Airport::~Airport() {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling destructor");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        delete(runways[i]);
    }
}

void Airport::cleanup() {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when calling cleanup");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        delete(runways[i]);
    }
    runways.clear();
    ENSURE(runways.empty(),"cleanup postcondition failed");
}


std::ostream& operator<<(std::ostream& output,Airport& airport){
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when getting output");
    output<<"Airport: "<<airport.getName()<<" ("<<airport.getIata()<<")"<<endl;
    output<<" -> gates: "<<airport.gates.size()<<endl;
    output<<" -> runways: "<<airport.runways.size()<<endl;
    return output;
}








bool Airport::receiveSignal(Airplane *airplane, Signaltower::SignaltowerallowedSignal signal) {
    REQUIRE(ProperInitialized(),"Airport wasn't initialized when transmitting signal");
    return tower->receiveSignal(airplane,signal);
}







void Airport::setName(const string &name) {
    Airport::name = name;
}

void Airport::setIata(const string &iata) {
    Airport::iata = iata;
}

void Airport::setCallsign(const string &callsign) {
    Airport::callsign = callsign;
}

void Airport::setGates(const vector<Gate *> &gates) {
    Airport::gates = gates;
}

void Airport::setPassengers(int passengers) {
    Airport::passengers = passengers;
}

void Airport::setRunways(const vector<Runway *> &runways) {
    Airport::runways = runways;
}

void Airport::setTaxipoints(const vector<Taxipoint *> &taxipoints) {
    Airport::taxipoints = taxipoints;
}

void Airport::setTower(Signaltower *tower) {
    Airport::tower = tower;
}




