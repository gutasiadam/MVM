#ifndef ADD_HEADER
#define ADD_HEADER
/**
 * \file Array.hpp
 *
 * Ez a fájl tartalmazza az Array sablont.
 */

template <class T>
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
        T& get(size_t ind) const{
            //visszaad egy elemet adott indexn, hasonló az operator[]-hoz.
        }
        size_t size() const{
            //visszaadja a tömb méretét.
        }
        bool isElement(T& e) const{
            //logikai értékkel té vissza, attól függően, hogy egy adott elem benne, van-e a tömbben.
        }
        void del(size_t index){
            //töröl egy adott indexű elemet.
            //std::out_of_range hibát dob hibás indexelés esetén
        }
        void del(T& e){
            //töröl egy adott elemet a tömbből.
            //std::logic_error-t dob, ha a törölni kívánt elem nem tagja az arraynek.
        }
        void add(T& e){
            //hozzáad egy elemet a tömbhöz.
            //ha nem fér bele a tömbbe az új elem, növeli a tömb méretét.
        }

        void resize(){
            //1 mérettel növeli a tároló méretét(ha hozzáadásnál nem fér bele )
        }

        template<class FuncType>
        void traverse(FuncType func){
            for(size_t i=0;i<len;i++){
                func(elements[i]);
            }
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