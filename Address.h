#ifndef ADDRESS_HEADER
#define ADDRESS_HEADER
/**
 * @file Address.h
 * @author Gutási Ádám
 * @brief Ez a fájl tartalmazza az Address osztály deklarációját és inline függvényeit.
 * @date 2022-05-15
 * 
 */
#include <iostream>
#include "String.h"

class Address{
    private:
        String town; /*!< Város */
        /**
         * @brief Utcanév
         * 
         * \warning Csak az utca nevét tárolja el, típusát nem, mert nem kell a nyilvántartásba.
         * 
         * Így például az Almafa utca csak Almafa a rendszerben.
         */
        String street; 

        int house; /*!< Házszám */
        int apartment; /*!< Lakásszám - 1 akkor is, ha egy egylakásos házról van szó. */
    public:
        Address() {};
        Address(String t, String str,int h,int apt=1): town(t), street(str), house(h), apartment(apt){};
        
        String& getStreet(); /*!< Utca nevének lekérése */
        String& getTown(); /*!< Város nevének lekérése */
        int getHouse(); /*!< Házszám lekérése */
        int getApartment(); /*!< Lakásszám lekérése */

        bool operator==(Address& rhs); /*!< Egyenlőség operátor */
};

#endif
