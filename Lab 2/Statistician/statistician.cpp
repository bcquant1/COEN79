//
//  statistician.cpp
//  Lab2
//
//  Created by Brandon Quant on 1/17/19.
//  Copyright Â© 2019 SCU. All rights reserved.
//

#include <stdio.h>
#include "statistician.h"
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
    statistician::statistician(){
        count = 0.0;
        total = 0.0;
    }
    void statistician::next(double x){
        total += x;
        count++;
        if (length() == 1 || (x < tiniest)){
            tiniest = x;
        }
        if (length() == 1 || x > largest){
                largest = x;
        }
    }
 
    void statistician::reset(){
        count = 0.0;
        total = 0.0;
    }
    
    
    double statistician::mean() const{
        assert(length() > 0);
        return total/count;
    }
    
    double statistician::minimum() const{
        assert(length() > 0);
        return tiniest;
    }
    
    double statistician::maximum() const{
        return largest;
    }
    
    bool operator ==(const statistician &s1, const statistician &s2){
        if (s1.length() == 0 || s2.length() == 0){
            return (s1.length() == 0) && (s2.length() ==0);
        }
        else return (s1.length() == s2.length() && s1.mean() == s2.mean() && s1.sum() == s2.sum() && s1.maximum() == s2.maximum() && s1.minimum() == s2.minimum());
    }
    
    statistician operator+ (const statistician &s1, const statistician &s2){
        statistician tmp;
        tmp.count = s1.count + s2.count;
        tmp.total = s1.total + s2.total;
        if (s1.tiniest < s2.tiniest){
            tmp.tiniest = s1.tiniest;
        }
        else{
            tmp.tiniest = s2.tiniest;
        }
        if (s1.largest < s2.largest){
            tmp.largest = s2.largest;
        }
        else{
            tmp.largest = s1.largest;
        }
        return tmp;
    }
    
    statistician operator *(double scale, const statistician &s){
        statistician tmp;
        tmp.total = (scale * s.total);
        tmp.count = s.count;
        if (scale >= 0){
            tmp.tiniest = (scale * s.tiniest);
            tmp.largest = (scale * s.largest);
        }
        else if(scale < 0){
            tmp.largest = (scale * s.tiniest);
            tmp.tiniest = (scale * s.largest);
        }
        return tmp;
        
    }
    
}

