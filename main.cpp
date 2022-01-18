//
// Created by majga on 20.12.2021.
//

#include "include/storage_types.hpp"
#include "src/package.cpp"
#include "src/storage_types.cpp"
#include "include/package.hpp"
#include "include/config.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<unsigned int> ids;
    for (unsigned int i = 0; i < 10; i++) {
        ids.push_back(1 - i);
    }
    std::sort(ids.begin(),ids.end());
    std::cout << ids[0] <<std::endl;




    return 0;
}