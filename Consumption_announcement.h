#ifndef CANNOUNCEMENT_H
#define CANNOUNCEMENT_H
/**
 * \file Consumption_announcement.h
 *
 * Ez a fájl tartalmazza a Consumption_announcement osztály deklarációját és inline függvényeit.
 */
#include "Client.h"
#include "Date.h"

class Consumption_announcement{
    private:
        Date date;
        int electricMeterVal;
    public:
        Consumption_announcement() {};
        Consumption_announcement(Date d, int emVal): date(d), 
        electricMeterVal(emVal){};

        Date& getDate();
        int get_EM_val();

};
#endif