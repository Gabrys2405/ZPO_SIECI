//
// Created by majga on 15.12.2021.
//

#ifndef ZPO_SIECI_STORAGE_HPP
#define ZPO_SIECI_STORAGE_HPP


#include <list>
#include "types.hpp"




class Package{
public:
    Package(){};
    Package(const ElementID id): ID(id) {}
    Package(Package&&){};
    ElementID get_id() const {return ID;};
    ~ Package(){};
private:
     ElementID ID;



};




class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;


    virtual void push(Package&&) = 0;//???
//    const_iterator it_cbegin1 = ?????.begin();TODO;
//    const_iterator it_cbegin2 = ?????.cbegin();
//    const_iterator it_cend1 = ?????.end();
//    const_iterator it_cend2 = ?????.cend();??????????

    virtual std::size_t size() = 0;
    virtual bool empty() = 0;
    virtual ~IPackageStockpile(){};//????






};
class IPackageQueue: public IPackageStockpile{  //?????
public:
    virtual Package pop() = 0;//wyciąganie półproduktu z kolejki w zależności od rodzaju kolejki
    virtual PackageQueueType  get_queue_type() = 0; //identyfikacja typu kolejki FIFO/LIFO

};

class PackageQueue : public IPackageQueue{
public:
    PackageQueue(PackageQueueType type):queueType(type){}
    Package pop(){throw;}  //TODO;
    PackageQueueType get_queue_type() { return queueType; }; //TODO;
    void push(Package&&);
    std::size_t size();
    bool empty();

private:
PackageQueueType queueType;
};









#endif //ZPO_SIECI_STORAGE_HPP
