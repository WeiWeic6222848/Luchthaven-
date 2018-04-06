//
// Created by c6222848 on 4/6/18.
//

#include "Signaltower.h"
#include "algorithm"

Signaltower::Signaltower(Airport *airport) : airport(airport) {}

void Signaltower::receiveSignal(Airplane *airplane, string signal) {
    if (signal=="Approaching"){
        approachingAirplanes.push_back(airplane);
        airplane->setPermission("10000");
    }
    else if(signal=="Leaving"){
        leavingAirplanes.push_back(airplane);
    }
    else if(signal=="Approachingtogate"){
        taxiingtogate.push_back(airplane);
    }
    else if(signal=="LeavingtoRunway"){
        taxiingtorunway.push_back(airplane);
        Runway* destinaterunway=airport->findFreeRunway(airplane);
        airplane->setDestinaterunway(destinaterunway);
        destinaterunway->planeQueued();
    }
    else if(signal=="Emergency"){
        emergency.push_back(airplane);
    }
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
    bool buzyat3000=false;
    bool buzyat5000=false;
    vector<Airplane*> allflying=allflyingplanes();
    vector<int> planestoremove;
    for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
        if(approachingAirplanes[i]->getPermission()=="3000"){
            Runway* freerunway=airport->findFreeRunway(approachingAirplanes[i]);
            if(freerunway){
                freerunway->setCurrentairplane(approachingAirplanes[i]);
                approachingAirplanes[i]->setPermission("0");
                approachingAirplanes[i]->setDestinaterunway(freerunway);
            }
            else{
                buzyat3000=true;
                //not breaking here, beacause we're also checking all planes that have landed on the ground(runway), and removing them
                //to the next phase where the airplane needs to call the signal tower again.
            }
        }
        else if(approachingAirplanes[i]->getPermission()=="0"&&approachingAirplanes[i]->getHeight()==0){
            planestoremove.push_back(i);
            //plane landed on runway. waiting for next contact.
        }
    }

    for (unsigned int j = 0; j < planestoremove.size(); ++j) {
        approachingAirplanes[planestoremove[j]]->setLocation(
                approachingAirplanes[planestoremove[j]]->getDestinaterunway()->getTaxipoint());
        //plane goes to the taxipoint of the runway after landing.
        approachingAirplanes[planestoremove[j]]->getDestinaterunway()->getTaxipoint()->setCrossing(true);
        approachingAirplanes[planestoremove[j]]->setPermission("");
        approachingAirplanes[planestoremove[j]]->getDestinaterunway()->setCurrentairplane(NULL);
        approachingAirplanes[planestoremove[j]]->setDestinaterunway(NULL);
        approachingAirplanes.erase(approachingAirplanes.begin()+planestoremove[j]);
    }

    //looking for buzyat5000;
    for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
        if(approachingAirplanes[i]->getPermission()=="5000"){
            if(!buzyat3000){
                approachingAirplanes[i]->setPermission("3000");
                //no need to set buzy3000 anymore, not using it
            }
            else{
                buzyat5000=true;
                break;
            }
        }
    }

    if (!buzyat5000){
        for (unsigned int i = 0; i < approachingAirplanes.size(); ++i) {
            if(approachingAirplanes[i]->getHeight()>5000){
                approachingAirplanes[i]->setPermission("5000");
                break;
            }
        }
    }
}

void Signaltower::regulateTaxiingtoGate() {

    vector<int> planestoremove;

    for (unsigned int i = 0; i < taxiingtorunway.size(); ++i) {
        Airplane* taxiingplane=taxiingtorunway[i];
        Location* planelocation=taxiingplane->getLocation();
        if(!planelocation->getRoute().empty()){
            Location* nextlocation=(planelocation->getRoute().end()-1).operator*();
            if(!(nextlocation->isCrossing())&&!(nextlocation->isOnuse())){
                nextlocation->setCrossing(true);
                planelocation->setCrossing(false);
                taxiingplane->setLocation(nextlocation);
            }
            else{
                //plane wait on current location
            }
        }
        else{
            int freegate=airport->findFreeGates();
            if(freegate!=-1){
                airport->parkAirplane(freegate,taxiingplane);
                planelocation->setCrossing(false);
                taxiingplane->setLocation(NULL);
                planestoremove.push_back(i);
            }
            else{
                //plane wait until there is an free gate to park
            }
        }
    }
    for (unsigned int j = 0; j < planestoremove.size(); ++j) {
        taxiingtogate.erase(taxiingtogate.begin()+planestoremove[j]);
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
            if(!(nextlocation->isCrossing())&&!(nextlocation->isOnuse())){
                nextlocation->setCrossing(true);
                planelocation->setCrossing(false);
                taxiingplane->setLocation(nextlocation);
                if(nextlocation==(destination->getRoute().end()-1).operator*()){
                    taxiingplane->getDestinaterunway()->getTaxipoint()->addPlanesWaiting(taxiingplane);
                }
            }
            else{
                //plane wait on current location
            }
        }
        else{
            Taxipoint* currentlocation=taxiingplane->getDestinaterunway()->getTaxipoint();
            if(currentlocation->getPlanesWaitingForRunway()[0]==taxiingplane&&!destination->isOnuse()&&!destination->isCrossing()){

            }

            else{
                //plane wait until there is an free gate to park
            }
        }
    }

    for (unsigned int j = 0; j < planestoremove.size(); ++j) {
        taxiingtogate.erase(taxiingtogate.begin()+planestoremove[j]);
    }
}
