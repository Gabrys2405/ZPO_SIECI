//
// Created by majga on 20.12.2021.
//
#include "../include/nodes.hpp"


//ReceiverPreferences
void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    double sum_of_prefs = 0.0;
    size_t num_of_prefs = _preferences.size();
    for (auto& preference : _preferences) {
        preference.second = probability_generator() / double(num_of_prefs);
        sum_of_prefs += preference.second;
    }
    _preferences.emplace(std::make_pair(r, 1 - sum_of_prefs));
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double sum_of_prefs = 0.0;
    size_t num_of_prefs = _preferences.size() - 1;
    if (!_preferences.empty()) {
        for (auto receiver = _preferences.begin(); receiver != _preferences.end();) {
            if (receiver->first->get_id() == r->get_id()) {
                _preferences.erase(receiver);
            }
        }
        for (auto receiver = _preferences.begin(); receiver != _preferences.end();) {
            if (receiver != _preferences.end()) {
                receiver->second = probability_generator() / double(num_of_prefs);
                sum_of_prefs += receiver->second;
            } else {
                receiver->second = 1 - sum_of_prefs;
            }
        }
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double recv = 0.0;
    IPackageReceiver* choosen = _preferences.end()->first;
    if (!_preferences.empty()) {
        for (auto& preference : _preferences) {
            recv += preference.second;
            if (_pg() <= recv) {
                choosen = preference.first;
            }
        }
        return choosen;
    } else {
        return 0;
    }
}


//PackageSender
void PackageSender::push_package(Package&& package) {
    _buffer.emplace(std::move(package));
}

void PackageSender::send_package() {
    if (_buffer) {
        receiver_preferences_.choose_receiver()->receive_package(std::move(*_buffer));
        _buffer.reset();
    }
}


//Ramp
void Ramp::deliver_goods (Time t) {
    if (not t % get_delivery_interval()) {
        Package p;
        push_package(std::move(p));
    }
}


//Worker
void Worker::do_work(Time t) {
    if (t - get_package_processing_start_time() == get_processing_duration()) {
        if (_work_buffer) {
            push_package(std::move(*_work_buffer));
            _work_buffer.reset();
        }
        _work_buffer.emplace(_queue->pop());
        _t = t;
    } else {
        if (!_work_buffer) {
            _work_buffer.emplace(_queue->pop());
            _t = t;
        }
    }
}

void Worker::receive_package(Package&& p) {
    _queue->push(std::move(p));
}


//Storehouse
void Storehouse::receive_package(Package&& p) {
    _queue->push(std::move(p));
}
