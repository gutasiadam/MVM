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


void add_newClient(){
	// Kérje be a szükséges adatokat...
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
		system("CLEAR");
		int id;
		switch(option){
			case 1:
				std::cout << "=== Új Ügyfél felvétele ===" << std::endl;
				add_newClient();
				break;
			case 2:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				std::cout << "> "; std::cin >> id;
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
				// addClientFunds()
				break;
			case 4:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				id=0;
				std::cout << "> "; std::cin >> id;
				std::cout << "Fogyasztás bejelentése - " << Ctrl.getClient(id-1).getId() << std::endl;
				int emVal;
				std::cout << "Mérőóra állása: " << std::endl;
				std::cout << "> "; std::cin >> emVal;
				// Fogyasztás bejelentés...
				Ctrl.getClient(id).announcement=Consumption_announcement(Date(2022,5,8),emVal);
				break;
			case 5:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				id=0;
				std::cout << "> "; std::cin >> id;
				std::cout << "Tartozás ellenőrzése - " << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << std::endl;
				std::cout << "WIP";
				break;
			case 7:
				goto exit;
				break;
			default:
				std::cout << "Ismeretlen parancs." << std::endl;
		}
		
	}
	exit: 
	///Perzisztencia - adatok kimentése az eredeti fájljaikba.
	Ctrl.saveData("TSTClientdata.txt", "TSTInvoices_archived.txt", "TSTInvoices_pending.txt");
	log.close();


	return 0;
}