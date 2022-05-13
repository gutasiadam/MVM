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
#define DEBUG 1

template <typename T>
void debug(std::ostream& os, T message){
    #ifdef DEBUG
        os << message << std::flush;
    #endif //DEBUG makró
}



void add_newClient(Controller& Ctrl, int incr){
	// Kérje be a szükséges adatokat...
	std:: cout << "!- Az adatokat ékezet nélkül kell beírni -!" << std::endl;
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
	std::cout << " Város: "; std::cin >> e_mail;
	char street[101];
	std::cout << " Utca "; std::cin >> street;
	//std::cout << " Utca: "; std::cin >> street;
	int houseNum;
	std::cout << " Házszám: "; std::cin >> std::skipws >> houseNum;
	int aptNum=1;
	std::cout << " Lakás száma (1, ha egylakásos a ház): "; std::cin >> aptNum;
	char taxNum[13];
	std::cout << " Adószám: "; std::cin >> taxNum;
    bool type;
	std::cout << " Ügyfél típusa (0: lakossági | 1: vállalti): "; std::cin >> type;
    int Y; int M; int D;
	std::cout << " Születési dátum (É H N): "; std::cin >> Y >> M >> D;
    int phases;
	std::cout << " Fázisok száma: "; std::cin >> phases;
	int strength;
	std::cout << " Főbiztosíték erőssége: "; std::cin >> strength;
	//Létrehozzuk az Ügyfelet, majd eltároljuk
	Date tmp_born(Y,M,D);
	String ln(lastName); String fn(firstName);
	Address tmp_address(String(City),String(street),houseNum,aptNum);
	Client tmpClient(incr, ln, fn,tmp_born,tmp_address,String(mobileNum),String(e_mail),String(taxNum),type,phases,strength);
	Ctrl.newClient(tmpClient);
}


int main(void){
	Date todayDate(2022,5,13);
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
				add_newClient(Ctrl,Ctrl.clientsCount());
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
				std::cout << "Egyenleg feltöltése " << Ctrl.getClient(id).getlastName() << " " << Ctrl.getClient(id).getfirstName() << "Számára." << std::endl;
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
				Ctrl.create_Invoices(todayDate);
				std::cout << "Hol áll meg???" << std::endl;
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
	Ctrl.saveData("Clientdata.txt", "Invoices_archived.txt", "Invoices_pending.txt");
	log.close();


	return 0;
}
