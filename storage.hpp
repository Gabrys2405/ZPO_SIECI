//
// Created by majga on 15.12.2021.
//

#ifndef ZPO_SIECI_STORAGE_HPP
#define ZPO_SIECI_STORAGE_HPP

#include <vector>
#include <list>


using element_id = unsigned int; // Dla uproszczenia(<<primitive>> )
using pack = std::list<int>; //Wydaje mi się że ta kolejka elementów ma byc kolejką ID ale pewności nie mam

class Package{
public:
    Package(const element_id id): ElementID(id) {}

    element_id get_id() const {return ElementID;};
    ~ Package() = default;//????
private:
    element_id ElementID;



};



class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;


    virtual void push(Package&&);
    virtual void push();
    virtual std::size_t size();
    virtual bool empty();
    virtual ~IPackageStockpile() = default;//????
private:




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
