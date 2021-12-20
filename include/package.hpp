//
// Created by majga on 19.12.2021.
//

#ifndef ZPO_SIECI_PACKAGE_HPP
#define ZPO_SIECI_PACKAGE_HPP
#include "types.hpp"

class Package{
public:
    Package(){};
    Package(ElementID id): _id(id){
        if(freed_IDs.empty() && assigned_IDs.empty()){
            _id = 1;
            assigned_IDs.insert(_id);
        }
        else if (freed_IDs.empty() && !assigned_IDs.empty()){
            ElementID max_id = *assigned_IDs.begin();
            //TODO Trzeba znaleźć największe ID w assigned_IDs i dodać do niego 1 a następnie ustawić jako id!!!
        }
        else if(!freed_IDs.empty() && assigned_IDs.empty()){
            //TODO Tym razem trzeba znaleźć najmniejsze ID w freed_IDs i ustawić je jako ID a następnie przenieść to ID z freed_IDs do assigned_IDs!!!
        }
    }
    Package(Package&& package) = default;
    Package& operator=(Package&&) = default;
    ElementID get_id() const {return _id;};
    ~ Package(){};//TODO Kiedy usuwamy obiekt klasy Package jego ID ląduje w zbiorze freed_IDs!!!
private:
    ElementID _id;
    static std::set<ElementID> assigned_IDs; // przydzielone obecnie ID
    static std::set<ElementID> freed_IDs; // kiedyś użyte ale obecnie zwolnione ID




};
#endif //ZPO_SIECI_PACKAGE_HPP
