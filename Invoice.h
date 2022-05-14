#ifndef ADDRESS_H
#define ADDRESS_H
/**
 * \file Invoice.h
 *
 * Ez a fájl tartalmazza az Invoice osztály deklarációját és inline függvényeit.
 */

#include "Date.h"
#include "Consumption_announcement.h"


class Invoice{
    private:
        Date created;
        Consumption_announcement announcement;
        int consumptionAmt;
        double toBePaid;
        
    public:
        Invoice() : consumptionAmt(0), toBePaid(0){}; // Default ctor, Array-be rendezés miatt.
        Invoice(Date c, Consumption_announcement& cAnnounce): created(c), 
        announcement(cAnnounce), consumptionAmt(cAnnounce.get_EM_val()), toBePaid(0) {};
        
        Date& getCreated();
        Consumption_announcement& getCAnn();
        void set_toBePaid(double what){this->toBePaid=what;}
        int getConsumptionAmt() const;
        double get_toBePaid() const;

        friend std::ostream& operator<<(std::ostream& os, Invoice& c);

        bool operator==(Invoice& rhs);
};

#endif