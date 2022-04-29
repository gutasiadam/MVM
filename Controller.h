#ifndef CONTROLLER_H
#define CONTROLLER_H
/**
 * \file Controller.h
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek deklarációját
 */
#include "Client.h"
#include "Array.hpp"
#include "Tariffs.h"

class Controller {
    private:
        Array<Client> clients;
        Tariffs tariffs;
    public:
        Controller();
        
        void create_invoices();
        void create_invoice();
        void newClient(Client& c);
        void announceConsumption(Client&c,int emVal);
        Client& getClient(int id);
        Client& getClient(String& name);

        ~Controller();
}
#endif