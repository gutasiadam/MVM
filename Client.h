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
#include "string.h"
#include "Client.h"

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

        unsigned int electricMeter_last;
        double balance;
        //Array<Invoice> archivedInvoices;
        //Array<Invoice> pendingInvoices;
    public:
        Client(String N, Date b, Address res, String m, 
        String em, int taxN, bool type): Name(N), born(b), resAddress(res), 
        mobile(m), e_mail(em), taxNumber(taxN){
            //validate e-mail, mobileNum?
        }
};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param c0 - Client, amit kiírunk
/// @return os
std::ostream& operator<<(std::ostream& os, const Client& c0);

#endif
