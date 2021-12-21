//
// Created by majga on 19.12.2021.
//

#ifndef ZPO_SIECI_STORAGE_TYPES_HPP
#define ZPO_SIECI_STORAGE_TYPES_HPP
#include "../include/package.hpp"
#include"../src/package.cpp"
#include"../include/types.hpp"
#include <list>
#include <utility>


enum class PackageQueueType{
    LIFO,FIFO
};

class IPackageStockpile {
public:
    using const_iterator = std::list<Package>::const_iterator;

    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;

    virtual void push(Package&&) = 0;
    virtual std::size_t size() = 0;
    virtual bool empty() = 0;
    virtual ~IPackageStockpile() = default;

};

class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() = 0;//wyciąganie półproduktu z kolejki w zależności od rodzaju kolejki
    virtual PackageQueueType  get_queue_type() = 0; //identyfikacja typu kolejki FIFO/LIFO

};

class PackageQueue : public IPackageQueue {
public:

    PackageQueue(PackageQueueType type): _queueType(type) {}
    Package pop() override;
    PackageQueueType get_queue_type() override {return _queueType;}
    void push(Package&&) override;
    std::size_t size() override {return _package_queue.size();}
    bool empty() override {return _package_queue.empty();}

    IPackageStockpile::const_iterator begin() const override {return _package_queue.cbegin();}
    IPackageStockpile::const_iterator cbegin() const override {return _package_queue.cbegin();}
    IPackageStockpile::const_iterator end() const override {return _package_queue.cend();}
    IPackageStockpile::const_iterator cend() const override {return _package_queue.cend();}

private:
    PackageQueueType _queueType;
    std::list<Package> _package_queue;

};

#endif //ZPO_SIECI_STORAGE_TYPES_HPP
