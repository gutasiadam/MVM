/**
 * \file: hetero_store.hpp
 *
 */

#ifndef HETEROSTORE_HPP
#define HETEROSTORE_HPP

#include <iostream>
#include <stdexcept>


//#error "Itt készítse el a HeteroStore sablont!"

template <class ItemType, size_t Siz = 100, class Exc = std::out_of_range>
class HeteroStore{
    ItemType* data[Siz];
    size_t db;
    size_t cap;
    void check(size_t i) const {
        if (i>=Siz) {
            throw Exc("error");
        }
    }
    public:
        HeteroStore() :db(0), cap(Siz){};
        size_t size() const {return db;}
        size_t capacity() const {return cap;}
        void add(ItemType* p){
            if (db>=Siz) {
                delete p;
                throw Exc("error");
            }else{
                data[db]=p;
                db++;
            }
            
        };
        template<class FuncType>
        void traverse(FuncType func){
            for(size_t i=0;i<db;i++){
                func(data[i]);
            }
        }
        void clear(){
            for(size_t i=0;i<db;i++){
                delete data[i];
            }
            db=0;
            }
        virtual ~HeteroStore() {clear();};    
};

#endif //HETEROSTORE_HPP
