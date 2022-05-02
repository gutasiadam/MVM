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
        Consumption_announcement announcement;
        int consumptionAmt;
        double toBePaid;
        
    public:
        Invoice() {}; // Default ctor, Array-be rendezés miatt.
        Invoice(Date c, Consumption_announcement& cAnnounce): created(c), 
        announcement(cAnnounce), consumptionAmt(cAnnounce.get_EM_val()), toBePaid(0) {};
        double calculate_toBePaid(Tariffs& t); // Tarifa számításának módja: log2(Főbiztosíték erőssége)*tarifa*fogyasztás

        double get_toBePaid();
};

#endif