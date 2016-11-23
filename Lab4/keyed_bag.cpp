/*
 * keyed_bag.cpp
 * Written by: Stephen Pacwa and Maggie Cai
 * 10/11/2016
 * Implementation file for the Keyed Bag class
 * See header file for information
 */

/*
 * Invariant for the keyed_bag class:
 * 1. The number of items in the bag is stored in used.
 * 2. When empty, the contents of the bag does not matter.
 * 3. When there is at least one item, data is stored between data[0] and data[used-1].
 * 4. When there is at least one item, keys are stored between keys[i] and keys[used-1].
 * 5. The index of data is the same as the index of its corresponding key.
 */

#include <cassert>
#include "keyed_bag.h"

namespace coen70_lab4 {
    bool keyed_bag::erase(const key_type& key) {
        for(int i = 0; i < used; ++i) {                         //Looks for key
            if(keys[i] == key) {
                for(int j = i; j < used - 1; ++j) {
                    data[j] = data[j+1];                        //Shifts all values left
                    keys[j] = keys[j+1];
                    return true;
                }
                --used;
            }
        }
        
        return false;
    }
    
    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert(size() < CAPACITY && !has_key(key));
        
        data[used] = entry;                                     //Inserts at end
        keys[used] = key;
        
        ++used;
    }
    
    void keyed_bag::operator+=(const keyed_bag& addend) {
        assert(size() + addend.size() <= CAPACITY);
        
        for(int i = 0; i < addend.used; i++) {                  //Scrolls through and inserts
            if(!this->has_key(addend.keys[i]))
                this->insert(addend.data[i], addend.keys[i]);
        }
    }
    
    bool keyed_bag::has_key(const key_type& key) const {
        for(int i = 0; i < used; i++) {                         //Looks for key and returns
            if(keys[i] == key)
                return true;
        }
        
        return false;
    }
    
    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key));
        
        for(int i = 0; i < used; i++) {                         //Returns if key exists
            if(keys[i] == key) {
                return data[i];
            }
        }
        
        return 0;
    }
    
    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        int num = 0;
        
        for(int i = 0; i < used; i++) {                         //Looks for all instances of key
            if(data[i] == target)
                ++num;
        }
        
        return num;
    }
    
    keyed_bag operator+(const keyed_bag& b1, const keyed_bag& b2) {
        assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);   //Uses operator+= to overcome non-member status
        
        keyed_bag b3;
        
        b3 += b1;
        b3 += b2;
        
        return b3;
    }
}

