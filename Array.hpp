#ifndef ADD_HEADER
#define ADD_HEADER

#include <stdexcept>
/*
 * \file Array.hpp
 */

template <class T>
class Array{
    T* data;
    size_t used; // A tömbben levő elemek DARABSZÁMA!
    public:
        Array(size_t Siz=0): used(Siz){
            data=new T[used];
        }
        virtual ~Array(){
            std::cout << "Array dtor - Siz: " << used << std::endl;
            delete[] data;
        }

        //hozzáad egy elemet a tömbhöz.
        void add(T& newElement){
            T* tmp=new T[this->used+1];
            for(size_t i=0;i<this->used;i++){
                tmp[i]=this->data[i];
            }
        tmp[this->used]=newElement;
        std::cout << "pukk";
        delete[] this->data;
        this->data=tmp;
        used++; // használt méret nő eggyel.
        }

        //visszaad egy elemet adott indexen, hasonló az operator[]-hoz.
        T& get(size_t index) const{
            if(index>=used){throw(std::out_of_range("Indexelesi hiba get"));}
            return this->data[index];
        }
            
        //visszaadja a tömb méretét.
        size_t size() const{
            return this->used;
        }
        
        T* begin() const{
            return data; // Az elejére mutat.
        }
        T* end() const{
            // pl.: 1 elem van -> data elején van az adat, 1-el előrebb kell mutasson a pointer!
            // Ha 0 elem van használatban, akkor önmmagára fog mutatni, nem fut.
            return data+(used);
        }

        //int értékkel tér vissza, attól függően, 
        //hogy egy adott elem hol van benne, van-e a tömbben.
        ///@return -1, ha nincs benne, a szám indexét, ha benne van.
        int isElement(T& e) const{
                int i=0;
                for (T* dat=begin(); dat!=end(); dat++,i++) {
                    std::cout << e << " == " << *dat << " ? ";
                    if ((*dat==e)) {
                        std::cout << " - I - " << i << std::endl;
                        return i;
                    }
                    std::cout << " - N" << std::endl;
                }
                return -1;
        }
            //töröl egy adott indexű elemet.
            //std::out_of_range hibát dob hibás indexelés esetén
        void del(size_t indx){
            //TODO A törlés nem működik rendesen!
            //Indexelési hiba esetén dobjon kivételt
            std::cout << "Array: törlés! - index: " << indx << " | used: " << used <<std::endl;
            if(indx>=used){throw(std::out_of_range("Indexelesi hiba - del"));}
            T* tmp= new T[used-1]; size_t tmpAt=0;
            for(size_t pos=0;pos<used;pos++){
                if(pos!=indx){
                    std::cout << pos << " másolása az új tempbe" << std::endl;
                    tmp[tmpAt++]=data[pos];
                }
            }
            std::cout << "Új pending méret: " << tmpAt << std::endl;
            used--;
            std::cout << "pukk" << std::endl;
            //delete[] this->data;
            std::cout << "; add" << std::endl;
            this->data=tmp;


        }

        //töröl egy adott elemet a tömbből.
        //std::logic_error-t dob, ha a törölni kívánt elem nem tagja az arraynek.
        void del(T& e){
            int flag=isElement(e);
            std::cout << "flag: " << flag << std::endl;
            if(flag==-1){
                throw(std::logic_error("Element not in array."));
            }else{
               del(flag);
            }
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
            // a used a használatban levő Elemek számát adja meg.
            if(index>=used){throw(std::out_of_range("Indexelesi hiba - operator[]"));}
            return data[index];
        }


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