//
// Created by majga on 15.12.2021.
//

#ifndef ZPO_SIECI_STORAGE_HPP
#define ZPO_SIECI_STORAGE_HPP

#include <vector>
#include <list>


using element_id = unsigned int; // Dla uproszczenia
using pack = std::list<int>; //Wydaje mi się że ta kolejka elementów ma byc kolejką ID ale pewności nie mam

class Package{
public:
    Package(const element_id id): ElementID(id) {}

    element_id get_id() const {return ElementID;};
    ~ Package() = default;
private:
    element_id ElementID;


};

class PackageQueue{
public:


private:

};
class IPackageQueue{
public:
    virtual pack pop(){return Package;};

private:
pack Package;
};


class IPackageStockpile{
public:

private:




};





#endif //ZPO_SIECI_STORAGE_HPP
