/*
 * Sequence.cpp
 * Written by: Stephen Pacwa and James Olivas
 * 10/4/2016
 * Implementation file for sequence class
 * See header file for information
 */

#include <cstdlib>  //Provides size_t
#include <cassert>  //Provides assert
#include "sequence.h"

#include <iostream>

using namespace coen70_lab3;

sequence::sequence() {
    used = 0;
    current_index = 0;
}

void sequence::start() {
    current_index = 0;
}

void sequence::advance() {
    assert(is_item());
    
    ++current_index;
}

void sequence::insert(const value_type& entry) {
    assert(size() < CAPACITY);

    if(is_item()) {
        for(int i = used; i > current_index; i--)
            data[i] = data[i - 1];
        data[current_index] = entry;
    } else {
        for(int i = used; i > 0; i--)
            data[i] = data[i - 1];
        data[0] = entry;
        current_index = 0;
    }
    ++used;
}

void sequence::attach(const value_type& entry) {
    assert(size() < CAPACITY);
    
    if(is_item()) {
        for(int i = used; i > current_index; i--)
            data[i] = data[i - 1];
        data[++current_index] = entry;
    } else {
        data[current_index] = entry;
    }
    
    ++used;
}

void sequence::remove_current() {
    assert(is_item());
    
    for(int i = current_index; i < used - 1; i++)
        data[i] = data[i + 1];
    --used;
}

void sequence::insert_front(const value_type& entry) {
    assert(size() < CAPACITY);
    
    for(int i = used; i > 0; i--)
        data[i] = data[i - 1];
    data[0] = entry;
    current_index = 0;
    ++used;
}

void sequence::remove_front() {
    if(size() == 0)
        return;
    
    for(int i = 0; i < used; i++)
        data[i] = data[i + 1];
    --used;
}

void sequence::attach_back(const value_type& entry) {
    assert(size() < CAPACITY);
    
    data[used] = entry;
    ++used;
    ++current_index;
}

void sequence::end() {
    if(used == 0)
        current_index = 0;
    else
        current_index = used - 1;
}

coen70_lab3::sequence::size_type sequence::size() const {
    return used;
}

bool sequence::is_item() const {
    if(current_index + 1 <= used)
        return true;
    else
        return false;
}

coen70_lab3::sequence::value_type sequence::current() const {
    return data[current_index];
}

sequence sequence::operator+(const sequence& seq) {
    assert(this->size() + seq.size() < CAPACITY);
    
    sequence newSeq;
    
    for(int i = 0; i < this->size(); i++) {
        newSeq.data[i] = this->data[i];
        ++newSeq.used;
    }
    int place = newSeq.size();
    for(int i = 0; i < seq.size(); i++) {
        newSeq.data[place + i] = seq.data[i];
        ++newSeq.used;
    }
   
    return newSeq;
}

void sequence::operator+=(const sequence& seq) {
    assert(this->size() + seq.size() < CAPACITY);
    
    int place = this->used;
    for(int i = 0; i < seq.size(); i++) {
        this->data[place + i] = seq.data[i];
        ++this->used;
    }
}