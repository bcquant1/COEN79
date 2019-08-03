//
//  main.cpp
//  lab5
//
//  Created by Brandon Quant on 2/7/19.
//  Copyright Â© 2019 SCU. All rights reserved.


#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include "mystring.h"

// Invariants:
// current_length and allocated can't be less than 0
// length of a string cannot be bigger than the memory that has been allocated

namespace coen79_lab5{

string::string(const char str []){
    current_length = strlen(str);
    allocated = current_length + 1;
    characters = new char[allocated];
    std::strncpy(characters, str, current_length);
}
string::string(char c){
    current_length = 1;
    allocated = current_length + 1;
    characters = new char[allocated];
    characters[0] = c;
    characters[1] = '\0';
}
string::string(const string& source){
    current_length = source.current_length;
    allocated= current_length + 1;
    characters = new char[allocated];
    for (int i = 0; i < source.current_length; i++){
        characters[i] = source.characters[i];
    }
}
string::~string( ){
    delete [] characters;
    characters = NULL;
    allocated = 0;
    current_length = 0;
}

// MODIFICATION MEMBER FUNCTIONS
void string::operator +=(const string& addend){
    *this += addend.characters;
}
void string::operator +=(const char addend[ ]){
    assert(addend[strlen(addend)] == '\0');
    if (current_length + std::strlen(addend) > allocated){
        reserve(current_length + strlen(addend) + 1);
    }
    for (int i = 0; i < strlen(addend); i++){
        characters[current_length] = addend[i];
        current_length++;
    }
    characters[current_length] = '\0';
}
void string::operator +=(char addend){
    if(current_length + 1 > allocated){
        reserve (current_length + 1);
    }
    characters[current_length] = addend;
    current_length++;
    characters[current_length] = '\0';
}
void string::reserve(size_t n){
    char *tmp;
    if (n == allocated){
        return;
    }
    if (n < current_length + 1){
        n = current_length + 1;
    }
    tmp = new char[n];
    strncpy (tmp, characters, n);
    delete [] characters;
    characters = tmp;
    allocated = n + 1;
}
string& string::operator =(const string& source){
    if(this == &source){
        return *this;
    }
    if (source.current_length > allocated){
        reserve(source.current_length + 1);
    }
    for (int i = 0; i <= source.current_length; i++){
        characters[i] = source.characters[i];
    }
    current_length = source.current_length;
    characters[current_length] = '\0';
    return *this;
}
void string::insert(const string& source, unsigned int position){
    assert(position <= current_length);
    if (allocated < (current_length + source.current_length)){
        reserve(current_length + source.current_length);
    }
    for (size_t i = current_length; i > position; i--){
        characters[i] = characters[i-1];
    }
    for (int i = 0; i < source.current_length; i++){
        characters[position+i] = source.characters[i];
    }
    current_length = current_length + source.current_length;
}
void string::dlt(unsigned int position, unsigned int num){
    assert((position + num) <= current_length);
    for (int i = position; i < current_length; i++){
        characters[i] = characters[num+i];
    }
    current_length = current_length - num;
}
void string::replace(char c, unsigned int position){
    assert(position < current_length);
    characters[position] = c;
}
void string::replace(const string& source, unsigned int position){
    assert((position + source.length()) <= current_length);
    for (int i = 0; i < source.length(); i++){
        characters[position] = source.characters[i];
        position++;
    }
}

// CONSTANT MEMBER FUNCTIONS
char string::operator [ ](size_t position) const{
    assert(position < current_length);
    return characters[position];
}
int string::search(char c) const{
    for (int i = 0; i < current_length; i++){
        if (characters[i] == c){
            return i;
        }
    }
    return -1;
}
int string::search(const string& substring) const{
    int total_length = 0;
    for (int i = 0; i< current_length; i++){
        if (i + substring.current_length <= current_length){
            for (int j = 0; j < substring.current_length; j++){
                if (characters[i+j] == substring.characters[j]){
                    total_length++;
                }
            }
            if (total_length == substring.current_length){
                return i;
            }
        }
        total_length = 0;
    }
    return -1;
}
unsigned int string::count(char c) const{
    int count = 0;
    for (int i = 0; i < current_length; i++){
        if (characters[i] == c){
            count++;
        }
    }
    return count;
}

// FRIEND FUNCTIONS
std::ostream& operator <<(std::ostream& outs, const string &source){
    for (int i = 0; i < source.current_length; i++){
        outs << source.characters[i];
    }
    return outs;
}
bool operator ==(const string& s1, const string& s2){
    if (s1.current_length != s2.current_length){
        return false;
    }
    for (int i = 0; i < s1.current_length; i++){
        if (s1.characters[i] != s2.characters[i]){
            return false;
        }
    }
    return true;
}
bool operator !=(const string& s1, const string& s2){
    if (s1.current_length != s2.current_length){
        return true;
    }
    for (int i = 0; i < s1.current_length; i++){
        if (s1.characters[i] != s2.characters[i]){
            return true;
        }
    }
    return false;
}
bool operator > (const string& s1, const string& s2){
    size_t length;
    if (s1.current_length > s2.current_length){
        length = s1.current_length;
    }
    else{
        length = s2.current_length;
    }
    if(strncmp(s1.characters,s2.characters,length) > 0){
        return true;
    }
    else {
        return false;
    }
}
bool operator < (const string& s1, const string& s2){
    size_t length;
    if (s1.current_length > s2.current_length){
        length = s1.current_length;
    }
    else{
        length = s2.current_length;
    }
    if(strncmp(s1.characters,s2.characters,length) < 0){
        return true;
    }
    else {
        return false;
    }
}
bool operator >=(const string& s1, const string& s2){
    size_t length;
    if (s1.current_length > s2.current_length){
        length = s1.current_length;
    }
    else{
        length = s2.current_length;
    }
    if(strncmp(s1.characters,s2.characters,length) >= 0){
        return true;
    }
    else {
        return false;
    }
}
bool operator <=(const string& s1, const string& s2){
    size_t length;
    if (s1.current_length > s2.current_length){
        length = s1.current_length;
    }
    else{
        length = s2.current_length;
    }
    if(strncmp(s1.characters,s2.characters,length) <= 0){
        return true;
    }
    else {
        return false;
    }
}

// NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2){
        string tmp;
        tmp += s1;
        tmp += s2;
        return tmp;
    }
    string operator +(const string& s1, const char addend[ ]){
        string tmp;
        tmp += s1;
        tmp += addend;
        return tmp;
    }
    std::istream& operator >> (std::istream& ins, string& target){
        target= "";
        char a;
        while ((ins) && isspace(ins.peek())){
            ins.ignore();
        }
        while (!(ins.eof()) && !isspace(ins.peek())){
            ins >>a;
            target += a;
        }
       
        return ins;
    }
}

