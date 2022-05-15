/**
 * @file Client.cpp
 * @author Gutási Ádám
 * @brief Ez a fájl tartalmazza a Client osztály deklarációját és inline függvényeit.
 * @date 2022-05-15
 * 
 */
#include "Client.h"

/**
 * @brief Lekérdezi az ügyfél egyenlegét.
 * 
 * @return double 
 */
double Client::getBalance() const{return balance;}

/**
 * @brief Egyenleget ír jóvá az ügyfél számláján.
 * 
 * @param moneyVal 
 */
void Client::addFunds(double moneyVal){balance+=moneyVal;}

/**
 * @brief Lekérdzei az ügyfél azonosítóját.
 * 
 * @return int 
 */
int Client::getId() const{return id;}

/**
 * @brief Lekérdezi az ügyfél telefonszámát.
 * 
 * @return String 
 */
String Client::getPhoneNumber() const{return mobile;}

/**
 * @brief Lekérdezi az ügyfél születési dátumát.
 * 
 * @return Date& a dátum referenciájával tér vissza.
 */
Date& Client::getDate(){return born;}

/**
 * @brief Lekérdezi az ügyfél keresztnevét.
 * 
 * @return String 
 */
String Client::getfirstName() const{return firstName;}

/**
 * @brief Lekérdezi az ügyfél vezetéknevét.
 * 
 * @return String 
 */
String Client::getlastName() const{return lastName;}

/**
 * @brief Lekérdezi az ügyfél lakcímét.
 * 
 * @return Address& 
 */
Address& Client::getAddress(){return resAddress;}

/**
 * @brief Lekérdezi az ügyfél e-mail címét.
 * 
 * @return String 
 */
String Client::getEMail() const{return e_mail;}

/**
 * @brief Lekérdezi a fázisok számát.
 * 
 * @return int 
 */
int Client::getPhases() const{return phases;}

/**
 * @brief Lekérdezi a főbiztosíték áramerősségét.
 * 
 * @return int 
 */
int Client::getStrength() const{return strength;}

/**
 * @brief Lekérdezi az ügyfél típusát
 * 
 * @return true , ha vállalati
 * @return false , ha lakossági
 */
bool Client::getType() const{return type;}

/**
 * @brief 
 * 
 * @return String 
 */
String Client::getTN() const{return taxNumber;}

/**
 * @brief 
 * 
 * @return int 
 */
int Client::getElectricMeterVal() const{return electricMeter_last;}

/**
 * @brief Megpróbálja befizetni a befizetésre váró számlákat.
 * 
 * 1. Kronologikus sorrendben halad, a legrégebbi tartozástól a legújabbig.
 * 2. Addig halad, míg van elegendő fedezet a tartozások teljesítésére.
 * 
 */
void Client::pay_Pending_Invoices(){
    debug(std::cout, "=======================");
    if(pendingInvoices.size()>0){
        debug(std::cout,"Befizetésre váró számlák:"); debug(std::cout, pendingInvoices.size());
        debug(std::cout, "\n");

    //Ebből vesszük, melyik számlát próbáljuk éppen fizetni.
    Array<Invoice> tmp_Invoices=pendingInvoices;

    for(size_t idx=0;idx<tmp_Invoices.size() ; idx++){
        debug(std::cout, "=======================\n *");
        debug(std::cout, tmp_Invoices[idx].get_toBePaid());
        debug(std::cout, " - ");
        if(balance>=tmp_Invoices[idx].get_toBePaid()){
            // A számla teljesíthető!
            debug(std::cout, "🟡 Van elegendő fedezet");
            balance-=tmp_Invoices[idx].get_toBePaid();

            // A számlát átmozgatjuk az archiváltak közé.
            archivedInvoices.add(tmp_Invoices[idx]);
            pendingInvoices.del(tmp_Invoices[idx]);
            debug(std::cout, "\t\t Új egyenleg: ");
            debug(std::cout, balance);
            debug(std::cout, "\n");

        }else{
            debug(std::cout, "🔴 Nincs teljesítésre elegendő fedezet");
            debug(std::cout, "=======================");
            break;
        }
    }
    debug(std::cout, "Befizetésre váró számlák (db) :");
    debug(std::cout, pendingInvoices.size());

    }else{
        debug(std::cout, "🟢 Nincs tartozás.");
        debug(std::cout, "\n");
    }
}

/**
 * @brief Értékadó operátor
 * 
 * @param rhs a másolandó Client obejktum referenciája
 * @return Client& - az új Client objektum referenciája.
 */
Client& Client::operator=(Client& rhs){
    this->id = rhs.getId();
    this->firstName= rhs.getfirstName();
    this->lastName= rhs.getlastName();
    this->born=rhs.getDate();
    this->resAddress=rhs.getAddress();
    this->mobile=rhs.getPhoneNumber();
    this->e_mail=rhs.getEMail();
    this->taxNumber=rhs.getTN();
    this->electricMeter_last=rhs.getElectricMeterVal();
    this->type=rhs.getType();
    this->phases=rhs.getPhases();
    this->strength=rhs.getStrength();
    this->balance=rhs.getBalance();
    this->archivedInvoices=rhs.archivedInvoices;
    this->pendingInvoices=rhs.pendingInvoices;
    this->announcement=rhs.announcement;
    return *this;
}

/**
 * @brief Villanyóra állásának módosítása
 * 
 * @param amt - a mennyiség, amennyivel módosítandó.
 */
void Client::modify_electricMeter(int amt){
	electricMeter_last=amt;
}

/**
 * @brief Tartozás mennyiségének lekérése.
 * 
 *  Összegzi a befizetésre váró számlák fizetendőit.
 * 
 * @return double 
 */
double Client::getDebtval() const{
    double s=0;
    if(pendingInvoices.size()==0)
        return 0;
    for(size_t i=0;i<pendingInvoices.size();i++){
        s+=pendingInvoices[i].get_toBePaid();
    }
    return s;
}


/**
 * @brief stream operátor
 * 
 * @param os - stream
 * @param c - Ügyfél obejmtum referenciája
 * @return std::ostream& - stream
 */
std::ostream& operator<<(std::ostream& os, Client& c){
    os << c.getlastName()+' '+c.getfirstName() << " (" << c.getId() << ") " <<
    '\n' << "Egyenleg: " << c.getBalance() <<
    '\n' << c.getAddress().getTown() << ", "<< c.getAddress().getStreet()
	 << " utca " <<
    c.getAddress().getHouse() << " " << c.getAddress().getApartment() <<
    '\n' << "főbiztosíték erőssége:" << c.getStrength() << std::endl;

    return os;
}
