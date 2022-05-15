#ifndef INVOICE_H
#define INVOICE_H

/**
 * @file Invoice.h
 * @author Gutási Ádám
 * @brief Ez a fájl tartalmazza az Invoice osztály deklarációját és inline függvényeit.
 * @date 2022-05-15
 * 
 */
#include "Date.h"
#include "Consumption_announcement.h"

/**
 * @brief Egy számla osztálya
 * 
 */
class Invoice{
    private:
        Date created; /*!< Létrehozás dátuma */
        Consumption_announcement announcement; /*!< A számlához tartozó fogyasztási bejelentés */
        int consumptionAmt; /*!< Fogyasztás mennyisége*/
        double toBePaid; /*!< Fizetendő összeg. */
        
    public:
        Invoice() : consumptionAmt(0), toBePaid(0){};

        /**
         * @brief Konstruktor
         * 
         * @param c A létrehozandó számla dátuma.
         * @param cAnnounce A számlához tartozó fogyasztási bejelentés.
         * @param cAmt A fogyasztás mennyisége
         */
        Invoice(Date c, Consumption_announcement& cAnnounce, int cAmt): created(c), 
        announcement(cAnnounce), consumptionAmt(cAmt), toBePaid(0) {};
        
        Date& getCreated(); /*!< Létrehozás dátumának lekérdezése */
        Consumption_announcement& getCAnn(); /*!< Fogyasztási bejelentés lekérése */
        void set_toBePaid(double what); /*!< Fizetendő összeg beállítása */
        int getConsumptionAmt() const; /*!< Fogyasztás mennyiségének lekérdezése */
        double get_toBePaid() const; /*!< Fizetendő összeg lekérdezése */
        friend std::ostream& operator<<(std::ostream& os, Invoice& c); /*!< Stream operator */

        bool operator==(Invoice& rhs); /*!< Egyenlőség operator. */
};

#endif