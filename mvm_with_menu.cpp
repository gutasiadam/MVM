/**
                                ..       :                   ..       :
                               ,W,     .Et t      .DD.      ,W,     .Et
                              t##,    ,W#t EK:   ,WK.      t##,    ,W#t
                             L###,   j###t E#t  i#D       L###,   j###t
      ____                 .E#j##,  G#fE#t E#t j#f      .E#j##,  G#fE#t
 ____|    \               ;WW; ##,:K#i E#t E#tL#i      ;WW; ##,:K#i E#t
(____|     `._____       j#E.  ##f#W,  E#t E#WW,      j#E.  ##f#W,  E#t
 ____|       _|___     .D#L    ###K:   E#t E#K:     .D#L    ###K:   E#t
(____|     .'         :K#t     ##D.    E#t ED.     :K#t     ##D.    E#t
     |____/            ...     #G      ..  t       ...      #G      .. 
                               j                            j          
	(M)eseországi (V)illamos (M)űvek
	Gutási Ádám
	Budapesti Műszaki és Gazdaságtudományi Egyetem
	Programozás Alapjai II.
	2022.

	CLI főprogram (felhasználói változat)

	fájl: mvm_with_menu.cpp

 * */

#include <iostream>
#include <fstream>

//#include "memtrace.h"
#include "Controller.h"
#include "Array.hpp"

template <typename T>
void debug(std::ostream& os, T message){
    #ifdef DEBUG
        os << msg << std::flush
    #endif DEBUG
}
#define DEBUG 1


Client add_newClient(Controller& Ctrl, int incr){
	// Kérje be a szükséges adatokat...
	/*std::cout << "==== Új Ügyfél ====";
	int bal=0;
	std::cout << " Kezőegyenleg: "; std::cin >> bal;
	char firstName[51]; char lastName[51];
	std::cout << " Vezetéknév: "; std::cin >> lastName;
	std::cout << " Keresztnév: "; std::cin >> firstName;
	char mobileNum[21];
	std::cout << " Telefonszám: "; std::cin >> mobileNum; //TODO: regexes validálás
	char e_mail[51];
	std::cout << " E-mail cím: "; std::cin >> e_mail; //TODO: regexes validálás
    char City[31];
	std::cout << " Város "; std::cin >> e_mail;
    char street[101];
	std::cout << " Utca "; std::cin >> street;
	int houseNum;
	std::cout << " Házszám "; std::cin >> e_mail;
	int aptNum=1;
	std::cout << " Lakás száma (hagyja üresen, ha csak egylakásos a szám) "; std::cin >> e_mail;
	char taxNum[13];
	std::cout << " Adószám "; std::cin >> taxNum;
    bool type;
	std::cout << " Ügyfél típusa (0: lakossági, 1: vállalti) "; std::cin >> type;
    int Y; int M; int D;
	std::cout << " Születési dátum (É H N) "; std::cin >> Y >> M >> D;
    int phases;
	std::cout << " Fázisok száma "; std::cin >> phases;
	int strength;
	std::cout << " Főbiztosíték erőssége  "; std::cin >> strength;*/
	//Létrehozzuk az Ügyfelet, majd eltároljuk
	//Date tmp_born(Y,M,D);
	//String ln(lastName); String fn(firstName);
	//Address tmp_address(String(City),String(street),houseNum,aptNum);
	//Client tmpClient(incr, ln, fn,tmp_born,tmp_address,String(mobileNum),String(e_mail),String(taxNum),type,phases,strength);
	Date tmp_tst_born(2002,11,26);
	Address tmp_address_t("Budapest","Alma",27,1);
	Client tmpClient_t(incr,"Test", "Elek",tmp_tst_born,tmp_address_t,"069245743","jajaj@gmail.com","077732832-0030",0,3,32);
    tmpClient_t.addFunds(400);
	std::cout << "Elfut idáig??";
	return tmpClient_t;
    
}


int main(void){
	std::cout << "Meseországi Villamos Művek" << std::endl;
	//Menü, amíg ki nem lép a felhasználó
	std::ofstream log("log.log");
	// Adatok betöltése a streamről
	 log << "[init] Adatok betöltése folyamatban.." << std::endl;
	 Controller Ctrl; Ctrl.loadData("Clientdata.txt", "Invoices_archived.txt", "Invoices_pending.txt");// (Clientdata.txt, Invoices.txt)...)
	 log << "[init] Betöltés kész." << std::endl;
	while(true){
		int option=0;
		std::cout << "== Ügyfelek ügykörei ==" << std::endl;
		std::cout << "[1] - Új ügyfél felvétele" << std::endl;
		std::cout << "[2] - Egyenleg lekérdezése" << std::endl;
		std::cout << "[3] - Egyenleg feltöltése" << std::endl;
		std::cout << "[4] - Fogyasztás bejelentése" << std::endl;
		std::cout << "[5] - Tartozás ellenőrzése" << std::endl;
		std::cout << "== MVM ügykörei ==" << std::endl;
		std::cout << "[6] - Számlázási időszak lezárása és számlázás" << std::endl;
		std::cout << "== Rendszer ==" << std::endl;
		std::cout << "[7] - Kilépés" << std::endl;
		std::cout << "> "; std::cin >> option;
		system("CLEAR"); // A JPORTára úgyis a unit etestes verzió kerül feltölésre.
		int id;
		switch(option){
			case 1:
				std::cout << "=== Új Ügyfél felvétele ===" << std::endl;
				//TODO: megoldani az elem hozzáadása során keletkező problémát.
				//Ctrl.newClient();
				break;
			case 2:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				std::cout << "> "; std::cin >> id;
				std::cout << Ctrl.getClient(id);
				// Egyenleg lekérdezése..
				std::cout << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << " ("  << id << ") egyenlege: "<< Ctrl.getClient(id).getBalance() << ".- " << std::endl;
				char buf; std::cin >> buf;
				break;
			case 3:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				double val;
				std::cout << "> "; std::cin >> id;
				std::cout << "Egyenleg feltöltése " << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << "Számára." << std::endl;
				std::cout << "Összeg: "; std::cin >> val;
				Ctrl.getClient(id).addFunds(val);
				std::cout << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << " ("  << id << ") új egyenlege: "<< Ctrl.getClient(id).getBalance() << ".- " << std::endl;
				Ctrl.getClient(id).pay_Pending_Invoices(); // Próbáljuk meg befizettetni a tartoásokat.
				break;
			case 4:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				id=0;
				std::cout << "> "; std::cin >> id;
				std::cout << "Fogyasztás bejelentése - " << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << std::endl;
				int emVal;
				std::cout << "Mérőóra állása: " << std::endl;
				std::cout << "> "; std::cin >> emVal;
				// Fogyasztás bejelentés...
				Ctrl.getClient(id).announcement=Consumption_announcement(Date(2022,5,13),emVal);
				break;
			case 5:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				id=0;
				std::cout << "> "; std::cin >> id;
				std::cout << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << std::endl;
				std::cout << "Befizetésre váró számlák száma: " << Ctrl.getClient(id).pendingInvoices.size() << " | " << Ctrl.getClient(id).getDebtval() << " .-" << std::endl;
				break;
			case 6:
				std::cout << " A számlázási időszak lezárul. Számlák kiírása" << std::endl;
				/**
				 * Minden egyes kliensre meghívódik:
				 * 	1. Ha van az ügyfélnek fogyasztási bejelentése az időszakra, akkor ez alapján számoljunk!
				 * 	2. Ha nincs, akkor az archivált számlák alapján határozzunk meg egy átlagot, majd ennek vegyük a fogyasztását, 
				 * az órájukat is az átlag szerint toljuk tovább.
				 *	3. Ha nem volt még archivált számlája ( új ügyfél ), akkor kapjon az összes ügyfél ezen számlázási 
				 időszakból vett fogyasztás szerinti átlagát, és ennek az összegéz fizesse.
				 */
			case 7:
				goto exit;
				break;
			default:
				std::cout << "Ismeretlen parancs." << std::endl;
		}
		
	}
	exit: 
	///Perzisztencia - adatok kimentése az eredeti fájljaikba.
	///TODO: Ha teljesen jó a mentés, akkor az igazi fájlnevek használata.
	Ctrl.saveData("TSTClientdata.txt", "TSTInvoices_archived.txt", "TSTInvoices_pending.txt");
	log.close();


	return 0;
}