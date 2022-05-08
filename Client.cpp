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

String Client::getName() const{
	return Name;
}

Address Client::getAddress() const{
	return resAddress;
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

void Client::modify_electricMeter(int amt){
	electricMeter_last+=amt;
}