/**
 * \file Controller.h
 *
 * Egyszerű program az iterátoros generikus tömb kipróbálásához.
 * NHF 3:  A következőre fordul: g++    -pedantic -Wall -Werror -std=c++11  -ggdb    -c -o main.o main.cpp
 * Linkelés a -c kapcsolóval: g++    -ggdb  main.o   -o mvm_test -c  
 */

#define ELKESZULT 20

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Controller.h"
#include <fstream>

#include "gtest_lite.h"

using std::cout;
using std::endl;
int main() {
    std::cout << "Begin testing";
    Controller c; // fájlok neve ide..
    Client& dummy_1 = c.getClient(16);
    Client& dummy_2 = c.getClient(25); // -> még nem használt változó
  
    TEST(Init, FilesLoaded_Client){
      //véletlenszerű adatelérés, az ügyfél adatainak betölésének ellenőrzésére.
      EXPECT_EQ("Benedek",dummy_1.getName().c_str());
      EXPECT_EQ("Jakab",dummy_2.getName().c_str());
    }END
    

    TEST(Init, FilesLoaded_Invoices){
      Client& dummy_3 = c.getClient(20); // Varga Henretta befizetésre váró számláinak száma.
      EXPECT_EQ(2, dummy_3.pendingInvoices.size());  // Ez 2 lesz majd, tehát el lesz maradva egy hónappal (Invoices_pending fájlban van rekordja.)
      EXPECT_EQ(1, dummy_2.pendingInvoices.size());
    }END

    TEST(Clients, addNewClient){
      // Új Ügyfél hozzáadásának tesztelése...
      // Teszteljük, hogy növekedik e az Ügyfeleket tároló Array, nézzük meg a nevet, stb..
      Date dummy_1_date_test(1943,8,9);
      Address dummy_1_Address_test("Budapest", "Almafa utca",5);
      Client addNewClient_dummy_1(31,"Teszt Elek",dummy_1_date_test,dummy_1_Address_test,"06209145771","info@tesztelek.hu","7963370-5-65",0,2,32);
      c.newClient(addNewClient_dummy_1);
    }END

    TEST(Clients, addfundsTest){
      // Egyenleg feltölésének tesztelése
      Client& dummy_3 = c.getClient(20); // Varga Henretta befizet összeget.
      dummy_3.addFunds(50000.5); // Amint befizetett, megpróbálja teljesíteni a rendszer a tartozását.
      // Utána még nézzük meg, hogy fogyott-e a pénz, **ehhez kell még tesztadat**!
    }END

    TEST(Clients, add_consumption_announcement_test){
      // Fogyasztási bejelentés tesztelése
      // Jelentse be mondjuk a 3-as id jű Ügyfél a fogyasztását!
      Client& dummy_3 = c.getClient(20); // Varga Henretta bejelent új fogyasztást.
      c.announceConsumption(dummy_3, 340);
      c.getClient(3);
    }ENDM

    TEST(Invoices, create_with_avg_invoice){
      // Átlag alapján számított számla tesztelése
      // ! Legyen teszt akkor is, hogy mi van, ha új ügyfélt veszük fel, akinek nincsenek régebbi számlái, és ekkor kell átlagot számolnunk - > ezesetben const char* kivételt várunk !
    }ENDM

    TEST(Operators, operator_eq_tests){ // operator== tesztek
      Address tstaddr_1("Budapest", "Márton lejtő", 72);
      EXPECT_EQ(tstaddr_1, dummy_1.getAddress()); // Address == operator test
      
      Date dummy_1_date_test(1943,8,9);
      EXPECT_EQ(dummy_1_date_test,dummy_1.getDate()); // Date == operator test
    }ENDM

    TEST(OPerators, operator_greater_than test){ // kisebb/nagyobb mint operátor tesztelése
      Date dummy_1_date_test(1999,8,9);
      Date dummy_2_date_test(1999,10,9);
      EXPECT_FALSE(dummy_2_date_test<dummy_1_date_test);
      EXPECT_TRUE(dummy_2_date_test>dummy_1_date_test);
    }ENDM

    TEST(Tariff, Tariff_calc){
      //Tarifa számítási módjának tesztelése
      Date dummy_1_date_test(2020,12,04);
      Consumption_announcement dummy_1_cAnnounce(dummy_1_date_test,382);
      Invoice dummy1_invoice(dummy_1_date_test,dummy_1_cAnnounce);
      dummy1_invoice.calculate_toBePaid(c.getTariffs());
      double dummy1_testagainstVal=9999999.99;
      EXPECT_EQ(dummy1_testagainstVal,dummy1_invoice.get_toBePaid()); // TODO: 999999.99 helyére konkrét szám kell jöjjön, ezt még ki kell számolni.
    }ENDM

    TEST(Tariff, Invoices_created_from_tariffs){ //Létrejönnek-e helyesen a számlák, a tarifa számolás után?
      c.create_invoices();
      //Tesztek a lértejött számlák vizsgálatához..
    }ENDM
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
