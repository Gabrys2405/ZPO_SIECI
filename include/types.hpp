//
// Created by majga on 18.12.2021.
//

#ifndef ZPO_SIECI_TYPES_HPP
#define ZPO_SIECI_TYPES_HPP
#include "storage_types.hpp"
#include <set>
#include <functional>

using ElementID = unsigned int;

using Time = unsigned int;
using TimeOffset = unsigned int;

using ProbabilityGenerator = std::function<double()>;

#endif //ZPO_SIECI_TYPES_HPP
