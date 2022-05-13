#ifndef ADD_HEADER
#define ADD_HEADER

#include <stdexcept>
//#include "memtrace.h"
/**
 * \file Array.hpp
 *
 * Gutási Ádám
 * lastMod: 2022.05.08.
 * Ez a fájl tartalmazza az Array sablont.
 */

template <class T>
class Array{
    T* data;
    T* first;
    T* last;
    size_t used;
    public:
        Array(size_t Siz=0): used(Siz){
            data=new T[used];
            first=data;
            last=data+used;
        }
        virtual ~Array(){
            delete[] data;
        }

        //hozzáad egy elemet a tömbhöz.
        void add(T& newElement){ 
            //std::cout << "Add indul, tömb mérete: " << this->used << std::endl;
            T* tmp=new T[this->used+1]; // Itt akad el, ha hozzá akar adni új elemet. Miért?
            for(size_t i=0;i<this->used;i++){
                tmp[i]=this->data[i];
            }
        tmp[this->used]=newElement;
        delete[] this->data;
        this->data=tmp;
        used++; // használt méret nő eggyel.
        }

        //visszaad egy elemet adott indexn, hasonló az operator[]-hoz.
        T& get(size_t ind) const{
            return this->data[ind];
        }
            
        //visszaadja a tömb méretét.
        size_t size() const{
            return this->used;
        }
        
        T* begin() const{
            return data;
        }
        T* end() const{
            return data+used;
        }

        //int értékkel tér vissza, attól függően, 
        //hogy egy adott elem hol van benne, van-e a tömbben.
        ///@return -1, ha nincs benne, a szám indexét, ha benne van.
        int isElement(T& e) const{
                int i=0;
                for (T* dat=begin(); dat!=end(); dat++,i++) {
                    if ((*dat==e)) {
                        return i;
                    }
                return -1;
                }
        }
            //töröl egy adott indexű elemet.
            //std::out_of_range hibát dob hibás indexelés esetén
        void del(size_t index){
            //TODO A törlés még nem működik rendesen!
            if(index>used-1 || index<0){
                throw(std::out_of_range("Indexelesi hiba"));
                return;
            }
            else{
                for (int i = 0; i < used-1; i++)
            if (i==index){
                for ( ; i < used - 1; i++){
                    data[i] = data[i + 1];
                }
            // Legutolsó elem már nem másolandó, hiszen előbbre került.
            used-= 1;
            T* tmp=new T[used];
            for(size_t e=0;e<used;e++){
                tmp[e]=data[e];
            }
            delete[] data;
            data=tmp;
        } 
            }
            
        }

        //töröl egy adott elemet a tömbből.
        //std::logic_error-t dob, ha a törölni kívánt elem nem tagja az arraynek.
        void del(T& e){
            int flag=isElement(e);
            if(flag==-1){
                throw(std::logic_error("Element not in array."));
            }else{
               del(flag);
            }
        }


        //Újraméretezi a tömböt a paraéterként kapott értékre.
        //Ha az új méret kisebb, mint a mostani, 
        //egyszerűen eldobja azokat az elemeket, amik nem férnek be.
        void resize(size_t NewSiz){
            std::cout << "I am a dummy resize !";
            /*
            T* tmp= new T [Siz];
            for(size_t e=0;e<used-1;e++){
                tmp[e]=data[e];
            }
            delete[] data;
            data=tmp;*/
        }

        template<class FuncType>
        void traverse(FuncType func){
            for(size_t i=0;i<used;i++){
                func(data[i]);
            }
        }

        //indexelő operátor
        // egy adott indexű elem refernciájával tér vissza.
        T& operator[](size_t index) const{
            return data[index];
        }


        Array& operator=(const Array& rhs){
            used=rhs.size();
            delete[] data; 
            data= new T[used];
            for(size_t i=0;i<used;i++){
                data[i]=rhs[i];
            }
            return *this;
        }

};

#endif