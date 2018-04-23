//
// Created by c6222848 on 4/6/18.
//

#include <fstream>
#include "Signaltower.h"
#include "algorithm"

Signaltower::Signaltower(Airport *airport) : airport(airport) {

    string filename="../output/"+airport->getIata()+"_Tower.txt";
    file.open(filename.c_str(),ios::app);
    time=Time();
}

bool Signaltower::receiveSignal(Airplane *airplane, string signal) {
    if (signal=="Approaching"){
        file<<"["<<time<<"]"<<"[AIR]"<<endl;
        file<<airport->getCallsign()<<", "<<airplane->getCallsign()<<", "<<"arriving at "<<airport->getName()<<endl;
        approachingAirplanes.push_back(airplane);
        airplane->setPermission("10000");
        return true;
    }
    else if(signal=="Leaving"){

        if(!(airplane->getDestinaterunway()->isCrossing())){

            file<<"["<<time<<"]"<<"[ATC]"<<endl;
            file<<airplane->getCallsign()<<", runway "<<airplane->getDestinaterunway()->getName()<<" cleared for take-off."<<endl;
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<"runway "<<airplane->getDestinaterunway()->getName()<<" cleared for take-off."<<airplane->getCallsign()<<endl;

            airplane->getDestinaterunway()->setCurrentairplane(airplane);
            airplane->getDestinaterunway()->setPlaneAtbegin(NULL);
            airplane->setPermission("fly");
            return true;
        }

        return false;
    }
    else if(signal=="ApproachingtoGate"){
        file<<"["<<time<<"]"<<"[AIR]"<<endl;
        file<<airport->getCallsign()<<", " <<airplane->getCallsign()<<", "<<"Runway " <<airplane->getLocation()->getName()<<" Vacated"<<endl;

        taxiingtogate.push_back(airplane);
        makeInstructionToGate(airplane);
        return true;
    }
    else if(signal=="LeavingtoRunway"){
        file<<"["<<time<<"]"<<"[AIR]"<<endl;
        file<<airplane->getCallsign()<<" is ready to taxi."<<endl;


        if(airplane->getDestinaterunway()!=NULL){
            taxiingtorunway.push_back(airplane);
            makeInstructionToRunway(airplane);
            return true;
        }
        return false;
    }
    else if(signal=="Emergency"){
        emergency.push_back(airplane);
        return true;
    }
    else if(signal=="Push back"){
        Runway* destinaterunway=airport->findFreeRunway(airplane);
        if(destinaterunway){
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<airport->getCallsign()<<", "<<airplane->getCallsign()<<", requesting IFR clearancy to "<<airplane->getDestination()->getCallsign()<<endl;
            file<<"["<<time<<"]"<<"[ATC]"<<endl;
            file<<airplane->getCallsign()<<", "<<airport->getCallsign()<<", cleared to "<<airplane->getDestination()->getCallsign()<<" , maintain "
                    "five thousand, expect flight level one zero zero - ten minutes after"
                    "departure, squawk"<<" <SQUAWK CODE>"<<endl;
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<"Cleared to "<<airplane->getDestination()->getCallsign()<<" , initial altitude five thousand, expecting one zero zero in ten, squawking"<< " <SQUAWK CODE> ,"<<airplane->getCallsign()<<endl;


            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<airport->getCallsign()<<", "<<airplane->getCallsign()<<" at gate "<<airplane->getLocation()->getName()<<", requesting pushback"<<endl;
            file<<"["<<time<<"]"<<"[ATC]"<<endl;
            file<<airplane->getCallsign()<<", "<<airport->getCallsign()<<", pushback approved."<<endl;
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<"Pushback approved, "<<airplane->getCallsign()<<endl;

            airplane->setDestinaterunway(destinaterunway);
            destinaterunway->planeQueued();
            return true;
        }
        else{

        }
        return false;
    }
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

vector<Airplane *> Signaltower::allgroundplanes() {
    vector<Airplane*> allground=taxiingtorunway;
    for (unsigned int i = 0; i < taxiingtogate.size(); ++i) {
        allground.push_back(taxiingtogate[i]);
    }
    return allground;
}

void Signaltower::regulateApproachingplanes() {
    time++;
    bool buzyat3000=false;
    bool buzyat5000=false;
    vector<Airplane*> allflying=allflyingplanes();
    vector<int> planestoremove;
    for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
        if(approachingAirplanes[i]->getPermission()=="3000"&&approachingAirplanes[i]->getHeight()==3000){
            Runway* freerunway=airport->findFreeRunway(approachingAirplanes[i]);
            if(freerunway!=NULL){
                freerunway->setCurrentairplane(approachingAirplanes[i]);
                approachingAirplanes[i]->setPermission("0");
                approachingAirplanes[i]->setDestinaterunway(freerunway);


                file<<"["<<time<<"]"<<"[ATC]"<<endl;
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"cleared ILS approach runway "<<freerunway->getName()<<endl;
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<"Cleared ILS approach runway " <<freerunway->getName()<<", " <<approachingAirplanes[i]->getCallsign()<<endl;

            }
            else{

                file<<"["<<time<<"]"<<"[ATC]"<<endl;
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"hold south on the one eighty radial, expect further clearance at "<< time++ <<endl;
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<"Hold south on the one eighty radial, "<<approachingAirplanes[i]->getCallsign()<<endl;

                buzyat3000=true;
                //not breaking here, beacause we're also checking all planes that have landed on the ground(runway), and removing them
                //to the next phase where the airplane needs to call the signal tower again.
            }
        }

        else if(approachingAirplanes[i]->getPermission()=="3000"&&approachingAirplanes[i]->getHeight()!=3000){
            buzyat3000=true;
        }
        else if(approachingAirplanes[i]->getPermission()=="0"&&approachingAirplanes[i]->getHeight()==0){
            planestoremove.push_back(i);
            //plane landed on runway. waiting for next contact.
        }
    }

    for (unsigned int j = 0; j < planestoremove.size(); ++j) {
        //plane goes to the taxipoint of the runway after landing.
        approachingAirplanes[planestoremove[j]-j]->setPermission("");
        approachingAirplanes.erase(approachingAirplanes.begin()+planestoremove[j]-j);
    }

    //looking for buzyat5000;
    for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
        if(approachingAirplanes[i]->getPermission()=="5000"&&approachingAirplanes[i]->getHeight()==5000){
            if(!buzyat3000){

                file<<"["<<time<<"]"<<"[ATC]"<<endl;
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"descend and maintain three thousand feet."<<endl;
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<"Descend and maintain three thousand feet, "<<approachingAirplanes[i]->getCallsign()<<endl;

                approachingAirplanes[i]->setPermission("3000");
                buzyat3000=true;
                //no need to set buzy3000 anymore, not using it
            }
            else {

                file<<"["<<time<<"]"<<"[ATC]"<<endl;
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"hold south on the one eighty radial, expect further clearance at "<<time++<<endl;
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<"Hold south on the one eighty radial, "<<approachingAirplanes[i]->getCallsign()<<endl;

                buzyat5000=true;
                break;
            }
        }
        else if(approachingAirplanes[i]->getPermission()=="5000"&&approachingAirplanes[i]->getHeight()!=5000){
            buzyat5000=true;
        }
    }

    if (!buzyat5000){
        for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
            if(approachingAirplanes[i]->getPermission()=="10000"){

                file<<"["<<time<<"]"<<"[ATC]"<<endl;
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"radar contact"<<", "<<"descend and maintain five thousand feet, squawk <squawk-code>."<<endl;
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<"Descend and maintain five thousand feet, squawking <squawk-code>, "<<approachingAirplanes[i]->getCallsign()<<endl;

                approachingAirplanes[i]->setPermission("5000");
                break;
            }
        }
    }
    if (!buzyat3000){
        for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
            if(approachingAirplanes[i]->getPermission()=="5000"&&approachingAirplanes[i]->getHeight()==5000){

                file<<"["<<time<<"]"<<"[ATC]"<<endl;
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"descend and maintain three thousand feet."<<endl;
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<"Descend and maintain three thousand feet, "<<approachingAirplanes[i]->getCallsign()<<endl;

                approachingAirplanes[i]->setPermission("3000");
                break;
            }
        }
    }
}

void Signaltower::regulateTaxiingtoGate() {

    vector<int> planestoremove;
    vector<Location*> nextStop;
    for (unsigned int i = 0; i < taxiingtogate.size(); ++i) {
        Airplane* taxiingplane=taxiingtogate[i];
        Location* planelocation=taxiingplane->getLocation();
        nextStop.clear();
        makeInstructionToGate(taxiingplane);
        if(planelocation==taxiingplane->getInstruction().begin().operator*()&&taxiingplane->getInstruction().begin().operator*()!=(taxiingplane->getInstruction().end()-1).operator*()){
            planelocation->setCrossing(false);
        }
        if(planelocation==taxiingplane->getInstruction()[taxiingplane->getInstruction().size()-1]){
            //plane finished running;
            nextStop.clear();
            if(planelocation->isRunway()){
                    file<<"["<<time<<"]"<<"[AIR]"<<endl;
                    file<<airport->getCallsign()<<", " <<taxiingplane->getCallsign()<<", "<<"Hold short at " <<planelocation->getName()<<endl;
                    nextStop.push_back(planelocation);
                    if(planelocation->isCrossing()||planelocation->isOnuse()){
                        nextStop.push_back(planelocation);
                        file<<"["<<time<<"]"<<"[ATC]"<<endl;
                        file<<taxiingplane->getCallsign()<<", "<<"Hold more at"<<planelocation->getName()<<"." << endl;
                        taxiingplane->setInstruction(nextStop);
                    }
                    else{
                        file<<"["<<time<<"]"<<"[ATC]"<<endl;
                        file<<taxiingplane->getCallsign()<<", "<<"Cleared to Cross runway "<<planelocation->getName() << endl;
                        file<<"["<<time<<"]"<<"[AIR]"<<endl;
                        file<<"Cleared to Cross runway "<<planelocation->getName()<<", "<<taxiingplane->getCallsign() << endl;
                        planelocation->setCrossing(true);
                        nextStop.clear();
                        taxiingplane->setInstruction(nextStop);
                        makeInstructionToGate(taxiingplane);
                    }
            }
            else if(planelocation->isGate()){
                vector<Location*> a;
                taxiingplane->setInstruction(a);
                planestoremove.push_back(i);
            }
        }
        /*
        bool WaitingToCrossrunway=false;
        if(planelocation->isRunway()){
            WaitingToCrossrunway=true;
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<airport->getCallsign()<<", " <<taxiingplane->getCallsign()<<", "<<"Hold short at " <<planelocation->getName()<<endl;
        }
        if(planelocation==taxiingplane->getDestinaterunway()){
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<airport->getCallsign()<<", " <<taxiingplane->getCallsign()<<", "<<"Runway " <<planelocation->getName()<<" Vacated"<<endl;

        }
        if(!planelocation->getRoute().empty()){
            Location* nextlocation=(planelocation->getRoute().end()-1).operator*();
            if(!(nextlocation->isCrossing()&&nextlocation->isRunway())&&
                !(nextlocation->isOnuse())&&(!WaitingToCrossrunway||!planelocation->isCrossing())){
                taxiingplane->setNextLocation(nextlocation);
                if(WaitingToCrossrunway&&planelocation!=taxiingplane->getDestinaterunway()){
                    file<<"["<<time<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", "<<"Cleared to Cross runway "<<planelocation->getName() << endl;
                    file<<"["<<time<<"]"<<"[AIR]"<<endl;
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
*/
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
        if(planelocation==taxiingplane->getInstruction().begin().operator*()&&taxiingplane->getInstruction().begin().operator*()!=(taxiingplane->getInstruction().end()-1).operator*()){
            planelocation->setCrossing(false);
        }
        if(planelocation==taxiingplane->getInstruction()[taxiingplane->getInstruction().size()-1]){
            //plane finished running;
            nextStop.clear();
            if(planelocation->isRunway()&&planelocation!=taxiingplane->getDestinaterunway()){
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<airport->getCallsign()<<", " <<taxiingplane->getCallsign()<<", "<<"Hold short at " <<planelocation->getName()<<endl;
                nextStop.push_back(planelocation);
                if(planelocation->isCrossing()||planelocation->isOnuse()){
                    nextStop.push_back(planelocation);
                    file<<"["<<time<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", "<<"Hold more at"<<planelocation->getName()<<"." << endl;
                    taxiingplane->setInstruction(nextStop);
                }
                else{
                    file<<"["<<time<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", "<<"Cleared to Cross runway "<<planelocation->getName() << endl;
                    file<<"["<<time<<"]"<<"[AIR]"<<endl;
                    file<<taxiingplane->getCallsign()<<", "<<"Cleared to Cross runway "<<planelocation->getName() << endl;
                    planelocation->setCrossing(true);
                    nextStop.clear();
                    taxiingplane->setInstruction(nextStop);
                    makeInstructionToRunway(taxiingplane);
                }
            }
            else if(planelocation==taxiingplane->getDestinaterunway()){

                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<airport->getCallsign()<<", "<<taxiingplane->getCallsign()<<", holding short at "<<taxiingplane->getLocation()->getName()<<endl;

                Runway* destination=taxiingplane->getDestinaterunway();
                if(destination->getPlaneAtbegin()==NULL&&!destination->isOnuse()&&!destination->isCrossing()){

                    file<<"["<<time<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", runway "<<taxiingplane->getDestinaterunway()->getName()<<" cleared for take-off."<<endl;
                    file<<"["<<time<<"]"<<"[AIR]"<<endl;
                    file<<"runway "<<taxiingplane->getDestinaterunway()->getName()<<" cleared for take-off, "<<taxiingplane->getCallsign()<<endl;


                    vector<Location*> a;
                    taxiingplane->setInstruction(a);

                    taxiingplane->setPermission("fly");
                    destination->setPlaneAtbegin(taxiingplane);
                    destination->setCurrentairplane(taxiingplane);
                    planestoremove.push_back(i);
                }
                else if(destination->getPlaneAtbegin()==NULL&&!destination->isOnuse()){

                    file<<"["<<time<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", line up runway "<<taxiingplane->getDestinaterunway()->getName()<<" and wait."<<endl;
                    file<<"["<<time<<"]"<<"[AIR]"<<endl;
                    file<<"Line up runway "<<taxiingplane->getDestinaterunway()->getName()<<" and wait."<<taxiingplane->getCallsign()<<endl;


                    vector<Location*> a;
                    taxiingplane->setInstruction(a);

                    destination->setPlaneAtbegin(taxiingplane);
                    planestoremove.push_back(i);
                }
                else{

                    file<<"["<<time<<"]"<<"[ATC]"<<endl;
                    file<<taxiingplane->getCallsign()<<", hold position"<<endl;
                    file<<"["<<time<<"]"<<"[AIR]"<<endl;
                    file<<"Hold position, "<<airport->getCallsign()<<endl;
                }
            }
        }
        /*
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
//                file<<'a'<<endl;

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
         */
    }

    for (unsigned int j = 0; j < planestoremove.size(); ++j) {
        taxiingtorunway.erase(taxiingtorunway.begin()+planestoremove[j]-j);
    }
}

bool Signaltower::permissionLeavingGate(Airplane *airplane) {
    //didn't see any condition
    return true;
}

void Signaltower::makeInstructionToGate(Airplane *airplane) {
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

        string taxipoints="";
        for (unsigned int j = 0; j < nextStop.size(); ++j) {
            if(nextStop[j]->isTaxipoint()){
                if(taxipoints==""){
                    taxipoints=" via ";
                }
                taxipoints+=nextStop[j]->getName()+",";
            }
        }
        taxipoints=taxipoints.substr(0,taxipoints.size()-1);

        if(nextLocation!=planelocation->getRoute().begin()){

            file<<"["<<time<<"]"<<"[ATC]"<<endl;
            file<<taxiingplane->getCallsign()<<", "<<"Taxi to holdpoint "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+"." << endl;
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<"Taxi to holdpoint "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+", " <<airport->getCallsign()<< endl;
            taxiingplane->setInstruction(nextStop);
        }
        else{
            Gate* freegate=airport->findFreeGates();
            if(freegate){
                nextStop.push_back(freegate);
                airport->parkAirplane(freegate,taxiingplane);
                file<<"["<<time<<"]"<<"[ATC]"<<endl;
                file<<taxiingplane->getCallsign()<<", "<<"Taxi to gate "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+"." << endl;
                file<<"["<<time<<"]"<<"[AIR]"<<endl;
                file<<"Taxi to gate "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+", " <<airport->getCallsign()<< endl;
                taxiingplane->setInstruction(nextStop);
            }
        }
    }

}

void Signaltower::makeInstructionToRunway(Airplane *airplane) {
    vector<Location*> nextStop;
    Airplane* taxiingplane=airplane;
    Location* planelocation=taxiingplane->getLocation();
    Location* destination=taxiingplane->getDestinaterunway();
    nextStop.clear();
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

        string taxipoints="";
        for (unsigned int j = 0; j < nextStop.size(); ++j) {
            if(nextStop[j]->isTaxipoint()){
                if(taxipoints==""){
                    taxipoints=" via ";
                }
                taxipoints+=nextStop[j]->getName()+",";
            }
        }
        taxipoints=taxipoints.substr(0,taxipoints.size()-1);

        if(nextLocation!=destination->getRoute().end()){
            nextStop.push_back(nextLocation.operator*());
            file<<"["<<time<<"]"<<"[ATC]"<<endl;
            file<<taxiingplane->getCallsign()<<", "<<"Taxi to holdpoint "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+"." << endl;
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<"Taxi to holdpoint "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+", " <<airport->getCallsign()<< endl;
            taxiingplane->setInstruction(nextStop);
        }
        else{
            nextStop.push_back(destination);
            file<<"["<<time<<"]"<<"[ATC]"<<endl;
            file<<taxiingplane->getCallsign()<<", "<<"Taxi to runway "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+"." << endl;
            file<<"["<<time<<"]"<<"[AIR]"<<endl;
            file<<"Taxi to runway "<<nextStop[nextStop.size()-1]->getName()<<taxipoints+", " <<airport->getCallsign()<< endl;
            taxiingplane->setInstruction(nextStop);
        }
    }

}

