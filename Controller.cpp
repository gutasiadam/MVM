/**
 * \file Controller.cpp
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek definícióját.
 */

#include "Controller.h"
//#include "memtrace.h"

void Controller::loadData(char const* CData, char const* Invoices, char const* Invoices_pending){
    // Először az ügyfelek adatait töltjük be.
    std::ifstream ClientsDat(CData);
	while(!ClientsDat.eof()){
        int id;
        int balance;
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
        ClientsDat >> id >> lastName >> firstName >> taxNum >> City >> street >> houseNum >> aptNum >> mobileNum >> e_mail >> type >> Y >> M >> D >> phases >> strength >> balance;
        //std::cout << "id:" << id << " lastName: " << lastName <<  "firstName: "<< firstName << taxNum << City <<"str: " << street << "houseNum: " << houseNum << "aptNum: " << aptNum << " mobile: " << mobileNum << "email: " << e_mail << "type: " << type << "Y: " << Y << "M: " << M << "D: " << D << "phases: " << phases << "strength: " << strength << std::endl;
		Date tmp_born(Y,M,D);
        String ln(lastName); String fn(firstName);
        Address tmp_address(String(City),String(street),houseNum,aptNum);
		Client tmpClient(id, ln, fn,tmp_born,tmp_address,String(mobileNum),String(e_mail),String(taxNum),type,phases,strength);
        tmpClient.addFunds(balance); // Fájlban tárolt kezdőegyenleg tárolása -> bezáráskor frissül a fájlban.
        clients.add(tmpClient);
    }
    for(size_t i=0;i<clientsCount();i++){
        std::cout << clients[i].getId() <<" ";
    }
    Date tmp_tst_born(2002,11,26);
	Address tmp_address_t("Budapest","Alma",27,1);
    Client tmpClient_t(31,"Test", "Elek",tmp_tst_born,tmp_address_t,"069245743","jajaj@gmail.com","077732832-0030",0,3,32);
    clients.add(tmpClient_t);
    ClientsDat.close();
    std::cout << "ClientDat done" << std::endl;
    //debug(std::cout, "ClientDat done.");
    std::ifstream InvoicesDat(Invoices);
    while(!InvoicesDat.eof()){
        int id;
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;


        InvoicesDat >> id >> Y >> M >> D >> consumptionAmt >> toBePaid;
        if(id==30){
            continue; //Segfaultol, valahol rossz cimre probalok irni.
        }
        //Gyors, ideiglenes teszt az adat hovakerülésének ellenőezésére.
        //std::cout << clients[id].getName() << Y << M << D << consumptionAmt << toBePaid << std::endl;
        Date tmpDate(Y,M,D);
        Consumption_announcement tmpCAnnounce(tmpDate,consumptionAmt);
        Invoice tmpInvoice(tmpDate,tmpCAnnounce);
        std::cout <<  clients[id].getId() << " - Számla hozzáadása" << std::endl;
        clients[id].archivedInvoices.add(tmpInvoice);
        clients[id].modify_electricMeter(tmpCAnnounce.get_EM_val()); // Óraállást pörgeti, ahogy töltődnek be az adatok.
    }
    std::cout << "Invoicedat done" << std::endl;
    InvoicesDat.close();

    std::ifstream Invoices_pending_Dat(Invoices_pending);
    while(!Invoices_pending_Dat.eof()){
        int id;
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;


        Invoices_pending_Dat >> id >> Y >> M >> D >> consumptionAmt >> toBePaid;
        if(id==30){
            continue; //Segfaultol, valahol rossz cimre probalok irni.
        }
        //Gyors, ideiglenes teszt az adat hovakerülésének ellenőezésére.
        //std::cout << clients[id].getName() << Y << M << D << consumptionAmt << toBePaid << std::endl;
        Date tmpDate(Y,M,D);
        Consumption_announcement tmpCAnnounce(tmpDate,consumptionAmt);
        Invoice tmpInvoice(tmpDate,tmpCAnnounce);
        tmpInvoice.set_toBePaid(toBePaid); //A kimentett adat már tartalmazza a fizetendőt.
        std::cout <<  clients[id-1].getId() << " - Fizetendő hozzáadása" << std::endl;
        clients[id-1].pendingInvoices.add(tmpInvoice);
        clients[id-1].modify_electricMeter(tmpCAnnounce.get_EM_val()); // Óraállást pörgeti, ahogy töltődnek be az adatok.
    }
    Invoices_pending_Dat.close();
}

void Controller::saveData(char const* CData, char const* Invoices, char const* Invoices_p){
    // Először az ügyfelek adatait töltjük be.
    std::ofstream ClientsDat(CData); std::ofstream Invoices_archived(Invoices); std::ofstream Invoices_pending(Invoices_p);
    std::cout << "Clients mérete:" << clients.size() << std::endl;
    for(Client* ptr=clients.begin(); ptr <= clients.end(); ptr++){
        // Átfutunk a kliens adatán, kiírjuk..
        // Todo: név szeparálása!
        ClientsDat << ptr->getId()
        << '\t' << ptr->getlastName()
        << '\t' << ptr->getfirstName()
        << '\t' << ptr->getTN() 
        << '\t' << ptr->getAddress().getTown() << '\t' << ptr->getAddress().getStreet() 
        << '\t' << ptr->getAddress().getHouse() << '\t' << ptr->getAddress().getApartment() 
        << '\t' << ptr->getPhoneNumber() << '\t' << ptr->getEMail() << ptr->getType() 
        << '\t'  << ptr->getDate().getYear()<< '\t' << ptr->getDate().getMonth()  
        << '\t' << ptr->getDate().getDay() << '\t' << ptr->getPhases() 
        << '\t' << ptr->getStrength() << '\t' << ptr->getBalance() << '\n';


        
        ///TODO: Archivált számlák kiírása
        //Aztán az archivált számláin...

        ///TODO: Befizetésre váró, pending számlák kiírása
        //Majd a befizetésre váró számláin...


    }
    ClientsDat.close();
    //debug(std::cout, "ClientDat Write done.");
    Invoices_archived.close();
    //debug(std::cout, "Archived Write done.");
    Invoices_pending.close();
    
}

void Controller::newClient(){
    Date tmp_tst_born(2002,11,26);
	Address tmp_address_t("Budapest","Almaa",27,1);
    Client tmpClient_t(32,"Test", "Elek 2 ",tmp_tst_born,tmp_address_t,"06945743","jajaj@gmail.com","077832-0030",0,3,32);
    clients.add(tmpClient_t);
}

///TODO: Clients getclient név alapján megírása
/*Client& Controller::getClient(String& name){
    return clients[0];
}*/
Client& Controller::getClient(int id){
    if(id>clients.size()){
        throw std::out_of_range("Indexelési hiba!");
        ///TODO: indexlési hiba elkapása
    }
    return clients[(id-1)];
}

int Controller::clientsCount(){
    return this->clients.size()-1;
}