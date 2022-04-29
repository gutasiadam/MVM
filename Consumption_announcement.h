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
        Client& client;
        Date date;
        int electricMeterVal;
    public:
        Consumption_announcement(Client& c, Date d, int emVal): client(c), date(d), 
        electricMeterVal(emVal){};

        Date& getDate();
        int get_EM_val();

};
#endif