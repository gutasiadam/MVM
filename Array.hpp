/**
 * @file Array.hpp
 * @author Gutási Ádám
 * @brief A generikus  dinamikus tömb megvaósítását tartalmazó fájl.
 * @date 2022-05-15
 * 
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

/**
 * @brief Debug információ kiírása egy streamre.
 * 
 * Azért itt lett definiíálva, mert az Array minden olyan osztályban includoeolva van, ahol kell
 * debug információ.
 * 
 * Csak a DEBUG makró definiálása esetén működik
 * 
 * @tparam MSG - üzenet típusa
 * @param os - stream, amire kiírjuk a debug információt.
 * @param message - streamre kiírandó üzenet
 */
template <typename MSG>
void debug(std::ostream& os, MSG message){
    #ifdef DEBUG
        os << message << std::flush;
    #endif
}
#define DEBUG 1

/**
 * @brief Generikus dinamikus tömb
 * 
 * @tparam T A tömbben tárolandó objektumok típusa.
 */
template <class T>
class Array{
    T* data; /*!< Adatra mutató pointer */
    size_t used; /*!< A tömbben levő elemek darabszáma */
    public:
        Array(size_t Siz=0): used(Siz){data=new T[used];} /*!< Konstruktor. alapesetben nulla elemű. */
        virtual ~Array(){delete[] data;} /*!< Destruktor */

        /**
         * @brief Hozzáad egy elemet a tömb végéhez.
         * 
         * @param newElement - a hozzáadandó elem referenciája.
         */
        void add(T& newElement){
            T* tmp=new T[this->used+1]; // ideiglenes, 1 mérettel nagyobb tároló
            for(size_t i=0;i<this->used;i++){
                tmp[i]=this->data[i];
            }
        tmp[this->used]=newElement; // ideiglenes térolóhoz adjuk
        delete[] this->data; // Array tárolójának törlése
        this->data=tmp; // data pointer átállítása
        used++; // használt méret nő.
        }

        /**
         * @brief Visszaad egy adott indexű elemet
         * 
         * hasonló az operator[]-hoz.
         * 
         * Ha túlindexelünk, std::out_of_range kivételt dob.
         * 
         * @param index a keresendő elem idexe
         * @return T& Az adott indexen levő objektum referenciája.
         */
        T& get(size_t index) const{
            if(index>=used){throw(std::out_of_range("Indexelesi hiba get"));}
            return this->data[index];
        }
            
        /**
         * @brief Visszaadja a tömb méretét
         * 
         * @return size_t - méret
         */
        size_t size() const{return used;}
        
        /**
         * @brief Visszad egy pointert a legelső elemre.
         * 
         * @return T* - pointer a legelső elemre.
         */
        T* begin() const{return data;}

        /**
         * @brief Visszad egy pointert az utolsó elem után
         * 
         * Intervallum ok az arrayben:
         * [begin,end[
         * 
         * @return T* pointer az Array utolsó elemének utánra.
         */
        T* end() const{
            // pl.: 1 elem van -> data elején van az adat, 1-el előrebb kell mutasson a pointer!
            // Ha 0 elem van használatban, akkor önmmagára fog mutatni, nem fut.
            return data+(used);
        }

        /**
         * @brief Megnézi, hogy egy adott elem benne van-e a tömbben
         * 
         * @param e - a keresendő elem
         * @return int -1, ha nincs benne, különben az elem indexével tér vissza.
         */
        int isElement(T& e) const{
                int i=0;
                for (T* dat=begin(); dat!=end(); dat++,i++) {
                    debug(std::cout,e); debug(std::cout,"=="); debug(std::cout, *dat); debug(std::cout,"?\n");
                    if ((*dat==e)) {
                        debug(std::cout, "@"); debug(std::cout,i);
                        return i;
                    }
                    debug(std::cout,"N");
                }
                return -1;
        }
        /**
         * @brief Töröl egy adott indexűelemet
         * 
         * indexelési hiba esetén std::out_of_range hibát dob
         * 
         * @param indx - a törlendő index
         */
        void del(size_t indx){
            if(indx>=used){throw(std::out_of_range("Indexelesi hiba - del"));}
            T* tmp= new T[used-1]; size_t tmpAt=0;
            for(size_t pos=0;pos<used;pos++){
                if(pos!=indx){
                    tmp[tmpAt++]=data[pos];
                }
            }
            used--;
            this->data=tmp;

        }

        
        /**
         * @brief Töröl egy adott elemet a tömbből
         * 
         * std::logic_error -t dob, ha a törölni kívánt elem nem tagja az arraynek.
         * @param e - a törlendő elem.
         */
        void del(T& e){
            int flag=isElement(e);

            debug(std::cout, "flag:");
            debug(std::cout, flag);
            debug(std::cout, "\n");

            if(flag==-1){
                throw(std::logic_error("Element not in array."));
            }else{
               del(flag);
            }
        }

        /**
         * @brief Bejárja a tömböt, és végrehajt rajtuk egyesével egy függvényt (funktor)
         * 
         * @tparam FuncType - funktor osztály
         * @param func - funktor osztály
         */
        template<class FuncType>
        void traverse(FuncType func){
            for(size_t i=0;i<used;i++){
                func(data[i]);
            }
        }
        /**
         * @brief Indexelő operátor
         * egy adott indexű elem refernciájával tér vissza.
         * 
         * indexelési hiba esetén std::out_of_range hibát dob
         * 
         * @param index - a kért index
         * @return T& - A kért indexen levő obejtuk referenciájával tér vissza.
         */
        T& operator[](size_t index) const{
            // a used a használatban levő Elemek számát adja meg.
            if(index>=used){throw(std::out_of_range("Indexelesi hiba - operator[]"));}
            return data[index];
        }

        /**
         * @brief Értékadó operátor
         * 
         * @param rhs - másolandó rvalue
         * @return Array& - az új tömb referenciájával tér vissza.
         */
        Array& operator=(const Array& rhs){
            delete[] data; 
            data= new T[rhs.size()];
            for(size_t i=0;i<used;i++){
                data[i]=rhs[i];
            }
            return *this;
        }

};

#endif