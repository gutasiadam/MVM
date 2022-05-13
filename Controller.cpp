/**
 * \file Controller.cpp
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek definícióját.
 */

#include "Controller.h"
#include "math.h"
//#include "memtrace.h"

void Controller::loadData(char const* CData, char const* Invoices, char const* Invoices_pending){
    /**
     * Ügyfelek adatainak betölése
     */
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
    Client tmpClient_t(32,"Tett", "Elek",tmp_tst_born,tmp_address_t,"069245743","jajaj@gmail.com","077732832-0030",0,3,32);
    clients.add(tmpClient_t);
    
    ClientsDat.close();
    std::cout << "ClientDat done" << std::endl;
    
    /**
     * Számlák betölése
     */
    std::ifstream InvoicesDat(Invoices);
    while(!InvoicesDat.eof()){
        int id;
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;


        InvoicesDat >> id >> Y >> M >> D >> consumptionAmt >> toBePaid;
        Date tmpDate(Y,M,D);
        Consumption_announcement tmpCAnnounce(tmpDate,consumptionAmt);
        Invoice tmpInvoice(tmpDate,tmpCAnnounce);
        tmpInvoice.set_toBePaid(toBePaid); //A kimentett adat már tartalmazza a fizetendőt.
        //std::cout <<  clients[id].getId() << " - Számla hozzáadása" << std::endl;
        clients[id-1].archivedInvoices.add(tmpInvoice);

        // Óraállást pörgeti, ahogy töltődnek be az adatok.
        clients[id-1].modify_electricMeter(tmpCAnnounce.get_EM_val()); 
    }
    std::cout << "Invoicedat done" << std::endl;
    InvoicesDat.close();

    /**
     * Számlák betölése
     */
    std::ifstream TarfiffsDat("Tariffs.txt");
    while(!TarfiffsDat.eof()){
        TarfiffsDat >> Tariffs::residental_16;
        TarfiffsDat >> Tariffs::residental_32;
        TarfiffsDat >> Tariffs::corporate_2ph_32;
        TarfiffsDat >> Tariffs::corporate_2ph_63;
        TarfiffsDat >> Tariffs::corporate_2ph_128;
        TarfiffsDat >> Tariffs::corporate_3ph_32;
        TarfiffsDat >> Tariffs::corporate_3ph_63;
        TarfiffsDat >> Tariffs::corporate_3ph_128;
        TarfiffsDat >> Tariffs::usage_fee;
    }
    TarfiffsDat.close();
    
    /**
     * Fogyasztási bejelentések betöltése
     */
    //TODO: mérőóra-állások kiszámolása. Amyg nincs kész nem tölthet be a consumption ann.
    /*std::ifstream Consumption_ann_Dat("Consumption_announcements.txt");
    while(!Consumption_ann_Dat.eof()){
        int id; int Y;int M; int D; int emVal;
        Consumption_ann_Dat >> id >> Y >> M >> D >> emVal;
        Date tmpDate(Y,M,D);
        Consumption_announcement tmpAnnounce(tmpDate,emVal);
        clients[id].announcement=tmpAnnounce;
    }*/

    /**
     * Befizetésre váró számlák betöltése
     */
    std::ifstream Invoices_pending_Dat(Invoices_pending);
    while(!Invoices_pending_Dat.eof()){
        int id;
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;


        Invoices_pending_Dat >> id >> Y >> M >> D >> consumptionAmt >> toBePaid;
        /*if(id==30){
            continue; //Segfaultol, valahol rossz cimre probalok irni.
        }*/
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
    for(Client* ptr=clients.begin(); ptr != clients.end(); ptr++){
        // Átfutunk a kliens adatán, kiírjuk..
        // Todo: név szeparálása!
        ClientsDat << ptr->getId()
        << '\t' << ptr->getlastName()
        << '\t' << ptr->getfirstName()
        << '\t' << ptr->getTN() 
        << '\t' << ptr->getAddress().getTown() << '\t' << ptr->getAddress().getStreet() 
        << '\t' << ptr->getAddress().getHouse() << '\t' << ptr->getAddress().getApartment() 
        << '\t' << ptr->getPhoneNumber() << '\t' << ptr->getEMail() << '\t' << ptr->getType() 
        << '\t' << ptr->getDate().getYear()<< '\t' << ptr->getDate().getMonth()  
        << '\t' << ptr->getDate().getDay() << '\t' << ptr->getPhases() 
        << '\t' << ptr->getStrength() << '\t' << ptr->getBalance() << '\n';

        
        //Aztán az archivált számlákat írjuk ki...
        for(Invoice* archived=ptr->archivedInvoices.begin();
        archived != ptr->archivedInvoices.end(); archived++){
            Invoices_archived << ptr->getId()
            << '\t' << archived->getCreated().getYear()
            << '\t' << archived->getCreated().getMonth()
            << '\t' << archived->getCreated().getDay()
            << '\t' << archived->getConsumptionAmt()
            << '\t' << archived->get_toBePaid() << '\n';
        }


        //Majd a befizetésre váró számlákat ítjuk ki...

        for(Invoice* archived=ptr->pendingInvoices.begin();
        archived != ptr->pendingInvoices.end(); archived++){
            Invoices_pending << ptr->getId()
            << '\t' << archived->getCreated().getYear()
            << '\t' << archived->getCreated().getMonth()
            << '\t' << archived->getCreated().getDay()
            << '\t' << archived->getConsumptionAmt()
            << '\t' << archived->get_toBePaid() << '\n';
        }

    }
    ClientsDat.close();
    //debug(std::cout, "ClientDat Write done.");
    Invoices_archived.close();
    //debug(std::cout, "Archived Write done.");
    Invoices_pending.close();
    
}

void Controller::newClient(Client& c){
    //TODO: pararméteresre átalakítani
    /*Date tmp_tst_born(2002,11,26);
	Address tmp_address_t("Budapest","Almaa",27,1);
    Client tmpClient_t(32,"Test", "Elek 2 ",tmp_tst_born,tmp_address_t,"06945743","jajaj@gmail.com","077832-0030",0,3,32);*/
    clients.add(c);
}

double Controller::calculate_toBePaid(Client& c){
    std::cout << "Fizetendő számolása..." << std::endl;
	// Tarifa számításának módja: log2(Főbiztosíték erőssége)*tarifa*fogyasztás
	if(c.getType()==0){ // lakossági
        if(c.getStrength()==16){
            return log2(c.getStrength()*Tariffs::residental_16*
            c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
        }else{
            return log2(c.getStrength()*Tariffs::residental_32*
            c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
        }
    }else{ // vállalati
    switch(c.getPhases()){
        default:
            if(c.getStrength()==32){
                return log2(c.getStrength()*Tariffs::corporate_2ph_32*
                c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
            }else if(c.getStrength()==63){
                return log2(c.getStrength()*Tariffs::corporate_2ph_63*
                c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
            }else{ // 128A
                return log2(c.getStrength()*Tariffs::corporate_2ph_128*
                c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
            }
            break;
        case 3:
            if(c.getStrength()==32){
                return log2(c.getStrength()*Tariffs::corporate_3ph_32*
                c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
            }else if(c.getStrength()==63){
                return log2(c.getStrength()*Tariffs::corporate_3ph_63*
                c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
            }else{ // 128A
                return log2(c.getStrength()*Tariffs::corporate_3ph_128*
                c.pendingInvoices.end()->getConsumptionAmt())+Tariffs::usage_fee;
            }
            break;
    }
    }
    
}

void Controller::create_Invoices(Date& todayDate){
    std::cout << "Kezdődjön a számolás" << std::endl;
    /**
	 * Minden egyes kliensre meghívódik:
	 * 	1. Ha van az ügyfélnek fogyasztási bejelentése az időszakra, akkor ez alapján számoljunk!
	 * 	2. Ha nincs, akkor az archivált számlák alapján határozzunk meg egy átlagot, majd ennek vegyük a fogyasztását, 
	 * az órájukat is az átlag szerint toljuk tovább.
	 *	3. Ha nem volt még archivált számlája ( új ügyfél ), akkor 10 000 HUF értékű késedelmi díjat 
     (büntetést) kell fizetnie. A fogyasztása a számlán 0-t fog mutatni, a teljesített óraállása sem fog előrébb haladni.
	 */
    for(Client* it=clients.begin();it!=clients.end();it++){ // Minden egyes Ügyfélre.
        if(it->announcement.get_EM_val()!=-1){ // ekkor van fogyasztási bejelentés
            std::cout << it->getId() << " - van bejelentés";
            Invoice clientInvoice(todayDate,it->announcement);

            this->calculate_toBePaid(*it);
            it->pendingInvoices.add(clientInvoice);

            
        }else{ // Ekkor nincs bejelentés, átlagolni kell.
            std::cout << it->getId() << " - nincs bejelentés";
            Invoice* invoiceptr=it->archivedInvoices.begin();
            Invoice* invend=it->archivedInvoices.end();

            //Ha van archivált számla.
            if(invoiceptr!=invend){
                std::cout << "Van archivált számla.";
                int s=0; int n=0;
                for(invoiceptr;invoiceptr!=invend;invoiceptr++,n++){
                    s+=invoiceptr->getConsumptionAmt();
                }
                double avg=(s/n);
                Consumption_announcement tmpAnnounce(todayDate,avg);
                Invoice clientInvoice(todayDate,tmpAnnounce);
                it->pendingInvoices.add(clientInvoice);
            }
            //Ha nincs archivált számla:
            else{
                std::cout << "Nincs archivált számla.";
                Consumption_announcement tmpAnnounce(todayDate,0);
                Invoice clientInvoice(todayDate,tmpAnnounce);
                clientInvoice.set_toBePaid(10000);
                it->pendingInvoices.add(clientInvoice);
            }
        }// nincs fogyasztási bejelentés blokk.
        std::cout << "befizetésre váró számlák: " << it->pendingInvoices.size() << std::endl;
    } // minden egyes ügyfél blokk
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