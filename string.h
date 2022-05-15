#ifndef STRING_H
#define STRING_H
/**
 * @file String.h
 * @author Gutási Ádám
 * @brief Ez a fájl taartalmazza a String osztály deklarációit, és az inline függvényeket.
 * @date 2022-05-15
 * 
 * 
 */

#include <iostream>

class String {
    char *pData;    ///< Adat pointer
    size_t len;     ///< Lezáró nulla nélküli hossz
public:
    /**
     * @brief Visszaadja a string hosszát.
     * 
     * @return size_t A string hossza
     */
	size_t size() const { return len; }

    String() :pData(0), len(0) {}

    /**
     * @brief C99 típusú string visszaadása
     * 
     * @return const char* 
     */
    const char* c_str() const { return pData;}
    char* c_str() { return pData;}

    ///Konstruktor méretből
    String(size_t siz);
    
    /// Konstruktor karakterből
    /// @param ch - karakter, amiből létrehozzuk a stringet.
    String(char ch);

    /**
     * @brief Konstruktor egy C99 típusú stringből
     * 
     * Ez a default konstruktor is
     * @param p - C99 típusú string
     */
    String(const char *p); // Ugyanaz, mint a "".

    /**
     * @brief Másoló konstruktor
     * 
     * @param s1 - String, amit másolunk.
     */
    String(const String& s1);

    ///Destruktor.
    virtual ~String() { delete[] pData; }

    /**
     * @brief Egyenlőség operátor
     * 
     * Megvizsgálja, hogy két String megegyezik-e.
     * @param rhs - jobb oldali String objektum referenciája.
     * @return true , ha megegyeznek.
     * @return false , ha nem egyeznek meg.
     */
    bool operator==(const String& rhs)const;


    /**
     * @brief Értékadó operátor
     * 
     * @param rhs_s - A jobb oldali String objektum referenciája.
     * @return String& A bal oldal módosított String referenciája.
     */
    String& operator=(const String& rhs_s);

    /**
     * @brief Két String objektumot összefűt
     * 
     * @param rhs_s - A jobb oldali string 
     * @return String - Az új összefűzött, módosított String .
     */
    String operator+(const String& rhs_s) const ;

    /**
     * @brief Stream operator
     * 
     * @param os - output stream
     * @param p - Kiírandó String
     * @return std::ostream& - stream
     */
    friend std::ostream& operator<<(std::ostream& os, String p);
};
/**
 * @brief Karakterhez sztringet fűz
 * 
 * @param ch - lvalue
 * @param str - rvalue
 * @return String - Új, összefűzött Stringgel tér vissza.
 */
inline String operator+(char ch, const String& str) { return String(ch) + str; }

#endif
