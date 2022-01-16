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

ParsedLineData parse_line(const std::string& line){
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(line);
    char delimiter = ' ';

    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }
    std::string elem_type = tokens.front();
    tokens.erase(tokens.begin());
    ParsedLineData parsed_data;


    if(elem_type == "LINK"){
        parsed_data.element_type = ElementType::LINK;
    }
    else if (elem_type == "WORKER"){
        parsed_data.element_type = ElementType::WORKEK;
    }
    else if (elem_type == "STOREHOUSE"){
        parsed_data.element_type = ElementType::STOREHOUSE;

    }
    else if(elem_type == "RAMP"){
        parsed_data.element_type = ElementType::RAMP;
    }


    for (const auto& pair: tokens){
            std::istringstream token_one(pair);
            std::vector<std::string> pairs;
            std::string token_pair;
            char delim = '=';

            while (std::getline(token_one, token_pair, delim)) {
                pairs.push_back(token);
            }
            parsed_data.parameters[pairs[0]] = pairs[1];


    }
    return parsed_data;
}


Factory load_factory_structure(std::istream& is){
    Factory factory;
    std::string line;
    while (std::getline(is, line)) {
        if(line[0] == ';' or line.empty()){ //W pliku wejściowym komentarz zaczyna się od ;
            continue;
        }

    }
    ParsedLineData parseline = parse_line(line);
    if(parseline.element_type == ElementType::RAMP){
        ElementID id = 0;
        TimeOffset di = 0;

        for(auto& ramps_parameter : parseline.parameters){
           if (ramps_parameter.first == "id" ){
               id = static_cast<ElementID>(std::stoi(ramps_parameter.second));

           }
           else if(ramps_parameter.first == "delivery-interval"){
               di = static_cast<TimeOffset>(std::stoi(ramps_parameter.second));

           }

        }
        factory.add_ramp(Ramp(id,di));
    }
    else if(parseline.element_type == ElementType::STOREHOUSE){
        ElementID id = 0;
        for(auto& storehouse_parameter : parseline.parameters){
            if(storehouse_parameter.first == "id"){
                id = static_cast<ElementID>(std::stoi(storehouse_parameter.second));

            }
        }
        factory.add_storehouse(Storehouse(id));
    }
    else if(parseline.element_type == ElementType::WORKEK){
        ElementID id = 0;
        TimeOffset pd = 0;
        PackageQueueType type;

        for(auto& worker_parameters: parseline.parameters){
            if(worker_parameters.first == "id"){
                id = static_cast<ElementID>(std::stoi(worker_parameters.second));

            }
            else if(worker_parameters.first == "processing-time"){
                pd = static_cast<TimeOffset>(std::stoi(worker_parameters.second));
            }
            else if (worker_parameters.first == "queue-type"){
                if (worker_parameters.second == "FIFO"){
                    type = PackageQueueType::FIFO;
                }
                else if(worker_parameters.second == "LIFO"){
                    type = PackageQueueType::LIFO;
                }
            }
        }
        std::unique_ptr<IPackageQueue> ttype = std::make_unique<PackageQueue>(type);
        factory.add_worker(Worker(id,pd,std::move(ttype)));
    }
    else if(parseline.element_type == ElementType::LINK){
        std::string src_type;

        std::string dest_type;

        ElementID src_id;
        ElementID dest_id;
        for(auto& link_parameters : parseline.parameters){
            if(link_parameters.first == "src"){//Musimy dokonać parsowania
                std::vector<std::string> tokens;
                std::string token;

                std::istringstream token_stream(line);
                char delimiter = '-';

                while (std::getline(token_stream, token, delimiter)) {
                    tokens.push_back(token);
                }
                src_type = tokens[0];
                src_id = static_cast<ElementID>(std::stoi(tokens[1]));

            }
            else if (link_parameters.first == "dest"){
                std::vector<std::string> tokens;
                std::string token;

                std::istringstream token_stream(line);
                char delimiter = '-';

                while (std::getline(token_stream, token, delimiter)) {
                    tokens.push_back(token);
                }
                dest_type = tokens[0];
                dest_id = static_cast<ElementID>(std::stoi(tokens[1]));
            }
        }
        if (src_type == "ramp"){
            auto ramp = factory.find_ramp_by_id(src_id);
            if(dest_type == "store"){
                auto storehouse = factory.find_storehouse_by_id(dest_id);
                ramp->receiver_preferences_.add_receiver(&(*storehouse));
            }
            else if(dest_type == "worker"){
                auto worker = factory.find_worker_by_id(dest_id);
                ramp->receiver_preferences_.add_receiver(&(*worker));
            }

        }
        else if(src_type == "worker"){
            auto worker = factory.find_worker_by_id(src_id);
            if(dest_type == "store"){
                auto storehouse = factory.find_storehouse_by_id(dest_id);
                worker->receiver_preferences_.add_receiver(&(*storehouse));
            }
            else if(dest_type == "worker"){
                auto worker1 = factory.find_worker_by_id(dest_id);
                worker->receiver_preferences_.add_receiver(&(*worker1));
            }
        }
    }
    return factory;
}