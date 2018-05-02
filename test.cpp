//
// Created by c6222848 on 3/17/18.
//
#include <fstream>
#include "gtest/gtest.h"
#include "Airportsim.h"
#include "AirportUtils.h"

int stoi(const string& string);



using namespace std;

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



    string filename;
    ofstream a;
/*
    for (int i = 1; i <= 5; ++i) {

        filename="../inputTest/Partial_import/Airplane/AlreadyExist/input_test_"+to_string(i)+".xml";
        a.open(filename.c_str());
        a.close();

        filename="../inputTest/Partial_import/Airplane/Fuel/input_test_"+to_string(i)+".xml";
        a.open(filename.c_str());
        a.close();

        filename="../inputTest/Partial_import/Airplane/Passenger/input_test_"+to_string(i)+".xml";
        a.open(filename.c_str());
        a.close();

        filename="../inputTest/Partial_import/Airplane/PassengerCapacity/input_test_"+to_string(i)+".xml";

        a.open(filename.c_str());
        a.close();

        filename="../inputTest/Partial_import/Runway/Taxiroute/input_test_"+to_string(i)+".xml";

        a.open(filename.c_str());
        a.close();
        filename="../inputTest/Partial_import/Runway/Name/input_test_"+to_string(i)+".xml";

        a.open(filename.c_str());
        a.close();
    }*/

    return RUN_ALL_TESTS();
}