//
// Created by tristan on 3/05/18.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "DesignByContract.h"

#include "Airportsim.h"
#include "AirportUtils.h"
#include "output_system.h"


class AirplaneOutputTest: public ::testing::Test{
protected:
    friend class Airport;

    Airportsim simulator;

    virtual void SetUp(){

    }

    virtual void TearDown(){

    }
};
TEST_F(AirplaneOutputTest, checkInfo){
    //settings
    //endofsettings
    for (int i = 1; i <= 13; ++i) {
        Airportsim simulator;
        string filename = "../outputTest/ActualData/happyday/input_test_"+to_string(i)+".xml";
        ofstream a;
        LoadAirport(filename.c_str(), a, simulator);
        output_system::writeToFile(simulator);
        string happydayFilename = "../outputTest/happydayOutput/info/Juist_Info"+to_string(i)+".txt";
        string actualOutputFilename = "../output/Info.txt";
        REQUIRE(fileExist(actualOutputFilename),"info.txt file does not exists");
        /*
        ofstream write;
        ifstream actual;
        string temp;
        actual.open(actualOutputFilename.c_str());
        write.open(happydayFilename.c_str(),ios::out);
        while(getline(actual,temp)){
            write<<temp<<endl;
        }
         */
        REQUIRE(fileExist(happydayFilename.c_str()),"happyday output not found");


        EXPECT_TRUE(FileCompare(happydayFilename,actualOutputFilename));

    }
}

TEST_F(AirplaneOutputTest, checkFloormap){
    for (int i = 1; i <= 13; ++i) {
        string filename = "../outputTest/ActualData/happyday/input_test_"+to_string(i)+".xml";
        ofstream a;
        LoadAirport(filename.c_str(), a, simulator);
        simulator.Simulate();
        string happydayFilename = "../outputTest/happydayOutput/floormap/Juist_Floormap"+to_string(i)+".txt";
        string actualOutputFilename = "../output/floormap_state_airport["+simulator.getAirports().front()->getIata()+"].txt";
        REQUIRE(fileExist(actualOutputFilename),"info.txt file does not exists");
        /*
        ofstream write;
        ifstream actual;
        string temp;
        actual.open(actualOutputFilename.c_str());
        write.open(happydayFilename.c_str(),ios::out);
        while(getline(actual,temp)){
            write<<temp<<endl;
        }
         */
        REQUIRE(fileExist(happydayFilename.c_str()),"happyday output not found");


        EXPECT_TRUE(FileCompare(happydayFilename,actualOutputFilename));

    }
}
TEST_F(AirplaneOutputTest, checkTower){

}
TEST_F(AirplaneOutputTest, checkCessna849){

}