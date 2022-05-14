#include "Consumption_announcement.h"
Date& Consumption_announcement::getDate(){
	return date;
}
int Consumption_announcement::get_EM_val(){
	return electricMeterVal;
}

bool Consumption_announcement::operator==(Consumption_announcement& rhs){
	return(getDate()==rhs.getDate()) && (electricMeterVal==rhs.get_EM_val());
}