//
// Created by c6222848 on 4/23/18.
//

#ifndef LUCHTHAVEN_TIME_H
#define LUCHTHAVEN_TIME_H

#include "iostream"
#include "DesignByContract.h"


class Time {
    int hour;
    int minute;


public:
    Time(int hour, int minute);

    friend std::ostream& operator<<(std::ostream& output,Time time);

    Time() {hour=12;minute=0;}

    Time operator++(int){
        int minute=Time::minute;
        int hour=Time::hour;
        minute++;
        if(minute==60){
            hour++;
            minute=0;
            if(hour==24){
                hour=0;
            }
        }
        return Time(hour,minute);
    };

    Time operator+(int a){

        int minute=Time::minute;
        int hour=Time::hour;
        minute+=a;
        while(minute>=60){
            hour++;
            minute-=60;
        }
        while(hour>=24){
            hour-=24;
        }
        return Time(hour,minute);
    }

    bool operator<(const Time &rhs) const;

    bool operator>(const Time &rhs) const;

    bool operator<=(const Time &rhs) const;

    bool operator>=(const Time &rhs) const;

    bool operator==(const Time &rhs) const;

    bool operator!=(const Time &rhs) const;

    int getHour() const;

    int getMinute() const;
};





#endif //LUCHTHAVEN_TIME_H
