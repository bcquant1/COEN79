//
//  random.cpp
//  Lab2Part2
//
//  Created by Brandon Quant on 1/17/19.
//  Copyright Â© 2019 SCU. All rights reserved.
//

#include <stdio.h>
#include "random.h"
#include <iostream>
#include <cassert>

using namespace std;

namespace coen79_lab2 {

    rand_gen::rand_gen(int newseed, int newmultiplier, int newincrement, int newmodulus){
        seed = newseed;
        multiplier = newmultiplier;
        increment = newincrement;
        modulus = newmodulus;
    }
    
    void rand_gen::set_seed(int new_seed){
        seed = new_seed;
    }

    int rand_gen::next(){
        int product = (multiplier * seed + increment) % modulus;
        set_seed(product);
        return product;
    }

    void rand_gen::print_info(){
        cout << "Seed: " << seed <<endl;
        cout << "Multiplier: " << multiplier <<endl;
        cout << "Increment: " << increment <<endl;
        cout << "Modulus: " << modulus <<endl;
    }

}
