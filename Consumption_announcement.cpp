/**
 * @file Consumption_announcement.cpp
 * @author Gutási Ádám
 * @brief Consumption_announcement osztály tagfüggvényeinek definíiót tartalmazó fájl.
 * @date 2022-05-15
 * 
 */
#include "Consumption_announcement.h"

/**
 * @brief Bejelentés dátumának lekérése
 * 
 * @return Date& - dátum referenciával tér vissza.
 */
Date& Consumption_announcement::getDate(){return date;}

/**
 * @brief Bejelentéskori óraállás lekérése.
 * 
 * @return int - óraállás 
 */
int Consumption_announcement::get_EM_val(){return electricMeterVal;}

/**
 * @brief Egyenlőség operátor
 * 
 * @param rhs - fogyasztás bejelentés rlvalue
 * @return true , ha a két bejelentés egyezik.
 * @return false , ha a két bejelentés nem egyezik.
 */
bool Consumption_announcement::operator==(Consumption_announcement& rhs){return(getDate()==rhs.getDate()) && (electricMeterVal==rhs.get_EM_val());}

/**
	* @brief Visszaállítja a bejelentett óraállást -1 -re.
	* @details -1 beállításával a menüből új fogyasztás jelenthető be.
*/
void Consumption_announcement::Reset(){electricMeterVal=-1;}
