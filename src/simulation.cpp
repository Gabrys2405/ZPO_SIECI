// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)
//
// Created by majga on 20.12.2021.
//
#include "../include/simulation.hpp"

void simulate(Factory& f ,TimeOffset d,const std::function<void(Factory&, Time)>& rf){
    if (f.is_consistent()){
        rf(f,d);
        for(TimeOffset time = 1; time <= d; time++){
            f.do_deliveries(time);
            f.do_package_passing();
            f.do_work(time);
        }
       }
    else{
        throw std::logic_error("Factory is not consistent");

    }
}

// 3b: Maciasz (405560), Maj (406094), Łuczak (405699)