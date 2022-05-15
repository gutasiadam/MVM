#ifndef CANNOUNCEMENT_H
#define CANNOUNCEMENT_H

/**
 * @file Consumption_announcement.h
 * @author Gutási Ádám
 * @brief Ez a fájl tartalmazza a Consumption_announcement osztály deklarációját és inline függvényeit.
 * @date 2022-05-15
 * 
 */
#include "Date.h"

class Consumption_announcement{
    private:
        Date date;/*!< Bejelentés dátuma */
        int electricMeterVal; /*!< Bejelentkéskori óraállás. */
    public:
        Consumption_announcement() :electricMeterVal(-1){};
        Consumption_announcement(Date d, int emVal): date(d), 
        electricMeterVal(emVal){};

        Date& getDate();/*!< Bejelentés dátumának lekérése */
        int get_EM_val();/*!< Bejelentkéskori óraállás lekérése */

        /**
         * @brief Visszaállítja a bejelentett óraállást -1 -re.
         * @details -1 beállításával a menüből új fogyasztás jelenthető be.
         */
        void Reset();


        bool operator==(Consumption_announcement& rhs); /*!< Egyenlőség operátor */

};
#endif