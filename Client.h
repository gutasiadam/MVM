#ifndef CLIENT_H
#define CLIENT_H
/**
 * \file Address.h
 *
 * Ez a fájl tartalmazza a Client osztály deklarációját és inline függvényeit.
 */

#include <iostream>
#include "Address.h"
#include "Date.h"
#include "String.h"
#include "Client.h"
#include "Invoice.h"
#include "Array.hpp"
#include <regex> // E-mail és telefonszám validálására.

class Client{
    private:
        int id;
        String Name;
        Date born;
        Address resAddress;
        String mobile;
        String e_mail;
        bool type;
        int taxNumber;

        unsigned short int phases;
        unsigned short int strength;

        Consumption_announcement* announcement;

        unsigned int electricMeter_last;
        double balance;

        Array<Invoice> archivedInvoices; // Archivált számlák
        Array<Invoice> pendingInvoices; // Befizetésre váró számlák
    public:
        Client() {}; // default ctor
        Client(String N, Date b, Address res, String m, 
        String em, int taxN, bool type): Name(N), born(b), resAddress(res), 
        mobile(m), e_mail(em), taxNumber(taxN){
            //e-mail, telefonszám validálása, majd beírás..
            //
        }
        

        void addFunds(double moneyVal); // Összeget ír jóvá az ügyfél számláján.
        double getBalance() const;// Lekérdezi az ügyfél egyenlegét.
        int getId() const; // Lekérdezi az Ügyfél azonosítóját.
        int getPhoneNumber() const; // lekérdezi az ügyfél telefonszámát.
        Date& getDate() const; //  Lekérdezi az ügyfél születési dátumát.
        String& getName() const; // Lekérdezi az ügyfél nevét.

        bool getType() const; // Visszaadja az ügyfél típusát (magánszemély/vállalati)
        
        int getTN() const;
            // Lekérdezi az ügyfél/vállalat adóazonosítóját.
        int getElectricMeterVal() const; // Lekérdezi a villanyóra azon állását, amediig be van fizetve

        void pay_Pending_Invoices();
            // Egyenleg hozzáadása után egyből lefut
            // Megpróbálja befizetni a befizetésre váró számlákat.

            // Visszaadja, hány darab számla vár még befizetésre.
            // (lényegében a pendingInvoices új hosszát.)

        protected:
            void modify_electricMeter(unsigned int amt);
            // befizetés után módosítja a villanyóra azon
            // állását, ameddig be van fizetve
            // (electricMeter_last)

};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param c0 - Client, amit kiírunk
/// @return os
std::ostream& operator<<(std::ostream& os, const Client& c0);

#endif
