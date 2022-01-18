//
// Created by majga on 20.12.2021.
//

#include "../include/reports.hpp"
#include "../include/nodes.hpp"

#include "../include/factory.hpp"


std::string queue_to_string(PackageQueueType type) {
    std::string queue;
    switch (type) {
        case(PackageQueueType::LIFO):
            queue = "LIFO";
            break;

        case(PackageQueueType::FIFO):
            queue = "FIFO";
            break;

        default:
            break;
    }
    return queue;
}


void generate_structure_report(const Factory& f, std::ostream& os) {
    // Sortowanie
    std::vector<ElementID> ramps;
    std::vector<ElementID> workers;
    std::vector<ElementID> stores;
    for (auto ramp = f.ramp_cbegin(); ramp != f.ramp_cend(); ramp++) {
        ramps.push_back(ramp->get_id());
    }
    for (auto worker = f.worker_cbegin(); worker != f.worker_cend(); worker++) {
        workers.push_back(worker->get_id());
    }
    for (auto store = f.storehouse_cbegin(); store != f.storehouse_cend(); store++) {
        stores.push_back(store->get_id());
    }
    std::sort(ramps.begin(), ramps.end());
    std::sort(workers.begin(), workers.end());
    std::sort(stores.begin(), stores.end());

    os << "\n== LOADING RAMPS ==\n\n";
    for (auto ramp : ramps) {
        os << "LOADING RAMP #" << f.find_ramp_by_id(ramp)->get_id() << "\n";
        os << "  Delivery interval: " << f.find_ramp_by_id(ramp)->get_delivery_interval() << "\n";
        os << "  Receivers:" << '\n';
        std::vector<ElementID> worker_id;
        std::vector<ElementID> store_id;
        for (auto rec : f.find_ramp_by_id(ramp)->receiver_preferences_) {
            if (rec.first->get_receiver_type() == ReceiverType::WORKER) {
                worker_id.push_back(rec.first->get_id());
                //os << "    worker #" << rec.first->get_id() << '\n';

            } else {
                store_id.push_back(rec.first->get_id());
                //os << "    storehouse #" << rec.first->get_id() << "\n";
            }
        }
        // Sortowanie
        std::sort(worker_id.begin(), worker_id.end());
        std::sort(store_id.begin(), store_id.end());
        if (!store_id.empty()) {
            for (auto s : store_id) {
                os << "    storehouse #" << s << "\n";
            }
        }
        if (!worker_id.empty()) {
            for (auto w: worker_id) {
                os << "    worker #" << w << "\n";
            }
        }
        os<<'\n';
    }

    os << "\n== WORKERS ==\n\n";
    for (auto worker : workers) {
        os << "WORKER #" << f.find_worker_by_id(worker)->get_id() << "\n";
        os << "  Processing time: " << f.find_worker_by_id(worker)->get_processing_duration() << "\n";
        os << "  Queue type: " << queue_to_string(f.find_worker_by_id(worker)->get_queue()->get_queue_type()) << "\n";
        os << "  Receivers:\n";
        std::vector<ElementID> workers_ids;
        std::vector<ElementID> stores_ids;
        for (auto rec: f.find_worker_by_id(worker)->receiver_preferences_) {
            if (rec.first->get_receiver_type() == ReceiverType::WORKER) {
                workers_ids.push_back(rec.first->get_id());
                //os << "    worker #" << rec.first->get_id();

            } else if(rec.first->get_receiver_type() == ReceiverType::STOREHOUSE){
                stores_ids.push_back(rec.first->get_id());
                //os << "    storehouse #" << rec.first->get_id();
            }

        }
        // Sortowanie
        std::sort(workers_ids.begin(), workers_ids.end());
        std::sort(stores_ids.begin(), stores_ids.end());
        if (!stores.empty()) {
            for (auto s : stores_ids) {
                os << "    storehouse #" << s << "\n";
            }
        }
        if (!workers.empty()) {
            for (auto w : workers_ids) {
                os << "    worker #" << w << "\n";
            }
        }
        os << "\n";
    }
    os << "\n== STOREHOUSES ==\n\n";
    for (auto storehouse : stores) {
        os << "STOREHOUSE #" << storehouse << '\n';
        os << '\n';
    }
}

void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t) {
    os << "=== [ Turn: " << t << " ] ===\n\n";
    os << "== WORKERS ==\n";
    for (auto worker = f.worker_cbegin(); worker != f.worker_cend(); worker++) {
        os << "\nWORKER #" << worker->get_id() << "\n";

        os << "  PBuffer: ";
        if (worker->get_processing_buffer() != std::nullopt) {
            os << "#" << worker->get_processing_buffer()->get_id() << " (pt = " << worker->get_package_processing_start_time() << ")\n";
        } else {
            os << "(empty)\n";
        }
        os << "  Queue: ";
        if (!worker->get_queue()->empty()) {
            for (auto& qelem : *worker->get_queue()) {
                os << "#" << qelem.get_id();
                if (qelem.get_id() != worker->get_queue()->end()->get_id()) {
                    os << ", ";
                }
            }
            os << "\n";
        } else {
            os << "(empty)" << '\n';
        }
        os << "  SBuffer: ";
        if (worker->get_sending_buffer() != std::nullopt) {
            os << "#" << worker->get_sending_buffer()->get_id() << "\n";
        } else {
            os << "(empty)\n";
        }
    }
    os << "\n\n== STOREHOUSES ==\n\n";
    for (auto storehouse = f.storehouse_cbegin(); storehouse != f.storehouse_cend(); storehouse++) {
        os << "STOREHOUSE #" << storehouse->get_id() << "\n";
        os << "  Stock: ";
        if (storehouse->cbegin() != storehouse->cend()) {
            for (auto qelem = storehouse->cbegin(); qelem != storehouse->cend(); qelem++) {
                os << "#" << qelem->get_id();
                if (qelem->get_id() != storehouse->cend()->get_id()) {
                    os << ", ";
                }
            }
            os << "\n\n";
        } else {
            os << "(empty)\n\n";
        }
    }
}