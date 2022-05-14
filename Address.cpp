#include "Address.h"
////#include "memtrace.h"/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param a0 - Address, amit kiírunk
/// @return os
/*std::ostream& operator<<(std::ostream& os, Address& a){
    os << a.getTown() << ", "<< a.getStreet() << " utca " <<
    a.getHouse() << " " << a.getApartment();
    return os;
}
*/

bool Address::operator==(Address& rhs){
            if(town==rhs.getTown() && street==rhs.getStreet() 
            && house==rhs.getHouse() && apartment==rhs.getApartment()){
                return true;
            }else{
                return false;
            }
}