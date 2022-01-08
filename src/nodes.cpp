//
// Created by majga on 20.12.2021.
//
#include "../include/nodes.hpp"


//ReceiverPreferences
void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    double sum_of_prefs = 0.0;
    int num_of_prefs = 0;
    for (auto& preference : _preferences) {
        num_of_prefs += 1;
    }
    for (auto& preference : _preferences) {
        preference.second = probability_generator() / num_of_prefs;
        sum_of_prefs += preference.second;
    }
    _preferences.emplace(std::make_pair(r, 1 - sum_of_prefs));
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double sum_of_prefs = 0.0;
    int num_of_prefs = 0;
    for (auto receiver = _preferences.begin(); receiver != _preferences.end();) {
        if (receiver->first->get_id() == r->get_id()) {
            _preferences.erase(receiver);
        } else {
            num_of_prefs += 1;
        }
    }
    for (auto receiver = _preferences.begin(); receiver != _preferences.end();) {
        if (receiver != _preferences.end()) {
            receiver->second = probability_generator() / num_of_prefs;
            sum_of_prefs += receiver->second;
        } else {
            receiver->second = 1 - sum_of_prefs;
        }
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double recv = 0.0;
    for (auto& preference : _preferences) {
        if (_pg <= recv) {

        }
    }
}


//PackageSender
void PackageSender::push_package(Package&& package) {
    _buffer.emplace(std::move(package));
}

void PackageSender::send_package() {
    if (_buffer) {
        _receiver_preferences.choose_receiver()->receive_package(std::move(*_buffer));
        _buffer.reset();
    }
}


//Ramp
void Ramp::deliver_goods (Time t) {

}


//Worker
void Worker::do_work(Time t) {

}

void Worker::receive_package(Package&& p) {
    _queue->push(std::move(p));
}


//Storehouse
void Storehouse::receive_package(Package&& p) {
    _queue->push(std::move(p));
}
