//
// Created by c6222 on 2018/3/8.
//

#include "Airplane.h"
#include "DesignByContract.h"
#include "algorithm"
#include "AirportUtils.h"
//getters
const string &Airplane::getStatus() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getStatus");
    //ENSURE(status!=NULL,"returning a null object status");
    return status;
}

const string &Airplane::getNumber() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getNumber");
    return number;
}

const string &Airplane::getModel() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getModel");
    return model;
}

const string &Airplane::getCallsign() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCallsign");
    return callsign;
}

const string &Airplane::getType() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getType");
    return type;
}

const string &Airplane::getEngine() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getEngine");
    return engine;
}

const string &Airplane::getSize() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getSize");
    return size;
}

int Airplane::getPassenger() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassenger");
    //ENSURE(passenger!=NULL,"returning a null object passenger");
    return passenger;
}

int Airplane::getFuel() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuel");
    return fuel;
}

int Airplane::getFuelCapacity() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuel");
    //ENSURE(fuel!=NULL,"returning a null object fuel");
    return fuelCapacity;
}

int Airplane::getHeight() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getHeight");
    return height;
}

int Airplane::getPassengerCapacity() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassengerCapacity");
    return passengerCapacity;
}

const string &Airplane::getPermission() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPermission");
    return permission;
}

Airport *Airplane::getDestination() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDestination");
    return destination;
}

Airport *Airplane::getNextDestination() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getNextDestination");
    return nextDestination;
}

Location *Airplane::getLocation() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getLocation");
    return location;
}

const vector<Location *> &Airplane::getInstruction() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getInstruction");
    return instruction;
}

const Time &Airplane::getCurrentTime() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCurrentTime");
    return currentTime;
}

bool Airplane::isDoingNothing() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling isDoingNothing");
    return doingNothing;
}

Runway *Airplane::getDestinateRunway() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDestinateRunway");
    return destinaterunway;
}

const string &Airplane::getCheckProcedure() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCheckProcedure");
    return checkprocedure;
}

bool Airplane::ProperInitialized() const {
    return _initcheck==this;
}



//setters
void Airplane::setStatus(const string &status) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
    Airplane::status = status;
    ENSURE(getStatus()==status,"setStatus Postcondition failed");
}

void Airplane::setPassenger(int passenger) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
    Airplane::passenger = passenger;
    ENSURE(getPassenger()==passenger,"setPassenger postcondition failed");
}

void Airplane::setFuel(int fuel) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setFuel");
    Airplane::fuel = fuel;
    ENSURE(getFuel()==fuel,"setFuel postcondition failed");
}

void Airplane::setFuelCapacity(int fuel) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
    Airplane::fuelCapacity = fuel;
    ENSURE(getFuelCapacity()==fuel,"setFuelCapacity postcondition failed");
}

void Airplane::setPermission(string descendingpermission) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPermission");
    if(descendingpermission!="0"){
        //...
    }
    Airplane::permission = descendingpermission;
    ENSURE(getPermission()==descendingpermission,"setFuelCapacity postcondition failed");
}

void Airplane::setDestination(Airport *destination) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setDestination");
    Airplane::destination = destination;
    ENSURE(getDestination()==destination,"setDestination postcondition failed");
}

void Airplane::setNextDestination(Airport *nextDestination) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setNextDestination");
    Airplane::nextDestination = nextDestination;
    ENSURE(getNextDestination()==nextDestination,"setNextDestination postcondition failed");
}

void Airplane::setLocation(Location *location) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setLocation");
    Airplane::location = location;
    ENSURE(getLocation()==location,"setLocation postcondition failed");
}

void Airplane::setInstruction(const vector<Location *> &instruction) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setInstruction");
    Airplane::instruction = instruction;
    ENSURE(getInstruction()==instruction,"setInstruction postcondition failed");
}

void Airplane::setDestinateRunway(Runway *destinaterunway) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setDestinateRunway");
    Airplane::destinaterunway = destinaterunway;
    ENSURE(getDestinateRunway()==destinaterunway,"setDestinateRunway postcondition failed");


}








//outputter
std::ostream& operator<<(std::ostream& output,Airplane& airplane){
    REQUIRE(airplane.ProperInitialized(),"Airplane wasn't initialized when getting output");
    output<<"Airplane: "<<airplane.getCallsign()<<" ("<<airplane.getNumber()<<")"<<std::endl;
    output<<" -> model: "<<airplane.getModel()<<endl;
    output<<" -> type: "<<airplane.getType()<<endl;
    output<<" -> engine: "<<airplane.getEngine()<<endl;
    output<<" -> size: "<<airplane.getSize()<<endl;
    return output;
}







//constructor
Airplane::Airplane(const string &status, const string &number, const string &callsign, const string &model,
                   const string &type, const string &engine, const string &size, int passenger, int fuel,
                   int passengerCapacity, Airport *destination) : number(number), callsign(callsign),
                                                                  model(model), type(type), engine(engine), size(size),
                                                                  passenger(passenger), fuelCapacity(fuel),
                                                                  passengerCapacity(passengerCapacity),
                                                                  destination(destination) {
    REQUIRE(find(allowedstatus.begin(),allowedstatus.end(),status)!=allowedstatus.end(),"a wrong status string has been passed to the initiator of the airplane");
    Airplane::status=status;
    _initcheck=this;
    if (status=="Approaching"){
        height=10000;
    }
    else{
        height=0;
    }
    checkprocedure="Just landed";
    actionDone=currentTime+(-1);
    doingNothing=true;
    ENSURE(ProperInitialized(),"this airplane object failed to Initialize properly");
}








//all signals
bool Airplane::sendSignalApproaching() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Approaching");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", "<<"arriving at "<<destination->getName()<<endl;
        //doingNothing=true;
        bool received=destination->receiveSignal(this,"Approaching");
        ENSURE(received==true,"Tower didnt receive the signal Approaching");
        return received;
    }
    return false;
}

bool Airplane::sendSignalLeaving() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Leaving");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        bool received=destination->receiveSignal(this,"Leaving");
        ENSURE(received==true,"Tower didnt receive the signal Leaving");
        return received;
    }
    return false;
}

bool Airplane::sendSignalTaxiingtoGate() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoGate");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", " <<this->getCallsign()<<", "<<"Runway " <<this->getLocation()->getName()<<" Vacated"<<endl;
        bool received=destination->receiveSignal(this,"ApproachingtoGate");
        ENSURE(received==true,"Tower didnt receive the signal ApproachingtoGate");
        return received;
    }
    return false;
}

bool Airplane::sendSignalTaxiingtoRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoRunway");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<this->getCallsign()<<" is ready to taxi."<<endl;
        bool received=destination->receiveSignal(this,"LeavingtoRunway");
        ENSURE(received==true,"Tower didnt receive the signal LeavingtoRunway");
        return received;
    }
    return false;
}

bool Airplane::sendSignalEmergency() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Emergency");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        bool received=destination->receiveSignal(this,"Emergency");
        ENSURE(received==true,"Tower didnt receive the signal Emergency");
        return received;
    }
    return false;
}


bool Airplane::sendSignalPushBack() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal PushBack");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;

        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<" at gate "<<this->getLocation()->getName()<<", requesting pushback"<<endl;
        bool received=destination->receiveSignal(this,"Push back");
        return received;
    }
    return false;
}

bool Airplane::sendSignalCrossingRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal CrossingRunway");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", " <<this->getCallsign()<<", "<<"Hold short at " <<location->getName()<<endl;
        bool received=destination->receiveSignal(this,"Crossing runway");
        ENSURE(received==true,"Tower didnt receive the signal Crossing runway");
        return received;
    }
    return false;
}

bool Airplane::sendSignalAtRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal AtRunway");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", holding short at "<<this->getLocation()->getName()<<endl;
        bool received=destination->receiveSignal(this,"At runway");
        ENSURE(received==true,"Tower didnt receive the signal At runway");
        return received;
    }
    return false;
}


bool Airplane::sendSignalIFR() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal IFR");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", requesting IFR clearancy to "<<this->getDestination()->getCallsign()<<endl;
        bool received=destination->receiveSignal(this,"IFR clearancy");
        ENSURE(received==true,"Tower didnt receive the signal IFR clearancy");
        return received;
    }
    return false;
}












//receive signals
bool Airplane::receiveSignal(string signal) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a normal signal");
    if(signal=="Keep flying"){
        destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
        destination->getTower().getFile() << "Hold south on the one eighty radial, " << this->getCallsign() << endl;
    }
    else if(signal=="3000"){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Descend and maintain three thousand feet, "<<this->getCallsign()<<endl;
        permission="3000";
    }
    else if(signal=="5000"){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Descend and maintain five thousand feet, "<<this->getCallsign()<<endl;
        permission="5000";
    }
    else if(signal=="Cleared to cross"){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Cleared to Cross runway "<<location->getName()<<", "<<this->getCallsign();
        permission="Cleared to cross";
    }
    else if(signal=="Hold position"){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Hold position, "<<this->getCallsign()<<endl;
    }
    else if(signal=="Line up"){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Line up runway "<<this->getDestinateRunway()->getName()<<" and wait."<<this->getCallsign()<<endl;
        permission="Line up";
    }
    else if(signal=="Fly"){
        destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
        destination->getTower().getFile() << "runway " <<this->getDestinateRunway()->getName() << " cleared for take-off, "
                                          << this->getCallsign() << endl;
        permission="Fly";
    }
    else if(signal=="IFR clearancy"){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Cleared to "<<this->getDestination()->getCallsign()<<" , initial altitude five thousand, expecting one zero zero in ten, squawking"<< " <SQUAWK CODE> ,"<<this->getCallsign()<<endl;
        permission="IFR clearancy";
    }
    else if(signal=="Push back"){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Pushback approved, "<<this->getCallsign()<<endl;
        permission="Push back";
    }
    doingNothing=true;
    //optimization possible
    if(signal=="Keep Flying"){
        doingNothing=false;
    }
    return false;
}



bool Airplane::receiveLandingSignal(Runway *runway) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a landing signal");

    setDestinateRunway(runway);
    setPermission("0");

    destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
    destination->getTower().getFile() << "Cleared ILS approach runway " << runway->getName() << ", " << this->getCallsign() << endl;
    doingNothing=true;
    return true;

}


bool Airplane::receiveInstruction(vector<Location *> Instruction, bool adding) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving an instruction");

    string taxipoints;
    for (unsigned int j = 0; j < Instruction.size(); ++j) {
        if(Instruction[j]->isTaxipoint()){
            if(taxipoints==""){
                taxipoints=" via ";
            }
            taxipoints+=Instruction[j]->getName()+",";
        }
    }

    taxipoints=taxipoints.substr(0,taxipoints.size()-1);
    if(adding){
        if(Instruction[Instruction.size()-1]->isGate()){
            destination->getTower().getFile()<<", "<<"Taxi to gate "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
        }
        else if(Instruction[Instruction.size()-1]==this->getDestinateRunway()){
            destination->getTower().getFile()<<", "<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
        }
        else if(Instruction[Instruction.size()-1]!=this->getDestinateRunway()&&Instruction[Instruction.size()-1]->isRunway()){
            destination->getTower().getFile()<<", "<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
        }
    }
    else{
        if (Instruction[Instruction.size()-1]->isGate()){
            destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            destination->getTower().getFile()<<"Taxi to gate "<<Instruction[Instruction.size()-1]->getName()<<taxipoints<<", "<<this->getCallsign()<<  endl;
        }
        else if(Instruction[Instruction.size()-1]==this->getDestinateRunway()) {
            destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            destination->getTower().getFile()<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints <<", "<<this->getCallsign()<<  endl;
        }
        else if(Instruction[Instruction.size()-1]!=this->getDestinateRunway()&&Instruction[Instruction.size()-1]->isRunway()) {
            destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            destination->getTower().getFile()<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints<<", "<<this->getCallsign()<< endl;
        }
        permission="Taxiing";
    }
    doingNothing=true;
    instruction=Instruction;
    return true;
}














void Airplane::progressCheck() {
    if(checkprocedure=="Just landed"){
        if(isDoingNothing()){
            /*
            int totalminute=0.5+passenger*1.0/2;
            actionDone=currentTime+totalminute;*/
            if(size=="small"){
                actionDone=currentTime+5;
            }
            else if(size=="medium"){
                actionDone=currentTime+10;
            }
            else if(size=="large"){
                actionDone=currentTime+15;
            }
            doingNothing=false;
        }
        if(actionDone==currentTime) {
            checkprocedure = "Technical control";
        }
    }
    if(checkprocedure=="Technical control"){
        if(isDoingNothing()){
            if(size=="small"){
                actionDone=currentTime++;
            }
            else if(size=="medium"){
                actionDone=currentTime+2;
            }
            else if(size=="large"){
                actionDone=currentTime+3;
            }
            doingNothing=false;
        }
        if(actionDone==currentTime) {
            doingNothing=true;
            checkprocedure="Refueling";
        }
    }
    else if(checkprocedure=="Refueling"){
        if(isDoingNothing()){
            int totalminue=fuelCapacity*1.0/10000+0.9999;
            actionDone=currentTime+totalminue;
            doingNothing=false;
        }
        if(actionDone==currentTime) {
            doingNothing=true;
            checkprocedure="Boarding";
        }
    }
    else if(checkprocedure=="Boarding"){
        if(isDoingNothing()){/*
            int totalminute=0.5+passenger*1.0/2;
            actionDone=currentTime+totalminute;*/
            if(size=="small"){
                actionDone=currentTime+5;
            }
            else if(size=="medium"){
                actionDone=currentTime+10;
            }
            else if(size=="large"){
                actionDone=currentTime+15;
            }
            doingNothing=false;
        }
        if(actionDone==currentTime) {
            doingNothing=true;
            checkprocedure="Ready to leave";
        }
    }
    else if(checkprocedure=="Ready to leave"){
        checkprocedure="Ready to leave";
    }
}




void Airplane::resetCheckProcedure() {
    checkprocedure="Just landed";
}


bool Airplane::fall() {
    REQUIRE(height >= 1000, "vliegtuig is te laag!");
    if(isDoingNothing()){
        if(engine=="jet"){
            actionDone=currentTime++;
        }
        else if(engine=="propeller"){
            actionDone=currentTime+2;
        }
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        height -= 1000;
        doingNothing=true;
        return true;
    }
    return false;
}

bool Airplane::rise() {
    //REQUIRE(signal)
    if(isDoingNothing()){
        if(engine=="jet"){
            actionDone=currentTime++;
        }
        else if(engine=="propeller"){
            actionDone=currentTime+2;
        }
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        height += 1000;
        doingNothing=true;
        return true;
    }
    return false;
}


bool Airplane::landing() {
    if(isDoingNothing()){
        actionDone=currentTime+2;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        doingNothing=true;
        status="Landed";
        return true;
    }
    return false;
}

bool Airplane::takeOff() {
    if(isDoingNothing()){
        if(engine=="jet"){
            actionDone=currentTime+2;
        }
        else if(engine=="propeller"){
            actionDone=currentTime+3;
        }
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        doingNothing=true;
        return true;
    }
    return false;
}



void Airplane::timeRuns() {
    currentTime=currentTime++;
}

bool Airplane::pushBack() {
    if(isDoingNothing()){
        if(size=="small"){
            actionDone=currentTime+1;
        }
        else if(size=="medium"){
            actionDone=currentTime+2;
        }

        else if(size=="large"){
            actionDone=currentTime+3;
        }
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        doingNothing=true;
        return true;
    }
    return false;
}

bool Airplane::taxiing() {
    if(isDoingNothing()){
        actionDone=currentTime+5;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        doingNothing=true;
        return true;
    }
    return false;
}

bool Airplane::liningUp() {
    if(isDoingNothing()){
        actionDone=currentTime+1;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        destinaterunway->setPlaneAtbegin(this);
        if(permission=="Fly"){
            destinaterunway->setCurrentairplane(this);
        }
        doingNothing=true;
        return true;
    }
    return false;
}

bool Airplane::crossingRunway() {
    if(isDoingNothing()){
        actionDone=currentTime+1;
        location->setCrossing(true);
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        location->setCrossing(false);
        permission="";
        doingNothing=true;
        return true;
    }
    return false;
}







