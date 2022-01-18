// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)
//
// Created by majga on 19.12.2021.
//

#ifndef ZPO_SIECI_PACKAGE_HPP
#define ZPO_SIECI_PACKAGE_HPP
#include "types.hpp"

class Package{
public:
    Package(){
        if(freed_IDs.empty() && assigned_IDs.empty()){
            _id = 1;
            assigned_IDs.insert(_id);
        }
        else if (freed_IDs.empty() && !assigned_IDs.empty()){
            ElementID max_id = *assigned_IDs.begin();
            for(auto it = assigned_IDs.begin(); it != assigned_IDs.end(); it++){
                if(max_id < *it){
                    max_id = *it;
                }
            }
            _id = max_id + 1;
            assigned_IDs.insert(_id);
        }
        else if(!freed_IDs.empty()){
            ElementID min_id = *freed_IDs.begin();
            for(auto it = std::begin(freed_IDs);it!=std::end(freed_IDs);it++){
                if (min_id > *it){
                    min_id = *it;
                }
            }
            _id = min_id;
            freed_IDs.erase(_id);
            assigned_IDs.insert(_id);
        }};
    Package(ElementID id): _id(id){}
    Package(Package&& package) = default;
    Package& operator=(Package&&) = default;
    ElementID get_id() const {return _id;};
    ~ Package(){
        assigned_IDs.erase(_id);
        freed_IDs.insert(_id);
    };
private:
    ElementID _id;
    static std::set<ElementID> assigned_IDs; // przydzielone obecnie ID
    static std::set<ElementID> freed_IDs; // kiedyś użyte ale obecnie zwolnione ID
};
#endif //ZPO_SIECI_PACKAGE_HPP
// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)