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
    friend std::ostream& operator<<(std::ostream& output,Time& time);

    Time() {hour=12;minute=0;}

    Time& operator++(int){
        minute++;
        if(minute==60){
            hour++;
            minute=0;
            if(hour==24){
                hour=0;
            }
        }
        return *this;
    };
};





#endif //LUCHTHAVEN_TIME_H
