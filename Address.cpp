/**
 * @file Address.cpp
 * @author Gutási Ádám
 * @brief Ez a fájl tartalmazza az Address osztály definíciót.
 * @date 2022-05-15
 * 
 * 
 */

#include "Address.h"
/**
 * @brief utca nevének lekérése
 * 
 * @return String& - String referenciájával tér vissza.
 */
String& Address::getStreet(){return street;}
/**
 * @brief város nevének lekérése
 * 
 * @return String& - String referenciájával tér vissza.
 */
String& Address::getTown(){return town;}; /*!< Város nevének lekérése *
/**
 * @brief házszám lekérése
 * 
 * @return int
 */
int Address::getHouse(){return house;}
/**
 * @brief Lakásszám lekérése
 * 
 * @return int 
 */
int Address::getApartment(){return apartment;};


/**
 * @brief Egyenlőség operátor
 * 
 * @param rhs - Cím rvalue
 * @return true , ha a két cím egyezik
 * @return false , ha a két cím nem egyezik meg.
 */
bool Address::operator==(Address& rhs){
    if(town==rhs.getTown() && street==rhs.getStreet() 
    && house==rhs.getHouse() && apartment==rhs.getApartment()){
        return true;
    }else{
        return false;
    }
}

