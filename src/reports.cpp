//
// Created by majga on 20.12.2021.
//

#include "../include/reports.hpp"
#include "../include/nodes.hpp"

std::string queue_to_string(PackageQueueType type) {
    switch (type) {
        case(PackageQueueType::LIFO):
            return "LIFO";
        case(PackageQueueType::FIFO):
            return "FIFO";
        default:
            break;
    }
}


void generate_structure_report(const Factory& f, std::ostream& os) {
    os << "\n== LOADING RAMPS ==\n\n";
    for (auto ramp = f.ramp_cbegin(); ramp != f.ramp_cend(); ramp++) {
        os << "LOADING RAMP #" << ramp->get_id() << "\n";
        os << "  Delivery interval: " << ramp->get_delivery_interval() << "\n";
        os << "  Receivers:\n";
        for (auto rec : ramp->receiver_preferences_) {
            if (rec.first->get_receiver_type() == ReceiverType::WORKER) {
                os << "    worker #" << rec.first->get_id() << "\n";
            } else {
                os << "    storehouse #" << rec.first->get_id() << "\n";
            }
        }
    }
    os << "\n\n== WORKERS ==\n\n";
    for (auto worker = f.worker_cbegin(); worker != f.worker_cend(); worker++) {
        os << "WORKER #" << worker->get_id() << "\n";
        os << "  Processing time: " << worker->get_processing_duration() << "\n";
        os << "  Queue type: " << queue_to_string(worker->get_queue()->get_queue_type()) << "\n";
        os << "  Receivers:\n";
        for (auto rec: worker->receiver_preferences_) {
            if (rec.first->get_receiver_type() == ReceiverType::WORKER) {
                os << "    worker #" << rec.first->get_id() << "\n";
            } else {
                os << "    storehouse #" << rec.first->get_id() << "\n";
            }
        }
    }
    os << "\n\n== STOREHOUSES ==\n\n";
    for (auto storehouse = f.storehouse_cbegin(); storehouse != f.storehouse_cend(); storehouse++) {
        os << "STOREHOUSE #" << storehouse->get_id() << "\n";
    }
    os << "\n";

}

void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t) {
    os << "=== [ Turn: " << t << " ] ===\n\n";
    os << "== WORKERS ==\n\n";
    for (auto worker = f.worker_cbegin(); worker != f.worker_cend(); worker++) {
        os << "WORKER #" << worker->get_id() << "\n";
        os << "  PBuffer: ";
        if (f.find_worker_by_id(worker->get_id())->get_processing_buffer() != std::nullopt) {
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
            os << "(empty)\n";
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
            os << "\n";
        } else {
            os << "(empty)\n";
        }
    }
}