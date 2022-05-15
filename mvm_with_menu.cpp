/*
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
	CLI version
	Gutási Ádám
	Budapesti Műszaki és Gazdaságtudományi Egyetem
	Programozás Alapjai II.
	2022.
 */

/**
 * @file mvm_with_menu.cpp
 * @author Gutási Ádám
 * @brief Ez a fájl a parancssori, végfelhasználói verzió. 
	A felhasználó egy menün keresztül tudja vezérelni a programot, 
	adatokat pedig a terminálon keresztül tud bevinni.

	A Debug információ a DEBUG makró befiniálásával kapcsolható be.
 * @date 2022-05-15
 * 
 * 
 */

#include <iostream>
#include <fstream>

#include "Controller.h"
#include "Array.hpp"
#include "memtrace.h"


void add_newClient(Controller& Ctrl, int incr){
	// Kérje be a szükséges adatokat...
	std:: cout << "!- Az adatokat ékezet nélkül kell beírni -!" << std::endl;
	int bal=0;
	std::cout << " Kezőegyenleg: "; std::cin >> bal;
	char firstName[51]; char lastName[51];
	std::cout << " Vezetéknév: "; std::cin >> lastName;
	std::cout << " Keresztnév: "; std::cin >> firstName;
	char mobileNum[21];
	std::cout << " Telefonszám: "; std::cin >> mobileNum;
	char e_mail[51];
	std::cout << " E-mail cím: "; std::cin >> e_mail;
    char City[31];
	std::cout << " Város: "; std::cin >> City;
	char street[101];
	std::cout << " Utca (csak a neve)"; std::cin >> street;
	int houseNum;
	std::cout << " Házszám: "; std::cin >> houseNum;
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
	tmpClient.addFunds(bal); // Kezdőegyenleg hozzáadása.
	Ctrl.newClient(tmpClient);
}


int main(void){
	std::cout.setf(std::ios::fixed);
	std::cout.setf(std::ios::showpoint);
	std::cout.precision(2);
	Date todayDate(2020,12,31); //A példában éppen a novemberi időszakot zárjuk.
	std::cout << "Meseországi Villamos Művek" << std::endl;
	//Menü, amíg ki nem lép a felhasználó
	Controller Ctrl; Ctrl.loadData("Clientdata.txt", "Invoices_archived.txt", "Invoices_pending.txt","Tariffs.txt","Consumption_announcements.txt");
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
		//system("CLEAR"); // A JPORTára úgyis a unit etestes verzió kerül feltölésre.
		int id;
		switch(option){
			case 1:
				std::cout << "=== Új Ügyfél felvétele ===" << std::endl;
				add_newClient(Ctrl,Ctrl.clientsCount()+1);
				break;
			case 2:
				try
				{
					std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
					std::cout << "> "; std::cin >> id;
					std::cout << Ctrl.getClient(id);
					// Egyenleg lekérdezése..
					std::cout << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << " ("  << id << ") egyenlege: "<< Ctrl.getClient(id).getBalance() << ".- " << std::endl;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
				
				break;
			case 3:
				try{
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				double val;
				std::cout << "> "; std::cin >> id;
				std::cout << "Egyenleg feltöltése " << Ctrl.getClient(id).getlastName() << " " << Ctrl.getClient(id).getfirstName() << "Számára." << std::endl;
				std::cout << "Összeg: "; std::cin >> val;
				Ctrl.getClient(id).addFunds(val);
				std::cout << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << " ("  << id << ") új egyenlege: "<< Ctrl.getClient(id).getBalance() << ".- " << std::endl;
				Ctrl.getClient(id).pay_Pending_Invoices(); // Próbáljuk meg befizettetni a tartoásokat.
				}catch(const std::exception& e){
					std::cerr << e.what() << '\n';
				}
				break;
			case 4:
				try{
				std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
				
				id=0;
				std::cout << "> "; std::cin >> id;
				if(Ctrl.getClient(id).announcement.get_EM_val()!=-1){
					std::cout << "⛔️ Erre az időszakra már bejelntett óraállást!" << std::endl;
					break;
				}
				std::cout << "Fogyasztás bejelentése - " << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << std::endl;
				int emVal;
				std::cout << "Legutóbbi állás: " << Ctrl.getClient(id).getElectricMeterVal() << std::endl;
				std::cout << "Mérőóra állása: " << std::endl;
				std::cout << "> "; std::cin >> emVal;
				// Fogyasztás bejelentés...
				Ctrl.getClient(id).announcement=Consumption_announcement(todayDate,emVal);
				}catch(const std::exception& e){
					std::cerr << e.what() << '\n';
				}
				break;
			case 5:
				try{
					std::cout << "Ügyfél azonosítója (id) ?" << std::endl;
					id=0;
					std::cout << "> "; std::cin >> id;
					std::cout << Ctrl.getClient(id).getlastName() << Ctrl.getClient(id).getfirstName() << std::endl;
					std::cout << "Befizetésre váró számlák száma: " << Ctrl.getClient(id).pendingInvoices.size() << " | " << Ctrl.getClient(id).getDebtval() << " .-" << std::endl;
				}catch(const std::out_of_range& e){
					std::cerr << e.what() << '\n';
				}
				
				break;
			case 6:
				try{
					std::cout << " A számlázási időszak lezárul. Számlák kiírása" << std::endl;
					Ctrl.create_Invoices(todayDate);
				}catch(const std::exception& e){
					std::cerr << e.what() << '\n';
				}
				break;
			case 7:
				goto exit;
				break;
			default:
				std::cout << "Ismeretlen parancs." << std::endl;
		}
		
	}
	exit: 
	//Perzisztencia - adatok kimentése az eredeti fájljaikba.

	Ctrl.saveData("Clientdata.txt", "Invoices_archived.txt", "Invoices_pending.txt","Consumption_announcements.txt");


	return 0;
}
