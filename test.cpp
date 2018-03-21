//
// Created by c6222848 on 3/17/18.
//
#include <fstream>
#include "iostream"
#include "gtest/gtest.h"
#include "Airportsim.h"
#include "output_system.h"
#include "algorithm"
#include "DesignByContract.h"

int stoi(const string& string);

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
    ifstream leftFile, rightFile;
    char leftRead, rightRead;
    bool result;

    // Open the two files.
    leftFile.open(leftFileName.c_str());
    if (!leftFile.is_open()) {
        return false;
    };
    rightFile.open(rightFileName.c_str());
    if (!rightFile.is_open()) {
        leftFile.close();
        return false;
    };

    result = true; // files exist and are open; assume equality unless a counterexamples shows up.
    while (result && leftFile.good() && rightFile.good()) {
        leftFile.get(leftRead);
        rightFile.get(rightRead);
        result = (leftRead == rightRead);
    };
    if (result) {
        // last read was still equal; are we at the end of both files ?
        result = (!leftFile.good()) && (!rightFile.good());
    };

    leftFile.close();
    rightFile.close();
    return result;
}

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
TEST_F(Airporttest, Outputtest){
    Airplane* a=simulator.getAirplanes()[0];
    Airport* b=simulator.getAirports()[0];
    simulator.landing(*a,*b);
    simulator.AirplaneAtGate(*a,*b);
    simulator.takingOff(*a,*b);
    output_system op;
    op.writeToFile(simulator);
    EXPECT_TRUE(FileCompare("../output/Cessna 842_AtGate.txt","../testoutput/Juist_Cessna 842_AtGate.txt"));
    EXPECT_TRUE(FileCompare("../output/Cessna 842_Landing.txt","../testoutput/Juist_Cessna 842_Landing.txt"));
    EXPECT_TRUE(FileCompare("../output/Cessna 842_TakingOff.txt","../testoutput/Juist_Cessna 842_TakingOff.txt"));
    EXPECT_TRUE(FileCompare("../output/Info.txt","../testoutput/Juist_Info.txt"));
}
TEST_F(Airporttest, dyingtest){
    EXPECT_DEATH(simulator.getAirports()[0]->parkAirplane(100,simulator.getAirplanes()[0]),"");
    EXPECT_DEATH(simulator.takingOff(*simulator.getAirplanes()[0],*simulator.getAirports()[0]),"");
}

TEST_F(Airporttest, airplaneclassgeneraltest){
    EXPECT_TRUE(simulator.getAirplanes()[0]->ProperInitialized());
    simulator.getAirplanes()[0]->setStatus("Standing at Gate");
    EXPECT_TRUE(simulator.getAirplanes()[0]->getStatus()=="Standing at Gate");
    simulator.getAirplanes()[0]->setStatus("Approaching");
    EXPECT_TRUE(simulator.getAirplanes()[0]->getStatus()=="Approaching");
    //other states yet to be defined
}

TEST_F(Airporttest, airportclassgeneraltest){
    EXPECT_TRUE(simulator.getAirports()[0]->ProperInitialized());
    simulator.getAirplanes()[0]->setStatus("Standing at Gate");
    Runway* i=new Runway("abc",simulator.getAirports()[0]);
    simulator.getAirports()[0]->addrunway(i);
    EXPECT_TRUE(find(simulator.getAirports()[0]->getRunways().begin(),simulator.getAirports()[0]->getRunways().end(),i)!=simulator.getAirports()[0]->getRunways().end());
    simulator.getAirplanes()[0]->setStatus("Approaching");
    EXPECT_TRUE(simulator.getAirplanes()[0]->getStatus()=="Approaching");
    EXPECT_TRUE(simulator.getAirports()[0]->findfreegates()==1);
    EXPECT_TRUE(simulator.getAirports()[0]->findfreerunway()==simulator.getAirports()[0]->getRunways()[0]);
    simulator.getAirports()[0]->parkAirplane(1,simulator.getAirplanes()[0]);
    EXPECT_TRUE(simulator.getAirports()[0]->getGateFromAirplane(simulator.getAirplanes()[0])==1);
    simulator.getAirports()[0]->freeGate(1);
    EXPECT_TRUE(simulator.getAirports()[0]->getGateFromAirplane(simulator.getAirplanes()[0])==-1);
    EXPECT_TRUE(simulator.getAirports()[0]->getGates().begin().operator*().second==NULL);
    //other states yet to be defined
}


TEST(Stoi_general_Test,general){
    EXPECT_TRUE(stoi("5")==5);
    EXPECT_TRUE(stoi("500")==500);
    EXPECT_FALSE(stoi("55822558888")==55822558888);//overflow
    EXPECT_TRUE(stoi("123456789")==123456789);
}

TEST(Stoi_dying_Test,dying){
    EXPECT_ANY_THROW(stoi("a"));
    EXPECT_ANY_THROW(stoi(""));
    EXPECT_ANY_THROW(stoi("q1aa"));
    EXPECT_ANY_THROW(stoi("1238855a"));
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}