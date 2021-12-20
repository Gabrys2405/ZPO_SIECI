//
// Created by majga on 18.12.2021.
//

#ifndef ZPO_SIECI_TYPES_HPP
#define ZPO_SIECI_TYPES_HPP
#include <set>
using ElementID = unsigned int;



class IDs {///nwm gdzie to dać i czy wgl jest potrzebne
public:
    IDs() = default;
    ~IDs() = default;
private:
    static std::set<ElementID> assigned_IDs; // przydzielone obecnie ID
    static std::set<ElementID> freed_IDs; // kiedyś użyte ale obecnie zwolnione ID

};





#endif //ZPO_SIECI_TYPES_HPP