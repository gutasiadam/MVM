#include "Invoice.h"

double Invoice::get_toBePaid() const {return toBePaid;}
int Invoice::getConsumptionAmt() const{ return consumptionAmt;};

Date& Invoice::getCreated(){return created;}
Consumption_announcement& Invoice::getCAnn(){return announcement;};

bool Invoice::operator==(Invoice& rhs){
	return ((created==rhs.getCreated()) && (announcement==rhs.getCAnn()));
}
