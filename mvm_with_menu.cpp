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

#include "Controller.h"
#include <iostream>
#include <fstream>

void add_newClient(){
	// Kérje be a szükséges adatokat...
}

int main(void){
	std::cout << "Meseországi Villamos Művek" << std::endl;
	//Menü, amíg ki nem lép a felhasználó
	std::ofstream log("log.log");
	/**
	 * NHF 3- skeletonnál egyelőre nem kell helyesen működjön..
	 * log << "Adatok betöltése folyamatban.." << std::endl;
	 * Controller Ctrl("Clientdata.txt", "Invoices.txt");// (Clientdata.txt, Invoices.txt)...
	 * log << "Betöltés kész." << std::endl;
	 */
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
		switch(option){
			case 1:
				add_newClient();
				std::cout << "Uf" << std::endl;
				break;
			case 2:
				std::cout << "Egyenlegle" << std::endl;
				// Egyenleg lekérdezése..
				// getClientFunds()
				break;
			case 3:
				std::cout << "Egyenlegfel" << std::endl;
				// Egyenleg feltölése...
				// addClientFunds()
				break;
			case 4:
				std::cout << "Fogyasztasbe" << std::endl;
				// Fogyasztás bejelentés...
				// consumptionAnnouncement();
				break;
			case 5:
				std::cout << "Szamlazas" << std::endl;
				//Számlázás...
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