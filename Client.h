#ifndef CLIENT_H
#define CLIENT_H

/**
 * @file Client.h
 * @author Gutási Ádám
 * @brief Ez a fájl tartalmazza a Client osztály deklarációját és inline függvényeit.
 * @date 2022-05-15
 * 
 */


#include <iostream>
#include <regex> // E-mail és telefonszám validálására.
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
        int id; /*!< Ügyfél azonosítója */
        String firstName; /*!< Ügyfél keresztneve */
        String lastName; /*!< Ügyfél vezetékneve */
        Date born; /*!< Ügyfél születési dátuma */
        Address resAddress; /*!< Ügyfél címe */
        String mobile; /*!< Ügyfél telefonszáma */
        String e_mail; /*!< Ügyfél e-mail címe */
        String taxNumber; /*!< Ügyfél adóazonoító jele */
        int electricMeter_last; /*!< Ügyfél utolsó, fizetett óraállása */

        bool type; /*!< Ügyfél típusa ( lakossági / vállalati) */

        int phases; /*!< Ügyfél csomagjának fázisszáma (2,3) */
        int strength; /*!< Ügyfél főbiztosítékjának erőssége. */


        double balance; /*!< Ügyfél egyenlege */

    public:
        Consumption_announcement announcement; /*!< Fogyasztási bejelentés */
        Array<Invoice> archivedInvoices; /*!< Archivált számlák */
        Array<Invoice> pendingInvoices; /*!< Befizetésre váró számlák */
        
        Client() {}; // default ctor
        Client(int id, String lN, String fN, Date b, Address res, String m, 
        String em, String taxN, bool type, int phases, int strength): id(id), firstName(fN), lastName(lN), born(b), resAddress(res), 
        mobile(m), e_mail(em), taxNumber(taxN), electricMeter_last(0), type(type), phases(phases), strength(strength), balance(0){
            ///TODO: e-mail, telefonszám validálása
        }

        Client& operator=(Client& rhs); /*!< Értékadó operatáror */

        size_t ClientSize();

        void addFunds(double moneyVal); /*!< Összeget ír jóvá az ügyfél számláján.*/
        double getBalance() const;/*!< Lekérdezi az ügyfél egyenlegét.*/
        int getId() const; /*!< Lekérdezi az Ügyfél azonosítóját.*/
        String getPhoneNumber() const; /*!< lekérdezi az ügyfél telefonszámát.*/
        String getEMail() const; /*!< lekérdezi az ügyfél e-mail címét*/
        Date& getDate(); /*!<  Lekérdezi az ügyfél születési dátumát.*/
        String getfirstName() const; /*!< Lekérdezi az ügyfél keresztnevét.*/
        String getlastName() const; /*!< Lekérdezi az ügyfél vezetéknevét.*/
        Address& getAddress(); /*!< Lakcím lekérdezése*/

        int getPhases() const; /*!< Fázisok számának  lekérdezése*/
        int getStrength() const; /*!< Főbiztosíték erősségének lekérdezése*/


        bool getType() const; /*!< Visszaadja az ügyfél típusát (magánszemély/vállalati)*/
        
        String getTN() const; /*!< Lekérdezi az ügyfél/vállalat adóazonosítóját.*/
        int getElectricMeterVal() const; /*!< Lekérdezi a villanyóra azon állását, amediig be van fizetve*/

        double getDebtval() const; /*!<Tartozás mennyiségének kiszámolása.*/

        void pay_Pending_Invoices(); /*!< Megpróbálja befizetni a befizetésre váró számlákat. */

        friend std::ostream& operator<<(std::ostream& os, Client& c); /*!< Stream operator*/
        protected:
            void modify_electricMeter(int amt); /*!< Villanyóra állásának módosítása*/


};

#endif
