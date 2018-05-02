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
#include "AirportsimImporter.h"


class AirportDomeinTest: public ::testing::Test{
protected:
    friend class Airportsim;

    Airportsim simulator;

    virtual void SetUp(){

    }

    virtual void TearDown(){

    }
};