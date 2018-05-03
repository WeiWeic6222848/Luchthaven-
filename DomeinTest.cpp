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


    //setting
    string filename="../domeinTest/Airplane.xml";

    string number="BAW466";
    string callsign="Speedbird 466";
    string model="Boeing 747";
    string type="airline";
    string engine="jet";
    string size="large";
    string status="Approaching";
    int passenger=10;
    int passengercapacity=10;
    int fuel=123;
    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(),a,simulator);
    Airplane* testsubject=simulator.findAirplane(number);


    EXPECT_TRUE(testsubject->getCurrentTime()==Time());
    if(status=="Approaching"){
        EXPECT_TRUE(testsubject->getLocation()==NULL);
        EXPECT_TRUE(testsubject->getHeight()==10000);
    }
    else if(status=="Standing at gate"){
        EXPECT_TRUE(testsubject->getLocation()->isGate());
        EXPECT_TRUE(testsubject->getHeight()==0);
    }

    EXPECT_TRUE(testsubject->getStatus()==status);
    EXPECT_TRUE(testsubject->getPermission()=="");
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
    EXPECT_TRUE(testsubject->getCheckProcedure()=="Just landed");
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


    //setting
    string filename = "../domeinTest/Airplane.xml";

    string number = "BAW466";
    string callsign = "Speedbird 466";
    string model = "Boeing 747";
    string type = "airline";
    string engine = "jet";
    string size = "large";
    string status = "Approaching";
    int passengercapacity = 10;
    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airplane *testsubject = simulator.findAirplane(number);

    EXPECT_TRUE(testsubject->getCurrentTime()==Time());

    testsubject->setStatus("Standing at gate");
    EXPECT_TRUE(testsubject->getStatus()=="Standing at gate");
    testsubject->setPermission("5000");
    EXPECT_TRUE(testsubject->getPermission()=="5000");
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
    Airport temp2("123","123","123",10,10);
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
    //setting
    string filename = "../domeinTest/Airport.xml";
    string name = "Antwerp International Airport";
    string iata = "ANR";
    string callsign = "Antwerp Tower";
    unsigned int gates = 10;
    unsigned int runways = 0;
    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airport *testsubject = simulator.getAirports()[0];

    EXPECT_TRUE(testsubject->getName()==name);
    EXPECT_TRUE(testsubject->getIata()==iata);
    EXPECT_TRUE(testsubject->getCallsign()==callsign);
    EXPECT_TRUE(testsubject->getGates().size()==gates);
    EXPECT_TRUE(testsubject->getRunways().size()==runways);
}
TEST_F(AirplaneDomeinTest,settersAirport) {
    //setting
    string filename = "../domeinTest/Airport.xml";
    string name = "Antwerp International Airport";
    string iata = "ANR";
    string callsign = "Antwerp Tower";

    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    Airport *testsubject = simulator.getAirports()[0];
    testsubject->addPassenger(10)
    EXPECT_TRUE(testsubject->getPassengers()==10);
}
TEST_F(AirplaneDomeinTest,gettersRunway) {
    //setting
    string filename = "../domeinTest/Runway.xml";
    string name = "11R";
    string airport = "ANR";
    Runwaytype type = grass;
    int length = 1010;
    string taxipoint = "Alpha";
    int airplanesqueing=0;
    Airplane* plane=NULL;
    //endofsetting

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


}
TEST_F(AirplaneDomeinTest,settersRunway){
    //setting
    string filename = "../domeinTest/Runway.xml";
    string name = "11R";
    string airport = "ANR";
    string taxipoint = "Alpha";

    Airplane* plane=NULL;

    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    plane = simulator.getAirplanes()[0];
    string callsign = plane->getCallsign();
    Runway *testsubject = simulator.getAirports()[0]->getRunways()[0];

    EXPECT_FALSE(testsubject->isOnuse());
    testsubject->setOnuse(true);
    EXPECT_TRUE(testsubject->isOnuse());

    testsubject->setCurrentairplane(plane);
    EXPECT_TRUE(testsubject->getCurrentairplane()->getCallsign()==callsign);

    testsubject->setPlaneAtbegin(plane)
    EXPECT_TRUE(testsubject->getPlaneAtbegin()->getCallsign()==callsign);

    testsubject->setPlaneAtEnd(plane)
    EXPECT_TRUE(testsubject->getPlaneAtEnd()->getCallsign()==callsign);

    EXPECT_FALSE(testsubject->isTaxipoint());

    EXPECT_FALSE(testsubject->isCrossing());
    testsubject->setCrossing(true)
    EXPECT_TRUE(testsubject->isCrossing());

}
TEST_F(AirplaneDomeinTest, testingGate){
    //setting
    string filename = "../domeinTest/Airport.xml";
    unsigned int gates = 10;
    Airplane* plane=NULL;
    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(), a, simulator);
    vector<Gate*> testsubject = simulator.getAirports()[0]->getGates();

    EXPECT_TRUE(testsubject.size()==gates);
    for (unsigned int i = 0; i < testsubject.size(); ++i) {
        EXPECT_FALSE(testsubject[i]->isOnuse());
        EXPECT_FALSE(testsubject[i]->isTaxipoint());
        EXPECT_TRUE(testsubject[i]->isGate());
        EXPECT_TRUE(testsubject[i]->ProperInitialized());
        EXPECT_TRUE(testsubject[i]->getCurrentPlane()==plane);
    }
}

    TEST_F(AirplaneDomeinTest,invalidInput){

    /*
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
    Airplane* testsubject=simulator.findAirplane(number);


    EXPECT_NO_FATAL_FAILURE(testsubject->setStatus("qb"));
    EXPECT_NO_FATAL_FAILURE(testsubject->setPassenger(passengercapacity+1));
    EXPECT_NO_FATAL_FAILURE(testsubject->setFuel(fuel+1));
    EXPECT_NO_FATAL_FAILURE(testsubject->setFuelCapacity(fuel-1));
     */
}

TEST_F(AirplaneDomeinTest,){


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
    //int passengercapacity=10;
    //int fuel=123;
    //endofsetting

    ofstream a;

    LoadAirport(filename.c_str(),a,simulator);
    //Airplane* testsubject=simulator.findAirplane(number);

    /*
    EXPECT_NO_FATAL_FAILURE(testsubject->setStatus("qb"));
    EXPECT_NO_FATAL_FAILURE(testsubject->setPassenger(passengercapacity+1));
    EXPECT_NO_FATAL_FAILURE(testsubject->setFuel(fuel+1));
    EXPECT_NO_FATAL_FAILURE(testsubject->setFuelCapacity(fuel-1));
     */
}