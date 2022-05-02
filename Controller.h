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
#include <fstream>

class Controller {
    private:
        Array<Client> clients;
        Tariffs tariffs;
    public:
        Controller(){};
        Controller(const char* CData, const char* Invoices){
            //std::cout << "Ezen kicsi sorocskák mutatják a hiba helyét :-) " << std::endl;
    std::ifstream ClientsDat(CData);
    std::ifstream InvoicesDat(Invoices);
	while(!ClientsDat.eof()){
        int id;
        char firstName[51];
        char lastName[51];
        char mobileNum[21];
        char City[31];
        char street[101];
        char taxNum[13];
        int houseNum;
        int aptNum;
        bool type; // intből konv. boolba?
        int Y; int M; int D;
        int phases;
		int strength;
        char e_mail[51];
        ClientsDat >> id >> lastName >> firstName >> taxNum >> City >> street >> houseNum >> aptNum >> mobileNum >> e_mail >> type >> Y >> M >> D >> phases >> strength;
		Date tmp_born(Y,M,D);
        String first(firstName);
        String last(lastName);
        Address tmp_address(String(City),String(street),houseNum); // TODO: Legyen a lakásszám is benne!
		Client tmpClient(id, last+first,tmp_born,tmp_address,String(mobileNum),String(e_mail),String(taxNum),type,phases,strength);
        //std::cout << "Client ok" << std::endl;
		clients.add(tmpClient);
        //std::cout << "Client [+]" << std::endl;
    }
    ClientsDat.close();
    InvoicesDat.close();
    // Fájlok (Clientdata.txt, Consumption_announcement.txt) beolvasása, feldolgozása,
    //tárolása az Arrayben.
}
        void create_invoices();
        void create_invoice();
        void newClient(Client& c);
        void announceConsumption(Client&c,int emVal);
        Client& getClient(int id);
        Client& getClient(String& name);
        
        Tariffs& getTariffs();

        //~Controller();
};
#endif
