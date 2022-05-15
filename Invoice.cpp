/**
 * @file Invoice.cpp
 * @author Gutási Ádám
 * @brief Az Invoice osztályhoz tartozó tagfüggvények definíciói.
 * @date 2022-05-15
 * 
 * 
 */

#include "Invoice.h"


/**
 * @brief Fizetendő összeg lekérése.
 * 
 * @return double - fizetendő összeg.
 */
double Invoice::get_toBePaid() const {return toBePaid;}

/**
 * @brief Fogyasztás mennyiségének lekérdezése
 * 
 * @return int - fogyasztás mennyisége
 */
int Invoice::getConsumptionAmt() const{ return consumptionAmt;}

/**
 * @brief létrheozás dátumának lekérése.
 * 
 * @return Date& - dátum referencia
 */
Date& Invoice::getCreated(){return created;}

/**
 * @brief Fogyasztási bejelentés lekérése
 * 
 * @return Consumption_announcement& - fogyasztási bejelentés referenciája
 */
Consumption_announcement& Invoice::getCAnn(){return announcement;}

/**
 * @brief Egyenlőség operátor
 * 
 * @param rhs - rval számla
 * @return true , ha a két számla megegyezik
 * @return false , ha a két számla nem egyezik meg.
 */
bool Invoice::operator==(Invoice& rhs){
	return ((created==rhs.getCreated()) && (announcement==rhs.getCAnn()));
}

/**
 * @brief Fizetendő összeg beállítása
 * 
 * @param what - beállítandó összeg.
 */
void Invoice::set_toBePaid(double what){
    toBePaid=what;
}

/**
 * @brief stream operátor
 * 
 * @param os - stream
 * @param i - Számla
 * @return std::ostream& - stream
 */
std::ostream& operator<<(std::ostream& os, Invoice& i){
    os << i.get_toBePaid();
    return os;
}
