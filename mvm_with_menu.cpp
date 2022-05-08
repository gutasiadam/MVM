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
	 log << "Adatok betöltése folyamatban.." << std::endl;
	 Controller Ctrl; Ctrl.loadData("Clientdata.txt", "Invoices.txt");// (Clientdata.txt, Invoices.txt)...)
	 log << "Betöltés kész." << std::endl;
	while(true){
		int option=0;
		std::cout << "== Ügyfelek ügykörei ==" << std::endl;
		std::cout << "[1] - Új ügyfél felvétele" << std::endl;
		std::cout << "[2] - Egyenleg lekérdezése" << std::endl;
		std::cout << "[3] - Egyenleg feltöltése" << std::endl;
		std::cout << "[4] - Fogyasztás bejelentése" << std::endl;
		std::cout << "== MVM ügykörei ==" << std::endl;
		std::cout << "[5] - Számlázási időszak lezárása és számlázás" << std::endl;
		std::cout << "== Rendszer ==" << std::endl;
		std::cout << "[6] - Kilépés" << std::endl;
		std::cout << "> "; std::cin >> option;
		system("CLEAR");
		int id;
		switch(option){
			case 1:
				std::cout << "=== Új Ügyfél felvétele ===" << std::endl;
				add_newClient();
				std::cout << "Uf" << std::endl;
				break;
			case 2:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				std::cout << "> "; std::cin >> id;
				// Egyenleg lekérdezése..
				std::cout<< "("  << id << ") egyenlege: "<< Ctrl.getClient(id).getBalance() << ".- " << std::endl;
				char buf; std::cin >> buf;
				break;
			case 3:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				double val;
				std::cout << "> "; std::cin >> id;
				std::cout << "Összeg: "; std::cin >> val;
				Ctrl.getClient(id).addFunds(val);
				std::cout<< "("  << id << ") új egyenlege: "<< Ctrl.getClient(id).getBalance() << ".- " << std::endl;
				system("CLEAR");
				// addClientFunds()
				break;
			case 4:
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				std::cout << "> "; std::cin >> id;
				std::cout << "Fogyasztás bejelentése - " << Ctrl.getClient(id).getId() << std::endl;
				int emVal;
				std::cout << "Mérőóra állása: " << std::endl;
				std::cout << "> "; std::cin >> emVal;
				// Fogyasztás bejelentés...
				Ctrl.getClient(id).announcement=Consumption_announcement(Date(2022,5,8),emVal);
				break;
			case 5:
				std::cout << "bzzzzzzz" << std::endl;
				std::cout << "todo: csináld meg" << std::endl;
				//batch_generateInvoices()
				break;
			case 6:
				goto exit;
				break;
		}
		
	}
	exit: log.close();

	return 0;
}