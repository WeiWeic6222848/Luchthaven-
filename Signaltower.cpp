//
// Created by c6222848 on 4/6/18.
//

#include <fstream>
#include "Signaltower.h"
#include "algorithm"

Signaltower::Signaltower(Airport *airport) : airport(airport) {

    string filename="../output/"+airport->getIata()+"_Tower.txt";
    file.open(filename.c_str(),ios::app);
    time=1;
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
            airplane->getDestinaterunway()->setCurrentairplane(airplane);
            airplane->getDestinaterunway()->setPlaneAtbegin(NULL);
            airplane->setPermission("fly");
            return true;
        }
        return false;
    }
    else if(signal=="ApproachingtoGate"){
        taxiingtogate.push_back(airplane);
        return true;
    }
    else if(signal=="LeavingtoRunway"){
        if(airplane->getDestinaterunway()!=NULL){
            taxiingtorunway.push_back(airplane);
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
            airplane->setDestinaterunway(destinaterunway);
            destinaterunway->planeQueued();
            return true;
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
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"hold south on the one eighty radial, expect further clearance at "<<time+1<<endl;
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
                file<<approachingAirplanes[i]->getCallsign()<<", "<<"hold south on the one eighty radial, expect further clearance at "<<time+1<<endl;
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

    for (unsigned int i = 0; i < taxiingtogate.size(); ++i) {
        Airplane* taxiingplane=taxiingtogate[i];
        Location* planelocation=taxiingplane->getLocation();
        if(!planelocation->getRoute().empty()){
            Location* nextlocation=(planelocation->getRoute().end()-1).operator*();
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
        Runway* destination=taxiingplane->getDestinaterunway();
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

bool Signaltower::permissionLeavingGate(Airplane *airplane) {
    //didn't see any condition
    return true;
}
