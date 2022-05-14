#ifndef CONTROLLER_H
#define CONTROLLER_H
/**
 * \file Controller.h
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek deklarációját
 */
#include <fstream>
//////#include "memtrace.h"
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

        void create_Invoices(Date& todayDate); // Számlázi időszak lezártával lefutó folyamat.
        void create_Invoice();
        void newClient(Client& c);
        void announceConsumption(Client&c,int emVal);
        Client& getClient(size_t id);
        Client& getClient(String& name);

        double calculate_toBePaid(Client& c); 

        size_t clientsCount();
        
        Tariffs& getTariffs();

        //virtual ~Controller();
};



#endif
