#include "Client.h"

double Client::getBalance() const{
	return balance;
}

void Client::addFunds(double moneyVal){
	balance+=moneyVal;
}

int Client::getId() const{
	return id;
}

String Client::getPhoneNumber() const{
	return mobile;
}

Date Client::getDate() const{
	return born;
}

String Client::getfirstName() const{
	return firstName;
}

String Client::getlastName() const{
	return lastName;
}

Address Client::getAddress() const{
	return resAddress;
}

String Client::getEMail() const{
	return e_mail;
}

int Client::getPhases() const{
	return phases;
}

int Client::getStrength() const{
	return strength;
}

bool Client::getType() const{
	return type;
}

String Client::getTN() const{
	return taxNumber;
}

int Client::getElectricMeterVal() const{
	return electricMeter_last;
}

void Client::pay_Pending_Invoices(){
    std::cout << "Fizessük be" << std::endl;
	
    std::cout << "Archivált számlák (db) :" << archivedInvoices.size() << std::endl;
    std::cout << "Befizetésre váró számlák (db) :" << pendingInvoices.size() << std::endl;
    for(Invoice *i=pendingInvoices.begin();i!=pendingInvoices.end();i++){
        if(balance>=i->get_toBePaid()){
            // A számla teljesíthető!
            std::cout << "A számlát sikerült teljesíteni!" << std::endl;
            balance-=i->get_toBePaid();
            // A számlát átmozgatjuk az archiváltak közé.
            archivedInvoices.add(*(i));
            pendingInvoices.del(*(i));
        }else{
            std::cout << "Nincs teljesítésre elegendő fedezet." << std::endl; // Nincs elég fedezet, mivel sorrendben haladunk, a többi számlát meg se nézzük.
            break;
        }
    }
    std::cout << "Befizetésre váró számlák (db) :" << pendingInvoices.size() << std::endl;
    std::cout << "Archivált számlák (db) :" << archivedInvoices.size() << std::endl;

}

Client& Client::operator=(Client& rhs){ // másoló operátor
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

void Client::modify_electricMeter(int amt){
	electricMeter_last+=amt;
}

double Client::getDebtval() const{
    double s=0;
    if(pendingInvoices.size()==0)
        return 0;
    for(size_t i=0;i<=pendingInvoices.size();i++){
        s+=pendingInvoices[i].get_toBePaid();
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, Client& c){
    os << c.getlastName()+' '+c.getfirstName() << " (" << c.getId() << ") " <<
    '\n' << "Egyenleg: " << c.getBalance() <<
    '\n' << c.getAddress().getTown() << ", "<< c.getAddress().getStreet()
	 << " utca " <<
    c.getAddress().getHouse() << " " << c.getAddress().getApartment() <<
    '\n' << "főbiztosíték erőssége:" << c.getStrength() << std::endl;

    return os;
}