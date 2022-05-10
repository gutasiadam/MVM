#ifndef ADDRESS_HEADER
#define ADDRESS_HEADER
/**
 * \file Address.h
 *
 * Ez a fájl tartalmazza az Address osztály deklarációját és inline függvényeit.
 */

#include <iostream>
#include "String.h"

class Address{
    private:
        String town;
        String street;
        int house;
        int apartment;
    public:
        Address() {};
        Address(String t, String str,int h,int apt=0): town(t), street(str), house(h), apartment(apt){};
        String& getStreet(){return street;};
        String& getTown(){return town;};
        int getHouse(){return house;};
        int getApartment(){return apartment;};

        bool operator==(Address& rhs){
            if(town==rhs.getTown() && street==rhs.getStreet() 
            && house==rhs.getHouse() && apartment==rhs.getApartment()){
                return true;
            }else{
                return false;
            }
        };
};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param a0 - Address, amit kiírunk
/// @return os
std::ostream& operator<<(std::ostream& os, const Address& a0);
#endif
