//
// Created by c6222 on 2018/3/8.
//

#include "Airplane.h"
#include "DesignByContract.h"
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
    REQUIRE(find(allowedstatus.begin(),allowedstatus.end(),status)!=allowedstatus.end(),"Airplane's condition is not correct");
    Airplane::status = status;
    ENSURE(getStatus()==status,"setStatus Postcondition failed");
}

void Airplane::setPassenger(int passenger) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
    REQUIRE(passenger>=0,"passenger must be bigger than zero!");
    REQUIRE(passenger<=getPassengerCapacity(),"passenger must be lesser than capacity!");
    Airplane::passenger = passenger;
    ENSURE(getPassenger()==passenger,"setPassenger postcondition failed");
}

void Airplane::setFuel(int fuel) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setFuel");
    REQUIRE(fuel>=0,"fuel must be bigger than zero!");
    REQUIRE(fuel<=getFuelCapacity(),"fuel must be lesser than capacity!");
    Airplane::fuel = fuel;
    ENSURE(getFuel()==fuel,"setFuel postcondition failed");
}

void Airplane::setFuelCapacity(int fuel) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPassenger");
    REQUIRE(fuel>=0,"fuelcapacity must be bigger than zero!");
    REQUIRE(fuel>=getFuel(),"fuelcapacity must be bigger than fuel!");
    Airplane::fuelCapacity = fuel;
    ENSURE(getFuelCapacity()==fuel,"setFuelCapacity postcondition failed");
}

void Airplane::setPermission(string descendingpermission) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPermission");
    if(descendingpermission!="0"){
        //...
    }
    Airplane::permission = descendingpermission;
    ENSURE(getPermission()==descendingpermission,"setPermission postcondition failed");
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
    Airplane::fuel=fuelCapacity;
    ENSURE(ProperInitialized(),"this airplane object failed to Initialize properly");
}








//all signals
bool Airplane::sendSignalApproaching() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Approaching");
    REQUIRE(getStatus()=="Approaching"&&getHeight()==10000,"Airplane can only contact tower if it's approaching at height 10000");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalLeaving() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Leaving");
    REQUIRE(getStatus()=="Leaving"&&getPermission()!="Fly","Leaving signal should only be sent when airplane is leaving and already standing at runway");
    REQUIRE(getLocation()==getDestinateRunway()&&getDestinateRunway()->getCurrentairplane()==this,"Leaving signal should only be sent when runway are set properly");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalTaxiingtoGate() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoGate");
    REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane can only taxi to gate if it just landed on the runway");
    REQUIRE(getStatus()=="Landed","Airplane can only taxi to gate if its just landed");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalTaxiingtoRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoRunway");
    REQUIRE(getCheckProcedure()=="Ready to leave","Airplane should only be able to taxi to runway after technical check");
    REQUIRE(getStatus()=="Standing at gate","Airplane should only be able to taxi to runway if its at gate right now");
    REQUIRE(getPermission()=="Push back","Airplane should only be able to taxi to runway after push back");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}


bool Airplane::sendSignalPushBack() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal PushBack");
    REQUIRE(getCheckProcedure()=="Ready to leave","Airplane should only be able to push back after technical check");
    REQUIRE(getPermission()=="IFR clearancy","Airplane shouldnt request push back when IFR are not cleared");
    REQUIRE(getStatus()=="Standing at gate","Airplane shouldnt request push back if it's not at gate");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;

        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<" at gate "<<this->getLocation()->getName()<<", requesting pushback"<<endl;
        bool received=destination->receiveSignal(this,"Push back");
        ENSURE(received==true,"Tower didnt receive the signal Push back");
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalCrossingRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal CrossingRunway");
    REQUIRE(getLocation()->isRunway()&&getLocation()!=getDestinateRunway(),"Airplane must be at an runway that isn't its destination");
    REQUIRE(getPermission()=="Taxiing","Airplane must have the permission to taxi");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalAtRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal AtRunway");
    REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane must be at its destinate runway");
    REQUIRE(getStatus()=="Taxiing to runway","Airplane must be taxiing to runway");
    REQUIRE(getPermission()=="Taxiing","Airplane must have the permission to taxi");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}


bool Airplane::sendSignalIFR() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal IFR");
    REQUIRE(getLocation()->isGate()&&getLocation()->isOnuse(),"Airplane must be standing at gate while asking IFR clearancy");
    REQUIRE(getStatus()=="Standing at gate","Airplane shouldnt request IFR clearancy if it's not at gate");
    REQUIRE(getCheckProcedure()=="Ready to leave","Airplane should only be able to ask for IFR clearancy after technical check");
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
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}












//receive signals
bool Airplane::receiveSignal(string signal) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a normal signal");
    REQUIRE(find(allowedReceiveSignal.begin(),allowedReceiveSignal.end(),signal)!=allowedReceiveSignal.end(),"Airplane has received a signal which it doesnt recongizes");
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
    else{
        cerr<<"Error signal"<<endl;
        return false;
    }
    doingNothing=true;
    //optimization possible
    if(signal=="Keep Flying"){
        doingNothing=false;
    }
    return true;
}



bool Airplane::receiveLandingSignal(Runway *runway) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a landing signal");
    REQUIRE(runway!=NULL,"Airplane has received a runway which is NULL, to land");
    REQUIRE(getStatus()=="Approaching"&&height==3000&&getPermission()=="3000","Airplane should only gets a landing signal when its at height 3000 and approaching");

    setDestinateRunway(runway);
    //setPermission("0");
    permission="0";

    destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
    destination->getTower().getFile() << "Cleared ILS approach runway " << runway->getName() << ", " << this->getCallsign() << endl;
    doingNothing=true;

    ENSURE(getPermission()=="0"&&isDoingNothing(),"receiveLandingSignal postcondition failed");
    return true;

}


bool Airplane::receiveInstruction(vector<Location *> Instruction, bool adding) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving an instruction");
    REQUIRE(Instruction.size()>1,"Airplane has received an instruction which has only one or less location");
    REQUIRE(find(Instruction.begin(),Instruction.end(),location)!=getInstruction().end(),"Airplane must have a correct taxi instruction with its own location");

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

    ENSURE((getPermission()=="Taxiing"||getPermission()=="Cleared to cross")&&isDoingNothing(),"receiveLandingSignal postcondition failed");
    return true;
}







void Airplane::timeRuns() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when time flies");
    currentTime=currentTime++;
}







void Airplane::progressCheck() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving doing the technical check");
    REQUIRE(getStatus()=="Standing at gate","Airplane must be standing at gate while doing the technical check");

    if(checkprocedure=="Just landed"){
        if(isDoingNothing()){
            permission="";//resetting the permission beacause airplane is currently checking
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
            doingNothing=true;
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
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when resetting the technical check status");
    checkprocedure="Just landed";
    ENSURE(getCheckProcedure()=="Just landed","reset checkprocedure failed");
}


bool Airplane::fall() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when falling");
    REQUIRE(getHeight() >= 1000, "airplane is too low to fall!! Its lower than 1000 meter");
    REQUIRE(getStatus()=="Approaching"||getStatus()=="Emergency","Airplane can only fall if it's approaching or having emergency");
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
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when rising");
    REQUIRE(getStatus()=="Leaving","Airplane can only rise if it's leaving");
    REQUIRE(getPermission()=="Fly","Airplane can only rise if it has the flying permission");
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
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when landing");
    REQUIRE(getStatus()=="Approaching"||getStatus()=="Emergency","Airplane can only land if it's approaching");
    REQUIRE(getPermission()=="0","Airplane can only land if it got the permission of landing");
    REQUIRE(getDestinateRunway()!=NULL,"Airplane can only land if it knows which runway to land");

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
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when takingOff");
    REQUIRE(getStatus()=="Leaving","Airplane can only takeOff if it is leaving");
    REQUIRE(getPermission()=="Fly","Airplane can only takeOff if it has the fly permission");

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




bool Airplane::pushBack() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when pushing back");
    REQUIRE(getStatus()=="Standing at gate"&&getLocation()->isGate(),"Airplane can only push back if it is standing at an gate");
    REQUIRE(getPermission()=="Push back","Airplane must get the permission to push back");

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
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when taxiing");
    REQUIRE(getStatus()=="Taxiing to runway"||getStatus()=="Taxiing to gate","Airplane can only taxi if it is taxiing to a gate or a runway");
    REQUIRE(getPermission()=="Taxiing","Airplane must get the permission to taxi");
    REQUIRE(find(getInstruction().begin(),getInstruction().end(),location)!=getInstruction().end(),"Airplane must have a correct taxi instruction with its own location");
    REQUIRE(find(getInstruction().begin(),getInstruction().end(),location)!=getInstruction().end()-1,"Airplane already finished taxi");

    if(isDoingNothing()){
        actionDone=currentTime+5;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        doingNothing=true;

        if(location->isTaxipoint()){
            this->getDestination()->findTaxipoint(location->getName())->removePlanesWaiting(this);
            if(this->getDestination()->findTaxipoint(location->getName())->getPlanesWaiting().size()==0){
                location->setOnuse(false);
            }
        }

        return true;

    }
    return false;
}

bool Airplane::liningUp() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when liningUp");
    REQUIRE(getStatus()=="Taxiing to runway","Airplane can only taxi if it is taxiing to a runway");
    REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane can only lineUp if it's at the destinate runway");
    REQUIRE(getPermission()=="Line up"||getPermission()=="Fly","Airplane must get permission to line up");
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
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when crossing runway");
    REQUIRE(getStatus()=="Taxiing to runway"||getStatus()=="Taxiing to gate","Airplane can only taxi if it is taxiing to a runway");
    REQUIRE(getPermission()=="Cleared to cross","Airplane must get permission to cross runway");
    REQUIRE(getLocation()->isRunway()&&getLocation()!=getDestinateRunway(),"Airplane shouldnt cross its destinate runway");

    if(isDoingNothing()){
        actionDone=currentTime+1;
        location->setCrossing(true);
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        location->setCrossing(false);
        permission="Taxiing";
        //the permission should be back to taxiing.
        doingNothing=true;
        return true;
    }
    return false;
}







