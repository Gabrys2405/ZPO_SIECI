//
// Created by majga on 20.12.2021.
//
#include "../include/factory.hpp"





bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED){
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;
    if (sender->receiver_preferences_.get_preferences().empty()){\
        throw std::logic_error("Nadawca nie ma zdefiniowanych odbiorców");

    }
    bool sender_has_receiver = false;
    for(auto receiver: sender->receiver_preferences_.get_preferences()) {
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
    if(sender_has_receiver){
        return true;
    }
    else {
        throw std::logic_error("Nadawca nie ma zdefiniowanych odbiorców");
    }
}
bool Factory::is_consistent() {
    std::map<const PackageSender*,NodeColor> enum_node_color;
//    for(auto& r:_ramp){
//        enum_node_color[(PackageSender*) &r] = NodeColor::UNVISITED;}
    for(auto& w:_worker ){
        enum_node_color.emplace(std::make_pair(&w, NodeColor::UNVISITED));
    }
    for(auto& r:_ramp ){
        enum_node_color.emplace(std::make_pair(&r, NodeColor::UNVISITED));
    }
    for(const auto& r: _ramp){
        try{
            has_reachable_storehouse((PackageSender*) &r, enum_node_color);
            return true;
        }
        catch (const std::logic_error&) {
            return false;
        }
    }
    return true;

}

void Factory::do_deliveries(Time t) {
//    for(auto& r:_ramp){
//        r.deliver_goods(t);
    std::for_each(_ramp.begin(),_ramp.end(),[t](auto& r){r.deliver_goods(t);});
}




void Factory::do_package_passing(){
    std::for_each(_ramp.begin(),_ramp.end(),[](auto& r){r.send_package();});
    std::for_each(_worker.begin(),_worker.end(),[](auto& w){w.send_package();});
}


void Factory::do_work(Time t) {
//   for (auto& w:_worker ){
//       w.do_work(t);
//   }
    std::for_each(_worker.begin(),_worker.end(),[t](auto& w){w.do_work(t);});
}


//template <typename Node>
//void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
//    std::for_each(_worker.begin(), _worker.end(), [](Worker &w) {
//        auto receivers = w.receiver_preferences_.get_preferences();
//        for (auto & receiver : receivers) {
//            w.receiver_preferences_.remove_receiver(receiver.first);
//        }
//    });
//    std::for_each(_ramp.begin(), _ramp.end(), [](Ramp &r) {
//        auto receivers = r.receiver_preferences_.get_preferences();
//        for (auto & receiver : receivers) {
//            r.receiver_preferences_.remove_receiver(receiver.first);
//        }
//    });
//    collection.remove_by_id(id);
//}




void Factory::remove_storehouse(ElementID id) {
    std::for_each(_worker.begin(),_worker.end(),[id](Worker &worker)
    {
        auto prefs=worker.receiver_preferences_.get_preferences();
        for(auto & pref : prefs)
        {
            if(pref.first->get_id()==id)
            {
                worker.receiver_preferences_.remove_receiver(pref.first);
            }
        }
    } );
    _storehouse.remove_by_id(id);

}

void Factory::remove_worker(ElementID id) {
    std::for_each(_ramp.begin(),_ramp.end(),[id](Ramp &ramp)
    {
        auto prefs=ramp.receiver_preferences_.get_preferences();
        for(auto & pref : prefs)
        {
            if(pref.first->get_id()==id)
            {
                ramp.receiver_preferences_.remove_receiver(pref.first);
            }
        }
    } );
    std::for_each(_worker.begin(),_worker.end(),[id](Worker &worker)
    {
        auto prefs=worker.receiver_preferences_.get_preferences();
        for(auto & pref : prefs)
        {
            if(pref.first->get_id()==id)
            {
                worker.receiver_preferences_.remove_receiver(pref.first);
            }
        }
    } );

    _worker.remove_by_id(id);

}
