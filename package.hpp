//
// Created by majga on 19.12.2021.
//

#ifndef ZPO_SIECI_PACKAGE_HPP
#define ZPO_SIECI_PACKAGE_HPP
#include "types.hpp"

class Package{
public:
    Package(){};
    Package(const ElementID id): ID(id) {}
    Package(Package&&){};
    Package& operator=(Package&&);
    ElementID get_id() const {return ID;};
    ~ Package(){};
private:
    ElementID ID;



};
#endif //ZPO_SIECI_PACKAGE_HPP