//
// Created by majga on 15.12.2021.
//

#ifndef ZPO_SIECI_STORAGE_HPP
#define ZPO_SIECI_STORAGE_HPP

#include <vector>
#include <list>
#include "types.hpp"



using pack = std::list<ElementID>; //Nwm co ta kolejka ma zawierać...
enum class queue_type{
    LIFO,FIFO
};
class Package{
public:
    Package(const ElementID id): ID(id) {}

    ElementID get_id() const {return ID;};
    ~ Package() = default;//????
private:
     ElementID ID;



};



class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;


    virtual void push(pack&& Package);//???
    virtual void push();
//    const_iterator it_cbegin1 = Package.begin();
//    const_iterator it_cbegin2 = Package.cbegin();
//    const_iterator it_cend1 = Package.end();
//    const_iterator it_cend2 = Package.cend();??????????

    virtual std::size_t size();
    virtual bool empty();
    virtual ~IPackageStockpile() = default;//????
private:
    pack Package;//???




};
class IPackageQueue : public IPackageStockpile{  //?????
public:
    virtual pack pop();
    //virtual  get_queue_type();
private:
pack Package;
};

class PackageQueue{
public:


private:

};








#endif //ZPO_SIECI_STORAGE_HPP
