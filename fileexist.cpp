//
// Created by c6222848 on 3/17/18.
//




#include <fstream>
#include "string"
using namespace std;

/**
 *
 * @param filename filename to check wether or not exist
 * @return if the file exists
 */
bool fileExist(const string&filename){
    ifstream a(filename.c_str());
    return a.good();
}