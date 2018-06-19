//
// Created by c6222848 on 5/2/18.
//


#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "DesignByContract.h"
#include "Airportsim.h"
#include "AirportUtils.h"
#include "Runway.h"
#include "Taxipoint.h"
#include "Gate.h"
#include "Airplane.h"

class AirplaneDomeinTest: public ::testing::Test{
protected:
    friend class Airport;

    Airportsim simulator;

    virtual void SetUp(){

    }

    virtual void TearDown(){

    }
};

TEST_F(AirplaneDomeinTest,gettersTestPlane){
    //settings
    string filename="../domeinTest/Airplane.xml";

    string number="BAW466";
    string callsign="Speedbird 466";
    string model="Boeing 747";
    string type="airline";
    string engine="jet";
    string size="large";
    Airplane::Airplaneallowedstatus status=Airplane::Approaching;
    int passenger=10;
    int passengercapacity=10;
    int fuel=123;
    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(),a,simulator);
    Airplane* testsubject=simulator.findAirplane(number);


    EXPECT_TRUE(testsubject->getCurrentTime()==Time());
    if(status==Airplane::Approaching){
        EXPECT_TRUE(testsubject->getLocation()==NULL);
        EXPECT_TRUE(testsubject->getHeight()==10000);
    }
    else if(status==Airplane::Standing_at_gate){
        EXPECT_TRUE(testsubject->getLocation()->isGate());
        EXPECT_TRUE(testsubject->getHeight()==0);
    }

    EXPECT_TRUE(testsubject->getStatus()==status);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::empty);
    EXPECT_TRUE(testsubject->getDestinateRunway()==NULL);
    EXPECT_TRUE(testsubject->getFuelCapacity()==fuel);
    EXPECT_TRUE(testsubject->getNumber()==number);
    EXPECT_TRUE(testsubject->getSize()==size);
    EXPECT_TRUE(testsubject->getModel()==model);
    EXPECT_TRUE(testsubject->getCallsign()==callsign);
    EXPECT_TRUE(testsubject->getEngine()==engine);
    EXPECT_TRUE(testsubject->getPassenger()==passenger);
    EXPECT_TRUE(testsubject->getPassengerCapacity()==passengercapacity);
    EXPECT_TRUE(testsubject->getType()==type);
    EXPECT_TRUE(testsubject->getFuel()==fuel);
    EXPECT_TRUE(testsubject->isDoingNothing()==true);
    EXPECT_TRUE(testsubject->getInstruction().size()==0);
    EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Just_landed);
    EXPECT_TRUE(testsubject->getDestination()==simulator.getAirports()[0]);



/*
    Time currenttime=testsubject->getCurrentTime();
    testsubject->timeRuns();
    EXPECT_TRUE(currenttime+1==testsubject->getCurrentTime());

    int height=testsubject->getHeight();
    testsubject->setPermission("Fly");
    testsubject->setStatus("Leaving");
    testsubject->rise();
    EXPECT_TRUE(testsubject->isDoingNothing()==false);
    while(!testsubject->isDoingNothing()){
        testsubject->timeRuns();
        testsubject->rise();
    }
    EXPECT_TRUE(testsubject->getHeight()==height+1000);

    height=testsubject->getHeight();
    testsubject->setStatus("Approaching");
    testsubject->fall();
    EXPECT_TRUE(testsubject->isDoingNothing()==false);
    while(!testsubject->isDoingNothing()){
        testsubject->timeRuns();
        testsubject->fall();
    }
    EXPECT_TRUE(testsubject->getHeight()==height-1000);

    Location nextlocation("abc");
    abcd.push_back(&nextlocation);*/

}


TEST_F(AirplaneDomeinTest,settersTestPlane) {


    //settings
    string filename = "../domeinTest/Airplane.xml";

    string number = "BAW466";
    string callsign = "Speedbird 466";
    string model = "Boeing 747";
    string type = "airline";
    string engine = "jet";
    string size = "large";
    //Airplane::Airplaneallowedstatus status = Airplane::Approaching;
    int passengercapacity = 10;
    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject = simulator.findAirplane(number);

    EXPECT_TRUE(testsubject->getCurrentTime()==Time());

    testsubject->setStatus(Airplane::Standing_at_gate);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Standing_at_gate);
    testsubject->setPermission(Airplane::fiveThousandPermission);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::fiveThousandPermission);
    Location abc("test");
    testsubject->setLocation(&abc);
    EXPECT_TRUE(testsubject->getLocation()==&abc);
    vector<Location*> abcd;
    abcd.push_back(&abc);
    testsubject->setInstruction(abcd);
    EXPECT_TRUE(testsubject->getInstruction()==abcd);
    testsubject->setPassenger(passengercapacity-1);
    EXPECT_TRUE(testsubject->getPassenger()==passengercapacity-1);
    Runway temp1("123",simulator.getAirports()[0],"asphalt",100);
    testsubject->setDestinateRunway(&temp1);
    EXPECT_TRUE(testsubject->getDestinateRunway()==&temp1);
    Airport temp2("123","123","123",100000,100000);
    testsubject->setDestination(&temp2);
    EXPECT_TRUE(testsubject->getDestination()==&temp2);
    testsubject->setNextDestination(&temp2);
    EXPECT_TRUE(testsubject->getNextDestination()==&temp2);
    testsubject->setFuel(1);
    EXPECT_TRUE(testsubject->getFuel()==1);
    testsubject->setFuelCapacity(1);
    EXPECT_TRUE(testsubject->getFuelCapacity()==1);
}

TEST_F(AirplaneDomeinTest,gettersAirport) {
    //settings
    string filename = "../domeinTest/Airport.xml";
    string name = "Antwerp International Airport";
    string iata = "ANR";
    string callsign = "Antwerp Tower";
    string runwayname = "11R";
    string taxipointname="Alpha";
    unsigned int gates = 10;
    unsigned int runways = 1;
    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airport *testsubject = simulator.getAirports()[0];

    EXPECT_TRUE(testsubject->ProperInitialized());
    EXPECT_TRUE(testsubject->getName()==name);
    EXPECT_TRUE(testsubject->getIata()==iata);
    EXPECT_TRUE(testsubject->getCallsign()==callsign);
    EXPECT_TRUE(testsubject->getGates().size()==gates);
    EXPECT_TRUE(testsubject->getRunways().size()==runways);


    EXPECT_TRUE(testsubject->findFreeGates()!=NULL);
    for (unsigned int i = 0; i <testsubject->getGates().size() ; ++i) {
        testsubject->getGates()[i]->setOnuse(true);
    }
    EXPECT_TRUE(testsubject->findFreeGates()==NULL);

    EXPECT_TRUE(testsubject->findTaxipoint("123456")==NULL);
    EXPECT_TRUE(testsubject->findTaxipoint(taxipointname)!=NULL);
    EXPECT_TRUE(testsubject->findRunway(runwayname)!=NULL);
    EXPECT_TRUE(testsubject->findRunway("123456")==NULL);
    EXPECT_TRUE(testsubject->findTaxipoint("")==NULL);
    EXPECT_TRUE(testsubject->findRunway("")==NULL);
}

TEST_F(AirplaneDomeinTest,settersAirport) {
    //settings
    string filename = "../domeinTest/Airport.xml";
    string name = "Antwerp International Airport";
    string iata = "ANR";
    string callsign = "Antwerp Tower";
    int passenger = 0;
    unsigned int runways = 1;


    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airport *testsubject = simulator.getAirports()[0];

    EXPECT_TRUE(testsubject->getPassengers()==passenger);
    testsubject->addPassenger(10)
    EXPECT_TRUE(testsubject->getPassengers()==passenger+10);
    testsubject->removePassenger(10);
    EXPECT_TRUE(testsubject->getPassengers()==passenger);

    Airplane* tempair=new Airplane(Airplane::Approaching,"123","123","123","private","jet","small",1,1,1,testsubject);
    EXPECT_TRUE(testsubject->getGateFromAirplane(tempair)==NULL);
    testsubject->parkAirplane(testsubject->getGates()[0],tempair);
    EXPECT_TRUE(testsubject->getGates()[0]->isOnuse());
    EXPECT_TRUE(testsubject->getGateFromAirplane(tempair)!=NULL);
    EXPECT_TRUE(testsubject->getGateFromAirplane(tempair)==testsubject->getGates()[0]);

    testsubject->freeGate(testsubject->getGates()[0]);
    EXPECT_TRUE(testsubject->getGateFromAirplane(tempair)==NULL);
    EXPECT_TRUE(!testsubject->getGates()[0]->isOnuse());

    delete(tempair);

    EXPECT_TRUE(testsubject->getTaxipoints().size()==1);
    EXPECT_TRUE(testsubject->findTaxipoint("123")==NULL);
    testsubject->addTaxipoints(new Taxipoint("123",testsubject->getRunways()[0]));
    EXPECT_TRUE(testsubject->findTaxipoint("123")!=NULL);
    EXPECT_TRUE(testsubject->getTaxipoints().size()==2);

    EXPECT_TRUE(testsubject->findRunway("123")==NULL);
    testsubject->addRunway(new Runway("123",testsubject,"asphalt",10000));
    EXPECT_TRUE(testsubject->findRunway("123")!=NULL);
    EXPECT_TRUE(testsubject->getRunways().size()==runways+1);
}

TEST_F(AirplaneDomeinTest,gettersRunway) {
    //settings
    string filename = "../domeinTest/Runway.xml";
    string name = "11R";
    string airport = "ANR";
    Runwaytype type = grass;
    int length = 1010;
    string taxipoint = "Alpha";
    int airplanesqueing=0;
    unsigned int routesize=1;
    Airplane* plane=NULL;
    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Runway *testsubject = simulator.getAirports()[0]->getRunways()[0];


    EXPECT_TRUE(testsubject->getName()==name);
    EXPECT_TRUE(testsubject->getTaxipoint()->getName()==taxipoint);
    EXPECT_TRUE(testsubject->getPlaneAtEnd()==plane);
    EXPECT_TRUE(testsubject->getPlaneAtbegin()==plane);
    EXPECT_TRUE(testsubject->getCurrentairplane()==plane);
    EXPECT_TRUE(testsubject->getRoute()[0]->getName()==taxipoint);
    EXPECT_TRUE(testsubject->getAirplanequeueing()==airplanesqueing);
    EXPECT_TRUE(testsubject->getAirport()->getIata()==airport);
    EXPECT_TRUE(testsubject->getLength()==length);
    EXPECT_TRUE(testsubject->getType()==type);

    EXPECT_TRUE(!testsubject->isOnuse());
    EXPECT_TRUE(testsubject->ProperInitialized());
    EXPECT_TRUE(!testsubject->isCrossing());
    EXPECT_TRUE(!testsubject->isTaxipoint());
    EXPECT_TRUE(!testsubject->isGate());
    EXPECT_TRUE(testsubject->isRunway());
    EXPECT_TRUE(testsubject->getRoute().size()==routesize);

}

TEST_F(AirplaneDomeinTest,settersRunway){
    //settings
    string filename = "../domeinTest/Runway.xml";
    string name = "11R";
    string airport = "ANR";
    string taxipoint = "Alpha";

    Airplane* plane=NULL;

    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    plane = simulator.getAirplanes()[0];
    string callsign = plane->getCallsign();
    Runway *testsubject = simulator.getAirports()[0]->getRunways()[0];

    EXPECT_FALSE(testsubject->isOnuse());
    testsubject->setOnuse(true);
    EXPECT_TRUE(testsubject->isOnuse());

    EXPECT_TRUE(testsubject->getCurrentairplane()==NULL);
    testsubject->setCurrentairplane(plane);
    EXPECT_TRUE(testsubject->getCurrentairplane()->getCallsign()==callsign);

    EXPECT_TRUE(testsubject->getPlaneAtbegin()==NULL);
    testsubject->setPlaneAtbegin(plane)
    EXPECT_TRUE(testsubject->getPlaneAtbegin()->getCallsign()==callsign);

    EXPECT_TRUE(testsubject->getPlaneAtEnd()==NULL);
    testsubject->setPlaneAtEnd(plane)
    EXPECT_TRUE(testsubject->getPlaneAtEnd()->getCallsign()==callsign);

    EXPECT_FALSE(testsubject->isTaxipoint());

    EXPECT_FALSE(testsubject->isCrossing());
    testsubject->setCrossing(true)
    EXPECT_TRUE(testsubject->isCrossing());

    Taxipoint* temptaxi=new Taxipoint("123",testsubject);
    testsubject->getAirport()->addTaxipoints(temptaxi);

    EXPECT_FALSE(testsubject->getTaxipoint()->getName()=="123");
    testsubject->setTaxipoint(temptaxi);
    EXPECT_TRUE(testsubject->getTaxipoint()->getName()=="123");

    unsigned int routesize=testsubject->getRoute().size();
    EXPECT_FALSE(testsubject->getRoute().size()==routesize+1);
    EXPECT_FALSE(testsubject->getRoute().back()==temptaxi);
    testsubject->addCrossingToRoute(temptaxi);
    EXPECT_TRUE(testsubject->getRoute().size()==routesize+1);
    EXPECT_TRUE(testsubject->getRoute().back()==temptaxi);

}
TEST_F(AirplaneDomeinTest, testingRunwayQueue){
    //settings
    string filename = "../domeinTest/Runway.xml";
    string name = "11R";
    string airport = "ANR";
    string taxipoint = "Alpha";

    Airplane* plane=NULL;

    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    plane = simulator.getAirplanes()[0];
    string callsign = plane->getCallsign();
    Runway *testsubject = simulator.getAirports()[0]->getRunways()[0];

    EXPECT_TRUE(testsubject->ProperInitialized());
    EXPECT_TRUE(testsubject->getAirplanequeueing()==0);
    testsubject->planeQueued()
    EXPECT_TRUE(testsubject->getAirplanequeueing()==1);
    testsubject->planeLeaved();
    EXPECT_TRUE(testsubject->getAirplanequeueing()==0);


}

TEST_F(AirplaneDomeinTest, testingGate){
    //settings
    string filename = "../domeinTest/Airport.xml";
    unsigned int gates = 10;
    Airplane* plane=NULL;
    //endofsettings

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    vector<Gate*> testsubject = simulator.getAirports()[0]->getGates();

    EXPECT_TRUE(testsubject.size()==gates);
    for (unsigned int i = 0; i < testsubject.size(); ++i) {
        EXPECT_FALSE(testsubject[i]->isOnuse());
        EXPECT_FALSE(testsubject[i]->isTaxipoint());
        EXPECT_FALSE(testsubject[i]->isCrossing());
        EXPECT_TRUE(testsubject[i]->isGate());
        EXPECT_TRUE(testsubject[i]->ProperInitialized());
        EXPECT_TRUE(testsubject[i]->getCurrentPlane()==plane);
        EXPECT_TRUE(testsubject[i]->getRoute().empty());
        EXPECT_TRUE(testsubject[i]->getName()==to_string(i+1));
        EXPECT_TRUE(testsubject[i]->getCurrentPlane()==NULL);
        EXPECT_TRUE(testsubject[i]->getPlaneNearGate()==NULL);
    }
}


TEST_F(AirplaneDomeinTest, testingLocation){

    //settings
    string filename = "../domeinTest/Airportsim.xml";

    Airplane::Airplaneallowedstatus statusPlane = Airplane::Approaching;
    string numberPlane = "N11843";
    string callsignPlane = "GOD";

    string nameAirport = "Brussels Airport";
    string iataAirport = "BRU";
    string callsignAirport = "Brussel tower";
    Airport* airport = new Airport(nameAirport,iataAirport,callsignAirport,10,50000);
    //endofsettings
    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airplane* plane=new Airplane(statusPlane,numberPlane,callsignPlane,"C 4","private","jet","medium",20,10000,80,simulator.getAirports().front());

    EXPECT_TRUE(simulator.ProperInitialized());

    simulator.addAirport(airport);
    EXPECT_EQ((unsigned)2,simulator.getAirports().size());
    EXPECT_EQ(iataAirport,simulator.getAirports().back()->getIata());
    simulator.removeAirport(airport);
    EXPECT_EQ((unsigned)1,simulator.getAirports().size());

    simulator.addAirplane(plane);
    EXPECT_EQ((unsigned)2,simulator.getAirplanes().size());
    EXPECT_EQ(numberPlane,simulator.getAirplanes().back()->getNumber());
}
TEST_F(AirplaneDomeinTest, AirportUtils){
    //settings
    string filename = "../domeinTest/AIrportUtils.xml";
    //endofsettings
    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airplane* plane = simulator.getAirplanes().front();

    EXPECT_TRUE(isRightAirplaneCombination("private","jet","small"));
    EXPECT_TRUE(isRightAirplaneCombination("private","propeller","small"));
    EXPECT_TRUE(isRightAirplaneCombination("private","jet","medium"));
    EXPECT_TRUE(isRightAirplaneCombination("airline","propeller","medium"));
    EXPECT_TRUE(isRightAirplaneCombination("airline","jet","medium"));
    EXPECT_TRUE(isRightAirplaneCombination("airline","jet","large"));
    EXPECT_TRUE(isRightAirplaneCombination("military","jet","small"));
    EXPECT_TRUE(isRightAirplaneCombination("military","propeller","large"));
    EXPECT_TRUE(isRightAirplaneCombination("emergency","propeller","small"));

    EXPECT_TRUE(isRightAirplaneCombination(plane->getType(),plane->getEngine(),plane->getSize()));

    EXPECT_FALSE(isRightAirplaneCombination("private","propeller","medium"));
    EXPECT_FALSE(isRightAirplaneCombination("airline","propeller","small"));
    EXPECT_FALSE(isRightAirplaneCombination("military","propeller","medium"));
    EXPECT_FALSE(isRightAirplaneCombination("emergency","propeller","medium"));
    EXPECT_FALSE(isRightAirplaneCombination("emergency","propeller","large"));
    EXPECT_FALSE(isRightAirplaneCombination("emergency","jet","small"));
    EXPECT_FALSE(isRightAirplaneCombination("trol","berg","brug"));

    Airplane* testplane = new Airplane(Airplane::Approaching,"N11843","GOD","C 4","private","jet","medium",20,10000,80,simulator.getAirports().front());
    EXPECT_TRUE(airplaneCanLandOnGrass(plane));
    EXPECT_FALSE(airplaneCanLandOnGrass(testplane));

    EXPECT_EQ(2000,requiredLengthOfRunway(testplane));
    EXPECT_EQ(500,requiredLengthOfRunway(plane));
    delete (testplane);
}

TEST_F(AirplaneDomeinTest, gettersAirportsim){
    //settings
    string filename = "../domeinTest/Airportsim.xml";
    string nameAirport="Antwerp International Airport";
    string iataAirport="ANR";
    string callsignAirplane="Speedbird 466";
    string numberAirplane="BAW466";
    //endofsettings
    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    EXPECT_TRUE(simulator.ProperInitialized());

    EXPECT_EQ(nameAirport,simulator.getAirports().front()->getName());
    EXPECT_EQ(nameAirport,simulator.findAirport(iataAirport)->getName());
    EXPECT_EQ(callsignAirplane,simulator.getAirplanes().front()->getCallsign());
    EXPECT_EQ(callsignAirplane,simulator.findAirplane(numberAirplane)->getCallsign());
    //simulator.findRunway()
    EXPECT_EQ(Time(12,0),simulator.getCurrentTime());

    EXPECT_TRUE(simulator.findAirplane(numberAirplane)!=NULL);
    EXPECT_TRUE(simulator.findAirplane("123")==NULL);
    EXPECT_TRUE(simulator.findAirport(iataAirport)!=NULL);
    EXPECT_TRUE(simulator.findAirport("123")==NULL);
    EXPECT_TRUE(simulator.findRunway(simulator.getAirports()[0]->getRunways()[0]->getName(),simulator.getAirports()[0]->getIata())!=NULL);
    EXPECT_TRUE(simulator.findRunway("123","123")==NULL);
}

TEST_F(AirplaneDomeinTest, settersAirportsim){
    //settings
    string filename = "../domeinTest/Airportsim.xml";

    Airplane::Airplaneallowedstatus statusPlane = Airplane::Approaching;
    string numberPlane = "N11843";
    string callsignPlane = "GOD";

    string nameAirport = "Brussels Airport";
    string iataAirport = "BRU";
    string callsignAirport = "Brussel tower";
    Airport* airport = new Airport(nameAirport,iataAirport,callsignAirport,10,50000);
    //endofsettings
    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airplane* plane=new Airplane(statusPlane,numberPlane,callsignPlane,"C 4","private","jet","medium",20,10000,80,simulator.getAirports().front());

    EXPECT_TRUE(simulator.ProperInitialized());

    simulator.addAirport(airport);
    EXPECT_EQ((unsigned)2,simulator.getAirports().size());
    EXPECT_EQ(iataAirport,simulator.getAirports().back()->getIata());
    simulator.removeAirport(airport);
    EXPECT_EQ((unsigned)1,simulator.getAirports().size());

    simulator.addAirplane(plane);
    EXPECT_EQ((unsigned)2,simulator.getAirplanes().size());
    EXPECT_EQ(numberPlane,simulator.getAirplanes().back()->getNumber());

    EXPECT_FALSE(simulator.getCurrentTime()==Time(12,50));
    simulator.setCurrentTime(Time(12,50));
    EXPECT_TRUE(simulator.getCurrentTime()==Time(12,50));}



TEST_F(AirplaneDomeinTest,invalidInput){


    //setting
    string filename="../domeinTest/Airplane.xml";

    string number="BAW466";
    string callsign="Speedbird 466";
    string model="Boeing 747";
    string type="airline";
    string engine="jet";
    string size="large";
    string status="Approaching";
    //int passenger=10;
    int passengercapacity=10;
    int fuel=123;
    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(),a,simulator);
    Airplane* testsubjectAirplane=simulator.findAirplane(number);
    Airport* testsubjectAirport=testsubjectAirplane->getDestination();
    Runway* testsubjectRunway=testsubjectAirport->getRunways()[0];


    EXPECT_DEATH(testsubjectAirplane->setPassenger(passengercapacity+1),"");
    EXPECT_DEATH(testsubjectAirplane->setFuel(fuel+1),"");
    EXPECT_DEATH(testsubjectAirplane->setFuelCapacity(fuel-1),"");
    EXPECT_DEATH(testsubjectAirport->getGateFromAirplane(NULL),"");
    EXPECT_DEATH(testsubjectAirport->findFreeRunway(NULL),"");
    EXPECT_DEATH(testsubjectRunway->addCrossingToRoute(NULL),"");
    EXPECT_DEATH(airplaneCanLandOnGrass(NULL),"");
    EXPECT_DEATH(requiredLengthOfRunway(NULL),"");
    EXPECT_DEATH(getBasesqwakcode(NULL),"");

}

TEST_F(AirplaneDomeinTest,gettersTaxpoint){
    //settings
    string filename = "../domeinTest/Runway.xml";
    string name="Alpha";
    //endofsettings
    ofstream a;
    LoadAirport(filename.c_str(),a,simulator);
    Taxipoint* testsubject=simulator.getAirports()[0]->getTaxipoints()[0];
    EXPECT_TRUE(testsubject->getName()==name);
    EXPECT_TRUE(testsubject->getRoute().empty());
    EXPECT_TRUE(testsubject->getPlanesWaiting().empty());
    EXPECT_TRUE(testsubject->getRunwayonpoint()==simulator.getAirports()[0]->getRunways()[0]);

}


TEST_F(AirplaneDomeinTest,SimulationGeneralTest) {
    //settings
    string filename = "../domeinTest/SimulationTest.xml";

    string type="airline";
    string engine="jet";
    string size="large";
    //endofsettings

    ofstream a;

    int fallingminute=0;
    int takeoffminute= 2;
    if(engine=="propeller"){
        fallingminute = 2;
        takeoffminute= 3;
    }
    else if(engine=="jet"){
        fallingminute = 1;
        takeoffminute= 2;
    }
    int landingminute = 2;
    int taxiingminute = 5;
    int crossingminute = 1;

    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject = new Airplane(Airplane::Approaching,"TestApproach_Subject_001","TAS001","TAS",type,engine,size,1,100000,100000,simulator.getAirports()[0]);
    simulator.addAirplane(testsubject);
    //made the test subject;

    //subject contact air-controller
    simulator.simulate_Onetime();
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==10000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::empty);//permission is empty when aircontroller didnt get any messenge;

    //air-controller gets subject's contact and try to contact subject
    simulator.simulate_Onetime();
    EXPECT_TRUE(!testsubject->isDoingNothing());//subject waiting for return signal and shouldnt be able to do anything atm;
    EXPECT_TRUE(testsubject->getHeight()==10000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::tenThousandPermission);//permission setted by aircontroller to control.

    //subject gets air-controller messenge to fall;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==10000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::fiveThousandPermission);

    //plane gets messenge, reacting;
    simulator.simulate_Onetime();
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==10000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::fiveThousandPermission);

    //after that plane knows he should continue falling, it's gonna be 2min each time;
    for (int j = 0; j <5 ; ++j) {
        for (int i = 0; i < fallingminute; ++i) {
            EXPECT_TRUE(!testsubject->isDoingNothing());
            simulator.simulate_Onetime();
        }

        EXPECT_TRUE(testsubject->getPermission()==Airplane::fiveThousandPermission);
        EXPECT_TRUE(testsubject->getHeight()==10000-1000*(j+1));
    }

    EXPECT_TRUE(testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==5000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::fiveThousandPermission);
    //airplane at 5000 meter standing still(potentially flying around but not falling)
    // waiting for tower to react.
    //tower should have detected it right away and start to contact airplane

    //plane gets messenge, reacting;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->isDoingNothing());//just got messenge shouldnt have moved yet.
    EXPECT_TRUE(testsubject->getHeight()==5000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::threeThousandPermission);


    //plane starts moving again;
    simulator.simulate_Onetime();
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==5000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::threeThousandPermission);

    for (int j = 0; j <2 ; ++j) {
        for (int i = 0; i < fallingminute; ++i) {
            EXPECT_TRUE(!testsubject->isDoingNothing());
            simulator.simulate_Onetime();
        }

        EXPECT_TRUE(testsubject->getPermission()==Airplane::threeThousandPermission);
        EXPECT_TRUE(testsubject->getHeight()==5000-1000*(j+1));
    }

    EXPECT_TRUE(testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==3000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::threeThousandPermission);
    //airplane at 3000 meter standing still(potentially flying around but not falling)
    // waiting for tower to react.
    //tower should have detected it right away and start to contact airplane

    //plane gets messenge, reacting;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->isDoingNothing());//just got messenge shouldnt have moved yet.
    EXPECT_TRUE(testsubject->getHeight()==3000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::LandingPermission);

    //plane starts moving again;
    simulator.simulate_Onetime();
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==3000);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::LandingPermission);

    for (int j = 0; j <3; ++j) {
        for (int i = 0; i < fallingminute; ++i) {
            EXPECT_TRUE(!testsubject->isDoingNothing());
            simulator.simulate_Onetime();
        }

        EXPECT_TRUE(testsubject->getPermission()==Airplane::LandingPermission);
        EXPECT_TRUE(testsubject->getHeight()==3000-1000*(j+1));
    }

    //subject starts to land on the runway;
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==0);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::LandingPermission);

    for (int k = 0; k <landingminute ; ++k) {
        simulator.simulate_Onetime();
    }

    //once landed, airplane going to send messenge to tower for taxiing.
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==0);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::LandingPermission);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Landed);

    //tower gets messenge;
    simulator.simulate_Onetime();
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(testsubject->getHeight()==0);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::LandingPermission);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Landed);

    //tower reacted, airplane gets messenge, airplane reacting;
    //tower gives instruction right away.
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->isDoingNothing());
    //atm airplane doesnt need to wait for another signal nor is it doing something.
    //so isDoingNothing means -> airplane can now proceed to next move.
    EXPECT_TRUE(testsubject->getHeight()==0);
    EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Landed);
    EXPECT_TRUE(!testsubject->getInstruction().empty());
    EXPECT_TRUE(testsubject->getLocation()==testsubject->getInstruction()[0]);












    //proceed to taxiing to gate state.
    //airplane change it's status, proceed to taxiing stage;
    simulator.simulate_Onetime();
    EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject taxiing to taxipoint.
    //EXPECT_TRUE(testsubject->getHeight()==0);
    //height doesnt matter now
    EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Taxiing_to_gate);
    EXPECT_TRUE(!testsubject->getInstruction().empty());
    EXPECT_TRUE(testsubject->getLocation()==testsubject->getInstruction()[1]);


    //testsubject goes on taxiing
    //this should be a while loop.
    while(!testsubject->getLocation()->isGate()){
        int m=2;
        //m=2, means that this is the third element on the instruction
        //instruction contains:current location as first element(runway), adjesing taxipoint as second element, and the next runway/gate as 3rd element
        //should always test on the case that m==2, and test the whole instruction at once;


        for (int l = 0; l <taxiingminute ; ++l) {
            EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject taxiing in taxipoint
            EXPECT_TRUE(testsubject->getLocation()->isTaxipoint());
            simulator.simulate_Onetime();
        }
        //airplane is now at runway or a gate

        //if the test subject is going to cross runway
        if(testsubject->getLocation()->isRunway()){
            //airplane at runway sending signal to cross runway last minute, and this minute it's finished
            simulator.simulate_Onetime();
            EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);
            EXPECT_TRUE(testsubject->getStatus()==Airplane::Taxiing_to_gate);
            EXPECT_TRUE(testsubject->getLocation()==testsubject->getInstruction()[m]);

            //tower react to airplane, airplane receive messenge.
            simulator.simulate_Onetime();
            EXPECT_TRUE(testsubject->getPermission()==Airplane::Cleared_to_crossPermission);//happy day scenario, tower gives permission right away.
            EXPECT_TRUE(testsubject->getLocation()->isCrossing());

            //airplane reacting.
            simulator.simulate_Onetime();
            EXPECT_TRUE(testsubject->getPermission()==Airplane::Cleared_to_crossPermission);//happy day scenario, tower gives permission right away.
            EXPECT_TRUE(testsubject->getLocation()->isCrossing());

            for (int l = 0; l <crossingminute ; ++l) {
                EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject crossing runway.
                EXPECT_TRUE(testsubject->getLocation()->isRunway());
                simulator.simulate_Onetime();
            }
            EXPECT_TRUE(testsubject->getLocation()->isTaxipoint());
            //a new cycle begins where airplane is taxiing at the next taxipoint.
        }
        else if(testsubject->getLocation()->isGate()){
            //test subject reaches it's destination gate.

            EXPECT_TRUE(testsubject->getPermission()==Airplane::empty);
            EXPECT_TRUE(testsubject->getLocation()==testsubject->getInstruction()[m]);
            EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject done taxiing,starts with maintanance/unloading passenger;
            EXPECT_TRUE(testsubject->getStatus()==Airplane::Standing_at_gate);
            break;
        }
        else{
            cerr<<"shouldnt happen"<<endl;
            throw "death";
        }
    }









    //proceed to at gate step;
    EXPECT_TRUE(testsubject->getPermission()==Airplane::empty);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Standing_at_gate);
    EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject done taxiing,starts with maintanance/unloading passenger;
    EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Just_landed);

    int passengerminute = 5;
    int techcontroltime = 1;
    int pushbackminute = 1;
    if(testsubject->getSize()=="medium"){
        passengerminute=10;
        techcontroltime = 2;
        pushbackminute = 2;
    }else if(testsubject->getSize()=="large"){
        passengerminute=15;
        techcontroltime = 3;
        pushbackminute = 3;
    }
    else if(testsubject->getSize()=="small"){
        passengerminute=5;
        techcontroltime= 1;
        pushbackminute = 1;
    }
    else{
        cerr<<"doesn't exist size"<<endl;
        throw;
    }

    for (int n = 0; n <passengerminute ; ++n) {
        EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Just_landed);
        EXPECT_TRUE(!testsubject->isDoingNothing());//unloading passenger;
        simulator.simulate_Onetime();
    }

    EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Technical_control);
    EXPECT_TRUE(testsubject->getPassenger()==0);

    for (int i1 = 0; i1 < techcontroltime ; ++i1) {

        EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Technical_control);
        EXPECT_TRUE(testsubject->getPassenger()==0);
        EXPECT_TRUE(!testsubject->isDoingNothing());//tech control;
        simulator.simulate_Onetime();
    }


    int fuelminute=testsubject->getFuelCapacity()*1.0/10000+0.9999;
    EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Refueling);
    EXPECT_TRUE(testsubject->getPassenger()==0);

    for (int k1 = 0; k1 <fuelminute ; ++k1) {
        EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Refueling);
        EXPECT_TRUE(testsubject->getPassenger()==0);
        simulator.simulate_Onetime();
    }

    EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Boarding);
    EXPECT_TRUE(testsubject->getPassenger()==0);
    EXPECT_TRUE(testsubject->getFuelCapacity()==testsubject->getFuel());

    for (int l1 = 0; l1 < passengerminute; ++l1) {
        EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Boarding);
        EXPECT_TRUE(testsubject->getPassenger()==0);
        EXPECT_TRUE(testsubject->getFuelCapacity()==testsubject->getFuel());
        simulator.simulate_Onetime();
    }

    EXPECT_TRUE(testsubject->getCheckProcedure()==Airplane::Ready_to_leave);
    EXPECT_TRUE(testsubject->getPassenger()==testsubject->getPassengerCapacity());
    EXPECT_TRUE(testsubject->getFuelCapacity()==testsubject->getFuel());



    Gate* planegate=testsubject->getDestination()->getGateFromAirplane(testsubject);
    if(planegate==NULL){
        cerr<<"???"<<endl;
        throw;
    }

    //plane sended signal, tower received it.
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::empty);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Standing_at_gate);
    EXPECT_TRUE(!testsubject->isDoingNothing());
    EXPECT_TRUE(planegate->getCurrentPlane()==testsubject);

    //tower sended signal back, happy day so IFR allowed
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::IFR_clearancyPermission);
    EXPECT_TRUE(testsubject->getLocation()==planegate);
    EXPECT_TRUE(testsubject->getInstruction().empty());
    EXPECT_TRUE(planegate->getCurrentPlane()==testsubject);

    //airplane reacting
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::IFR_clearancyPermission);
    EXPECT_TRUE(testsubject->getLocation()==planegate);
    EXPECT_TRUE(testsubject->getInstruction().empty());
    EXPECT_TRUE(planegate->getCurrentPlane()==testsubject);

    //airplane sending signal for pushback, tower received it.
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::IFR_clearancyPermission);
    EXPECT_TRUE(testsubject->getLocation()==planegate);
    EXPECT_TRUE(testsubject->getInstruction().empty());
    EXPECT_TRUE(planegate->getCurrentPlane()==testsubject);

    //tower react to signal, airplane received it.
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::Push_backPermission);
    EXPECT_TRUE(testsubject->getLocation()==planegate);
    EXPECT_TRUE(testsubject->getInstruction().empty());
    EXPECT_TRUE(planegate->getCurrentPlane()==testsubject);

    //airplane reacting;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::Push_backPermission);
    EXPECT_TRUE(testsubject->getLocation()==planegate);
    EXPECT_TRUE(testsubject->getInstruction().empty());
    EXPECT_TRUE(planegate->getCurrentPlane()==testsubject);

    for (int m1 = 0; m1 <pushbackminute ; ++m1) {
        EXPECT_TRUE(planegate->isOnuse());
        EXPECT_TRUE(testsubject->getPermission()==Airplane::Push_backPermission);
        EXPECT_TRUE(testsubject->getLocation()==planegate);
        EXPECT_TRUE(testsubject->getInstruction().empty());
        EXPECT_TRUE(!testsubject->isDoingNothing());
        EXPECT_TRUE(planegate->getCurrentPlane()==testsubject);
        simulator.simulate_Onetime();
    }

    //plane has moved out of the way
    EXPECT_TRUE(planegate->getPlaneNearGate()==testsubject);
    EXPECT_TRUE(!planegate->isOnuse());

    //plane sended taxi ready messenge, tower received it.
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::Push_backPermission);
    EXPECT_TRUE(testsubject->getInstruction().empty());
    EXPECT_TRUE(planegate->getPlaneNearGate()==testsubject);
    EXPECT_TRUE(!planegate->isOnuse());

    //tower react to plane, plane received it.
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);
    EXPECT_TRUE(!testsubject->getInstruction().empty());
    EXPECT_TRUE(testsubject->getLocation()==planegate);
    EXPECT_TRUE(planegate->getPlaneNearGate()==testsubject);

    //plane reacting&&moving to taxipoint(special case i just made in instant, it is possible to make it cost 1 minute)
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);
    EXPECT_TRUE(!testsubject->getInstruction().empty());
    EXPECT_TRUE(testsubject->getLocation()!=planegate);
    EXPECT_TRUE(testsubject->getLocation()->isTaxipoint());
    EXPECT_TRUE(testsubject->getLocation()==testsubject->getInstruction()[1]);


    //going to runway check, similair as going to gate check
    while(testsubject->getLocation()!=testsubject->getDestinateRunway()){
        int m=2;
        //m=2, means that this is the third element on the instruction
        //instruction contains:current location as first element(runway), adjesing taxipoint as second element, and the next runway/gate as 3rd element
        //should always test on the case that m==2, and test the whole instruction at once;


        for (int l = 0; l <taxiingminute ; ++l) {
            EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject taxiing in taxipoint
            EXPECT_TRUE(testsubject->getLocation()->isTaxipoint());
            simulator.simulate_Onetime();
        }
        //airplane is now at runway or a gate

        //if the test subject is going to cross runway
        if(testsubject->getLocation()->isRunway()&&testsubject->getLocation()!=testsubject->getDestinateRunway()){
            //airplane at runway sending signal to cross runway last minute, and this minute it's finished
            simulator.simulate_Onetime();
            EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);
            EXPECT_TRUE(testsubject->getStatus()==Airplane::Taxiing_to_runway);
            EXPECT_TRUE(testsubject->getLocation()==testsubject->getInstruction()[m]);

            //tower react to airplane, airplane receive messenge.
            simulator.simulate_Onetime();
            EXPECT_TRUE(testsubject->getPermission()==Airplane::Cleared_to_crossPermission);//happy day scenario, tower gives permission right away.
            EXPECT_TRUE(testsubject->getLocation()->isCrossing());

            //airplane reacting.
            simulator.simulate_Onetime();
            EXPECT_TRUE(testsubject->getPermission()==Airplane::Cleared_to_crossPermission);//happy day scenario, tower gives permission right away.
            EXPECT_TRUE(testsubject->getLocation()->isCrossing());

            for (int l = 0; l <crossingminute ; ++l) {
                EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject crossing runway.
                EXPECT_TRUE(testsubject->getLocation()->isRunway());
                simulator.simulate_Onetime();
            }
            EXPECT_TRUE(testsubject->getLocation()->isTaxipoint());
            //a new cycle begins where airplane is taxiing at the next taxipoint.
        }
        else if(testsubject->getLocation()==testsubject->getDestinateRunway()){
            //test subject reaches it's destination gate.

            EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);
            EXPECT_TRUE(testsubject->getLocation()==testsubject->getInstruction()[m]);
            EXPECT_TRUE(!testsubject->isDoingNothing());//testsubject done taxiing,starts with maintanance/unloading passenger;
            EXPECT_TRUE(testsubject->getStatus()==Airplane::Taxiing_to_runway);
            break;
        }
        else{
            cerr<<"shouldnt happen"<<endl;
            throw "death";
        }
    }

    //test subject now are sending to tower that it reached the destinated runway;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::TaxiingPermission);


    //tower shold react that airplane can fly;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::FlyPermission);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Taxiing_to_runway);
    EXPECT_TRUE(testsubject->getDestinateRunway()->getCurrentairplane()==testsubject);
    EXPECT_TRUE(testsubject->getDestinateRunway()->isOnuse());


    //airplane reacts
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject->getPermission()==Airplane::FlyPermission);
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Taxiing_to_runway);
    EXPECT_TRUE(testsubject->getDestinateRunway()->getCurrentairplane()==testsubject);
    EXPECT_TRUE(testsubject->getDestinateRunway()->isOnuse());


    //airplane lineup the runway;
    int lineupminute=1;
    for (int n1 = 0; n1 < lineupminute; ++n1) {
        EXPECT_TRUE(testsubject->getDestinateRunway()->getPlaneAtbegin()==testsubject);
        EXPECT_TRUE(testsubject->getPermission()==Airplane::FlyPermission);
        EXPECT_TRUE(testsubject->getDestinateRunway()->getCurrentairplane()==testsubject);
        EXPECT_TRUE(testsubject->getDestinateRunway()->isOnuse());
        simulator.simulate_Onetime();
    }


    //in this case, airplane can just leave without asking permission since permission is already gaved.
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Leaving);
    EXPECT_TRUE(testsubject->getDestinateRunway()->getPlaneAtbegin()==NULL);//airplane starts taking off.
    EXPECT_TRUE(testsubject->getDestinateRunway()->getCurrentairplane()==testsubject);
    EXPECT_TRUE(testsubject->getDestinateRunway()->isOnuse());













    //proceeding to leaving procedures.
    EXPECT_TRUE(testsubject->getStatus()==Airplane::Leaving);
    EXPECT_TRUE(testsubject->getDestinateRunway()->getCurrentairplane()==testsubject);
    EXPECT_TRUE(testsubject->getDestinateRunway()->isOnuse());


    //airplane takeoff
    Runway* destinaterunway=testsubject->getDestinateRunway();
    for (int i2 = 0; i2 <takeoffminute ; ++i2) {
        EXPECT_TRUE(testsubject->getDestinateRunway()->getCurrentairplane()==testsubject);
        EXPECT_TRUE(testsubject->getDestinateRunway()->isOnuse());
        simulator.simulate_Onetime();
    }

    EXPECT_TRUE(destinaterunway->getPlaneAtbegin()==NULL);
    EXPECT_TRUE(testsubject->getDestinateRunway()==NULL);

    //since falling==rising minute
    EXPECT_TRUE(testsubject->getHeight()==0);
    for (int k2 = 0; k2 <6 ; ++k2) {
        for (int j2 = 0; j2 <fallingminute ; ++j2) {
            simulator.simulate_Onetime();
        }
        EXPECT_TRUE(testsubject->getHeight()==(k2+1)*1000);
    }

    //plane left, it's higher than 5000
    EXPECT_TRUE(testsubject->getStatus()==Airplane::jobsdone);

    //end of test phew.
}



TEST_F(AirplaneDomeinTest,SimulationBuzy50003000Test) {
    //settings
    string filename = "../domeinTest/SimulationTest.xml";
    //endofsettings

    ofstream a;


    int subject1fallingminute=1;
    int subject2fallingminute=1;

    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject1 = new Airplane(Airplane::Approaching,"TestApproach_Subject_001","TAS001","TAS","airline","jet","large",1,100000,100000,simulator.getAirports()[0]);
    simulator.addAirplane(testsubject1);


    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject2 = new Airplane(Airplane::Approaching,"TestApproach_Subject_001","TAS001","TAS","private","jet","small",1,100000,100000,simulator.getAirports()[0]);
    simulator.addAirplane(testsubject2);


    //both airplane contact tower
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::empty);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::empty);

    //tower try react to one of them
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::tenThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::tenThousandPermission);

    //one of them receive messenge;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::fiveThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::tenThousandPermission);

    //reacting to the messenge;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::fiveThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::tenThousandPermission);

    for (int i = 0; i <5 ; ++i) {
        EXPECT_TRUE(testsubject1->getPermission()==Airplane::fiveThousandPermission);
        EXPECT_TRUE(testsubject2->getPermission()==Airplane::tenThousandPermission);
        for (int j = 0; j <subject1fallingminute ; ++j) {
            simulator.simulate_Onetime();
        }
        EXPECT_TRUE(testsubject1->getHeight()==10000-(i+1)*1000);
        EXPECT_TRUE(testsubject2->getHeight()==10000);
    }

    //tower sended further instruction to subject1, to let him fall;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::threeThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::tenThousandPermission);

    //subject1 reacts to tower, tower send further instruction to subject2.
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::threeThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::fiveThousandPermission);

    int counter=0;
    while(testsubject1->getHeight()!=3000){
        counter++;
        simulator.simulate_Onetime();
        if(counter%subject1fallingminute==0){
            EXPECT_TRUE(testsubject1->getHeight()==5000-counter/subject1fallingminute*1000);
        }
        if((counter-1)%subject1fallingminute==0){
            EXPECT_TRUE(testsubject2->getHeight()==10000-(counter-1)/subject2fallingminute*1000);
        }
    }



    //setup new cases for buzy3000
    //keep all runways on use.
    for (unsigned int k = 0; k <testsubject1->getDestination()->getRunways().size() ; ++k) {
        testsubject1->getDestination()->getRunways()[k]->setOnuse(true);
    }

    //tower trying to get a runway for subject one but it failed;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::threeThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::fiveThousandPermission);

    //fastforawrd
    while(testsubject2->getHeight()!=5000){
        simulator.simulate_Onetime();
    }

    //tower trying to get 3000meter for subject2 but it's buzy
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::threeThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::fiveThousandPermission);
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::threeThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::fiveThousandPermission);
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::threeThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::fiveThousandPermission);
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::threeThousandPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::fiveThousandPermission);
    //4 times for sure;


    //release all runways.
    for (unsigned int k = 0; k <testsubject1->getDestination()->getRunways().size() ; ++k) {
        testsubject1->getDestination()->getRunways()[k]->setOnuse(false);
    }

    //now tower should react to subject 1
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::LandingPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::fiveThousandPermission);

    //then subject two
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::LandingPermission);
    EXPECT_TRUE(testsubject2->getPermission()==Airplane::threeThousandPermission);
}

TEST_F(AirplaneDomeinTest,SimulationBotspreventieTest) {
    //settings
    string filename = "../domeinTest/SimulationTest.xml";
    //endofsettings

    ofstream a;



    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject1 = new Airplane(Airplane::Standing_at_gate, "TestApproach_Subject_001", "TAS001", "TAS", "airline", "jet", "large", 1, 10, 10, simulator.getAirports()[0]);
    simulator.addAirplane(testsubject1);

    testsubject1->setLocation(testsubject1->getDestination()->findFreeGates());
    testsubject1->setPermission(Airplane::TaxiingPermission);
    testsubject1->setDestinateRunway(testsubject1->getDestination()->getRunways()[testsubject1->getDestination()->getRunways().size()-1]);
    testsubject1->getDestination()->getTower().receiveSignal(testsubject1,Signaltower::LeavingtoRunway);
    testsubject1->getDestination()->getTower().sendSignal();
    testsubject1->getDestination()->getTower().timeRuns();
    testsubject1->getDestination()->getTower().sendSignal();
    //let tower release a instruction immidiately;
    testsubject1->setStatus(Airplane::Taxiing_to_runway);

    testsubject1->setLocation(testsubject1->getInstruction()[2]);//two is always the runway.

    //test subject sending signal to cross runway;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    //tower received signal
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    testsubject1->getInstruction()[2]->setCrossing(true);

    //test subject received none beacause runway is crossing;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);


    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);
    simulator.simulate_Onetime();

    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);
    simulator.simulate_Onetime();

    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    //3time for sure
    //release runway;
    testsubject1->getInstruction()[2]->setCrossing(false);
    //on the general test, its clear that the runway will be set on crossing true when it is crossing.
    //and on use true when its landing/takingoff.


    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::Cleared_to_crossPermission);


}


TEST_F(AirplaneDomeinTest,SimulationLineupTest) {
    //settings
    string filename = "../domeinTest/SimulationTest.xml";
    //endofsettings

    ofstream a;



    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject1 = new Airplane(Airplane::Standing_at_gate, "TestApproach_Subject_001", "TAS001", "TAS", "airline", "jet", "large", 1, 10, 10, simulator.getAirports()[0]);
    simulator.addAirplane(testsubject1);

    testsubject1->setLocation(testsubject1->getDestination()->findFreeGates());
    testsubject1->setPermission(Airplane::TaxiingPermission);
    testsubject1->setDestinateRunway(testsubject1->getDestination()->getRunways()[0]);
    testsubject1->getDestination()->getTower().receiveSignal(testsubject1,Signaltower::LeavingtoRunway);
    testsubject1->getDestination()->getTower().sendSignal();
    testsubject1->getDestination()->getTower().timeRuns();
    testsubject1->getDestination()->getTower().sendSignal();
    //let tower release a instruction immidiately;
    testsubject1->setStatus(Airplane::Taxiing_to_runway);

    testsubject1->setLocation(testsubject1->getInstruction()[2]);//two is always the runway,this case it's the destinated runway. beacause the first runway is always one with only one taxipoint.

    //test subject sending signal to line up;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    //tower received signal
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    //let the runway be crossing
    testsubject1->getInstruction()[2]->setCrossing(true);

    //then airplane should not be able to fly immidiately
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::LineupPermission);

    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::LineupPermission);

    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::LineupPermission);


    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::LineupPermission);

    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::LineupPermission);

    EXPECT_TRUE(testsubject1->getDestinateRunway()->getPlaneAtbegin()==testsubject1);
    //5times for lineup minute and test that it's consistent.
    testsubject1->getInstruction()[2]->setCrossing(false);

    EXPECT_TRUE(testsubject1->getDestination()->getTower().isDoingNothing());
    simulator.simulate_Onetime();//tower sees runway is free, contacting airplane.
    EXPECT_TRUE(!testsubject1->getDestination()->getTower().isDoingNothing());
    simulator.simulate_Onetime();//airplane gets contact.
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::FlyPermission);

}


TEST_F(AirplaneDomeinTest,SimulationLineupTest2) {
    //settings
    string filename = "../domeinTest/SimulationTest.xml";
    //endofsettings

    ofstream a;



    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject1 = new Airplane(Airplane::Standing_at_gate, "TestApproach_Subject_001", "TAS001", "TAS", "airline", "jet", "large", 1, 10, 10, simulator.getAirports()[0]);
    simulator.addAirplane(testsubject1);

    testsubject1->setLocation(testsubject1->getDestination()->findFreeGates());
    testsubject1->setPermission(Airplane::TaxiingPermission);
    testsubject1->setDestinateRunway(testsubject1->getDestination()->getRunways()[0]);
    testsubject1->getDestination()->getTower().receiveSignal(testsubject1,Signaltower::LeavingtoRunway);
    testsubject1->getDestination()->getTower().sendSignal();
    testsubject1->getDestination()->getTower().timeRuns();
    testsubject1->getDestination()->getTower().sendSignal();
    //let tower release a instruction immidiately;
    testsubject1->setStatus(Airplane::Taxiing_to_runway);

    testsubject1->setLocation(testsubject1->getInstruction()[2]);//two is always the runway,this case it's the destinated runway. beacause the first runway is always one with only one taxipoint.

    //test subject sending signal to line up;
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    //tower received signal
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    //let the runway be crossing
    testsubject1->getDestinateRunway()->setPlaneAtbegin(testsubject1);//occupy the slot.

    //then airplane should not be able to fly immidiately
    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);


    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);

    simulator.simulate_Onetime();
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::TaxiingPermission);


    EXPECT_TRUE(testsubject1->getDestinateRunway()->getPlaneAtbegin()==testsubject1);
    //5times for lineup minute and test that it's consistent.
    testsubject1->getDestinateRunway()->setPlaneAtbegin(NULL);//occupy the slot.

    EXPECT_TRUE(testsubject1->getDestination()->getTower().isDoingNothing());
    simulator.simulate_Onetime();//tower sees runway is free, contacting airplane.
    EXPECT_TRUE(!testsubject1->getDestination()->getTower().isDoingNothing());
    simulator.simulate_Onetime();//airplane gets contact.
    EXPECT_TRUE(testsubject1->getLocation()->isRunway());
    EXPECT_TRUE(testsubject1->getPermission()==Airplane::FlyPermission);
}

TEST_F(AirplaneDomeinTest,flightPlanImport){

    //settings
    string filename = "../domeinTest/flightPlan.xml";
    string des="LCY";
    int departure = 15;
    int arrival = 45;
    int interval = 1;
    //end of settings
    ofstream a;
    LoadAirport(filename.c_str(),a,simulator);
    Airplane* plane = simulator.getAirplanes().front();
    EXPECT_EQ(des,plane->getDes());
    EXPECT_EQ(departure,plane->getDeparture());
    EXPECT_EQ(arrival,plane->getArrival());
    EXPECT_EQ(interval,plane->getInterval());

}

TEST_F(AirplaneDomeinTest,flightPlanNotFound){

    //settings
    string filename = "../domeinTest/flightPlanNotFound.xml";
    string des="";
    int departure = 0;
    int arrival = 0;
    int interval = 0;

    //end of settings
    ofstream a;
    LoadAirport(filename.c_str(),a,simulator);
    Airplane* plane = simulator.getAirplanes().front();
    EXPECT_EQ(des,plane->getDes());
    EXPECT_EQ(departure,plane->getDeparture());
    EXPECT_EQ(arrival,plane->getArrival());
    EXPECT_EQ(interval,plane->getInterval());
}