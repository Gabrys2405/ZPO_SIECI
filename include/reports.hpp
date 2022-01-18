// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)
//
// Created by majga on 20.12.2021.
//

#ifndef ZPO_SIECI_REPORTS_HPP
#define ZPO_SIECI_REPORTS_HPP

#include "factory.hpp"

void generate_structure_report(const Factory& f, std::ostream& os);
void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t);

std::string queue_to_string(PackageQueueType type);


#endif //ZPO_SIECI_REPORTS_HPP
// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)