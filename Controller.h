#ifndef CONTROLLER_H
#define CONTROLLER_H
/**
 * \file Controller.h
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek deklarációját
 */
#include <fstream>
//#include "memtrace.h"

#include "Client.h"
#include "Array.hpp"
#include "Tariffs.h"
#include "Consumption_announcement.h"



class Controller {
    
    private:
        Array<Client> clients;
        Tariffs tariffs;
    public:
        Controller(){};
        //Controller(char const* CData, char const* Invoices){}
        void loadData(char const* CData, char const* Invoices, char const* Invoices_pending);
        void saveData(char const* CData, char const* Invoices, char const* Invoices_pending);

        void create_invoices();
        void create_invoice();
        void newClient(Client& c);
        void announceConsumption(Client&c,int emVal);
        Client& getClient(int id);
        Client& getClient(String& name);
        
        Tariffs& getTariffs();

        //virtual ~Controller();
};
#endif
