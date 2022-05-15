#ifndef DATE_H
#define DATE_H
/**
 * @file Date.h
 * @author Gutási Ádám
 * @brief A dátum osztály deklarációit tartalmazó fájl
 * @date 2022-05-15
 */

#include <iostream>

class Date{
    private:
        unsigned int year; /*!< A tárolandó év */
        unsigned int month; /*!< A tárolandó hónap */
        unsigned int day; /*!< A tárolandó nap */
    public:
        friend std::ostream& operator<<(std::ostream& os, Date& d); /*!< Stream operator */
        Date() {}; /*!< Default konstruktor */
        Date(unsigned int y,unsigned int m, unsigned int d): year(y), month(m), day(d){};
        
        /**
         * @brief A dátumban tárolt év visszaadása.
         * 
         * @return unsigned int 
         */
        unsigned int getYear(){return year;};

        /**
         * @brief A dátumban tárolt hónap visszaadása.
         * 
         * @return unsigned int 
         */
        unsigned int getMonth(){return month;};

        /**
         * @brief A dátumban tárolt nap visszaadása.
         * 
         * @return unsigned int 
         */
        unsigned int getDay(){return day;};

        /**
         * @brief Két dátum közti egyenlőséget vizsgáló operator.
         * 
         * @param rhs  - Dátum típusú objektum
         * @return true , ha a két dátum egyezik
         * @return false , ha a két dátum enm egyezik.
         */
        inline bool operator==(Date& rhs){
            if(year==rhs.getYear() && month==rhs.getMonth() && day==rhs.getDay()){
                return true;
            } 
            return false;
        }

        /**
         * @brief Megállapítja, hogy a dátum kisebb-e az rvaluenál.
         * 
         * @param rhs  - Dátum típusú objektum
         * @return true , ha lvalue kisebb, mint rvalue.
         * @return false , ha lvalue nagyobb, mint rvalue.
         */
        inline bool operator<(Date& rhs){
            if((year<rhs.getYear()) || ((year==rhs.getYear() && (month<rhs.getMonth()))) 
            || ((year==rhs.getYear() && (month==rhs.getMonth()) && (day<rhs.getDay())))){
                return true;
            }else{
                return false;
            }
        }
        inline bool operator<=(Date& rhs){return (operator<(rhs) || operator==(rhs));}

        /**
         * @brief Megállapítja, hogy a dátum nagyobb-e az rvaluenál.
         * 
         * @param rhs  - Dátum típusú objektum
         * @return true , ha lvalue nagyobb, mint rvalue.
         * @return false , ha lvalue kisebb, mint rvalue.
         */
        inline bool operator>(Date& rhs){
            if((year>rhs.getYear()) || ((year==rhs.getYear() && (month>rhs.getMonth()))) 
            || ((year==rhs.getYear() && (month==rhs.getMonth()) && (day>rhs.getDay())))){
                return true;
            }else{
                return false;
            }
        }

        /**
         * @brief Megállapítja, hogy a dátum nagyobb VAGY egyenlő-e az rvaluenál.
         * 
         * @param rhs - Dátum típusú objektum
         * @return true , ha lvalue nagyobb VAGY egyenlő az rvalueval.
         * @return false , ha lvalue kisebb, VAGY egyenlő az rvalueval.
         */
        inline bool operator>=(Date& rhs){return (operator>(rhs) || operator==(rhs));}

        
};

/**
 * @brief Kiír az ostream-re
 * 
 * @param os - ostream objektum
 * @param d - kiírandó dátum.
 * @return std::ostream& 
 */
inline std::ostream& operator<<(std::ostream& os, Date& d){
    os << d.getYear() << "." << d.getMonth() << "." << d.getDay();
    return os;
}

#endif
