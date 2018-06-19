//
// Created by c6222 on 2018/3/8.
//

#include "Airplane.h"
#include "DesignByContract.h"
#include "AirportUtils.h"
#include "Airport.h"
#include "Runway.h"
#include "Taxipoint.h"
#include "Gate.h"

//getters
const Airplane::Airplaneallowedstatus &Airplane::getStatus() const {
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

const Airplane::AirplaneallowedPermission &Airplane::getPermission() const {
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

const Airplane::AirplaneCheckProcedure &Airplane::getCheckProcedure() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getCheckProcedure");
    return checkprocedure;
}

bool Airplane::ProperInitialized() const {
    return _initcheck==this;
}



//setters
void Airplane::setStatus(const Airplaneallowedstatus &status) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setStatus");
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

void Airplane::setPermission(AirplaneallowedPermission descendingpermission) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setPermission");
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
Airplane::Airplane(const Airplaneallowedstatus &status, const string &number, const string &callsign, const string &model,
                   const string &type, const string &engine, const string &size, int passenger, int fuel,
                   int passengerCapacity, Airport *destination, const string &des,int departure, int arrival, int interval) : number(number), callsign(callsign),
                                                                  model(model), type(type), engine(engine), size(size),
                                                                  passenger(passenger), fuelCapacity(fuel),
                                                                  passengerCapacity(passengerCapacity),
                                                                  destination(destination),des(des),departure(departure),arrival(arrival),interval(interval) {
    Airplane::status=status;
    _initcheck=this;
    if (status==Approaching){
        height=10000;
    }
    else{
        height=0;
    }
    squawkcode=0;
    checkprocedure=Just_landed;
    actionDone=currentTime+(-1);
    doingNothing=true;
    Airplane::fuel=fuelCapacity;
    permission=empty;
    ENSURE(ProperInitialized(),"this airplane object failed to Initialize properly");
}








//all signals
bool Airplane::sendSignalApproaching() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Approaching");
    REQUIRE(getStatus()==Approaching&&getHeight()==10000,"Airplane can only contact tower if it's approaching at height 10000");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", "<<"arriving at "<<destination->getName()<<endl;
        //doingNothing=true;
        bool received=destination->receiveSignal(this,Signaltower::Approaching);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalLeaving() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Leaving");
    REQUIRE(getStatus()==Leaving&&getPermission()!=FlyPermission,"Leaving signal should only be sent when airplane is leaving and already standing at runway");
    REQUIRE(getLocation()==getDestinateRunway()&&getDestinateRunway()->getCurrentairplane()==this,"Leaving signal should only be sent when runway are set properly");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        bool received=destination->receiveSignal(this,Signaltower::Leaving);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalTaxiingtoGate() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoGate");
    REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane can only taxi to gate if it just landed on the runway");
    REQUIRE(getStatus()==Landed,"Airplane can only taxi to gate if its just landed");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", " <<this->getCallsign()<<", "<<"Runway " <<this->getLocation()->getName()<<" Vacated"<<endl;
        bool received=destination->receiveSignal(this,Signaltower::ApproachingtoGate);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalTaxiingtoRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal TaxiingtoRunway");
    REQUIRE(getCheckProcedure()==Ready_to_leave,"Airplane should only be able to taxi to runway after technical check");
    REQUIRE(getStatus()==Standing_at_gate,"Airplane should only be able to taxi to runway if its at gate right now");
    REQUIRE(getPermission()==Push_backPermission,"Airplane should only be able to taxi to runway after push back");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"["<<getCallsign()<<"]"<<endl;
        destination->getTower().getFile()<<this->getCallsign()<<" is ready to taxi."<<endl;
        bool received=destination->receiveSignal(this,Signaltower::LeavingtoRunway);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalEmergency() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal Emergency");
    //REQUIRE(getStatus()==Emergency,"Airplane shouldnt request emergency if it's not in emergency");
    //REQUIRE(getType()=="Emergency","Airplane shouldnt request emergency if it's not in emergency");
    if(isDoingNothing()){
        actionDone=currentTime;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        doingNothing=false;
        if(getHeight()>=3000){
            ostream& stream = destination->getTower().getFile();
            stream<<"["<<currentTime<<"]"<<"["<<getCallsign()<<"]"<<endl;
            stream<<"Mayday mayday mayday, "<<destination->getCallsign()<<", "<<getCallsign()<<", out of fuel, request immediate landing, "<<getPassenger()<<" persons on board."<<endl;
        }
        else{
            ostream& stream = destination->getTower().getFile();
            stream<<"["<<currentTime<<"]"<<"["<<getCallsign()<<"]"<<endl;
            stream<<"Mayday mayday mayday, "<<destination->getCallsign()<<", "<<getCallsign()<<", out of fuel, performing emergency landing, "<<getPassenger()<<" persons on board."<<endl;
        }
        setSquawkcode(7700);
        bool received=destination->receiveSignal(this,Signaltower::Emergency);
        return received;
    }
    return false;
}


bool Airplane::sendSignalPushBack() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal PushBack");
    REQUIRE(getCheckProcedure()==Ready_to_leave,"Airplane should only be able to push back after technical check");
    REQUIRE(getPermission()==IFR_clearancyPermission,"Airplane shouldnt request push back when IFR are not cleared");
    REQUIRE(getStatus()==Standing_at_gate,"Airplane shouldnt request push back if it's not at gate");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;

        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<" at gate "<<this->getLocation()->getName()<<", requesting pushback"<<endl;
        bool received=destination->receiveSignal(this,Signaltower::Push_back);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalCrossingRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal CrossingRunway");
    REQUIRE(getLocation()->isRunway()&&getLocation()!=getDestinateRunway(),"Airplane must be at an runway that isn't its destination");
    REQUIRE(getPermission()==TaxiingPermission,"Airplane must have the permission to taxi");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", " <<this->getCallsign()<<", "<<"Hold short at " <<location->getName()<<endl;
        bool received=destination->receiveSignal(this,Signaltower::Crossing_runway);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}

bool Airplane::sendSignalAtRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal AtRunway");
    REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane must be at its destinate runway");
    REQUIRE(getStatus()==Taxiing_to_runway,"Airplane must be taxiing to runway");
    REQUIRE(getPermission()==TaxiingPermission,"Airplane must have the permission to taxi");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", holding short at "<<this->getLocation()->getName()<<endl;
        bool received=destination->receiveSignal(this,Signaltower::At_runway);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}


bool Airplane::sendSignalIFR() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when sending signal IFR");
    REQUIRE(getLocation()->isGate()&&getLocation()->isOnuse(),"Airplane must be standing at gate while asking IFR clearancy");
    REQUIRE(getStatus()==Standing_at_gate,"Airplane shouldnt request IFR clearancy if it's not at gate");
    REQUIRE(getCheckProcedure()==Ready_to_leave,"Airplane should only be able to ask for IFR clearancy after technical check");
    if(isDoingNothing()){
        actionDone=currentTime++;
        doingNothing=false;
    }
    else if(actionDone==currentTime) {
        //doingNothing=true;
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<destination->getCallsign()<<", "<<this->getCallsign()<<", requesting IFR clearancy to "<<this->getDestination()->getCallsign()<<endl;
        bool received=destination->receiveSignal(this,Signaltower::IFR_clearancy);
        return received;
    }
    //ENSURE(actionDone>=currentTime,"airplane's action was skipped!");
    return false;
}












//receive signals
bool Airplane::receiveSignal(AirplaneallowedSignal signal) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a normal signal");
    if(signal==Keep_flying){
        destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
        destination->getTower().getFile() << "Hold south on the one eighty radial, " << this->getCallsign() << endl;
    }
    else if(signal==threeThousand){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Descend and maintain three thousand feet, "<<this->getCallsign()<<endl;
        permission=threeThousandPermission;
    }
    else if(signal==fiveThousand){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Descend and maintain five thousand feet, ";
        permission=fiveThousandPermission;
    }
    else if(signal==Cleared_to_cross){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Cleared to Cross runway "<<location->getName()<<", "<<this->getCallsign();
        permission=Cleared_to_crossPermission;
    }
    else if(signal==Hold_position){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Hold position, "<<this->getCallsign()<<endl;
    }
    else if(signal==Line_up){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Line up runway "<<this->getDestinateRunway()->getName()<<" and wait."<<this->getCallsign()<<endl;
        permission=LineupPermission;
    }
    else if(signal==Fly){
        destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
        destination->getTower().getFile() << "runway " <<this->getDestinateRunway()->getName() << " cleared for take-off, "
                                          << this->getCallsign() << endl;
        permission=FlyPermission;
    }
    else if(signal==IFR_clearancy){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Cleared to "<<this->getDestination()->getCallsign()<<" , initial altitude five thousand, expecting one zero zero in ten,";
        permission=IFR_clearancyPermission;
    }
    else if(signal==Push_back){
        destination->getTower().getFile()<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
        destination->getTower().getFile()<<"Pushback approved, "<<this->getCallsign()<<endl;
        permission=Push_backPermission;
    }
    else if(signal==EmergencySignal){
        setStatus(Emergency);
        doingNothing=true;
    }
    else{
        cerr<<"Error signal"<<endl;
        return false;
    }
    doingNothing=true;
    //optimization possible
    if(signal==Keep_flying){
        doingNothing=false;
    }
    ENSURE(signal==Keep_flying||doingNothing==true,"receiveSignal postcondition failed");
    return true;
}



bool Airplane::receiveLandingSignal(Runway *runway) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving a landing signal");
    REQUIRE(runway!=NULL,"Airplane has received a runway which is NULL, to land");
    REQUIRE(getStatus()==Approaching&&height==3000&&getPermission()==threeThousandPermission,"Airplane should only gets a landing signal when its at height 3000 and approaching");

    setDestinateRunway(runway);
    //setPermission("0");
    permission=LandingPermission;

    destination->getTower().getFile() << "[" << currentTime << "]" << "[AIR]" << endl;
    destination->getTower().getFile() << "Cleared ILS approach runway " << runway->getName() << ", " << this->getCallsign() << endl;
    doingNothing=true;

    ENSURE(getPermission()==LandingPermission&&isDoingNothing(),"receiveLandingSignal postcondition failed");
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
        permission=TaxiingPermission;
    }
    doingNothing=true;
    instruction=Instruction;

    ENSURE((getPermission()==TaxiingPermission||getPermission()==Cleared_to_crossPermission)&&isDoingNothing(),"receiveLandingSignal postcondition failed");
    return true;
}







void Airplane::timeRuns() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when time flies");
    currentTime=currentTime++;
}







void Airplane::progressCheck() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when receiving doing the technical check");
    REQUIRE(getStatus()==Standing_at_gate||getStatus()==Emergency,"Airplane must be standing at gate/Emergency while doing the technical check");

    if(checkprocedure==Just_landed){
        if(isDoingNothing()){
            permission=empty;//resetting the permission beacause airplane is currently checking
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
            passenger=0;
            doingNothing=true;
            checkprocedure = Technical_control;
        }
    }
    else if(checkprocedure==Technical_control){
        if(isDoingNothing()){
            permission=empty;//resetting the permission beacause airplane is currently checking

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
            checkprocedure=Refueling;
        }
    }
    else if(checkprocedure==Refueling){
        if(isDoingNothing()){
            permission=empty;//resetting the permission beacause airplane is currently checking

            int totalminue=fuelCapacity*1.0/10000+0.9999;
            actionDone=currentTime+totalminue;
            doingNothing=false;
        }
        if(actionDone==currentTime) {
            setFuel(fuelCapacity);
            doingNothing=true;
            checkprocedure=Boarding;
        }
    }
    else if(getStatus()==Emergency){
        setStatus(Landed);
        destinaterunway->setOnuse(false);
        destinaterunway->setPlaneAtEnd(this);
        destinaterunway->setEmergency(false);

        //resetCheckProcedure();
        sendSignalTaxiingtoGate();
    }
    else if(checkprocedure==Boarding){
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
            permission=empty;//resetting the permission beacause airplane is currently checking
            doingNothing=false;
        }
        if(actionDone==currentTime) {
            doingNothing=true;
            checkprocedure=Ready_to_leave;
        }
    }
    else if(checkprocedure==Ready_to_leave){
        permission=empty;//resetting the permission beacause airplane is currently checking
        checkprocedure=Ready_to_leave;
    }
}



void Airplane::resetCheckProcedure() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when resetting the technical check status");
    checkprocedure=Just_landed;
    ENSURE(getCheckProcedure()==Just_landed,"reset checkprocedure failed");
}


bool Airplane::fall() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when falling");
    REQUIRE(getStatus()==Approaching||getStatus()==Emergency,"Airplane can only fall if it's approaching or having emergency");
    REQUIRE((getHeight() >= 1000&& getStatus()==Approaching) || (getHeight()>=500 && getStatus()==Emergency), "airplane is too low to fall!! Its lower than 1000 meter");
    if(isDoingNothing()){
        if(getStatus()==Emergency){
            actionDone=currentTime++;
        }
        else if(engine=="jet"){
            actionDone=currentTime++;
        }
        else if(engine=="propeller"){
            actionDone=currentTime+2;
        }

        doingNothing=false;
    }
    else if(actionDone==currentTime){
        if(getStatus()==Emergency){
            height -=500;
        }
        else{
            height -= 1000;
        }
        doingNothing=true;
        return true;
    }
    return false;
}

bool Airplane::rise() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when rising");
    REQUIRE(getStatus()==Leaving,"Airplane can only rise if it's leaving");
    REQUIRE(getPermission()==FlyPermission,"Airplane can only rise if it has the flying permission");
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
    REQUIRE(getStatus()==Approaching||getStatus()==Emergency,"Airplane can only land if it's approaching");
    REQUIRE(getPermission()==LandingPermission,"Airplane can only land if it got the permission of landing");
    REQUIRE(getDestinateRunway()!=NULL,"Airplane can only land if it knows which runway to land");

    if(isDoingNothing()){
        actionDone=currentTime+2;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        doingNothing=true;
        if(getStatus()==Approaching){
            status=Landed;
        }
        return true;
    }
    ENSURE(!isDoingNothing()||status==Landed||status==Emergency,"status must be landed/Emergency when landing has been finished!");
    return false;
}

bool Airplane::takeOff() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when takingOff");
    REQUIRE(getStatus()==Leaving,"Airplane can only takeOff if it is leaving");
    REQUIRE(getPermission()==FlyPermission,"Airplane can only takeOff if it has the fly permission");

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
    REQUIRE(getStatus()==Standing_at_gate&&getLocation()->isGate(),"Airplane can only push back if it is standing at an gate");
    REQUIRE(getPermission()==Push_backPermission,"Airplane must get the permission to push back");

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
    REQUIRE(getStatus()==Taxiing_to_runway||getStatus()==Taxiing_to_gate,"Airplane can only taxi if it is taxiing to a gate or a runway");
    REQUIRE(getPermission()==TaxiingPermission,"Airplane must get the permission to taxi");
    REQUIRE(!getInstruction().empty(),"Airplane doesnt have any instruction yet!");
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
    REQUIRE(getStatus()==Taxiing_to_runway,"Airplane can only lineup if it is taxiing to a runway");
    REQUIRE(getLocation()->isRunway()&&getLocation()==getDestinateRunway(),"Airplane can only lineUp if it's at the destinate runway");
    REQUIRE(getPermission()==LineupPermission||getPermission()==FlyPermission,"Airplane must get permission to line up");
    if(isDoingNothing()){
        actionDone=currentTime+1;
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        destinaterunway->setPlaneAtbegin(this);
        if(permission==FlyPermission){
            destinaterunway->setCurrentairplane(this);
        }
        doingNothing=true;
        return true;
    }
    ENSURE(!isDoingNothing()||getDestinateRunway()->getPlaneAtbegin()==this,"lining up postcondition failed");
    return false;
}

bool Airplane::crossingRunway() {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when crossing runway");
    REQUIRE(getStatus()==Taxiing_to_runway||getStatus()==Taxiing_to_gate,"Airplane can only taxi if it is taxiing to a runway");
    REQUIRE(getPermission()==Cleared_to_crossPermission,"Airplane must get permission to cross runway");
    REQUIRE(getLocation()->isRunway()&&getLocation()!=getDestinateRunway(),"Airplane shouldnt cross its destinate runway");

    if(isDoingNothing()){
        actionDone=currentTime+1;
        location->setCrossing(true);
        doingNothing=false;
    }
    else if(actionDone==currentTime){
        location->setCrossing(false);
        permission=TaxiingPermission;
        //the permission should be back to taxiing.
        doingNothing=true;
        return true;
    }
    ENSURE((isDoingNothing()&&!getLocation()->isCrossing())||(!isDoingNothing()&&getLocation()->isCrossing()),"crossingRunway postcondition failed");
    return false;
}

int Airplane::getSquawkcode() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getSquawkcode");
    return squawkcode;
}

void Airplane::setSquawkcode(int squawkcode) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling setSquawkcode");
    REQUIRE(validSquawkcode(squawkcode),"the squawkcode that has been giving is not valid");
    Airplane::squawkcode = squawkcode;
    ENSURE(getSquawkcode()==squawkcode,"setSquawkcode postcondition failed");
}

bool Airplane::receiveSquawkcode(int squawkcode) {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling receiveSquawkcode");
    REQUIRE(validSquawkcode(squawkcode),"the squawkcode that has been giving is not valid");
    Airplane::squawkcode = squawkcode;

    destination->getTower().getFile()<< "squawking ";

    destination->getTower().getFile() <<    fillingintegergap(squawkcode,4)<< " ,"<<this->getCallsign()<<endl;
    ENSURE(getSquawkcode()==squawkcode,"receiveSquawkcode postcondition failed");
    return false;
}

void Airplane::fuelReduction() {
    if((getStatus()==Leaving&&getPermission()==FlyPermission) || getStatus()==Approaching || getStatus() == Emergency){
        if(fuel>0){
            int reduction=0;
            if(getSize()=="small"){
                reduction+=10;
            }
            else if(getSize()=="medium"){
                reduction+=50;
            }
            else if(getSize()=="large"){
                reduction+=100;
            }
            if(getEngine()=="jet"){
                reduction*=2.5;
            }
            fuel-=reduction;
        }
    }
}

const string &Airplane::getDes() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDes");
    return des;
}

int Airplane::getDeparture() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getDeparture");
    return departure;
}

int Airplane::getArrival() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getArrival");
    return arrival;
}

int Airplane::getInterval() const {
    REQUIRE(ProperInitialized(),"Airplane wasn't initialized when calling getInterval");
    return interval;
}
bool Airplane::flightPlanActivated(){
    REQUIRE(ProperInitialized(),"Airplane wasn't initalized when calling flightPlanActivated");
    return!(getDes()==""&&getInterval()==0);
}

void Airplane::setHeight(int height) {
    Airplane::height = height;
}

void Airplane::setCurrentTime(const Time &currentTime) {
    Airplane::currentTime = currentTime;
}

