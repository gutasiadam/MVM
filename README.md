
# MVM
**A Programozás Alapjai 2. - NHF**
*Feladatkiírás:*
Tervezze meg a  **Meseországi Villamos Művek (MVM)**  nyilvántartási rendszerének egyszerűsített objektummodelljét, majd valósítsa azt meg! A rendszerrel minimum a következő műveleteket kívánjuk elvégezni:

-   ügyfél adatinak felvétele
-   szolgáltatási szerződés kötése
-   szolgáltatási díj előírása (számlázás) (becsült átlagos fogyasztás)
-   szolgáltatási díj befizetése
-   egyenleg lekérdezése
-   fogyasztás bejelentése

A rendszer lehet bővebb funkcionalitású, ezért nagyon fontos, hogy jól határozza meg az objektumokat és azok felelősségét.  
Demonstrálja a működést külön modulként fordított tesztprogrammal!  A megoldáshoz  **ne**  használjon STL tárolót!
## Előrehaladás a részfeldatokban
 - [x] NHF 1. - specifikáció: Pontosított feladatspecifikáció elkészítése és feltöltése PDF formátumban. A pontosított specifikáció részletesen leírja feladatot. Megadja a bemenetek és az elvárt kimenetek tartalmát és formátumát, a program működésének feltételeit, valamint rögzít minden olyan körülményt, ami egyértelműsíti a feladatot. A specifikáció a megoldásra fekete dobozként tekint, azaz a program belső felépítésével, működésével nem foglalkozik.
 - [x] NHF 2. - terv: Osztálydiagram és/vagy algoritmus elkészítése és bemutatása. A részfeladat teljesítéséhez egyetlen PDF fájlba szerkesztve kell beadnia a pontosított feladatspecifikációt és a feladat megoldásához tervezett osztályok kapcsolatát és attribútumait bemutató osztálydiagramot. Feladat jellegétől függően ezt ki kell egészítenie a fontosabb algoritmusok leírásával. Az osztálydiagramot UML jelöléssel, az algoritmust tetszőleges (szöveges, folyamatábra, pszeudokód, …) kell megadnia.
 - [x] NHF 3. - váz: Véglegesített osztályok deklarációjának illetve a főbb algoritmusok elkészítése és bemutatása. A részfeladat ellenőrzéséhez fel kell tölteni a JPorta rendszerbe olyan nem végleges tesztprogramot, ami a megtervezett osztályokat használva bemutatja azok kapcsolatát, együttműködését. A feltöltött forráskódnak szintaktikailag helyesnek kell lennie, de nem kell érdemben működnie. A JPorta rendszer csak a fordítást ellenőrzi, a futás eredményét nem, így a (tag)függvények törzse teljesen hiányozhat! E határidőt akkor tudja megfelelően teljesíteni, ha az osztályokat már olyan részletesen megtervezte, hogy a deklarációk a tervek alapján könnyen leírhatók.
 - [ ] NHF 4. - végleges: A feltöltött programot a feladatbeadó rendszer lefordítja és összeszerkeszti. Feltételezheti, hogy a fordítás során a CPORTA és MEMTRACE azonosítók definiáltak. A feladat csak akkor elfogadható, ha a fordítás és szerkesztés eredményeként hiba- és figyelmeztető üzenet nem keletkezik! Sikeres fordítás után a rendszer lefuttatja a programot a megadott tesztadatokkal. Sikeres elektronikus beadás után a dokumentációt és a működő programot a laborvezetőnek személyesen is be kell mutatni a tárgykövetelményben megadott határidőig.

## Külső könyvtárak

 - [gtest_lite](https://git.ik.bme.hu/Prog2/ell_feladat/CppMonoton/blob/master/gtest_lite.h)
 - [memtrace](https://git.ik.bme.hu/Prog2/ell_feladat/Nem_OO/blob/master/memtrace.h)

# Fogyasztás

A fogyasztás számításának képlete a következő:
	log2(Főbiztosíték erőssége)*tarifa*fogyasztás

# Tesztadatok
A Teszt szövegfájlok adatai 2020. decemberét szimulálják. A következő számlázási időszak tehát 2020. 12. 31-én zárul. Eddig a dátumig a 2020. 12. 01-ig fogyasztott áram mennyiségét kell bejelenteni.
Ez azt jelenti, hogy az ügyfeleknek eddig kell bejelenteniük a havi fogyasztásukat.

Az átláthatóbb és egyszerűbb tesztelés érdekében az Archvált számlák a 2020. januári számlázási időszakig nyúlnak vissza. Így a legkorábbi számlák januáriak.
## Clientdata.txt

Az ügyfelek sample adatbázisban a következő mezők találhatóak tabulátorral elválasztva, ebben a sorrendben:

**ID**, **Keresztnév**, **Vezetéknév**, **Adószám**, **Város**, **Utca**, **Házszám**, (lakásszám), **telefonszám**, **e-mail cím**, **ügyfél típusa**, **születési év**, **hónap**, **nap**, **fázisok száma**, **főbiztosíték** áramerőssége (A).

## Invoices_archived.txt

Ez a fájl tartalmazza a már teljesített számlákhoz kapcsolódó adatokat, ezzel biztosítva ezen adatok perzisztenciáját.

Adatmezői a következők:
**ID**(Ügyfél azonosítója), **Számla létrejöttének dátuma (Év	Hónap	Nap)** ,**consumptionAmt** (fogyasztás mennyiságe), **toBePaid** (fizetendő).

## Consumption_announcements.txt

Ez a fájl tartalmazza a következő számlázási időszakig bejelentett fogyasztásokat.
A szövegájl egy sor a következőkat tartalmazza:
**Ügyfélazonosító ID**	**bejelentés dátuma (Év	Hónap	Nap)**	**Óraállás**

A mellékelt sample fájlból látható, hogy a(z) *5*, *7*, *13*,*22*, *24*, *25* számú ID-vel rendelkező Ügyfelek nem jelentették be fogyasztásukat, így ők a régebbi fogyasztásaik átlaga alapján kapnak majd számlát.

## Tariffs.txt

Ez a fájl tarifákat tartalmaz, melyek alapján a rendszer a díjakat tudja számolni. 
Ezen díjak több változótól is függenek, mint pldául a fázisok számától, az ügyfél típusától, és a főbiztosíték erősségétől.

Elrendezése a következő: *(x jelzi azokat a cellákat, amik érvénytelenek (pl. nem létezik vállalati, 2 fázisú, 16 Amperes csomag.)*
|Ügyfél típusa / fázisok száma|16 A|32 A|63 A|128 A|
|--|--|--|--|--|
|Lakossági, 2 fázis| | |x|x|
|Vállalati, 2 fázis|x| | | |
|Vállalati, 3 fázis|x| | | |

### Figyelmeztetés

! A tesztadatok véletlenszerű névgenerátor oldalak segítségével, mint például a[random-name-generator.com](https://www.random-name-generator.com/hungary?gender=&n=10&s=57094) lettek létrehozva. Esetleges egyezés véletlen történt. Amennyiben a neve szerepel a listán és változtatást szeretne kérni, kérem, keressen fel!

! Az adószámok egy egyszerű random szám generátorral lettek elkészítve, esetleges egyezés a véletlen következtében történt.
