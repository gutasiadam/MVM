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
	//TODO

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