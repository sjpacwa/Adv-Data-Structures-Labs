// FILE: sequence.cpp
// IMPLEMENTS: The functions of the sequence class
// WRITTEN BY: Stephen and Peter
// INVARIANT of the sequence class
//   Nodes are stored in a sequence.
//   The head pointer points to the first node in the list.
//   The tail pointer points to the last node in the list.
//   The cursor points to the current node position.
//   The precursor always points to the node before cursor.
//   When the tail pointer and head pointer are both NULL the list is empty.

#include <cassert>
#include <iostream>
#include "sequence.h"

namespace coen70_lab7
{
    sequence::sequence() {
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }
    
    sequence::sequence(const sequence& source) {
        *this = source;
        
        /*node place = source->head_ptr;
        head_ptr = new node(source->head_ptr.data(), NULL);
        node current = head_ptr;
        while(place.link() != NULL) {
            current.set_link(new node(place.link().data(), NULL));
            if(source.precursor == place)
                precursor = current;
            if(source.current == place)
                cursor = current;
            current = current.link();
            place = place.link();
        }
        
        tail_ptr = current;
        many_nodes = place.many_nodes;*/
    }
    
    sequence::~sequence() {
        node *check = head_ptr;
        node *next;
        while(check->link() != NULL) {
            next = check->link();
            delete check;
            check =  next;
        }
        head_ptr = NULL;
        tail_ptr = NULL;
        many_nodes = 0;
    }
    
    void sequence::start() {
        cursor = head_ptr;
        precursor = NULL;
    }
    
    void sequence::end() {
        cursor = tail_ptr;
        precursor = head_ptr;
        
        if(many_nodes <= 1)
            precursor = NULL;
        
        for(int i = 0; precursor != NULL && i < many_nodes - 1; i++) {
            precursor->set_link(precursor->link());
        }
    }
    
    void sequence::advance() {
        assert(is_item());
        
        precursor = cursor;
        cursor = cursor->link();
    }
    
    void sequence::insert(const value_type& entry) {
        if(precursor == NULL) {
            list_head_insert(head_ptr, entry);
            head_ptr->set_link(cursor);
            cursor = head_ptr;
            if(tail_ptr == NULL)
                tail_ptr = head_ptr;
        } else {
            list_insert(precursor, entry);
            precursor->link()->set_link(cursor);
            cursor = precursor->link();
        }
        ++many_nodes;
    }
    
    void sequence::attach(const value_type& entry) {
        if(precursor == NULL && cursor == NULL) {
            insert(entry);
            return;
        }
        
        if(cursor == NULL) {
            list_insert(precursor, entry);
            cursor = precursor->link();
            tail_ptr = cursor;
        } else {
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = precursor->link();
            if(cursor->link() == NULL)
                tail_ptr = cursor;
        }
        ++many_nodes;
    }
    
    void sequence::operator =(const sequence& source) {
        list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
        list_piece(source.cursor, NULL, cursor, tail_ptr);
        if (precursor != NULL)
            precursor->set_link(cursor);
        if (precursor == NULL && source.head_ptr != NULL)
            head_ptr = cursor;
        many_nodes = source.many_nodes;
    }
    
    void sequence::remove_current() {
        assert(is_item());
        
        if(cursor == tail_ptr) {
            delete tail_ptr;
            precursor->set_link(NULL);
            tail_ptr = precursor;
            cursor = NULL;
        } else {
            if (precursor != NULL)
                list_remove(precursor);
            else
                list_remove_at(head_ptr, 1);
        }
        
        --many_nodes;
    }
    
    sequence::size_type sequence::size() const {
        return many_nodes;
    }
    
    bool sequence::is_item() const {
        return cursor != NULL;
    }
    
    node::value_type sequence::current() const {
        assert(is_item());
        
        return cursor->data();
    }
}