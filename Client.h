#ifndef CLIENT_H
#define CLIENT_H
/**
 * \file Address.h
 *
 * Ez a fájl tartalmazza a Client osztály deklarációját és inline függvényeit.
 */

#include <iostream>
#include <regex> // E-mail és telefonszám validálására.
//////#include "memtrace.h"
#include "Address.h"
#include "Date.h"
#include "String.h"
#include "Client.h"
#include "Invoice.h"
#include "Array.hpp"
#include "Consumption_announcement.h"


class Client{
    friend class Controller;
    private:
        int id;
        String firstName;
        String lastName;
        Date born;
        Address resAddress;
        String mobile;
        String e_mail;
        String taxNumber;
        int electricMeter_last;

        bool type;

        int phases;
        int strength;


        double balance;

    public:
        Consumption_announcement announcement;
        Array<Invoice> archivedInvoices; // Archivált számlák
        Array<Invoice> pendingInvoices; // Befizetésre váró számlák
        
        Client() {}; // default ctor
        Client(int id, String lN, String fN, Date b, Address res, String m, 
        String em, String taxN, bool type, int phases, int strength): id(id), firstName(fN), lastName(lN), born(b), resAddress(res), 
        mobile(m), e_mail(em), taxNumber(taxN), electricMeter_last(0), type(type), phases(phases), strength(strength), balance(0){
            ///TODO: e-mail, telefonszám validálása
        }

        Client& operator=(Client& rhs); // Copy operator

        size_t ClientSize();

        void addFunds(double moneyVal); // Összeget ír jóvá az ügyfél számláján.
        double getBalance() const;// Lekérdezi az ügyfél egyenlegét.
        int getId() const; // Lekérdezi az Ügyfél azonosítóját.
        String getPhoneNumber() const; // lekérdezi az ügyfél telefonszámát.
        String getEMail() const; // lekérdezi az ügyfél e-mail címét
        Date& getDate(); //  Lekérdezi az ügyfél születési dátumát.
        String getfirstName() const; // Lekérdezi az ügyfél keresztnevét.
        String getlastName() const; // Lekérdezi az ügyfél vezetéknevét.
        Address& getAddress(); // Lakcím lekérdezése

        int getPhases() const;
        int getStrength() const;


        bool getType() const; // Visszaadja az ügyfél típusát (magánszemély/vállalati)
        
        String getTN() const;
            // Lekérdezi az ügyfél/vállalat adóazonosítóját.
        int getElectricMeterVal() const; // Lekérdezi a villanyóra azon állását, amediig be van fizetve

        double getDebtval() const; //Tartozás mennyiségének kiszámolása. Összegzi a befizetésre váró számlák fizetendőit.

        void pay_Pending_Invoices();
            // Egyenleg hozzáadása után egyből lefut
            // Megpróbálja befizetni a befizetésre váró számlákat.

            // Visszaadja, hány darab számla vár még befizetésre.
            // (lényegében a pendingInvoices új hosszát.)

        friend std::ostream& operator<<(std::ostream& os, Client& c);
        protected:
            void modify_electricMeter(int amt);
            // befizetés után módosítja a villanyóra azon
            // állását, ameddig be van fizetve
            // (electricMeter_last)

};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param c0 - Client, amit kiírunk
/// @return os


#endif
