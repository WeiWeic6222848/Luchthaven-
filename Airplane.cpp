//
// Created by c6222 on 2018/3/8.
//

#include "Airplane.h"
#include "DesignByContract.h"
#include "algorithm"
#include "AirportUtils.h"

const string &Airplane::getStatus() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getStatus");
    //ENSURE(status!=NULL,"returning a null object status");
    return status;
}

int Airplane::getPassenger() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassenger");
    //ENSURE(passenger!=NULL,"returning a null object passenger");
    return passenger;
}

int Airplane::getFuelCapacity() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuel");
    //ENSURE(fuel!=NULL,"returning a null object fuel");
    return fuelCapacity;
}

const string &Airplane::getNumber() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getNumber");
    return number;
}

const string &Airplane::getCallsign() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCallsign");
    return callsign;
}

const string &Airplane::getModel() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getModel");
    return model;
}

int Airplane::getPassengerCapacity() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getPassengerCapacity");
    return passengerCapacity;
}

std::ostream& operator<<(std::ostream& output,Airplane& airplane){
    REQUIRE(airplane.ProperInitialized(),"Airplane wasn't initialized when getting output");
    output<<"Airplane: "<<airplane.getCallsign()<<" ("<<airplane.getNumber()<<")"<<std::endl;
    output<<" -> model: "<<airplane.getModel()<<endl;
    output<<" -> type: "<<airplane.getType()<<endl;
    output<<" -> engine: "<<airplane.getEngine()<<endl;
    output<<" -> size: "<<airplane.getSize()<<endl;
    return output;
}


void Airplane::setStatus(const string &status) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
    Airplane::status = status;
    ENSURE(getStatus()==status,"setStatus Postcondition failed");
}

bool Airplane::ProperInitialized() const {
    return _initcheck==this;
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

void Airplane::setPassenger(int passenger) {
    Airplane::passenger = passenger;
}

void Airplane::setFuelCapacity(int fuel) {
    Airplane::fuelCapacity = fuel;
}

int Airplane::getHeight() const {
    return height;
}

const string &Airplane::getType() const {
    return type;
}

const string &Airplane::getEngine() const {
    return engine;
}

const string &Airplane::getSize() const {
    return size;
}

Airport *Airplane::getDestination() const {
    return destination;
}

void Airplane::setDestination(Airport *destination) {
    Airplane::destination = destination;
}

void Airplane::setPermission(string descendingpermission) {
    if(descendingpermission!="0"){
        //...
    }
    Airplane::permission = descendingpermission;
}

bool Airplane::sendSignalApproaching() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", "<<"arriving at "<<destination->getName()<<endl;
        //doingNothing=true;
        return destination->receiveSignal(this,"Approaching");
    }
    return false;
}

bool Airplane::sendSignalLeaving() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        return destination->receiveSignal(this, "Leaving");
    }
    return false;
}

bool Airplane::sendSignalTaxiingtoGate() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", " <<this->getCallsign()<<", "<<"Runway " <<this->getLocation()->getName()<<" Vacated"<<endl;
        return destination->receiveSignal(this, "ApproachingtoGate");
    }
    return false;
}

bool Airplane::sendSignalTaxiingtoRunway() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<this->getCallsign()<<" is ready to taxi."<<endl;
        return destination->receiveSignal(this, "LeavingtoRunway");
    }
    return false;
}

bool Airplane::sendSignalEmergency() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        return destination->receiveSignal(this, "Emergency");
    }
    return false;
}

void Airplane::setLocation(Location *location) {
    Airplane::location = location;
}

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

const string &Airplane::getPermission() const {
    return permission;
}

Location *Airplane::getLocation() const {
    return location;
}

Runway *Airplane::getDestinaterunway() const {
    return destinaterunway;
}

void Airplane::setDestinaterunway(Runway *destinaterunway) {
    Airplane::destinaterunway = destinaterunway;
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

const string &Airplane::getCheckprocedure() const {
    return checkprocedure;
}


bool Airplane::sendSignalPushBack() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;

        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<" at gate "<<this->getLocation()->getName()<<", requesting pushback"<<endl;
        return destination->receiveSignal(this, "Push back");
    }
    return false;
}

const vector<Location *> &Airplane::getInstruction() const {
    return instruction;
}

void Airplane::setInstruction(const vector<Location *> &instruction) {
    Airplane::instruction = instruction;
}

void Airplane::resetCheckProcedure() {
    checkprocedure="Just landed";
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

const Time &Airplane::getCurrentTime() const {
    return currentTime;
}

void Airplane::setCurrentTime(const Time &currentTime) {
    Airplane::currentTime = currentTime;
}

bool Airplane::isDoingNothing() {
    return doingNothing;
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

bool Airplane::receiveSignal(string signal) {
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
        destination->getTower().getFile()<<"Line up runway "<<this->getDestinaterunway()->getName()<<" and wait."<<this->getCallsign()<<endl;
        permission="Line up";
    }
    else if(signal=="Fly"){
        destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
        destination->getTower().getFile() << "runway " <<this->getDestinaterunway()->getName() << " cleared for take-off, "
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

    setDestinaterunway(runway);
    setPermission("0");

    destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
    destination->getTower().getFile() << "Cleared ILS approach runway " << runway->getName() << ", " << this->getCallsign() << endl;
    doingNothing=true;
    return true;

}

bool Airplane::sendSignalCrossingRunway() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", " <<this->getCallsign()<<", "<<"Hold short at " <<location->getName()<<endl;
        return destination->receiveSignal(this, "Crossing runway");
    }
    return false;
}

bool Airplane::sendSignalAtRunway() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", holding short at "<<this->getLocation()->getName()<<endl;
        return destination->receiveSignal(this, "At runway");
    }
    return false;
}

bool Airplane::receiveInstruction(vector<Location *> Instruction, bool adding) {

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
        else if(Instruction[Instruction.size()-1]==this->getDestinaterunway()){
            destination->getTower().getFile()<<", "<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
        }
        else if(Instruction[Instruction.size()-1]!=this->getDestinaterunway()&&Instruction[Instruction.size()-1]->isRunway()){
            destination->getTower().getFile()<<", "<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
        }
    }
    else{
        if (Instruction[Instruction.size()-1]->isGate()){
            destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            destination->getTower().getFile()<<"Taxi to gate "<<Instruction[Instruction.size()-1]->getName()<<taxipoints<<", "<<this->getCallsign()<<  endl;
        }
        else if(Instruction[Instruction.size()-1]==this->getDestinaterunway()) {
            destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            destination->getTower().getFile()<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints <<", "<<this->getCallsign()<<  endl;
        }
        else if(Instruction[Instruction.size()-1]!=this->getDestinaterunway()&&Instruction[Instruction.size()-1]->isRunway()) {
            destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            destination->getTower().getFile()<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints<<", "<<this->getCallsign()<< endl;
        }
        permission="Taxiing";
    }
    doingNothing=true;
    instruction=Instruction;
    return true;
}

Airport *Airplane::getNextDestination() const {
    return nextDestination;
}

void Airplane::setNextDestination(Airport *nextDestination) {
    Airplane::nextDestination = nextDestination;
}

bool Airplane::sendSignalIFR() {
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", requesting IFR clearancy to "<<this->getDestination()->getCallsign()<<endl;
        return destination->receiveSignal(this, "IFR clearancy");
    }
    return false;
}




