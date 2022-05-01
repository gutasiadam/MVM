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
	Meseországi Villamos Művek
	Gutási Ádám
	Budapesti Műszaki és Gazdaságtudományi Egyetem
	Programozás Alapjai II.
	2022.

	fájl: mvm_with_menu.cpp

 * */

#include "Controller.h"
#include <iostream>

int main(void){
	//Betöltéskor MVM logo kirajzolása
	std::cout << "Meseországi Villamos Művek" << std::endl;
	//Menü, amíg nem lép ki a felhasználó
	Controller c;// (Clientdata.txt, Invoices.txt)...
	while(true){
		int option=0;
		std::cout << "== Ugyfelek ugykorei ==" << std::endl;
		std::cout << "[1] - Uj ugyfel felvetele" << std::endl;
		std::cout << "[2] - Egyenleg lekerdezese" << std::endl;
		std::cout << "[3] - Egyenleg feltoltese" << std::endl;
		std::cout << "[4] - Fogyasztas bejelentese" << std::endl;
		std::cout << "== MVM ugykorei ==" << std::endl;
		std::cout << "[5] - Szamlazas" << std::endl;
		std::cout << "== Rendszer ==" << std::endl;
		std::cout << "[6] - Kilepes" << std::endl;
		std::cout << "> "; std::cin >> option;
		system("CLEAR");
		switch(option){
			case 1:
				std::cout << "Uf" << std::endl;
				// Ügyfél felvétele...
				//add_newClient();
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
	exit: ;

	return 0;
}