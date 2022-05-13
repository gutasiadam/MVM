/**
 *
 * \file string5.cpp
 *
 */


#include <iostream>
#include <cstring>

////#include "memtrace.h"           // include a standard headerek után
#include "String.h"

    String::String(size_t siz){
        len=siz;
        pData= new char[siz+1];
        pData[0]='\0';
    }

    String::String(char c){
        len=1;
        pData= new char[len+1];
        pData[0]=c;
        pData[1]='\0';
    }

    String::String(const char* c){
        len=strlen(c);
        pData= new char[len+1];
        strcpy(pData,c);
    }
/// Másoló konstruktor: String-ből készít (createString)
String::String(const String& a){
    len = a.len;
    pData=0;
    if(a.pData!=NULL){
      pData = new char[len+1];
      strcpy(pData, a.pData);
  }
        
}

/// Destruktor (disposeString)
    /* String::~String(){
        delete[] pData;
    }*/

/// operator=
String& String::operator=(const String& a){
        if (this != &a) {
        delete[] pData;
        len = a.len;
        pData = new char[len+1];
        strcpy(pData, a.pData);
    }
    return *this;
    }

String String::operator+(const String& rhs_s) const{
    String tmp(this->len+rhs_s.size());
    strcpy(tmp.pData,this->pData);
    strcat(tmp.pData,rhs_s.pData);
    tmp.pData[tmp.len]='\0';

    return tmp;
}
/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!


/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
///                 String-hez String-et ad (addString)
/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& os, const String s){
    os << s.c_str();
    return os;
}

/// >> operátor, ami beolvas az istream-ről egy szót

