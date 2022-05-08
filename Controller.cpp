/**
 * \file Controller.cpp
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek definícióját.
 */

#include "Controller.h"
//#include "memtrace.h"

void Controller::loadData(char const* CData, char const* Invoices){
	std::cout << "Starting LoadData.." << std::endl;
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
        bool type;
        int Y; int M; int D;
        int phases;
		int strength;
        char e_mail[51];
        ClientsDat >> id >> lastName >> firstName >> taxNum >> City >> street >> houseNum >> aptNum >> mobileNum >> e_mail >> type >> Y >> M >> D >> phases >> strength;
        //std::cout << "id:" << id << " lastName: " << lastName << firstName << taxNum << City <<"str: " << street << "houseNum: " << houseNum << "aptNum: " << aptNum << " mobile: " << mobileNum << "email: " << e_mail << "type: " << type << "Y: " << Y << "M: " << M << "D: " << D << "phases: " << phases << "strength: " << strength;
		Date tmp_born(Y,M,D);
        String first(firstName);
        String last(lastName);
        Address tmp_address(String(City),String(street),houseNum); // TODO: Legyen a lakásszám is benne!
		Client tmpClient(id, last+first,tmp_born,tmp_address,String(mobileNum),String(e_mail),String(taxNum),type,phases,strength);
        clients.add(tmpClient);
    }
    ClientsDat.close();
    InvoicesDat.close();
}

Client& Controller::getClient(String& name){
    return clients[0];
}

Client& Controller::getClient(int id){
    return clients[id];
}