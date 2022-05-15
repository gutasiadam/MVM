#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @file Controller.h
 * @author Gutási Ádám
 * @brief Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek deklarációját
 * @date 2022-05-15
 * 
 */

#include <fstream>
#include "Client.h"
#include "Array.hpp"
#include "Tariffs.h"
#include "Consumption_announcement.h"


/**
 * @brief Az MVM rendszert kezelő osztály, amely a nyilvántartást is tartalmazza.
 * 
 */
class Controller {
    
    private:
        Array<Client> clients; /**< Az ügyfeleket tartalmazó tömb. */
        // Tariffs tariffs; A tarfa absztrakt osztály. Nem kell létrehozni.
    public:
        Controller(){};
        void loadData(char const* CData, char const* Invoices, 
        char const* Invoices_pending, char const* Tariffs, char const* CAnnFile); //!< Az adatokat tartalmazó fájlok betöltése, tárolása.
        void saveData(char const* CData, char const* Invoices, 
        char const* Invoices_pending_file, char const* CAnnFile);//!< Az adatokat tartalmazó fájlok mentése.

        void create_Invoices(Date& todayDate); //!< Számlák létrehozása, számlázási időszak lezárása.
        //void create_Invoice();
        void newClient(Client& c); //!< Új Ügyfél hozzáadása a tárolóhoz.
        void announceConsumption(Client&c,int emVal, Date& d); //!< Fogyasztást jelent be.
        Client& getClient(size_t id); //!< Visszaad egy ügyfél objektum referenciát, az ügyfél ID-je alapján.

        double calculate_toBePaid(Client& c); //!< Fizetendő összeg kiszámolása

        size_t clientsCount(); //!< Visszaadja, hány ügyfél van a rendszerben

        /* Azért nincs a dtorban a mentés meghívása,
        ,mert például a számlázás, és fizetés után az adatok megváltoznak,
        a következő futáskor a teszt hibásan futna le.*/
};

#endif
