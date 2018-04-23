//
// Created by c6222848 on 4/23/18.
//

#include "Time.h"
#include "string"
using namespace std;

string to_string(int);


std::ostream& operator<<(std::ostream& output,Time& time){
    string hour=to_string(time.hour);
    string minute=to_string(time.minute);
    while(hour.size()<2){
        hour.insert(0,"0");
    }
    while(minute.size()<2){
        minute.insert(0,"0");
    }
    output<<" "<<hour<<":"<<minute<<" ";
    return output;
}