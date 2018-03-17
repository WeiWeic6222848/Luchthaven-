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
    simulator.addsourcefile("test.xml");
    EXPECT_TRUE(simulator.ProperInitialized());
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}