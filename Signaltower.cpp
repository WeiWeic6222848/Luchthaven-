//
// Created by c6222848 on 4/6/18.
//

#include "Signaltower.h"
#include "DesignByContract.h"
#include "AirportUtils.h"
#include "Airport.h"
#include "Airplane.h"
#include "Runway.h"
#include "Taxipoint.h"
#include "Gate.h"


Signaltower::Signaltower(Airport *airport) : airport(airport) {

    REQUIRE(airport->ProperInitialized(),"airport must be initialized properly when calling constructor");
    string filename="../output/"+airport->getIata()+"_Tower.txt";
    doingNothing=true;
    file.open(filename.c_str(),ios::app);
    _initCheck=this;
    buzy3000=false;
    buzy5000=false;
    ENSURE(ProperInitialized(),"Signal tower object failed to initialize properly");
}

bool Signaltower::receiveSignal(Airplane *airplane, SignaltowerallowedSignal signal) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling receiveSignal");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling receiveSignal");
    if (signal==Approaching){
        airplane->setPermission(Airplane::tenThousandPermission);
    }

    if(find(allplaneknown.begin(),allplaneknown.end(),airplane)==allplaneknown.end()){
        allplaneknown.push_back(airplane);
    }

    incomingSignal.push_back(pair<Airplane*,SignaltowerallowedSignal >(airplane,signal));
    return true;

    //else error, below.
    /*
    else if(signal=="ApproachingtoGate"){

        if(isDoingNothing()){
            airplane->setInstruction(vector<Location*>());
            vector<Location*> instruction=makeInstructionToGate(airplane);
            if(instruction.size()>0){
                sendInstruction(airplane,instruction);
            }
        }
        else{
            incomingSignal.push_back(pair<Airplane*,string>(airplane,signal));
        }

        else{
            sendSignalHoldPosition(airplane);
        }
        return true;
    }
    else if(signal=="LeavingtoRunway"){
        if(isDoingNothing()){
            if(airplane->getDestinateRunway()!=NULL){
                airplane->setInstruction(vector<Location*>());
                vector<Location*> instruction=makeInstructionToRunway(airplane);
                if(instruction.size()>0){
                    sendInstruction(airplane,instruction);
                }

                else{
                    sendSignalHoldPosition(airplane);
                }
                return true;
            }
        }
        else{
            incomingSignal.push_back(pair<Airplane*,string>(airplane,signal));
        }
        return false;
    }
    else if(signal=="Emergency"){
        emergency.push_back(airplane);
        return true;
    }
    else if(signal=="Push back"){
        if(isDoingNothing()) {
            Runway *destinaterunway = airport->findFreeRunway(airplane);
            if (destinaterunway) {
                sendSignalPushBack(airplane, destinaterunway);
                return true;
            }
        }
        else{
            incomingSignal.push_back(pair<Airplane*,string>(airplane,signal));
        }
        return false;
    }
    else if(signal=="IFR clearancy"){
        //dont see a reason not to
        if(isDoingNothing()){
            sendSignalIFRclear(airplane);
        }
        else{
            incomingSignal.push_back(pair<Airplane*,string>(airplane,signal));
        }
        return true;
    }
    else if(signal=="Crossing runway"){
        if(isDoingNothing()) {
            Location *runwayToCross = airplane->getLocation();
            if (!runwayToCross->isOnuse() && !runwayToCross->isCrossing()) {
                sendSignalClearedToCross(airplane);
                return true;
            }
        }
        else{
            incomingSignal.push_back(pair<Airplane*,string>(airplane,signal));
        }
        return false;

    }
    else if(signal=="At runway"){
        if(isDoingNothing()){
            Runway* runway=airplane->getDestinateRunway();
            if(!runway->isCrossing()&&!runway->isOnuse()&&runway->getPlaneAtbegin()==NULL){
                sendSignalLineup(airplane,true);
                return true;
            }
            else if(!runway->isOnuse()&&runway->getPlaneAtbegin()==NULL){
                sendSignalLineup(airplane,false);
                return true;
            }

            else{
                sendSignalHoldPosition(airplane);
                return false;
            }
        }
        else{
            incomingSignal.push_back(pair<Airplane*,string>(airplane,signal));
        }
        return false;
    }*/
    cerr<<"error signal"<<endl;
    return false;
}

vector<Location*> Signaltower::makeInstructionToGate(Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling makeInstructionToGate");
    REQUIRE(airplane->ProperInitialized(),"airplane must be initialized properly when calling makeInstructionToGate");
    //overhaul
    vector<Location*> nextStop;
    Airplane* taxiingplane=airplane;
    Location* planelocation=taxiingplane->getLocation();
    nextStop.clear();
    if(!planelocation->getRoute().empty()&&taxiingplane->getInstruction().empty()){
        nextStop.push_back(planelocation);
        vector<Location*>::const_iterator nextLocation=planelocation->getRoute().end()-1;
        nextStop.push_back(nextLocation.operator*());
        while (nextLocation!=planelocation->getRoute().begin()&&!nextLocation.operator*()->isRunway()){
            nextLocation=nextLocation.operator*()->getRoute().end()-1;
            nextStop.push_back(nextLocation.operator*());
        }
        if(nextLocation!=planelocation->getRoute().begin()){
            //taxiingplane->setInstruction(nextStop);
        }
        else{
            Gate* freegate=airport->findFreeGates();
            if(freegate && airport->getGateFromAirplane(airplane)==NULL){
                nextStop.push_back(freegate);
            }
            else if(airport->getGateFromAirplane(airplane)){
                nextStop.push_back(airport->getGateFromAirplane(airplane));
            }
            else{
                nextStop.clear();
                nextStop.push_back(planelocation);
                nextStop.push_back(planelocation);
            }
        }
    }
    return nextStop;
}

vector<Location*> Signaltower::makeInstructionToRunway(Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling makeInstructionToRunway");
    REQUIRE(airplane->ProperInitialized(),"airplane must be intialized properly when calling makeInstructionToRunway");
    vector<Location*> nextStop;
    Airplane* taxiingplane=airplane;
    Location* planelocation=taxiingplane->getLocation();
    Location* destination=taxiingplane->getDestinateRunway();
    if(!destination->getRoute().empty()&&taxiingplane->getInstruction().empty()){

        vector<Location*>::const_iterator nextLocation=find(destination->getRoute().begin(),destination->getRoute().end(),planelocation);
        if(nextLocation==destination->getRoute().end()){
            nextLocation=destination->getRoute().begin();
            nextStop.push_back(planelocation);
        }
        while (nextLocation!=destination->getRoute().end()&&(!nextLocation.operator*()->isRunway()||nextLocation.operator*()==planelocation)){
            nextStop.push_back(nextLocation.operator*());
            nextLocation=nextLocation+1;
        }

        if(nextLocation!=destination->getRoute().end()){
            nextStop.push_back(nextLocation.operator*());
            //taxiingplane->setInstruction(nextStop);
        }
        else{
            nextStop.push_back(destination);
            //taxiingplane->setInstruction(nextStop);
        }
    }
    return nextStop;
}

const Time &Signaltower::getCurrentTime() const {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling getCurrentTime");
    return currentTime;
}

void Signaltower::setCurrentTime(const Time &currentTime) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling setCurrentTime");
    Signaltower::currentTime = currentTime;
    ENSURE(getCurrentTime()==currentTime,"setCurrentTime postcondition failed");
}

void Signaltower::timeRuns() {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling timeRuns");
    currentTime=currentTime++;
}

bool Signaltower::isDoingNothing() {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling isDoingNothing");
    return doingNothing;
}

ofstream &Signaltower::getFile() {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling getFile");
    return file;
}

void Signaltower::sendSignalPermission5000(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPermission5000");

    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPermission5000");
    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        buzy5000=true;
        int basesquawkcode=getBasesqwakcode(airplane);
        int squawkcode=basesquawkcode+generatevalidRandomcode();

        while (!checkSquawkcodeunique(squawkcode)&&squawkcode!=7500&&squawkcode!=7600&&squawkcode!=7700){
            squawkcode=basesquawkcode+generatevalidRandomcode();
        }

        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << "radar contact" << ", " << "descend and maintain five thousand feet, squawk ";

        file << fillingintegergap(squawkcode,4)<<" ." << endl;

        doingNothing = true;
        airplane->receiveSignal(Airplane::fiveThousand);
        airplane->receiveSquawkcode(squawkcode);
    }
}

void Signaltower::sendSignalPermission3000(Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPermission3000");

    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPermission3000");
    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        buzy5000=false;
        buzy3000=true;

        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << "descend and maintain three thousand feet." << endl;

        doingNothing = true;
        airplane->receiveSignal(Airplane::threeThousand);
    }
}

void Signaltower::sendSignalPermissionLanding(Airplane *airplane,Runway* runway) {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPermissionLanding");

    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPermissionLanding");
    if(isDoingNothing()){
        doingNothing=false;
        //you dont have to wait until the signal has been sent to let it be used;
    }
    else {
        buzy3000=false;

        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << "cleared ILS approach runway "
             << runway->getName() << endl;

        doingNothing = true;

        runway->setCurrentairplane(airplane);
        airplane->receiveLandingSignal(runway);
    }

}

bool Signaltower::sendSignalWaiting(Airplane *airplane) {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalWaiting");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalWaiting");
    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", "
             << "hold south on the one eighty radial, expect further clearance at " << currentTime+incomingSignal.size() << endl;
        //currentTime+incomingSignal.size()+1+1f
        //incomingsignal always goes first, +1 for the signal delay from tower to airport, and +1 for unexpected signals;
        doingNothing = true;
        //incomingSignal.push_back(pair<Airplane*,string>(airplane,"Waiting"));
        airplane->receiveSignal(Airplane::Keep_flying);
        return true;
    }
    return false;
}

void Signaltower::sendSignalClearedToCross(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalClearedToCross");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalClearedToCross");
    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        airplane->setInstruction(vector<Location *>());
        vector<Location *> nextInstruction;

        if (airplane->getStatus() == Airplane::Taxiing_to_runway) {
            nextInstruction = makeInstructionToRunway(airplane);
        } else if (airplane->getStatus() == Airplane::Taxiing_to_gate) {
            nextInstruction = makeInstructionToGate(airplane);
        }

        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << "Cleared to Cross runway " << airplane->getLocation()->getName();

        doingNothing = true;
        airplane->getLocation()->setCrossing(true);
        sendInstruction(airplane, nextInstruction, true);
    }
}

void Signaltower::sendSignalHoldPosition(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalHoldPosition");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalHoldPosition");

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", hold position" << endl;

        doingNothing = true;
        airplane->receiveSignal(Airplane::Hold_position);
    }
}

void Signaltower::sendSignalLineup(Airplane *airplane, bool takeoff) {


    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalLineup");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalLineup");

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        if (takeoff) {
            file << "[" << currentTime << "]" << "[ATC]" << endl;
            file << airplane->getCallsign() << ", runway " << airplane->getDestinateRunway()->getName()
                 << " cleared for take-off." << endl;

            airplane->getDestinateRunway()->setCurrentairplane(airplane);
            airplane->getDestinateRunway()->setPlaneAtbegin(airplane);

            airplane->receiveSignal(Airplane::Fly);

            allplaneknown.erase(find(allplaneknown.begin(),allplaneknown.end(),airplane));
        } else {
            file << "[" << currentTime << "]" << "[ATC]" << endl;
            file << airplane->getCallsign() << ", line up runway " << airplane->getDestinateRunway()->getName()
                 << " and wait." << endl;

            airplane->getDestinateRunway()->setPlaneAtbegin(airplane);

            incomingSignal.push_back(pair<Airplane*,SignaltowerallowedSignal >(airplane,Leaving));
            airplane->receiveSignal(Airplane::Line_up);
        }
        doingNothing = true;
    }
}

void Signaltower::sendInstruction(Airplane *airplane, vector<Location *> Instruction, bool adding){

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendInstruction");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalInstruction");
    if(isDoingNothing()&&!adding){
        doingNothing=false;
    }
    else{
        string taxipoints="";
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
                file<<", "<<"Taxi to gate "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            else if(Instruction[Instruction.size()-1]==airplane->getDestinateRunway()){
                file<<", "<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            else if(Instruction[Instruction.size()-1]!=airplane->getDestinateRunway()&&Instruction[Instruction.size()-1]->isRunway()){
                file<<", "<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            airplane->receiveSignal(Airplane::Cleared_to_cross);
        }
        else{
            if (Instruction[Instruction.size()-1]->isGate()){
                file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                file<<airplane->getCallsign()<<", "<<"Taxi to gate "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            else if(Instruction[Instruction.size()-1]==airplane->getDestinateRunway()) {
                file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                file<<airplane->getCallsign()<<", "<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            else if(Instruction[Instruction.size()-1]!=airplane->getDestinateRunway()&&Instruction[Instruction.size()-1]->isRunway()) {
                file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                file<<airplane->getCallsign()<<", "<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
        }
        if(!adding){
            doingNothing=true;
        }
        if(Instruction[Instruction.size()-1]->isGate()){
            Instruction[Instruction.size()-1]->setOnuse(true);
        }
        airplane->receiveInstruction(Instruction,adding);
    }
}

void Signaltower::sendSignalIFRclear(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalIFRclear");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalIFRclear");

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        int basesquawkcode=getBasesqwakcode(airplane);

        int squawkcode=basesquawkcode+generatevalidRandomcode();

        while (!checkSquawkcodeunique(squawkcode)&&squawkcode!=7500&&squawkcode!=7600&&squawkcode!=7700){
            squawkcode=basesquawkcode+generatevalidRandomcode();
        }
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << airport->getCallsign() << ", cleared to "
             << airplane->getDestination()->getCallsign() << " , maintain "
                     "five thousand, expect flight level one zero zero - ten minutes after"
                     "departure, squawk ";


        file << fillingintegergap(squawkcode,4)<<" ." << endl;

        doingNothing = true;
        airplane->receiveSignal(Airplane::IFR_clearancy);
        airplane->receiveSquawkcode(squawkcode);
    }
}

void Signaltower::sendSignalPushBack(Airplane *airplane,Runway* destinaterunway) {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalPushBack");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalPushBack");

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "["<<airport->getIata()<<"]" << endl;
        file << airplane->getCallsign() << ", " << airport->getCallsign() << ", pushback approved." << endl;

        airplane->setDestinateRunway(destinaterunway);
        destinaterunway->planeQueued();

        doingNothing = true;
        airplane->receiveSignal(Airplane::Push_back);
    }
}

bool Signaltower::sendSignal() {

    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignal");
    unsigned int index = 0;
    if(!isDoingNothing()){
        parse_signal(currentworkingsignal.first,currentworkingsignal.second);
    }
    else{
        pair<Airplane*,SignaltowerallowedSignal > priority(NULL,Approaching);
        int code=-1;
        for (unsigned int i = 0; i <incomingSignal.size() ; ++i) {
            if(incomingSignal[i].first->getSquawkcode()>code){
                priority=incomingSignal[i];
                code=priority.first->getSquawkcode();
            }
        }

        while (index < incomingSignal.size()) {//make sure everything is searched
            SignaltowerallowedSignal Signal=priority.second;
            Airplane *airplane=priority.first;
            parse_signal(airplane,Signal);

            if(!isDoingNothing()){
                incomingSignal.erase(find(incomingSignal.begin(),incomingSignal.end(),priority));
                currentworkingsignal=priority;
                break;
            }
            else{
                int secondbiggestcode=-1;
                for (unsigned int i = 0; i <incomingSignal.size() ; ++i) {
                    if(incomingSignal[i].first->getSquawkcode()<code&&incomingSignal[i].first->getSquawkcode()>secondbiggestcode){
                        priority=incomingSignal[i];
                        secondbiggestcode=priority.first->getSquawkcode();
                    }
                }
                code=priority.first->getSquawkcode();//this is the new upper bound.
                index++;
            }
        }
    }
        return true;
}

bool Signaltower::ProperInitialized() const{
    return _initCheck==this;
}

void Signaltower::regulateApproachingplane(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling regulateApproachingplane");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling regulateApproachingplane");
    if (airplane->getPermission() == Airplane::threeThousandPermission && airplane->getHeight() == 3000) {
        Runway *freerunway = airport->findFreeRunway(airplane);
        if(freerunway==NULL){
            cerr<<"This airplane can never land as there is no single runway suitable for it!!"<<endl;
            throw ;
        }
        if (!freerunway->isOnuse()&&!freerunway->isCrossing()) {
            sendSignalPermissionLanding(airplane, freerunway);
        }
        else{
            sendSignalWaiting(airplane);
        }
    }
    else if(airplane->getPermission()==Airplane::fiveThousandPermission&&airplane->getHeight()==5000){
        if(!buzy3000){
            sendSignalPermission3000(airplane);
        }
        else{
            sendSignalWaiting(airplane);
        }
    }
    else if(airplane->getPermission()==Airplane::tenThousandPermission&&airplane->getHeight()==10000){
        if(!buzy5000){
            sendSignalPermission5000(airplane);
        }
        else{
            sendSignalWaiting(airplane);
        }
    }
    else{
        return;
    }
    //loop back
    if(airplane->getPermission()!=Airplane::LandingPermission&&isDoingNothing()){
        incomingSignal.push_back(pair<Airplane*,SignaltowerallowedSignal >(airplane,Approaching));
    }
}

void Signaltower::regulateLeavingplane(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling regulateLeavingplane");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling regulateLeavingplane");
    if(!airplane->getLocation()->isCrossing()||!isDoingNothing()){
        sendSignalLineup(airplane,true);
    }
}

void Signaltower::parse_signal(Airplane *airplane, SignaltowerallowedSignal stringSignal) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling parse_signal");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling parse_signal");
    if (stringSignal == ApproachingtoGate) {
        airplane->setInstruction(vector<Location *>());
        vector<Location *> instruction = makeInstructionToGate(airplane);
        if (instruction.size() > 0) {
            sendInstruction(airplane, instruction);
        }
    } else if (stringSignal == LeavingtoRunway) {
        if (airplane->getDestinateRunway() != NULL) {
            vector<Location *> instruction = makeInstructionToRunway(airplane);
            if (instruction.size() > 0) {
                sendInstruction(airplane, instruction);
            }
        }
    } else if (stringSignal == Emergency) {
        if(airplane->getHeight()>=3000){
            Runway* runway=airport->findFreeRunway(airplane,true);

            sendSignalEmergency(airplane,runway);
        }
        else{
            sendSignalEmergency(airplane);
        }


    } else if (stringSignal == Push_back) {
        Runway *destinaterunway = airport->findFreeRunway(airplane);
        Gate* gate=airport->getGateFromAirplane(airplane);
        if (destinaterunway&&gate->getPlaneNearGate()==NULL) {
            sendSignalPushBack(airplane, destinaterunway);
        }
    } else if (stringSignal == IFR_clearancy) {
        //dont see a reason not to
        sendSignalIFRclear(airplane);

    } else if (stringSignal == Crossing_runway) {
        Location *runwayToCross = airplane->getLocation();
        if (!runwayToCross->isOnuse() && !runwayToCross->isCrossing()) {
            sendSignalClearedToCross(airplane);

        }

    } else if (stringSignal == At_runway) {
        Runway *runway = airplane->getDestinateRunway();
        if (!runway->isCrossing() && !runway->isOnuse() && runway->getPlaneAtbegin() == NULL) {
            sendSignalLineup(airplane, true);

        } else if (!runway->isOnuse() && runway->getPlaneAtbegin() == NULL) {
            sendSignalLineup(airplane, false);
        }
        else{
            //if air already contacting, then just send hold position, else wait until there is free space;
            if(!isDoingNothing()){
                sendSignalHoldPosition(airplane);
                incomingSignal.push_back(pair<Airplane*,SignaltowerallowedSignal>(airplane,At_runway));
            }
        }
    }
    else if(stringSignal == Approaching){
        regulateApproachingplane(airplane);
    }
    else if(stringSignal == Leaving){
        regulateLeavingplane(airplane);
    }
    else{
        cerr << "error signal" << endl;
    }
}

bool Signaltower::checkSquawkcodeunique(int code) {
    for (unsigned int i = 0; i < allplaneknown.size(); ++i) {
        if(allplaneknown[i]->getSquawkcode()==code){
            return false;
        }
    }
    return true;
}

void Signaltower::sendSignalEmergency(Airplane *airplane, Runway *runway) {
    REQUIRE(ProperInitialized(),"Signal tower must be initialized properly when calling sendSignalEmergency");
    REQUIRE(airplane->ProperInitialized(),"Airplane must be initialized properly when calling sendSignalEmergency");

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        if(airplane->getHeight()>=3000){
            file << "[" << currentTime << "]" << "["<<airport->getIata()<<"]" << endl;
            file << airplane->getCallsign() << ", roger mayday, squawk seven seven zero zero, cleared ILS landing runway " <<runway->getName()<< endl;
            airplane->setDestinateRunway(runway);
            airplane->setPermission(Airplane::LandingPermission);
            runway->planeQueued();
        }
        else{
            file << "[" << currentTime << "]" << "["<<airport->getIata()<<"]" << endl;
            file << airplane->getCallsign() << ", roger mayday, squawk seven seven zero zero, emergency personal on standby, good luck! "<< endl;
            airplane->setDestinateRunway(NULL);

        }

        doingNothing = true;
        airplane->receiveSignal(Airplane::EmergencySignal);
    }
}