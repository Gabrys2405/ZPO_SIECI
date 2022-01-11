//
// Created by majga on 20.12.2021.
//

#ifndef ZPO_SIECI_HELPERS_HPP
#define ZPO_SIECI_HELPERS_HPP
#include <functional>
#include <random>
#include "types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;
#endif //ZPO_SIECI_HELPERS_HPP
