// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)
//
// Created by majga on 20.12.2021.
//

#include "../include/nodes.hpp"


//ReceiverPreferences
void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    double sum_of_prefs = 0.0;
    size_t num_of_prefs = _preferences.size() + 1;
    for (auto& preference : _preferences) {
        preference.second = 1 / double(num_of_prefs);
        sum_of_prefs += preference.second;
    }
    _preferences.emplace(std::make_pair(r, 1 - sum_of_prefs));
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    size_t num_of_prefs = _preferences.size() - 1;
    if (!_preferences.empty()) {
        _preferences.erase(r);
        for (auto& preference : _preferences) {
            preference.second = 1 / double(num_of_prefs);
        }
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double recv = 0.0;
    double num = _pg();
    for (auto& preference: _preferences) {
        recv += preference.second;
        if(num <= recv)
            return preference.first;
    }
    return _preferences.end()->first;
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
void Ramp::deliver_goods(Time t) {
    if(!((t - 1) % _di))
        push_package(Package());
}


//Worker
void Worker::do_work(Time t) {
    if(_t == 0) {
        if(!_queue->empty()){
        _t = t;
        _work_buffer = _queue->pop();
        }
    }
    if(t - _t + 1 == _pd){
        push_package(std::move(_work_buffer.value()));
        _t = 0;
        _work_buffer.reset();
        if(!_queue->empty()) {
            _t = t;
            _work_buffer = _queue->pop();
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

// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)