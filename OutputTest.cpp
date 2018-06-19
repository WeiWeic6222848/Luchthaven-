//
// Created by tristan on 3/05/18.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "DesignByContract.h"

#include "Airportsim.h"
#include "Airplane.h"
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
        Airportsim sim;
        LoadAirport(filename.c_str(), a, sim);
        sim.Simulate();
        string happydayFilename = "../outputTest/happydayOutput/floormap/Juist_Floormap"+to_string(i)+".txt";
        string actualOutputFilename = "../output/floormap_state_airport["+sim.getAirports().front()->getIata()+"].txt";
        REQUIRE(fileExist(actualOutputFilename),"floormpap_state_airport.txt file does not exists");
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
    for (int i = 1; i <= 13; ++i) {
        Airportsim sim;
        string filename = "../outputTest/ActualData/happyday/input_test_"+to_string(i)+".xml";
        ofstream a;
        LoadAirport(filename.c_str(), a, sim);
        sim.Simulate();
        string happydayFilename = "../outputTest/happydayOutput/tower/Juist_Tower"+to_string(i)+".txt";
        string actualOutputFilename = "../output/"+sim.getAirports().front()->getIata()+"_Tower.txt";
        REQUIRE(fileExist(actualOutputFilename),"Tower.txt file does not exists");
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
TEST_F(AirplaneOutputTest,checkAirplaneOutput){
    for (int i = 1; i <= 13; ++i) {
        Airportsim sim;
        string filename = "../outputTest/ActualData/happyday/input_test_"+to_string(i)+".xml";
        ofstream a;
        LoadAirport(filename.c_str(), a, sim);
        sim.Simulate();
        for (unsigned int j = 0; j < sim.getAirplanes().size(); ++j) {
            Airplane* plane = sim.getAirplanes()[j];
            string happydayFilename = "../outputTest/happydayOutput/airplanes/input_file"+to_string(i)+"plane"+plane->getCallsign()+".txt";
            string actualOutputFilename = "../output/"+plane->getCallsign()+".txt";
            REQUIRE(fileExist(actualOutputFilename),"Plane.txt file does not exists");
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
}
TEST_F(AirplaneOutputTest,checkSettingsGrafficsImpression){
    for (int i = 1; i <= 13; ++i) {
        Airportsim sim;
        string filename = "../outputTest/ActualData/happyday/input_test_"+to_string(i)+".xml";
        ofstream a;
        LoadAirport(filename.c_str(), a, sim);
        sim.Simulate();
        string happydayFilename = "../outputTest/happydayOutput/settings/Juist_setting"+to_string(i)+".ini";
        string actualOutputFilename = "../output/settings_2D_["+sim.getAirports().front()->getIata()+"].ini";
        REQUIRE(fileExist(actualOutputFilename),"Settings.ini file does not exists");
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