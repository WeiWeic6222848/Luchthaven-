//
// Created by c6222848 on 4/23/18.
//

#include "Time.h"
#include "string"
using namespace std;

string to_string(int);


std::ostream& operator<<(std::ostream& output,Time time){
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

bool Time::operator==(const Time &rhs) const {
    return hour == rhs.hour &&
           minute == rhs.minute;
}

bool Time::operator!=(const Time &rhs) const {
    return !(rhs == *this);
}

bool Time::operator<(const Time &rhs) const {
    if (hour < rhs.hour)
        return true;
    if (rhs.hour < hour)
        return false;
    return minute < rhs.minute;
}

bool Time::operator>(const Time &rhs) const {
    return rhs < *this;
}

bool Time::operator<=(const Time &rhs) const {
    return !(rhs < *this);
}

bool Time::operator>=(const Time &rhs) const {
    return !(*this < rhs);
}

Time::Time(int hour, int minute) : hour(hour), minute(minute) {}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}
