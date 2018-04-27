//
// Created by c6222848 on 4/6/18.
//

#include <fstream>
#include "Signaltower.h"
#include "algorithm"


static string allowedSignalprepare[]={"Approaching","Leaving","ApproachingtoGate","LeavingtoRunway","Emergency","Push back","IFR clearancy","Crossing runway","At runway"};
static vector<string> allowedSignal(allowedSignalprepare, allowedSignalprepare+sizeof(allowedSignalprepare)/ sizeof(allowedSignalprepare[0]));

Signaltower::Signaltower(Airport *airport) : airport(airport) {

    string filename="../output/"+airport->getIata()+"_Tower.txt";
    doingNothing=true;
    file.open(filename.c_str(),ios::app);
}

bool Signaltower::receiveSignal(Airplane *airplane, string signal) {
    if (signal=="Approaching"){
        approachingAirplanes.push_back(airplane);
        airplane->setPermission("10000");
        return true;
    }
    else if(signal=="Leaving"){
        leavingAirplanes.push_back(airplane);
        return false;
    }
    else if(find(allowedSignal.begin(),allowedSignal.end(),signal)!=allowedSignal.end()) {
        incomingSignal.push_back(pair<Airplane*,string>(airplane,signal));
        return false;
    }
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
            if(airplane->getDestinaterunway()!=NULL){
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
            Runway* runway=airplane->getDestinaterunway();
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

vector<Airplane *> Signaltower::allflyingplanes() {
    vector<Airplane*> allflying=approachingAirplanes;
    for (unsigned int i = 0; i < leavingAirplanes.size(); ++i) {
        allflying.push_back(leavingAirplanes[i]);
    }
    for (unsigned int j = 0; j < emergency.size(); ++j) {
        allflying.push_back(emergency[j]);
    }
    return allflying;
}


void Signaltower::regulateApproachingplanes() {
        bool buzyat3000 = false;
        bool buzyat5000 = false;
        vector<Airplane *> allflying = allflyingplanes();
        vector<int> planestoremove;
        bool buzysendingsignal=false;
        for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
                if (approachingAirplanes[i]->getPermission() == "3000" &&
                    approachingAirplanes[i]->getHeight() == 3000) {
                    Runway *freerunway = airport->findFreeRunway(approachingAirplanes[i]);
                    if (!freerunway->isOnuse()&&!freerunway->isCrossing()) {

                        if(!buzysendingsignal){
                            buzysendingsignal=true;
                            sendSignalPermissionLanding(approachingAirplanes[i], freerunway);
                        }

                    } else {

                        if(!buzysendingsignal){
                            buzysendingsignal=true;
                            sendSignalWaiting(approachingAirplanes[i]);
                            buzyat3000 = true;
                        }

                        //not breaking here, beacause we're also checking all planes that have landed on the ground(runway), and removing them
                        //to the next phase where the airplane needs to call the signal tower again.
                    }
                } else if (approachingAirplanes[i]->getPermission() == "3000" &&
                           approachingAirplanes[i]->getHeight() != 3000) {

                    buzyat3000 = true;
                } else if (approachingAirplanes[i]->getPermission() == "0" &&
                           approachingAirplanes[i]->getHeight() == 0) {

                    planestoremove.push_back(i);
                    //plane landed on runway. waiting for next contact.
                }
            }

        for (unsigned int j = 0; j < planestoremove.size(); ++j) {
            //plane goes to the taxipoint of the runway after landing.
            approachingAirplanes[planestoremove[j] - j]->setPermission("");
            approachingAirplanes.erase(approachingAirplanes.begin() + planestoremove[j] - j);
        }

        //looking for buzyat5000;
        for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
            if (approachingAirplanes[i]->getPermission() == "5000" && approachingAirplanes[i]->getHeight() == 5000) {
                if (!buzyat3000) {
                    if(!buzysendingsignal){
                        buzysendingsignal=true;
                        sendSignalPermission3000(approachingAirplanes[i]);
                    }

                    buzyat3000 = true;
                    //no need to set buzy3000 anymore, not using it
                } else {
                    if(!buzysendingsignal){
                        buzysendingsignal=true;
                        sendSignalWaiting(approachingAirplanes[i]);
                        buzyat5000 = true;
                        break;
                    }

                }
            } else if (approachingAirplanes[i]->getPermission() == "5000" &&
                       approachingAirplanes[i]->getHeight() != 5000) {
                buzyat5000 = true;
            }
        }

        if (!buzyat5000) {
            for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
                if (approachingAirplanes[i]->getPermission() == "10000") {
                    if(!buzysendingsignal){
                        buzysendingsignal=true;
                        sendSignalPermission5000(approachingAirplanes[i]);
                        break;
                    }
                }
            }
        }
        if (!buzyat3000) {
            for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
                if (approachingAirplanes[i]->getPermission() == "5000" &&
                    approachingAirplanes[i]->getHeight() == 5000) {
                    if(!buzysendingsignal) {
                        sendSignalPermission3000(approachingAirplanes[i]);
                        break;
                    }
                }
            }
        }
}
/*
void Signaltower::regulateTaxiingtoGate() {

    vector<int> planestoremove;
    vector<Location*> nextStop;
    for (unsigned int i = 0; i < taxiingtogate.size(); ++i) {
        Airplane* taxiingplane=taxiingtogate[i];
        Location* planelocation=taxiingplane->getLocation();
        nextStop.clear();
        makeInstructionToGate(taxiingplane);

        if(planelocation==taxiingplane->getInstruction()[taxiingplane->getInstruction().size()-1]){
            //plane finished running;
            nextStop.clear();
            if(planelocation->isRunway()){
                    nextStop.push_back(planelocation);
                    if(planelocation->isCrossing()||planelocation->isOnuse()){
                        nextStop.push_back(planelocation);
                        file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                        file<<taxiingplane->getCallsign()<<", "<<"Hold more at "<<planelocation->getName()<<"." << endl;
                        taxiingplane->setInstruction(nextStop);
                    }
                    else{
                        file<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
                        file<<"Cleared to Cross runway "<<planelocation->getName()<<", "<<taxiingplane->getCallsign() << endl;
                        planelocation->setCrossing(true);
                        nextStop.clear();
                        taxiingplane->setInstruction(nextStop);
                        makeInstructionToGate(taxiingplane);
                    }
            }
            else
            if(planelocation->isGate()){
                vector<Location*> a;
                taxiingplane->setInstruction(a);
                planestoremove.push_back(i);
            }
        }

        bool WaitingToCrossrunway=false;
        if(planelocation->isRunway()){
            WaitingToCrossrunway=true;
            file<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            file<<airport->getCallsign()<<", " <<taxiingplane->getCallsign()<<", "<<"Hold short at " <<planelocation->getName()<<endl;
        }
        if(planelocation==taxiingplane->getDestinaterunway()){
            file<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
            file<<airport->getCallsign()<<", " <<taxiingplane->getCallsign()<<", "<<"Runway " <<planelocation->getName()<<" Vacated"<<endl;

        }
        if(!planelocation->getRoute().empty()){
            Location* nextlocation=(planelocation->getRoute().end()-1).operator*();
            if(!(nextlocation->isCrossing()&&nextlocation->isRunway())&&
                !(nextlocation->isOnuse())&&(!WaitingToCrossrunway||!planelocation->isCrossing())){
                taxiingplane->setNextLocation(nextlocation);
                if(WaitingToCrossrunway&&planelocation!=taxiingplane->getDestinaterunway()){
                    file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", "<<"Cleared to Cross runway "<<planelocation->getName() << endl;
                    file<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
                    file<<taxiingplane->getCallsign()<<", "<<"Cleared to Cross runway "<<planelocation->getName() << endl;
                }
            }
            else{
                taxiingplane->setNextLocation(planelocation);
                //plane wait on current location
            }
            if(planelocation==taxiingplane->getDestinaterunway()){
                taxiingplane->getDestinaterunway()->setPlaneAtEnd(NULL);
                taxiingplane->setDestinaterunway(NULL);
            }
        }
        else{
            Gate* freegate=airport->findFreeGates();
            if(freegate!=NULL){
                taxiingplane->setNextLocation(freegate);
                airport->parkAirplane(freegate,taxiingplane);
                planestoremove.push_back(i);
            }
            else{
                //plane wait until there is an free gate to park
            }
        }

}
    for (unsigned int j = 0; j < planestoremove.size(); ++j) {
        taxiingtogate.erase(taxiingtogate.begin()+planestoremove[j]-j);
    }
}

void Signaltower::regulateTaxiingtorunway() {
    vector <int> planestoremove;

    for (unsigned int i = 0; i < taxiingtorunway.size(); ++i) {
        Airplane* taxiingplane=taxiingtorunway[i];
        Location* planelocation=taxiingplane->getLocation();
        vector<Location*> nextStop;
        makeInstructionToRunway(taxiingplane);
        if(planelocation==taxiingplane->getDestinaterunway()){
            planestoremove.push_back(i);
        }

        if(planelocation==taxiingplane->getInstruction()[taxiingplane->getInstruction().size()-1]){
            //plane finished running;
            nextStop.clear();
            if(planelocation->isRunway()&&planelocation!=taxiingplane->getDestinaterunway()){
                file<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
                file<<airport->getCallsign()<<", " <<taxiingplane->getCallsign()<<", "<<"Hold short at " <<planelocation->getName()<<endl;
                nextStop.push_back(planelocation);
                if((planelocation->isCrossing()&&taxiingplane->getPermission()!="Cleared to Cross")||planelocation->isOnuse()){
                    nextStop.push_back(planelocation);
                    file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", "<<"Hold more at "<<planelocation->getName()<<"." << endl;
                    taxiingplane->setInstruction(nextStop);
                }
                else{
                    if(taxiingplane->getPermission()!="Cleared to Cross"){
                        taxiingplane->setPermission("Cleared to Cross");
                        file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                        file<<taxiingplane->getCallsign()<<", "<<"Cleared to Cross runway "<<planelocation->getName() << endl;
                        file<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
                        file<<"Cleared to Cross runway "<<planelocation->getName()<<", "<<taxiingplane->getCallsign() << endl;
                        planelocation->setCrossing(true);
                    }

                    nextStop.clear();
                    taxiingplane->setInstruction(nextStop);
                    makeInstructionToRunway(taxiingplane);
                }
            }
            else
            if(planelocation==taxiingplane->getDestinaterunway()){


                Runway* destination=taxiingplane->getDestinaterunway();
                if(destination->getPlaneAtbegin()==NULL&&(!destination->isOnuse()||taxiingplane->getPermission()=="fly") &&!destination->isCrossing()){

                    if(taxiingplane->getPermission()!="fly"){

                        taxiingplane->setPermission("fly");
                        destination->setOnuse(true);
                    }

                    if(taxiingplane->liningUp()) {


                        vector<Location *> a;
                        taxiingplane->setInstruction(a);
                        planestoremove.push_back(i);
                    }
                }
                else if(destination->getPlaneAtbegin()==NULL&&(!destination->isOnuse()||taxiingplane->getPermission()=="Line up")){
                    taxiingplane->setPermission("Line up");
                    if(taxiingplane->liningUp()){


                        vector<Location*> a;
                        taxiingplane->setInstruction(a);

                        planestoremove.push_back(i);
                    }
                }
                else{

                    file<<"["<<currentTime<<"]"<<"[AIR]"<<endl;
                    file<<"Hold position, "<<airport->getCallsign()<<endl;
                }
            }
        }

        if(planelocation!=(destination->getRoute().end()-1).operator*()){
            Location* nextlocation=((find(destination->getRoute().begin(),destination->getRoute().end(),planelocation)+1).operator*());
            if(nextlocation==(destination->getRoute().end()+1).operator*()){
                nextlocation=destination->getRoute().begin().operator*();
            }
            if(!(nextlocation->isCrossing()&&nextlocation->isRunway())&&!(nextlocation->isOnuse())){

                taxiingplane->setNextLocation(nextlocation);
            }
            else{
                taxiingplane->setNextLocation(planelocation);
                file<<'a'<<endl;

                //plane wait on current location
            }
        }
        else{
            if(destination->getPlaneAtbegin()==NULL&&!destination->isOnuse()&&!destination->isCrossing()){
                taxiingplane->setPermission("fly");
                taxiingplane->setNextLocation(destination);
                destination->setCurrentairplane(taxiingplane);
                planestoremove.push_back(i);
            }
            else if(destination->getPlaneAtbegin()==NULL&&!destination->isOnuse()){
                taxiingplane->setNextLocation(destination);
                destination->setPlaneAtbegin(taxiingplane);
                planestoremove.push_back(i);
                //plane wait until the crossing is over.
                //the on use marker prevent the next plane from crossing over
            }
            else{
                taxiingplane->setNextLocation(planelocation);
                //plane wait until the runway is free
            }
        }

    }

    for (unsigned int j = 0; j < planestoremove.size(); ++j) {
        taxiingtorunway.erase(taxiingtorunway.begin()+planestoremove[j]-j);
    }
}
*/


bool Signaltower::permissionLeavingGate(Airplane *airplane) {
    //didn't see any condition
    return true;
}

vector<Location*> Signaltower::makeInstructionToGate(Airplane *airplane) {
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
            taxiingplane->setInstruction(nextStop);
        }
        else{
            Gate* freegate=airport->findFreeGates();
            if(freegate){
                nextStop.push_back(freegate);
                airport->parkAirplane(freegate,taxiingplane);
            }
        }
    }
    return nextStop;
}

vector<Location*> Signaltower::makeInstructionToRunway(Airplane *airplane) {
    //overhaul
    vector<Location*> nextStop;
    Airplane* taxiingplane=airplane;
    Location* planelocation=taxiingplane->getLocation();
    Location* destination=taxiingplane->getDestinaterunway();
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
            taxiingplane->setInstruction(nextStop);
        }
        else{
            nextStop.push_back(destination);
            taxiingplane->setInstruction(nextStop);
        }
    }
    return nextStop;
}

const Time &Signaltower::getCurrentTime() const {
    return currentTime;
}

void Signaltower::setCurrentTime(const Time &currentTime) {
    Signaltower::currentTime = currentTime;
}

void Signaltower::timeRuns() {
    currentTime=currentTime++;
}

bool Signaltower::isDoingNothing() {
    return doingNothing;
}

ofstream &Signaltower::getFile() {
    return file;
}

void Signaltower::sendSignalPermission5000(Airplane *airplane) {
    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << "radar contact" << ", "
             << "descend and maintain five thousand feet, squawk <squawk-code>." << endl;

        doingNothing = true;
        airplane->receiveSignal("5000");
    }
}

void Signaltower::sendSignalPermission3000(Airplane *airplane) {

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << "descend and maintain three thousand feet." << endl;

        doingNothing = true;
        airplane->receiveSignal("3000");
    }
}

void Signaltower::sendSignalPermissionLanding(Airplane *airplane,Runway* runway) {

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << "cleared ILS approach runway "
             << runway->getName() << endl;
        runway->setCurrentairplane(airplane);

        doingNothing = true;
        airplane->receiveLandingSignal(runway);
    }

}

void Signaltower::sendSignalWaiting(Airplane *airplane) {

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", "
             << "hold south on the one eighty radial, expect further clearance at " << currentTime+incomingSignal.size()+1 << endl;
        doingNothing = true;
        airplane->receiveSignal("Keep flying");
    }
}

void Signaltower::sendSignalClearedToCross(Airplane *airplane) {


    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        airplane->setInstruction(vector<Location *>());
        vector<Location *> nextInstruction;

        if (airplane->getStatus() == "Taxiing to runway") {
            nextInstruction = makeInstructionToRunway(airplane);
        } else if (airplane->getStatus() == "Taxiing to gate") {
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

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", hold position" << endl;

        doingNothing = true;
        airplane->receiveSignal("Hold position");
    }
}

void Signaltower::sendSignalLineup(Airplane *airplane, bool takeoff) {

    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        if (takeoff) {
            file << "[" << currentTime << "]" << "[ATC]" << endl;
            file << airplane->getCallsign() << ", runway " << airplane->getDestinaterunway()->getName()
                 << " cleared for take-off." << endl;

            airplane->getDestinaterunway()->setCurrentairplane(airplane);
            airplane->getDestinaterunway()->setPlaneAtbegin(airplane);

            airplane->receiveSignal("Fly");
        } else {
            file << "[" << currentTime << "]" << "[ATC]" << endl;
            file << airplane->getCallsign() << ", line up runway " << airplane->getDestinaterunway()->getName()
                 << " and wait." << endl;

            airplane->getDestinaterunway()->setPlaneAtbegin(airplane);

            leavingAirplanes.push_back(airplane);
            airplane->receiveSignal("Line up");
        }
        doingNothing = true;
    }
}

void Signaltower::sendInstruction(Airplane *airplane, vector<Location *> Instruction, bool adding){

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
            else if(Instruction[Instruction.size()-1]==airplane->getDestinaterunway()){
                file<<", "<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            else if(Instruction[Instruction.size()-1]!=airplane->getDestinaterunway()&&Instruction[Instruction.size()-1]->isRunway()){
                file<<", "<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            airplane->receiveSignal("Cleared to cross");
        }
        else{
            if (Instruction[Instruction.size()-1]->isGate()){
                file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                file<<airplane->getCallsign()<<", "<<"Taxi to gate "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            else if(Instruction[Instruction.size()-1]==airplane->getDestinaterunway()) {
                file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                file<<airplane->getCallsign()<<", "<<"Taxi to runway "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
            else if(Instruction[Instruction.size()-1]!=airplane->getDestinaterunway()&&Instruction[Instruction.size()-1]->isRunway()) {
                file<<"["<<currentTime<<"]"<<"[ATC]"<<endl;
                file<<airplane->getCallsign()<<", "<<"Taxi to holdpoint "<<Instruction[Instruction.size()-1]->getName()<<taxipoints+"." << endl;
            }
        }
        if(!adding){
            doingNothing=true;
        }
        airplane->receiveInstruction(Instruction,adding);
    }
}

void Signaltower::sendSignalIFRclear(Airplane *airplane) {
    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << airport->getCallsign() << ", cleared to "
             << airplane->getDestination()->getCallsign() << " , maintain "
                     "five thousand, expect flight level one zero zero - ten minutes after"
                     "departure, squawk" << " <SQUAWK CODE>" << endl;

        doingNothing = true;
        airplane->receiveSignal("IFR clearancy");
    }
}

void Signaltower::sendSignalPushBack(Airplane *airplane,Runway* destinaterunway) {
    if(isDoingNothing()){
        doingNothing=false;
    }
    else {
        file << "[" << currentTime << "]" << "[ATC]" << endl;
        file << airplane->getCallsign() << ", " << airport->getCallsign() << ", pushback approved." << endl;

        airplane->setDestinaterunway(destinaterunway);
        destinaterunway->planeQueued();

        doingNothing = true;
        airplane->receiveSignal("Push back");
    }
}

void Signaltower::regulateLeavingplanes() {
        vector<int> planestoremove;
        for (unsigned int i = 0; i < leavingAirplanes.size(); ++i) {
            if(!leavingAirplanes[i]->getLocation()->isCrossing()){
                sendSignalLineup(leavingAirplanes[i],true);
                if(isDoingNothing()){
                    planestoremove.push_back(i);
                }
                    break;
            }
        }

        for (unsigned int j = 0; j < planestoremove.size(); ++j) {
            leavingAirplanes.erase(leavingAirplanes.begin()+planestoremove[j]-j);
        }
}

bool Signaltower::sendSignal() {
        unsigned int index = 0;
    bool erase=false;
    while (index < incomingSignal.size()) {
            pair<Airplane *, string> temp = incomingSignal[index];
            string stringSignal=temp.second;
            Airplane *airplane=temp.first;


            if (stringSignal == "ApproachingtoGate") {
                    airplane->setInstruction(vector<Location *>());
                    vector<Location *> instruction = makeInstructionToGate(airplane);
                    if (instruction.size() > 0) {
                        sendInstruction(airplane, instruction);
                        if(isDoingNothing()){
                            erase=true;
                        }
                        break;
                    }
            } else if (stringSignal == "LeavingtoRunway") {
                    if (airplane->getDestinaterunway() != NULL) {
                        airplane->setInstruction(vector<Location *>());
                        vector<Location *> instruction = makeInstructionToRunway(airplane);
                        if (instruction.size() > 0) {
                            sendInstruction(airplane, instruction);
                            if(isDoingNothing()){
                                erase=true;
                            }
                            break;
                        }
                    }
            } else if (stringSignal == "Emergency") {
                emergency.push_back(airplane);
            } else if (stringSignal == "Push back") {
                    Runway *destinaterunway = airport->findFreeRunway(airplane);
                    if (destinaterunway) {
                        sendSignalPushBack(airplane, destinaterunway);
                        if(isDoingNothing()){
                            erase=true;
                        }
                        break;
                    }
            } else if (stringSignal == "IFR clearancy") {
                //dont see a reason not to
                    sendSignalIFRclear(airplane);
                if(isDoingNothing()){
                    erase=true;
                }
                    break;

            } else if (stringSignal == "Crossing runway") {
                    Location *runwayToCross = airplane->getLocation();
                    if (!runwayToCross->isOnuse() && !runwayToCross->isCrossing()) {
                        sendSignalClearedToCross(airplane);
                        if(isDoingNothing()){
                            erase=true;
                        }
                        break;

                    }

            } else if (stringSignal == "At runway") {
                    Runway *runway = airplane->getDestinaterunway();
                    if (!runway->isCrossing() && !runway->isOnuse() && runway->getPlaneAtbegin() == NULL) {
                        sendSignalLineup(airplane, true);
                        if(isDoingNothing()){
                            erase=true;
                        }
                        break;

                    } else if (!runway->isOnuse() && runway->getPlaneAtbegin() == NULL) {
                        sendSignalLineup(airplane, false);
                        if(isDoingNothing()){
                            erase=true;
                        }
                        break;

                    }
            }
            else{
                cerr << "error signal" << endl;
            }
            index++;
        }
    if(erase){
        if(!incomingSignal.empty()){
            incomingSignal.erase(incomingSignal.begin()+index);
        }
    }
        return true;
}

