//
// Created by c6222848 on 3/17/18.
//
#include "iostream"
#include "gtest/gtest.h"
#include "Airportsim.h"

using namespace std;

class Airporttest: public ::testing::Test{
protected:
    Airportsim simulator;
public:
    Airporttest() : simulator(Airportsim("test.xml")) {}

protected:
    virtual void SetUp(){

    }

    virtual void TearDown(){

    }
};

TEST_F(Airporttest, Readingfiletest){
    EXPECT_TRUE(simulator.ProperInitialized());
}
TEST_F(Airporttest, AmountPlanesTest){
    EXPECT_TRUE(simulator.getAirplanes().size()==1);
}
TEST_F(Airporttest, AmountAirportsTest){
    EXPECT_TRUE(simulator.getAirports().size()==1);
}
TEST_F(Airporttest, NameAirportTest){
    EXPECT_TRUE(simulator.getAirports()[0]->getName()=="Antwerp International Airport");
}
TEST_F(Airporttest, AmountGatesTest){
    EXPECT_TRUE(simulator.getAirports()[0]->getGates().size()==10);
}
TEST_F(Airporttest, CallsignPlaneTest){
    EXPECT_TRUE(simulator.getAirplanes()[0]->getCallsign()=="Cessna 842");
}
TEST_F(Airporttest, NumberPlaneTest){
    EXPECT_TRUE(simulator.getAirplanes()[0]->getNumber()=="N11842");
}
TEST_F(Airporttest, IataAirportTest){
    EXPECT_TRUE(simulator.getAirports()[0]->getIata()=="ANR");
}
TEST_F(Airporttest, CallsignAirportTest){
    EXPECT_TRUE(simulator.getAirports()[0]->getCallsign()=="Antwerp Tower");
}
TEST_F(Airporttest, RunwayNameTest){
    EXPECT_TRUE(simulator.getAirports()[0]->getRunways()[0]->getName()=="11R");
}
TEST_F(Airporttest, ModelPlaneTest){
    EXPECT_TRUE(simulator.getAirplanes()[0]->getModel()=="Cessna 340");
}
TEST_F(Airporttest, StatusPlaneTest){
    EXPECT_TRUE(simulator.getAirplanes()[0]->getStatus()=="Approaching");
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}