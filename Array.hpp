#ifndef ADD_HEADER
#define ADD_HEADER

#include <stdexcept>
/**
 * \file Array.hpp
 *
 * Gutási Ádám
 * lastMod: 2022.05.08.
 * Ez a fájl tartalmazza az Array sablont.
 */

template <class T,  size_t Siz = 100>
class Array{
    T data[Siz];
    size_t amt;
    size_t cap;
    public:
        Array(): amt(0), cap(Siz){
        }
        virtual ~Array(){}

        //visszaad egy elemet adott indexn, hasonló az operator[]-hoz.
        T& get(size_t ind) const{
            return this->data[ind];
        }
            
        //visszaadja a tömb méretét.
        size_t size() const{
            return this->amt;
        }
        /*T& first() const{
            return data[0];
        }
        T& last() const{
            return data[amt];
        }*/
        //logikai értékkel té vissza, attól függően, 
        //hogy egy adott elem benne, van-e a tömbben.
        bool isElement(T& e) const{
                for (size_t i=0; i<amt; i++) {
                    if ((data[i]==e)) {
                        return true;
                    }
                return false;
                }
        }
            //töröl egy adott indexű elemet.
            //std::out_of_range hibát dob hibás indexelés esetén
        /*void del(size_t index){
            if(index>len-1 || index<0){
                throw(std::out_of_range("Indexelesi hiba"));
                return;
            }
            else{
                for (int i = 0; i < len-1; i++)
            if (i==index){
                for ( ; i < len - 1; i++){
                    elements[i] = elements[i + 1];
                }
            // Legutolsó elem már nem másolandó, hiszen előbbre került.
            len-= 1;
            T* tmp=new T[len];
            for(size_t e;e<len-1;e++){
                tmp[e]=elements[e];
            }
            delete[] elements;
                elements=tmp;
        } 
            }
            
        }*/

        //töröl egy adott elemet a tömbből.
        //std::logic_error-t dob, ha a törölni kívánt elem nem tagja az arraynek.
        /*void del(T& e){
            if(!(isElement(e))){
                throw(std::logic_error("Element not in array."));
            }else{
                size_t i=0;
                T* first=this->elements;
                T* last=this->elements+(this->len-1);
                for (; first != last; ++first, ++last, i++) {
                    if ((*first==e)) {
                        break;
                    }
                del(i);
                }
            }
        }*/

        //hozzáad egy elemet a tömbhöz.
        void add(T p){
            if (amt>=Siz) {
                throw std::domain_error("Full");
            }else{
                data[amt]=p;
                amt++;
            }
        }

        //Újraméretezi a tömböt a paraéterként kapott értékre.
        //Ha az új méret kisebb, mint a mostani, 
        //egyszerűen eldobja azokat az elemeket, amik nem férnek be.
        void resize(size_t NewSiz){
            std::cout << "I am a dummy resize !";
            /*
            T* tmp= new T [Siz];
            for(size_t e=0;e<len-1;e++){
                tmp[e]=elements[e];
            }
            delete[] elements;
            elements=tmp;*/
        }

        template<class FuncType>
        void traverse(FuncType func){
            for(size_t i=0;i<amt;i++){
                func(data[i]);
            }
        }

        //indexelő operátor
        // egy adott indexű elem refernciájával tér vissza.
        T& operator[](size_t index){
            return data[index];
        }

        std::ostream& operator<<(std::ostream& os){
            os << "TODO: Array kiírása normálisan.";
            return os;
        }

};

#endif