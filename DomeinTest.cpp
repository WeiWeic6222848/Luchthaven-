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

TEST_F(AirplaneDomeinTest,Happyday){


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


TEST_F(AirplaneDomeinTest,InvalidInput){


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