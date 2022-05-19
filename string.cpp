/**
 * @file String.cpp
 * @author Gutási Ádám
 * @brief Tartalmazza a String osztály definícióit.
 * @date 2022-05-15
 * 
 */

#include <iostream>
#include <cstring>
#include "String.h"

    ///Konstruktor méretből.
    String::String(size_t siz){
        len=siz;
        pData= new char[siz+1];
        pData[0]='\0';
    }

    ///Konstruktor karakterből.
    String::String(char c){
        len=1;
        pData= new char[len+1];
        pData[0]=c;
        pData[1]='\0';
    }

    ///Konstruktor C99 típusú stringből.
    String::String(const char* c){
        len=strlen(c);
        pData= new char[len+1];
        strcpy(pData,c);
    }
    /**
     * @brief Másoló konstruktor
     * 
     * @param s1 - String, amit másolunk.
     */
    String::String(const String& a){
        len = a.len;
        pData=0;
        if(a.pData!=NULL){
          pData = new char[len+1];
          strcpy(pData, a.pData);
        }
      }


/**
* @brief Értékadó operátor 
* @param rhs_s - A jobb oldali String objektum referenciája.
* @return String& A bal oldal módosított String referenciája.
*/
String& String::operator=(const String& a){
        if (this != &a) {
        delete[] pData;
        len = a.len;
        pData = new char[len+1];
        strcpy(pData, a.pData);
    }
    return *this;
    }

/**
* @brief Két String objektumot összefűt
* 
* @param rhs_s - A jobb oldali string 
* @return String - Az új összefűzött, módosított String .
*/
String String::operator+(const String& rhs_s) const{
    String tmp(this->len+rhs_s.size());
    strcpy(tmp.pData,this->pData);
    strcat(tmp.pData,rhs_s.pData);
    tmp.pData[tmp.len]='\0';

    return tmp;
}
/**
 * @brief Stream operator
 * 
 * @param os - output stream
 * @param p - Kiírandó String
 * @return std::ostream& - stream
 */
std::ostream& operator<<(std::ostream& os, const String s){
    os << s.c_str();
    return os;
}


/**
 * @brief Egyenlőség operátor
 * 
 * Megvizsgálja, hogy két String megegyezik-e.
 * @param rhs - jobb oldali String objektum referenciája.
 * @return true , ha megegyeznek.
 * @return false , ha nem egyeznek meg.
 */
bool String::operator==(const String& rhs)const{
    int back=strcmp(this->pData,rhs.c_str());
    if(back==0){return true;}
    return false;
}
