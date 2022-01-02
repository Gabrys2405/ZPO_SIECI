//
// Created by majga on 20.12.2021.
//

#ifndef ZPO_SIECI_NODES_HPP
#define ZPO_SIECI_NODES_HPP
#include "types.hpp"
#include <memory>

class Ramp {
public:
    Ramp (ElementID id, TimeOffset di) {_id = id; _di = di;}
    void deliver_goods (Time t);
    TimeOffset get_delivery_interval() const {return _di;};
    ElementID get_id() const {return _id;};

private:
    ElementID _id = 0;
    TimeOffset _di = 0;
};

class Worker {
public:
    Worker (ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {_id = id; _pd = pd;}
    void do_work(Time t);
    TimeOffset get_processing_duration() const {return _pd;}
    Time get_package_processing_start_time() const {}
private:
    ElementID _id;
    TimeOffset _pd;
};

class Storehouse {
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d);
};

#endif //ZPO_SIECI_NODES_HPP
