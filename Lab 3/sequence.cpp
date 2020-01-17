//
//  sequence.cpp
//  Lab3
//
//  Created by Brandon Quant on 1/24/19.
//  Copyright Â© 2019 SCU. All rights reserved.
//

#include <stdio.h>
#include "sequence1.h"
#include <math.h>

using namespace std;

namespace coen79_lab3{

sequence::sequence(){
    used=0;
    current_index=0;
}

void sequence::start(){
    current_index=0;
}
void sequence::end(){
    current_index=used-1;
}
void sequence::last(){
    current_index=CAPACITY-1;
}
void sequence::advance(){
    assert(is_item());
    
    if(current_index < CAPACITY - 1){
        current_index++;
    }
}
void sequence::retreat(){
    if (current_index>0)
        current_index--;
}
void sequence::insert(const value_type& entry){
    assert(size()<CAPACITY);
    size_t i;
    
    if(!is_item()){
        current_index = 0;
    }

    for (i=used;i>current_index;i--){
        data[i]=data[i-1];
    }
    data[current_index]=entry;
    used++;
}
void sequence::insert_front(const value_type& entry){
    assert(size()<CAPACITY);
    start();
    insert(entry);
}
void sequence::attach(const value_type& entry){
    assert(size()<CAPACITY);
    size_t i;
    if (is_item()){
        for (i=used-1;i>current_index;i--)
            data[i]=data[i-1];
        data[current_index]=entry;
        used++;
    }
    else{
        attach_back(entry);
    }
}
void sequence::attach_back(const value_type& entry){
    assert(size()<CAPACITY);
    data[used]=entry;
    current_index=used;
    used++;
}
void sequence::remove_current(){
    assert(is_item());
    size_t i;
    for (i=current_index;i<used-1;i++)
        data[i]=data[i+1];
    used--;
}
void sequence::remove_front(){
    start();
    if (is_item())
        remove_current();
}

// CONSTANT MEMBER FUNCTINOS
size_type sequence::size() const{
    return used;
}
bool sequence::is_item() const{
    return (current_index<used);
}
value_type sequence::current() const{
    assert(is_item());
    return data[current_index];
    
//    if (is_item())
//        return data[current_index];
//    return false;
}

//size_type index() const { return current_index; }


// Subscript operator
value_type sequence::operator[](int index) const{
    assert(index<used);
    return data[index];
}


// Homework Question Functions
double sequence::mean() const{
    int i;
    value_type sum=0;
    for (i=0;i<used;i++){
        sum += data[i];
    }
    return sum/used;
}
double sequence::standardDeviation() const{
    double sum = 0.0;
    double avg = mean();
    for (int i = 0; i < used; i++){
        sum += (data[i]-avg)*(data[i]-avg);
    }
    return pow(sum/used,0.5);
}

    // NON-MEMBER functions for the sequence class
sequence operator+(sequence& lhs, sequence& rhs){
    sequence new_sequence;
    size_t i;
    new_sequence=rhs;
    
    lhs.start();
    new_sequence.end();
    new_sequence.advance();
    for (i=0;i<lhs.size();i++){
        new_sequence.insert(lhs.current());
        lhs.advance();
        new_sequence.advance();
    }
    return new_sequence;
}
sequence operator+=(sequence& lhs, sequence& rhs){
    size_t i;
    lhs.end();
    lhs.advance();
    rhs.start();
    for (i=0;i<rhs.size();i++){
        lhs.insert(rhs.current());
        lhs.advance();
        rhs.advance();
    }
    return lhs;
}
                       
                       
    // Homework Question Functions
value_type summation(const sequence &s){
    int i;
    sequence temp = s;
    double sum=0;
    for (i=0;i<temp.size();i++){
        sum += temp[i];
    }
    return sum;
}

}
