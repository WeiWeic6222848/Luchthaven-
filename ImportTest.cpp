//
// Created by c6222848 on 4/3/18.
//
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "DesignByContract.h"

#include "Airportsim.h"
#include "AirportUtils.h"
#include "AirportsimImporter.h"

class AirportImportTest: public ::testing::Test{
protected:
    friend class Airportsim;

    Airportsim simulator;

    virtual void SetUp(){

    }

    virtual void TearDown(){

    }
};


/**
 * input happydayfiles;
 */
TEST_F(AirportImportTest, InputHappyDay) {
    REQUIRE(DirectoryExists("../inputTest/Happyday"),"Happy day folder must exist");

    //settings
    int numberOfFiles=13;
    string expectoutputfilename="../inputTest/Happyday/expect_output.txt";
    string outputfilename="../inputTest/Happyday/output.txt";
    string inputfilenameprefix="../inputTest/Happyday/input_test_";
    string inputfilenamepostfix=".xml";
    //end of settings

    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;

    for (int i = 1; i <= numberOfFiles; ++i) {
        string filename=inputfilenameprefix+to_string(i)+=inputfilenamepostfix;
        expectoutput.open(expectoutputfilename.c_str());
        //expectoutput<<filename+" read no error"<<endl;
        outputfile.open(outputfilename.c_str());
        Airportsim testsim;//reinitialize the airportsim everytime;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==Success);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportRunwayLength) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Length"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Runway/Length/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Runway/Length/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Runway/Length/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Runway has a length which is not an integer, skipping this element"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}

TEST_F(AirportImportTest,InputPartialImportRunwayName) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/EmptyFields"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=4;
    string expectoutputfilename="../inputTest/Partial_import/Runway/EmptyFields/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Runway/EmptyFields/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Runway/EmptyFields/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Runway has one or more empty fields!"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}

TEST_F(AirportImportTest,InputPartialImportRunwayAlreadyExist) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/AlreadyExist"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Runway/AlreadyExist/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Runway/AlreadyExist/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Runway/AlreadyExist/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"runway is added on a earlier source, skipping"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportRunwayType) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Type"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Runway/Type/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Runway/Type/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Runway/Type/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Runway type is wrong"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportRunwayTaxiroute) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Taxiroute"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Runway/Taxiroute/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Runway/Taxiroute/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Runway/Taxiroute/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"unable to read Taxiroute"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportAirportAlreadyExist) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airport/AlreadyExist"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airport/AlreadyExist/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airport/AlreadyExist/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airport/AlreadyExist/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"airport is added on a earlier source, skipping"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}

TEST_F(AirportImportTest,InputPartialImportAirplaneEmptyField) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/EmptyField"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/EmptyField/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/EmptyField/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/EmptyField/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airplane has one or more empty fields!"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportAirplaneStatus) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/Status"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/Status/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/Status/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/Status/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airplane status is not correct"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportAirplaneWrongCombination) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/Wrong_Combination"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/Wrong_Combination/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/Wrong_Combination/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/Wrong_Combination/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airplane with has a invalid combination of engine, size and type, check specification for more information"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}

TEST_F(AirportImportTest,InputPartialImportAirplaneAlreadyExist) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/AlreadyExist"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/AlreadyExist/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/AlreadyExist/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/AlreadyExist/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"airplane is added on a earlier source, skipping"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportAirplanePassenger) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/Passenger"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/Passenger/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/Passenger/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/Passenger/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airplane has a passenger attribute which isn't a interger or is an negative number"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportAirplaneFuel) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/Fuel"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/Fuel/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/Fuel/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/Fuel/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airplane has a fuel attribute which isn't a interger"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportAirplanePassengerCapacity) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/PassengerCapacity"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/PassengerCapacity/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/PassengerCapacity/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/PassengerCapacity/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airplane has a passengercapacity attribute which isn't a interger or is an negative number"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputPartialImportAirplaneTooMuchPassenger) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Airplane/too_much_passenger"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=3;
    string expectoutputfilename="../inputTest/Partial_import/Airplane/too_much_passenger/expect_output.txt";
    string outputfilename="../inputTest/Partial_import/Airplane/too_much_passenger/output.txt";
    string inputfilenameprefix="../inputTest/Partial_import/Airplane/too_much_passenger/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airplane has more passenger than it's capacity."<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==PartialImport);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputImportAbortedAirportEmptyField) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Import_aboarted/Airport_EmptyField"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Import_aboarted/Airport_EmptyField/expect_output.txt";
    string outputfilename="../inputTest/Import_aboarted/Airport_EmptyField/output.txt";
    string inputfilenameprefix="../inputTest/Import_aboarted/Airport_EmptyField/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airport contains one or more emptyfields"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==ImportAborted);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputImportAbortedAirportMissing) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Import_aboarted/Airport_missing"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=2;
    string expectoutputfilename="../inputTest/Import_aboarted/Airport_missing/expect_output.txt";
    string outputfilename="../inputTest/Import_aboarted/Airport_missing/output.txt";
    string inputfilenameprefix="../inputTest/Import_aboarted/Airport_missing/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"this xml doesn't contain any airport!"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==ImportAborted);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputImportAbortedAirportGate) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Import_aboarted/Invalid_Gate"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Import_aboarted/Invalid_Gate/expect_output.txt";
    string outputfilename="../inputTest/Import_aboarted/Invalid_Gate/output.txt";
    string inputfilenameprefix="../inputTest/Import_aboarted/Invalid_Gate/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<< "Airport has a number of gate which isn't a integer"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==ImportAborted);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputImportAbortedAirportPassenger) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Import_aboarted/Invalid_Passenger"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=5;
    string expectoutputfilename="../inputTest/Import_aboarted/Invalid_Passenger/expect_output.txt";
    string outputfilename="../inputTest/Import_aboarted/Invalid_Passenger/output.txt";
    string inputfilenameprefix="../inputTest/Import_aboarted/Invalid_Passenger/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput << "Airport has a passenger attribute which isn't a interger" << endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==ImportAborted);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}

TEST_F(AirportImportTest,InputImportAbortedAirportNoRunway) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Import_aboarted/No_runway"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=3;
    string expectoutputfilename="../inputTest/Import_aboarted/No_runway/expect_output.txt";
    string outputfilename="../inputTest/Import_aboarted/No_runway/output.txt";
    string inputfilenameprefix="../inputTest/Import_aboarted/No_runway/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"Airport has no runway or a wrong amount of runway."<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==ImportAborted);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


TEST_F(AirportImportTest,InputImportAbortedAirportTooMuchAirplane) {
    //only test for one airplane duplicate in the xml.
    REQUIRE(DirectoryExists("../inputTest/Import_aboarted/Too_much_airplane"),"Happy day folder must exist");
//settings
    int numberOfFilesLength=3;
    string expectoutputfilename="../inputTest/Import_aboarted/Too_much_airplane/expect_output.txt";
    string outputfilename="../inputTest/Import_aboarted/Too_much_airplane/output.txt";
    string inputfilenameprefix="../inputTest/Import_aboarted/Too_much_airplane/input_test_";
    string inputfilenamepostfix=".xml";
//end of settings


    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;


    for (int j = 1; j <= numberOfFilesLength; ++j) {
        Airportsim testsim;
        outputfile.open(outputfilename.c_str());
        expectoutput.open(expectoutputfilename.c_str());

        expectoutput<<"airport has more airplanes at gates than it's gate"<<endl;

        string filename=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
        importResult=LoadAirport(filename.c_str(),outputfile,testsim);
        EXPECT_TRUE(importResult==ImportAborted);
        EXPECT_TRUE(FileCompare(expectoutputfilename,outputfilename));
        expectoutput.close();
        outputfile.close();
    }
}


/*
TEST_F(AirportImportTest, InputPartialImportRunway) {
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Length"),"Happy day folder must exist");
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Airport"),"Happy day folder must exist");
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Taxiroute"),"Happy day folder must exist");
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Name"),"Happy day folder must exist");
    REQUIRE(DirectoryExists("../inputTest/Partial_import/Runway/Type"),"Happy day folder must exist");

    //settings
    int numberOfFilesLength=5;
    int numberOfFilesAirport=5;
    int numberOfFilesTaxiroute=5;
    int numberOfFilesName=5;
    int numberOfFilesType=5;


    vector<string> testlist;
    vector<int> testFilesLength;
    testlist.push_back("Length/");
    testlist.push_back("Name/");

    //testlist.push_back("Airport/");
    //testlist.push_back("Taxiroute/");
    //testlist.push_back("Type/");
    testFilesLength.push_back(numberOfFilesLength);
    testFilesLength.push_back(numberOfFilesName);
    testFilesLength.push_back(numberOfFilesAirport);
    testFilesLength.push_back(numberOfFilesTaxiroute);
    testFilesLength.push_back(numberOfFilesType);

    string expectoutputdirectory="../inputTest/Partial_import/Runway/";
    string expectoutputfilename="expect_output.txt";
    string outputfilename="output.txt";
    string inputfilenameprefix="input_test_";
    string inputfilenamepostfix=".xml";
    //end of settings

    ofstream outputfile;
    Esucces importResult;
    ofstream expectoutput;

    for (unsigned int i = 0; i <testlist.size() ; ++i) {
        for (int j = 1; j < testFilesLength[i]; ++j) {
            Airportsim testsim;
            outputfile.open((expectoutputdirectory+testlist[i]+=outputfilename).c_str());
            expectoutput.open((expectoutputdirectory+testlist[i]+=expectoutputfilename).c_str());
            if(testlist[i]=="Length/"){
                expectoutput<<"Runway has a length which is not an integer, skipping this element"<<endl;
            }
            else if(testlist[i]=="Airport/"){
                expectoutput<<"cannot find airport for the runway"<<endl;
            }
            else if(testlist[i]=="Taxiroute/"){
                expectoutput<<"unable to read Taxiroute"<<endl;
            }
            else if(testlist[i]=="Name/"){
                expectoutput<<"Runway has an empty name!"<<endl;
            }
            else if(testlist[i]=="Type/"){
                expectoutput<<"Runway type is wrong"<<endl;
            }
            string filename=expectoutputdirectory+testlist[i]+=inputfilenameprefix+to_string(j)+=inputfilenamepostfix;
            importResult=LoadAirport(filename.c_str(),outputfile,testsim);
            EXPECT_TRUE(importResult==PartialImport);
            EXPECT_TRUE(FileCompare((expectoutputdirectory+testlist[i]+=outputfilename),(expectoutputdirectory+testlist[i]+=expectoutputfilename)));
            expectoutput.close();
            outputfile.close();
        }
    }
}*/
