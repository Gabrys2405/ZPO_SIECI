//
// Created by majga on 19.12.2021.
//

#ifndef ZPO_SIECI_PACKAGE_HPP
#define ZPO_SIECI_PACKAGE_HPP
#include "types.hpp"

class Package{
public:
    Package(){};
    Package(ElementID id): _id(id) {}
//    Package(Package&& package):_package(std::move(package)){}
    Package& operator=(Package&&) = default;
    ElementID get_id() const {return _id;};
    ~ Package(){};
private:
    ElementID _id;
    static std::set<ElementID> assigned_IDs; // przydzielone obecnie ID
    static std::set<ElementID> freed_IDs; // kiedyś użyte ale obecnie zwolnione ID




};
#endif //ZPO_SIECI_PACKAGE_HPP
