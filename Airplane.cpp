//
// Created by c6222 on 2018/3/8.
//

#include "Airplane.h"
#include "DesignByContract.h"


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
    return output;
}

Airplane::Airplane(const string &status, int passenger, int fuel, const string &number, const string &callsign,
                   const string &model, int passengerCapacity) : status(status), passenger(passenger), fuel(fuel),
                                                                 number(number), callsign(callsign), model(model),
                                                                 passengerCapacity(passengerCapacity) {
    _initcheck=this;
    if (status=="Approaching"){
        height=10000;
    }
    else{
        height=0;
    }
    ENSURE(ProperInitialized(),"this airplane object failed to Initialize properly");
}

void Airplane::setStatus(const string &status) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
    Airplane::status = status;
    ENSURE(getStatus()==status,"setStatus Postcondition failed");
}

bool Airplane::ProperInitialized() const {
    return _initcheck==this;
}

bool Airplane::dalen() {
    REQUIRE(height>=1000,"vliegtuig is te laag!");
    height-=1000;
    return true;
}

bool Airplane::stijgen() {
    //REQUIRE(signal)
    return true;
}
