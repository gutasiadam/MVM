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
	UNIT TEST
	Gutási Ádám
	Budapesti Műszaki és Gazdaságtudományi Egyetem
	Programozás Alapjai II.
	2022.
*/

/**
 * @file main.cpp
 * @author Gutási Ádám
 * @brief 	Ez a fájl a MVM projekt unit testje.
  A tesztelés a gtest_lite könyvtárral történik.

  Szúrópróbaszerű adatellenőrzések történnek, tömbhosszak összevetése az elvárt eredményekkel, stb.
 * @date 2022-05-15
 * 
 */

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Controller.h"
#include <fstream>

#include "gtest_lite.h"
#include "memtrace.h"

using std::cout;
using std::endl;
int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.setf(std::ios::showpoint);
    std::cout.precision(2);
    Date todayDate(2020,12,31); // A modell szerinti nap, 2020.12.31.
    Controller Ctrl; Ctrl.loadData("Clientdata.txt", "Invoices_archived.txt", "Invoices_pending.txt","Tariffs.txt","Consumption_announcements.txt");
    Client& dummy_1 = Ctrl.getClient(16); // --> Biro Benedek, Budapest, 16 A
    
    //Legutolsó bennlevő felhasználó.
    Client& dummy_2 = Ctrl.getClient(30); //--> Hegedüs Noel, Budapest, 63 A
  
    TEST(Init, FilesLoaded_Client){
      //véletlenszerű adatelérés, az ügyfél adatainak betölésének ellenőrzésére.
      EXPECT_EQ((size_t)30,Ctrl.clientsCount());
      EXPECT_TRUE(0==strcmp("Biro",dummy_1.getlastName().c_str()));
      EXPECT_TRUE(0==strcmp("Benedek",dummy_1.getfirstName().c_str()));
      EXPECT_TRUE(0==strcmp("Budapest",dummy_1.getAddress().getTown().c_str()));
      EXPECT_EQ(32,dummy_1.getStrength());

      EXPECT_TRUE(0==strcmp("Hegedüs",dummy_2.getlastName().c_str()));
      EXPECT_TRUE(0==strcmp("Noel",dummy_2.getfirstName().c_str()));
      EXPECT_TRUE(0==strcmp("Budapest",dummy_2.getAddress().getTown().c_str()));
      EXPECT_EQ(32,dummy_1.getStrength());

      
    }END
    

    TEST(Clients, Invoices_pending){
      // Varga Henretta befizetésre váró számláinak száma.
      Client& dummy_3 = Ctrl.getClient(20); 
      // még nem történt számlázás, de már el van egy fizetendő számlája - elmaradása van
      EXPECT_EQ((size_t)1, dummy_3.pendingInvoices.size());
      EXPECT_EQ(5000,dummy_3.getBalance());;
      // Tartozása: 149400 ft

      //144400 Ft-al épp ki tudná fizetni a tartozását, és kinullázódna.

      dummy_3.addFunds(144400); // Amint befizetett, megpróbálja teljesíteni a rendszer a tartozását.
      dummy_3.pay_Pending_Invoices();
      // Utána még nézzük meg, hogy fogyott-e a pénz.
      EXPECT_EQ(0,dummy_3.getBalance());
      EXPECT_EQ((size_t)0,dummy_3.pendingInvoices.size()); // 0 tartozással zárul
    }END

    TEST(Tariff, Invoices_created_from_tariffs){ 
      //Létrejönnek-e helyesen a számlák, a tarifa számolás után?
      Ctrl.create_Invoices(todayDate);
      //Tesztek a lértejött számlák vizsgálatához..
      EXPECT_EQ(196600.00,Ctrl.getClient(15).getDebtval());
      EXPECT_EQ(143600.00,Ctrl.getClient(7).getDebtval()); // Neki a rendszer sámolt a régebbi számlái alapján
    }END

    

    TEST(Clients, add_consumption_announcement_test){
      // Fogyasztási bejelentés tesztelése
      // Jelentse be az 5-ös id-jű egy bejelentést
      Client& dummy_3 = Ctrl.getClient(5); //Fabian Szervac bejelent új fogyasztást.
      //Bejelentés előtt -1-en kell állnia a bejelentésének.

      EXPECT_EQ(dummy_3.announcement.get_EM_val(),-1);

      // Archive szerinti legutolsó óraállás: 7601
      // 340kWh fizetése - 7941-en kell állnia a bejelentett állásnak.
      Ctrl.announceConsumption(dummy_3, 7941,todayDate);
      EXPECT_FALSE(dummy_3.announcement.get_EM_val()==-1);
      EXPECT_TRUE(dummy_3.announcement.get_EM_val()==7941);
      Ctrl.getClient(5).announcement.Reset(); //reset
      EXPECT_TRUE(dummy_3.announcement.get_EM_val()==-1);
    }END

    
///TODO: Tariff_calc szivárog valahol
    TEST(Tariff, Tariff_calc){
      //Tarifa számítási módjának tesztelése
      Date dummy_2_date_test(2020,12,4);
      // 382kWh-t fogyasztottunk. adjuk hozzá dummy_2-höz. 
      // Régi óraállás: 5774
      // Új óraállás: 6156
      Consumption_announcement dummy_2_cAnnounce(dummy_2_date_test,6156);

      std::cout << "dummy2 balance: " << dummy_2.getBalance();

      Invoice dummy2_invoice(dummy_2_date_test,dummy_2_cAnnounce,382);
      Ctrl.getClient(30).pendingInvoices.add(dummy2_invoice);

      (Ctrl.getClient(30).pendingInvoices.end()-1)->set_toBePaid(
        Ctrl.calculate_toBePaid(Ctrl.getClient(30)));
      double dummy2_testagainstVal=297831.72; // számítási képlet alapján.

      
      double val=(Ctrl.getClient(30).pendingInvoices.end()-1)->get_toBePaid();

      //std::cout << "val: " << val-dummy2_testagainstVal;
      EXPECT_EQ((int)dummy2_testagainstVal,(int)val);
    }END

    TEST(Invoices, create_with_avg_invoice){
      // Átlag alapján számított számla tesztelése
    }ENDM

    TEST(Operators, operator_eq_test){ // operator== dátum teszt
      Date dummy_1_date_test(2000,12,15);
      EXPECT_TRUE(dummy_1_date_test==dummy_1.getDate()); // Date == operator test
      EXPECT_EQ(dummy_1_date_test,dummy_1.getDate());
    }END

    TEST(Operators, operator_greater_than test){ // kisebb/nagyobb mint operátor tesztelése
      Date dummy_1_date_test(1999,8,9);
      Date dummy_2_date_test(1999,8,10);
      Date dummy_3_date_test(1999,10,9);
      Date dummy_4_date_test(2000,8,9);
      EXPECT_FALSE(dummy_2_date_test<dummy_1_date_test);
      EXPECT_TRUE(dummy_2_date_test>dummy_1_date_test);

      EXPECT_FALSE(dummy_3_date_test<dummy_1_date_test);
      EXPECT_TRUE(dummy_3_date_test>dummy_1_date_test);

      EXPECT_FALSE(dummy_4_date_test<dummy_1_date_test);
      EXPECT_TRUE(dummy_4_date_test>dummy_1_date_test);
    }END
    
    TEST(Clients, addNewClient){
      // Új Ügyfél hozzáadásának tesztelése
      // Teszteljük, hogy növekedik e az Ügyfeleket tároló Array, nézzük meg a nevet, stb..
      size_t initialClientsSize=Ctrl.clientsCount();

      Date dummy_1_date_test(1943,8,9);
      Address dummy_1_Address_test("Budapest", "Almafa utca",5,23);
      Client addNewClient_dummy_1(31,"Teszt","Elek",dummy_1_date_test,dummy_1_Address_test,"06209145771","info@tesztelek.hu","7963370-5-65",0,2,32);
      addNewClient_dummy_1.addFunds(101.11); // Kezdőegenlege 101.11 Ft.
      Ctrl.newClient(addNewClient_dummy_1);

      size_t sizeAfterAdd=Ctrl.clientsCount();
      EXPECT_FALSE(initialClientsSize==sizeAfterAdd); // Ekkor tehát hozzáadás történt.
    }END

    

    

  GTEND(std::cerr);       // Csak C(J)PORTA működéséhez kell
  return 0;

  /*
  gtest_lite.h fájlból átvett komment, ez alapján készülnek a tesztek.
   ...
   // Fatális hiba esetén a teszteset nem fut tovább. Ezek az ASSERT... makrók.
   // Nem lehet a kiírásukhoz további üzenetet fűzni. PL:
     TEST(TeszEsetNeve, TesztNeve)
       ASSERT_NO_THROW(f(0));  // itt nem lehet << "duma"
       EXPECT_EQ(4, f(2)) << "A függvény hibás eredményt adott" << std::endl;
       ...
     END
    ...
    */
  return 0;
}
