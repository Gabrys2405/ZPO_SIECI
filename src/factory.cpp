//
// Created by majga on 20.12.2021.
//
#include "factory.hpp"




template <typename Node>
void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
throw;
//TODO 1;
}
bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED){
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;
    if (sender->receiver_preferences_.get_preferences().empty()){/////TODO Nie wiem czy to tak, muszę mieć nodes
        throw std::logic_error("Nadawca nie ma zdefiniowanych odbiorców");

    }
    bool sender_has_receiver = false;
    for(auto receiver: sender->receiver_preferences_.get_preferences()) {////TODO To samo co wyżej
        if(receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE){
            sender_has_receiver = true;
        }
        else if(receiver.first->get_receiver_type() == ReceiverType::WORKER){
            IPackageReceiver* receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if (sendrecv_ptr != sender){
                sender_has_receiver = true;
            }
            if (node_colors[sendrecv_ptr] != NodeColor::VISITED){
                has_reachable_storehouse(sendrecv_ptr,node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(sender_has_receiver == true){
        return true;
    }
    else {
        throw std::logic_error("Nadawca nie ma zdefiniowanych odbiorców");
    }
}
bool Factory::is_consistent() {
    std::map<const PackageSender*,NodeColor> enum_node_color;
    for(auto& r:_ramp){
        enum_node_color[(PackageSender*) &r] = NodeColor::UNVISITED;}
    for (const auto& w:_worker){
        enum_node_color[(PackageSender*) &w] = NodeColor::UNVISITED;
    }
    for(const auto& r: _ramp){
        try{
            has_reachable_storehouse(&r,enum_node_color);
            return true;
        }
        catch (const std::logic_error&) {
            return false;
        }
    }
    return true;

}

void Factory::do_deliveries(Time) {
    throw;
    //TODO 2;

}

void Factory::do_package_passing(void) {
    throw;
    //TODO 3;

}

void Factory::do_work(Time) {
    throw;
    //TODO 4;

}





