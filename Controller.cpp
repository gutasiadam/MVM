/**
 * \file Controller.cpp
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek definícióját.
 */

//#include "memtrace.h"
#include "Controller.h"
#include "math.h"


void Controller::loadData(char const* CData, char const* Invoices, char const* Invoices_pending){
    /**
     * Ügyfelek adatainak betölése
     */
    std::ifstream ClientsDat(CData);
    ClientsDat.setf(std::ios::fixed); ClientsDat.setf(std::ios::showpoint); ClientsDat.precision(2);
	int id=-1;
    while(ClientsDat>>id){ //Elkerüljük az utolsó sor duplikálását.
        double balance=0;
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
        ClientsDat >> lastName >> firstName >> taxNum >> City >> street >> houseNum >> aptNum >> mobileNum >> e_mail >> type >> Y >> M >> D >> phases >> strength >> balance;
        //std::cout << "id:" << id << " lastName: " << lastName <<  "firstName: "<< firstName << taxNum << City <<"str: " << street << "houseNum: " << houseNum << "aptNum: " << aptNum << " mobile: " << mobileNum << "email: " << e_mail << "type: " << type << "Y: " << Y << "M: " << M << "D: " << D << "phases: " << phases << "strength: " << strength << std::endl;
        //std::cout << "id: " << id << "balance: " << balance << std::endl;
		Date tmp_born(Y,M,D);
        String ln(lastName); String fn(firstName);
        Address tmp_address(String(City),String(street),houseNum,aptNum);
		Client tmpClient(id, ln, fn,tmp_born,tmp_address,String(mobileNum),String(e_mail),String(taxNum),type,phases,strength);
        tmpClient.addFunds(balance); // Fájlban tárolt kezdőegyenleg tárolása -> bezáráskor frissül a fájlban.
        clients.add(tmpClient);
    }
    /*for(size_t i=0;i<clientsCount();i++){
        std::cout << clients[i].getId() <<" ";
    }/*
    
    ClientsDat.close();
    std::cout << "ClientDat done - hossz: " << clientsCount() << std::endl;
    
    /**
     * Befizetett számlák betölése
     */
    std::ifstream InvoicesDat(Invoices);
    InvoicesDat.setf(std::ios::fixed); InvoicesDat.setf(std::ios::showpoint); InvoicesDat.precision(2);
    id=0;
    while(InvoicesDat>>id){ //Elkerüljük az utolsó sor duplikálását.
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;
        int emVal;

        InvoicesDat >> Y >> M >> D >> consumptionAmt >> toBePaid >> emVal;
        std::cout << id << " \t" << Y << " \t" << M << " \t" << D << " \t" << consumptionAmt << " \t" << toBePaid << " \t" << emVal;
        InvoicesDat.ignore();

        Date tmpDate(Y,M,D);
        // A Consumption_announcement ÓRAÁLLÁST tárol!
        Consumption_announcement tmpCAnnounce(tmpDate,emVal);
        Invoice tmpInvoice(tmpDate,tmpCAnnounce);
        tmpInvoice.set_toBePaid(toBePaid); //A kimentett adat már tartalmazza a fizetendőt.
        //std::cout << "clients["<<id<<"].getId()" << std::endl;
        //std::cout << " " << clients[id-1].getId() << " - Számla hozzáadása" << std::endl;
        clients[id-1].archivedInvoices.add(tmpInvoice);

        // Óraállást pörgeti, ahogy töltődnek be az adatok.
        clients[id-1].modify_electricMeter(tmpCAnnounce.get_EM_val()); 
    }
    //std::cout << "Invoicedat done" << std::endl;
    InvoicesDat.close();

    /**
     * Tarifák betölése
     */
    std::ifstream TarfiffsDat("Tariffs.txt");
    TarfiffsDat.setf(std::ios::fixed); TarfiffsDat.setf(std::ios::showpoint); TarfiffsDat.precision(2);
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
     *  - befizetésre váró számlát a rendszer generál.
     */
    std::ifstream Invoices_pending_Dat(Invoices_pending);
    Invoices_pending_Dat.setf(std::ios::fixed); Invoices_pending_Dat.setf(std::ios::showpoint); Invoices_pending_Dat.precision(2);
    while(Invoices_pending_Dat>>id){ //Elkerüljük az utolsó sor duplikálását.
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;
        int emVal=0;


        Invoices_pending_Dat >> Y >> M >> D >> consumptionAmt >> toBePaid >> emVal;
        Invoices_pending_Dat.ignore();

        Date tmpDate(Y,M,D);
        Consumption_announcement tmpCAnnounce(tmpDate, emVal);

        Invoice tmpInvoice(tmpDate,tmpCAnnounce);
        tmpInvoice.set_toBePaid(toBePaid); //A kimentett adat már tartalmazza a fizetendőt.
        //std::cout <<  clients[id-1].getId() << " - ";
        //std::cout << " fogy: "<<tmpInvoice.getConsumptionAmt() << " ";
        clients[id-1].pendingInvoices.add(tmpInvoice);
        //std::cout <<  clients[id-1].pendingInvoices.size() << " méret" << std::endl;
        if(Invoices_pending_Dat.eof()) break;
    }
    Invoices_pending_Dat.close();
}

/**
 * @brief Adatok kimentése txt fájlokba
 * 
 * @param CData Az ügyfelek adatait tartalmazó szövegfájl
 * @param Invoices Az archivált (befizetettt) számlákat tartalmazó szövegfájl.
 * @param Invoices_p A befizetésre váró számlákat tartalmazó szövegfájl.
 */
void Controller::saveData(char const* CData, char const* Invoices, char const* Invoices_p){
    // Először az ügyfelek adatait töltjük be.
    std::ofstream ClientsDat(CData); std::ofstream Invoices_archived(Invoices); std::ofstream Invoices_pending(Invoices_p);
    ClientsDat.setf(std::ios::fixed); ClientsDat.setf(std::ios::showpoint); ClientsDat.precision(2);
    Invoices_archived.setf(std::ios::fixed); Invoices_archived.setf(std::ios::showpoint); Invoices_archived.precision(2);
    Invoices_pending.setf(std::ios::fixed); Invoices_pending.setf(std::ios::showpoint); Invoices_pending.precision(2);

    //std::cout << "Clients mérete:" << clients.size() << std::endl;
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
            << '\t' << archived->get_toBePaid()
            << '\t' << archived->getCAnn().get_EM_val() << '\n';
        }


        //Kiírjuk a befizetésre váró számlákat.
        for(Invoice* archived=ptr->pendingInvoices.begin();
        archived != ptr->pendingInvoices.end(); archived++){
            Invoices_pending << ptr->getId()
            << '\t' << archived->getCreated().getYear()
            << '\t' << archived->getCreated().getMonth()
            << '\t' << archived->getCreated().getDay()
            << '\t' << archived->getConsumptionAmt()
            << '\t' << archived->get_toBePaid()
            << '\t' << archived->getCAnn().get_EM_val() << '\n';
        }

    }
    ClientsDat.close();
    Invoices_archived.close();
    Invoices_pending.close();
    
}

void Controller::newClient(Client& c){
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
                for(;invoiceptr!=invend;invoiceptr++,n++){
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
Client& Controller::getClient(size_t id){
    if(id>clients.size()){
        throw std::out_of_range("Indexelési hiba!");
        ///TODO: indexlési hiba elkapása
    }
    return clients[(id-1)];
}

size_t Controller::clientsCount(){
    return this->clients.size();
}