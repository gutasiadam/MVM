#ifndef DATE_H
#define DATE_H
/**
 * \file Date.h
 *
 * Ez a fájl tartalmazza a Date osztály deklarációját és inline függvényeit.
 */

#include <iostream>

class Date{
    private:
        int year;
        int month;
        int day;
    public:
        friend std::ostream& operator<<(std::ostream& os, Date& d);
        Date() {};
        Date(int y,int m, int d): year(y), month(m), day(d){};
        int getYear(){return year;};
        int getMonth(){return month;};
        int getDay(){return day;};

        bool operator==(Date& rhs){
            if(year==rhs.getYear() && month==rhs.getMonth() && day==rhs.getDay()){
                return true;
            } 
            return false;
        }

        bool operator<(Date& rhs){
            if((year<rhs.getYear()) || ((year==rhs.getYear() && (month<rhs.getMonth()))) 
            || ((year==rhs.getYear() && (month==rhs.getMonth()) && (day<rhs.getDay())))){
                return true;
            }else{
                return false;
            }
        }
        bool operator>(Date& rhs){
            if((year>rhs.getYear()) || ((year==rhs.getYear() && (month>rhs.getMonth()))) 
            || ((year==rhs.getYear() && (month==rhs.getMonth()) && (day>rhs.getDay())))){
                return true;
            }else{
                return false;
            }
        }
};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param d - dátum, amit kiírunk
/// @return os
inline std::ostream& operator<<(std::ostream& os, Date& d){
    os << d.getYear() << "." << d.getMonth() << "." << d.getDay();
    return os;
}

#endif
