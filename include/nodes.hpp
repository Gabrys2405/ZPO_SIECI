//
// Created by majga on 20.12.2021.
//

#ifndef ZPO_SIECI_NODES_HPP
#define ZPO_SIECI_NODES_HPP
#include "types.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"
#include <memory>
#include <map>
#include <optional>
#include <utility>

enum class ReceiverType {
    WORKER, STOREHOUSE
};

class IPackageReceiver {
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type() const = 0;
    using const_iterator = IPackageStockpile::const_iterator;
    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;
};

class ReceiverPreferences {
public:
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : _pg(pg) {};
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();

    using preferences_t = std::map<IPackageReceiver*, double>;
    const preferences_t& get_preferences() const {return _preferences;}

    using const_iterator = preferences_t::const_iterator;
    const_iterator begin() const {return _preferences.cbegin();}
    const_iterator cbegin() const {return _preferences.cbegin();}
    const_iterator end() const {return _preferences.cend();}
    const_iterator cend() const {return _preferences.cend();}

private:
    preferences_t _preferences;
    ProbabilityGenerator _pg;
};

class PackageSender {
public:
    PackageSender() : _receiver_preferences() {}
    PackageSender(PackageSender&& package_sender) = default;
    void send_package();
    std::optional<Package>& get_sending_buffer() const {return _buffer;}

protected:
    void push_package(Package&& package);

private:
    ReceiverPreferences _receiver_preferences;
    std::optional<Package> _buffer;
};


class Ramp : public PackageSender {
public:
    Ramp (ElementID id, TimeOffset di) : _id(id), _di(di) {};
    void deliver_goods (Time t);
    TimeOffset get_delivery_interval() const {return _di;}
    ElementID get_id() const {return _id;}

private:
    ElementID _id;
    TimeOffset _di;
};

class Worker : public PackageSender , public IPackageReceiver {
public:
    Worker (ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : _id(id), _pd(pd), _queue(std::move(q)) {};
    void do_work(Time t);
    TimeOffset get_processing_duration() const {return _pd;}
    Time get_package_processing_start_time() const {return _t;}

    void receive_package(Package&& p) override;
    ElementID get_id() const override {return _id;}
    ReceiverType get_receiver_type() const override {return ReceiverType::WORKER;}

    const_iterator begin() const override {return _queue->cbegin();}
    const_iterator cbegin() const override {return _queue->cbegin();}
    const_iterator end() const override {return _queue->cend();}
    const_iterator cend() const override {return _queue->cend();}

private:
    ElementID _id;
    Time _t = 0;
    TimeOffset _pd;
    std::unique_ptr<IPackageQueue> _queue;
    std::optional<Package> _buffer;

};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::LIFO)) : _id(id),  _queue(std::move(d)) {};

    const_iterator begin() const override {return _queue->cbegin();}
    const_iterator cbegin() const override {return _queue->cbegin();}
    const_iterator end() const override {return _queue->cend();}
    const_iterator cend() const override {return _queue->cend();}

    void receive_package(Package&& p) override;
    ElementID get_id() const override {return _id;}
    ReceiverType get_receiver_type() const override {return ReceiverType::STOREHOUSE;}
private:
    ElementID _id;
    std::unique_ptr<IPackageStockpile> _queue;
};

#endif //ZPO_SIECI_NODES_HPP
