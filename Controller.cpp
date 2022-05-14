/**
 * \file Controller.cpp
 *
 * Ez a fájl tartalmazza a Controller osztály- és tagfüggvényeinek definícióját.
 */

//#include "memtrace.h"
#include "Controller.h"
#include "math.h"

void Controller::loadData(char const* CData, char const* Invoices, 
char const* Invoices_pending, char const* Tariffs, char const* CAnnFile){
    /**
     * Ügyfelek adatainak betölése
     */
    std::ifstream ClientsDat(CData);
    debug(std::cout, "ClientData betöltése...");
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


		Date tmp_born(Y,M,D);
        String ln(lastName); String fn(firstName);
        Address tmp_address(String(City),String(street),houseNum,aptNum);
		Client tmpClient(id, ln, fn,tmp_born,tmp_address,String(mobileNum),String(e_mail),String(taxNum),type,phases,strength);
        tmpClient.addFunds(balance); // Fájlban tárolt kezdőegyenleg tárolása -> bezáráskor frissül a fájlban.
        clients.add(tmpClient);
    }

    
    ClientsDat.close();
    debug(std::cout, "✅\n");
    debug(std::cout, clientsCount());
    
    /**
     * Befizetett számlák betölése
     */
    debug(std::cout, "\nBefizetettek betöltése...");
    std::ifstream InvoicesDat(Invoices);
    InvoicesDat.setf(std::ios::fixed); InvoicesDat.setf(std::ios::showpoint); InvoicesDat.precision(2);
    id=0;
    while(InvoicesDat>>id){ //Elkerüljük az utolsó sor duplikálását.
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;
        int emVal;

        InvoicesDat >> Y >> M >> D >> consumptionAmt >> toBePaid >> emVal;
        InvoicesDat.ignore();

        Date tmpDate(Y,M,D);
        // A Consumption_announcement ÓRAÁLLÁST tárol!
        Consumption_announcement tmpCAnnounce(tmpDate, emVal);
        Invoice tmpInvoice(tmpDate,tmpCAnnounce,consumptionAmt);
        tmpInvoice.set_toBePaid(toBePaid); //A kimentett adat már tartalmazza a fizetendőt.
        clients[id-1].archivedInvoices.add(tmpInvoice);

        // Óraállást pörgeti, ahogy töltődnek be az adatok.
        clients[id-1].modify_electricMeter(tmpCAnnounce.get_EM_val()); 
    }
    //std::cout << "Invoicedat done" << std::endl;
    InvoicesDat.close();
    debug(std::cout, "✅\n");
    /**
     * Tarifák betölése
     */
    debug(std::cout, "\nTarifák betöltése...");
    std::ifstream TarfiffsDat(Tariffs);
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
    debug(std::cout, "✅\n");
    TarfiffsDat.close();
    
    /**
     * Fogyasztási bejelentések betöltése
     */
    debug(std::cout, "Fogyasztási bejelentések betöltése....");
    std::ifstream Consumption_ann_Dat(CAnnFile);
    while(Consumption_ann_Dat>>id){ //Elkerüljük az utolsó sor duplikálását.
        int Y;int M; int D; int emVal;
        Consumption_ann_Dat >> Y >> M >> D >> emVal;
        Date tmpDate(Y,M,D);
        Consumption_announcement tmpAnnounce(tmpDate,emVal);
        clients[id-1].announcement=tmpAnnounce;
        debug(std::cout,id);
        debug(std::cout,": Bejelentett óraállás: ");
        debug(std::cout, clients[id-1].announcement.get_EM_val());
        debug(std::cout, "\n");
    }
    debug(std::cout, "✅\n");
    Consumption_ann_Dat.close();

    /**
     * Befizetésre váró számlák betöltése
     *  - befizetésre váró számlát a rendszer generál.
     */
    std::ifstream Invoices_pending_Dat(Invoices_pending);
    debug(std::cout,"\nFüggőben levő számlák betöltése...");
    Invoices_pending_Dat.setf(std::ios::fixed); Invoices_pending_Dat.setf(std::ios::showpoint); Invoices_pending_Dat.precision(2);
    while(Invoices_pending_Dat>>id){ //Elkerüljük az utolsó sor duplikálását.
        int Y; int M; int D;
        int consumptionAmt;
        double toBePaid;
        int emVal=0;


        Invoices_pending_Dat >> Y >> M >> D >> consumptionAmt >> toBePaid >> emVal;
        debug(std::cout,"id: "); debug(std::cout,id);
        debug(std::cout," Ft: "); debug(std::cout,toBePaid);
        Invoices_pending_Dat.ignore();

        Date tmpDate(Y,M,D);
        Consumption_announcement tmpCAnnounce(tmpDate, emVal);

        Invoice tmpInvoice(tmpDate,tmpCAnnounce,consumptionAmt);
        tmpInvoice.set_toBePaid(toBePaid); //A kimentett adat már tartalmazza a fizetendőt.

        clients[id-1].pendingInvoices.add(tmpInvoice);
        debug(std::cout,"Tartozasok szama: "); debug(std::cout,clients[id-1].pendingInvoices.size());
        if(Invoices_pending_Dat.eof()) break;
    }
    debug(std::cout,"✅\n");
    Invoices_pending_Dat.close();
}

/**
 * @brief Adatok kimentése txt fájlokba
 * 
 * @param CData Az ügyfelek adatait tartalmazó szövegfájl
 * @param Invoices Az archivált (befizetettt) számlákat tartalmazó szövegfájl.
 * @param Invoices_p A befizetésre váró számlákat tartalmazó szövegfájl.
 */
void Controller::saveData(char const* CData, char const* Invoices, 
char const* Invoices_pending_file, char const* CAnnFile){
    // Először az ügyfelek adatait töltjük be.
    std::ofstream ClientsDat(CData); std::ofstream Invoices_archived(Invoices); std::ofstream Invoices_pending(Invoices_pending_file);
    ClientsDat.setf(std::ios::fixed); ClientsDat.setf(std::ios::showpoint); ClientsDat.precision(2);
    Invoices_archived.setf(std::ios::fixed); Invoices_archived.setf(std::ios::showpoint); Invoices_archived.precision(2);
    Invoices_pending.setf(std::ios::fixed); Invoices_pending.setf(std::ios::showpoint); Invoices_pending.precision(2);
    std::ofstream Consumption_ann_Dat(CAnnFile);
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
        for(Invoice* pending=ptr->pendingInvoices.begin();
        pending != ptr->pendingInvoices.end(); pending++){
            Invoices_pending << ptr->getId()
            << '\t' << pending->getCreated().getYear()
            << '\t' << pending->getCreated().getMonth()
            << '\t' << pending->getCreated().getDay()
            << '\t' << pending->getConsumptionAmt()
            << '\t' << pending->get_toBePaid()
            << '\t' << pending->getCAnn().get_EM_val() << '\n';
        }


        //Fogyasztási bejelentések kiírása.
        {
            // Ha -1, akkor friss számlázás volt, nincs mit kiírni.
            if(ptr->announcement.get_EM_val()!=-1){
                Consumption_ann_Dat << ptr->getId()
                << '\t' << ptr->announcement.getDate().getYear()
                << '\t' << ptr->announcement.getDate().getMonth()
                << '\t' << ptr->announcement.getDate().getDay()
                << '\t' << ptr->announcement.get_EM_val() << '\n';
            }
            
        }

    }
    ClientsDat.close();
    Invoices_archived.close();
    Invoices_pending.close();
    Consumption_ann_Dat.close();
    debug(std::cout, "Fájlok mentése kész.\n");
}

void Controller::newClient(Client& c){
    clients.add(c);
}

double Controller::calculate_toBePaid(Client& c){
    int consumption=(c.pendingInvoices.end()-1)->getConsumptionAmt();
    debug(std::cout,"Fizetendő: "); debug(std::cout,consumption); debug(std::cout,"kWh\n");
	// Tarifa számításának módja: log2(Főbiztosíték erőssége)*tarifa*fogyasztás+alapdíj
    double endVal=0;
	if(c.getType()==0){ // lakossági
        if(c.getStrength()==16){
            endVal= log2(c.getStrength())*(Tariffs::residental_16*
            consumption)+Tariffs::usage_fee;
        }else{
            endVal= log2(c.getStrength())*(Tariffs::residental_32*
            consumption)+Tariffs::usage_fee;
        }
    }else{ // vállalati
    switch(c.getPhases()){
        default:
            if(c.getStrength()==32){
                endVal= log2(c.getStrength())*(Tariffs::corporate_2ph_32*
                consumption)+Tariffs::usage_fee;
            }else if(c.getStrength()==63){
                endVal= log2(c.getStrength())*(Tariffs::corporate_2ph_63*
                consumption)+Tariffs::usage_fee;
            }else{ // 128A
                endVal= log2(c.getStrength())*(Tariffs::corporate_2ph_128*
                consumption)+Tariffs::usage_fee;
            }
            break;
        case 3:
            if(c.getStrength()==32){
                endVal= log2(c.getStrength())*(Tariffs::corporate_3ph_32*
                consumption)+Tariffs::usage_fee;
            }else if(c.getStrength()==63){
                endVal= log2(c.getStrength())*(Tariffs::corporate_3ph_63*
                consumption)+Tariffs::usage_fee;
            }else{ // 128A
                endVal= log2(c.getStrength())*(Tariffs::corporate_3ph_128*
                consumption)+Tariffs::usage_fee;
            }
            break;
    }
    }
    debug(std::cout, endVal); debug(std::cout, " Ft.\n");
    return endVal;
}

void Controller::create_Invoices(Date& todayDate){
    /**
	 * Minden egyes kliensre meghívódik:
	 * 	1. Ha van az ügyfélnek fogyasztási bejelentése az időszakra, akkor ez alapján számoljunk!
	 * 	2. Ha nincs, akkor az archivált számlák alapján határozzunk meg egy átlagot, majd ennek vegyük a fogyasztását, 
	 * az órájukat is az átlag szerint toljuk tovább.
	 *	3. Ha nem volt még archivált számlája ( új ügyfél ), akkor a rendszer 1kWh fogyasztást mér fel, fizetendőnek pedig
     * 30 000 Huf-t számol fel.
     *  kell fizetnie.
	 */
    for(Client* it=clients.begin();it!=clients.end();it++){ // Minden egyes Ügyfélre.
        if(it->announcement.get_EM_val()!=-1){ // ekkor van fogyasztási bejelentés
            debug(std::cout, it->getId());
            debug(std::cout, " - 🟢 ");
            debug(std::cout, "Bejelentett óraállás: ");
            debug(std::cout, it->announcement.get_EM_val());
            debug(std::cout, "\n");
            int consumption=it->announcement.get_EM_val() - it->getElectricMeterVal();
            
            Invoice clientInvoice(todayDate,it->announcement,consumption);
            debug(std::cout, "Fogyasztás:");
            debug(std::cout, consumption);
            debug(std::cout, "\n");

            it->pendingInvoices.add(clientInvoice);
            double toBePaid=this->calculate_toBePaid(*(it));
            (it->pendingInvoices.end()-1)->set_toBePaid(toBePaid);

            
        }else{ // Ekkor nincs bejelentés, átlagolni kell.
            debug(std::cout, "⭕️ Nincs bejelentés, átlagolni kell \n");
            Invoice* invoiceptr=it->archivedInvoices.begin();
            Invoice* invend=it->archivedInvoices.end();

            //Ha van archivált számla.
            if(invoiceptr!=invend){
                debug(std::cout, "🟡 \n");
                int s=0; int n=0;
                for(;invoiceptr!=invend;invoiceptr++,n++){
                    s+=invoiceptr->getConsumptionAmt();
                    //std::cout << "\t " << s << '\t' << n << std::endl;
                }
                double avg=(s/(n+1));

                debug(std::cout, "átlag: ");
                debug(std::cout, avg);
                debug(std::cout, "\nÓraállás: ");
                debug(std::cout, (invend-1)->getCAnn().get_EM_val()+avg);

                Consumption_announcement tmpAnnounce(todayDate,
                (invend-1)->getCAnn().get_EM_val()+avg);
                Invoice clientInvoice(todayDate,tmpAnnounce,avg);
                it->pendingInvoices.add(clientInvoice);
                double toBePaid=this->calculate_toBePaid(*(it));
                
                (it->pendingInvoices.end()-1)->set_toBePaid(toBePaid);
                debug(std::cout, "\nFizetendő: ");
                debug(std::cout, (it->pendingInvoices.end()-1)->get_toBePaid());
            }
            //Ha nincs archivált számla:
            else{
                debug(std::cout, "🔴 Nincs archivált számla?\t");
                debug(std::cout, it->archivedInvoices.size());
                Consumption_announcement tmpAnnounce(todayDate,0);
                Invoice clientInvoice(todayDate,tmpAnnounce,1);
                clientInvoice.set_toBePaid(30000);
                it->pendingInvoices.add(clientInvoice);
            }
        }// nincs fogyasztási bejelentés blokk.

        debug(std::cout, "\nbefizetésre váró számlák:");
        debug(std::cout, it->pendingInvoices.size());
        debug(std::cout, "\n");
        //Ne felejtsük el az előre bejelentett adatot törölni, hogy a bezáráskor törlődjön a rendszerből.
        it->announcement.Reset();
    } // minden egyes ügyfél blokk
}

Client& Controller::getClient(size_t id){
    if(id>clients.size()){
        throw std::out_of_range("Indexelési hiba!");
    }
    return clients[(id-1)];
}

size_t Controller::clientsCount(){
    return this->clients.size();
}


void Controller::announceConsumption(Client&c,int emVal, Date& d){
    if(c.announcement.get_EM_val()==-1){
        c.announcement=Consumption_announcement(d,emVal);
    }
    
}