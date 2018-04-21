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

int Airplane::getFuel() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getFuel");
    //ENSURE(fuel!=NULL,"returning a null object fuel");
    return fuel;
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
    //if(height>stoi(permission)){
    height -= 1000;
    return true;
    //}
    //else{
        return false;
    //}
}

bool Airplane::rise() {
    //REQUIRE(signal)
    height+=1000;
    return true;
}

void Airplane::setPassenger(int passenger) {
    Airplane::passenger = passenger;
}

void Airplane::setFuel(int fuel) {
    Airplane::fuel = fuel;
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
    Airplane::permission = descendingpermission;
}

bool Airplane::sendSignalApproaching() {
    return destination->receiveSignal(this,"Approaching");
}

bool Airplane::sendSignalLeaving() {
    return destination->receiveSignal(this,"Leaving");
}

bool Airplane::sendSignalTaxiingtoGate() {
    return destination->receiveSignal(this,"ApproachingtoGate");
}

bool Airplane::sendSignalTaxiingtoRunway() {
    return destination->receiveSignal(this,"LeavingtoRunway");
}

bool Airplane::sendSignalEmergency() {
    return destination->receiveSignal(this,"Emergency");
}

void Airplane::setLocation(Location *location) {
    Airplane::location = location;
}

Airplane::Airplane(const string &status, const string &number, const string &callsign, const string &model,
                   const string &type, const string &engine, const string &size, int passenger, int fuel,
                   int passengerCapacity, Airport *destination) : number(number), callsign(callsign),
                                                                  model(model), type(type), engine(engine), size(size),
                                                                  passenger(passenger), fuel(fuel),
                                                                  passengerCapacity(passengerCapacity),
                                                                  destination(destination) {
    REQUIRE(find(allowedstatus.begin(),allowedstatus.end(),status)!=allowedstatus.end(),"a wrong status string has been passed to the initiator of the airplane");
    Airplane::status=status;
    _initcheck=this;
    if (status=="Approaching"){
        height=10000;
        checkprocedure="";
    }
    else{
        height=0;
        checkprocedure="";
    }
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
    if(checkprocedure==""){
        checkprocedure="Technical control";
    }
    else if(checkprocedure=="Technical control"){
        checkprocedure="Refueling";
    }
    else if(checkprocedure=="Refueling"){
        checkprocedure="Ready to leave";
    }
    else if(checkprocedure=="Ready to leave"){
        checkprocedure="";
    }
}

const string &Airplane::getCheckprocedure() const {
    return checkprocedure;
}


bool Airplane::sendSignalPushBack() {
    return destination->receiveSignal(this,"Push back");
}

const vector<Location *> &Airplane::getInstruction() const {
    return instruction;
}

void Airplane::setInstruction(const vector<Location *> &instruction) {
    Airplane::instruction = instruction;
}
