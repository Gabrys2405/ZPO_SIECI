//
// Created by majga on 19.12.2021.
//

#ifndef ZPO_SIECI_STORAGE_TYPES_HPP
#define ZPO_SIECI_STORAGE_TYPES_HPP
#include "package.hpp"
#include <list>


enum class PackageQueueType{
    LIFO,FIFO
};


class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;


    virtual void push(Package&&) = 0;//???
//    const_iterator it_cbegin1 = ?????.begin();TODO;
//    const_iterator it_cbegin2 = ?????.cbegin();
//    const_iterator it_cend1 = ?????.end();
//    const_iterator it_cend2 = package_queue.cend();??????????

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
    Package pop(); //TODO;
    PackageQueueType get_queue_type() { return queueType; };
    void push(Package&&);
    std::size_t size(){return package_queue.size();};
    bool empty();

private:
    PackageQueueType queueType;
    std::list<Package> package_queue;
};

#endif //ZPO_SIECI_STORAGE_TYPES_HPP
