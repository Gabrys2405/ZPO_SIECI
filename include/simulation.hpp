//
// Created by majga on 20.12.2021.
//

#ifndef ZPO_SIECI_SIMULATION_HPP
#define ZPO_SIECI_SIMULATION_HPP
#include "factory.hpp"

void simulate(Factory& f, TimeOffset d,const std::function<void(Factory&, Time)>& rf);
#endif //ZPO_SIECI_SIMULATION_HPP
