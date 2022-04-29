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
        Address(String t,String str,int h,int apt=0): town(t), street(str), house(h), apartment(apt){};
        String& getStreet();
        String& getTown();
        int getHouse();
        int getApartment();
};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param a0 - Address, amit kiírunk
/// @return os
std::ostream& operator<<(std::ostream& os, const Address& a0);

#endif
