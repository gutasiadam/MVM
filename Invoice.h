#ifndef ADDRESS_H
#define ADDRESS_H
/**
 * \file Invoice.h
 *
 * Ez a fájl tartalmazza az Invoice osztály deklarációját és inline függvényeit.
 */

#include "Date.h"
#include "Tariffs.h"
#include "Consumption_announcement.h"

class Invoice{
    private:
        Date created;
        int consumptionAmt;
        double toBePaid;
        Consumption_announcement announcement;
    public:
        Invoice(Date c, int cAmt, Consumption_announcement cAnnounce): created(c), 
        consumptionAmt(cAmt), announcement(cAnnounce) {};
        double calculate_toBePaid(Tariffs& t);
};

#endif