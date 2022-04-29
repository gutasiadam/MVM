#ifndef ADDRESS_HEADER
#define ADDRESS_HEADER
/**
 * \file Array.hpp
 *
 * Ez a fájl tartalmazza az Array sablont.
 */

template <typename T>
class Array{
    size_t len;
    T* elements;
    public:
        Array(int len=0): len(len){
            elements=new T[len];
        }
        ~Array(){
            delete[] elements;
        }
        T get(size_t ind) const{
            //visszaad egy elemet adott indexn, hasonló az operator[]-hoz.
        }
        size_t size() const{
            //visszaadja a tömb méretét.
        }
        bool isElement(T& e const) const{
            //logikai értékkel té vissza, attól függően, hogy egy adott elem benne, van-e a tömbben.
        }
        del(size_t index);{
            //töröl egy adott indexű elemet.
            //std::out_of_range hibát dob hibás indexelés esetén
        }
        del(T& e);{
            //töröl egy adott elemet a tömbből.
            //std::logic_error-t dob, ha a törölni kívánt elem nem tagja az arraynek.
        }
        add(T& e){
            //hozzáad egy elemet a tömbhöz.
            //ha nem fér bele a tömbbe az új elem, növeli a tömb méretét.
        }

        T& operator[](size_t index){
            //indexelő operátor
            // egy adott indexű elem refernciájával tér vissza.
        }

        /*std::ostream& operator<<(std::ostream& os){
            //Kiíír
        }*/

};

#endif