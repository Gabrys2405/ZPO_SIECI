//
// Created by majga on 20.12.2021.
//

#ifndef ZPO_SIECI_NODES_HPP
#define ZPO_SIECI_NODES_HPP
#include "types.hpp"
#include "helpers.hpp"
#include <memory>
#include <map>
#include <optional>


class IPackageReceiver {
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() = 0;
};

class ReceiverPreferences {
public:
    ReceiverPreferences(ProbabilityGenerator pg) {};
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();

    using preferences_t = std::map<IPackageReceiver*, double>;
    preferences_t& get_preferences();

    using const_iterator = preferences_t::const_iterator;
    const_iterator begin() const {return preferences_.cbegin();}
    const_iterator cbegin() const {return preferences_.cbegin();}
    const_iterator end() const {return preferences_.cend();}
    const_iterator cend() const {return preferences_.cend();}

private:
    preferences_t preferences_;
};

class PackageSender {
public:
    PackageSender(PackageSender&& package_sender) = default;
    void send_package();
    std::optional<Package>& get_sending_buffer();

protected:
    void push_package(Package&& package);

private:
    ReceiverPreferences receiver_preferences_;
};


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
