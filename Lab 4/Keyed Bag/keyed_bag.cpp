#include "keyed_bag.h"


namespace coen79_lab4{

keyed_bag::keyed_bag(){ // Constructor.
    used = 0;
}

void keyed_bag::erase(){ // Erase all values in the bag.
    used = 0;
}


bool keyed_bag::erase(const key_type& key){ // Remove an item from the bag if it is present.
    size_t i;
    for (i=0;i<used;i++)
        if (key == keys[i]){
            used--;
            keys[i]=keys[used];
            data[i]=data[used];
            return true;
        }
    return false;
}


void keyed_bag::insert(const value_type& entry, const key_type &key){ // Add a new entry.
    assert((size()<CAPACITY)&&!has_key(key));
    data[used]=entry;
    keys[used]=key;
    used++;
}

void keyed_bag::operator +=(const keyed_bag& addend){ // Overload the += operator.
    assert(size() + addend.size() <= CAPACITY);
    if (hasDuplicateKey(addend)){ // If there is a duplicate, run this.
        size_t i,size = addend.size();
        for (i=0;i<size;i++)
            if (!has_key(addend.keys[i])){ // Transferring the elements to data/keys.
                keys[used] = addend.keys[i];
                data[used] = addend.data[i];
                used++;
            }
    }
    else{ // Otherwise, copy the memory to data/keys.
    std::copy(addend.data,addend.data+addend.used,data+used);
    std::copy(addend.keys,addend.keys+addend.used,keys+used);
    used = addend.used + used;
    }
}

bool keyed_bag::has_key(const key_type& key) const{ // Checks if "key" exists in "keys".
    size_t i;
    for (i=0;i<used;i++)
        if (key==keys[i])
            return true;
    return false;
}

keyed_bag::value_type keyed_bag::get(const key_type& key) const{ // Return the value associated with key.
    assert(has_key(key));
    size_t i;
    for (i=0;i<used;i++)
        if (keys[i]==key)
            return data[i];
    return 0;
}

keyed_bag::size_type keyed_bag::size( ) const{ // Return the size of the bag.
    return used;
}

keyed_bag::size_type keyed_bag::count(const value_type& target) const{ // Count the total number of times the target is in the bag.
    size_t count=0,i;
    for (i=0;i<used;i++)
        if (data[i]==target)
            count++;
    return count;
}

bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{ // Returns true if there is a duplicate key between two bags.
    size_t i;
    for (i=0;i<used;i++)
        if (otherBag.has_key(keys[i]))
            return true;
    return false;
}

keyed_bag operator+(const keyed_bag& b1, const keyed_bag& b2){ // Overloading the + operator.
    keyed_bag tempbag; // Temp bag variable.
    tempbag = b1; // Valid value semantics.
    tempbag += b2; // Use overloaded += operator.
    return tempbag;
}
    
}
