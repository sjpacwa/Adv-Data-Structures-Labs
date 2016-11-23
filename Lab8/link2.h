// FILE: node2.h (part of the namespace scu_coen70_6B)
// PROVIDES: A template class for a node in a linked list, and list manipulation
// functions. The template parameter is the type of the data in each node.
// This file also defines a template class: node_iterator<Item>.
// The node_iterator is a forward iterators with two constructors:
// (1) A constructor (with a node<Item>* parameter) that attaches the iterator
// to the specified node in a linked list, and (2) a default constructor that
// creates a special iterator that marks the position that is beyond the end of a
// linked list. There is also a const_node_iterator for use with
// const node<Item>* .
//
// TYPEDEF for the node<Item> template class:
//   Each node of the list contains a piece of data and a pointer to the
//   next node. The type of the data (node<Item>::value_type) is the Item type
//   from the template parameter. The type may be any of the built-in C++ classes
//   (int, char, ...) or a class with a default constructor, an assignment
//   operator, and a test for equality (x == y).
// NOTE:
//   Many compilers require the use of the new keyword typename before using
//   the expression node<Item>::value_type. Otherwise
//   the compiler doesn't have enough information to realize that it is the
//   name of a data type.
//
// CONSTRUCTOR for the node<Item> class:
//   node(
//     const Item& init_data = Item(),
//     node<Item>* init_link = NULL
//   )
//     Postcondition: The node contains the specified data and link.
//     NOTE: The default value for the init_data is obtained from the default
//     constructor of the Item. In the ANSI/ISO standard, this notation
//     is also allowed for the built-in types, providing a default value of
//     zero. The init_link has a default value of NULL.
//
// NOTE about two versions of some functions:
//   The data function returns a reference to the data field of a node and
//   the link function returns a copy of the link field of a node.
//   Each of these functions comes in two versions: a const version and a
//   non-const version. If the function is activated by a const node, then the
//   compiler choses the const version (and the return value is const).
//   If the function is activated by a non-const node, then the compiler choses
//   the non-const version (and the return value will be non-const).
// EXAMPLES:
//    const node<int> *c;
//    c->link( ) activates the const version of link returning const node<Item>*
//    c->data( ) activates the const version of data returning const Item&
//    c->data( ) = 42; ... is forbidden
//    node<int> *p;
//    p->link( ) activates the non-const version of link returning node<Item>*
//    p->data( ) activates the non-const version of data returning Item&
//    p->data( ) = 42; ... actually changes the data in p's node
//
// MEMBER FUNCTIONS for the node<Item> class:
//   const Item& data( ) const <----- const version
//   and
//   Item& data( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is a reference to the  data from this node.
//
//   const node<Item>* link( ) const <----- const version
//   and
//   node<Item>* link( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is the link from this node.
//
//   void set_data(const Item& new_data)
//     Postcondition: The node now contains the specified new data.
//
//   void set_link(node<Item>* new_link)
//     Postcondition: The node now contains the specified new link.
//
// FUNCTIONS in the linked list toolkit:
//   template <class Item>
//   void list_clear(node<Item>*& head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: All nodes of the list have been returned to the heap,
//     and the head_ptr is now NULL.
//
//   template <class Item>
//   void list_copy
//   (const node<Item>* source_ptr, node<Item>*& head_ptr, node<Item>*& tail_ptr)
//     Precondition: source_ptr is the head pointer of a linked list.
//     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
//     a new list that contains the same items as the list pointed to by
//     source_ptr. The original list is unaltered.
//
//   template <class Item>
//   void list_head_insert(node<Item>*& head_ptr, const Item& entry)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: A new node containing the given entry has been added at
//     the head of the linked list; head_ptr now points to the head of the new,
//     longer linked list.
//
//   template <class Item>
//   void list_head_remove(node<Item>*& head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list, with at
//     least one node.
//     Postcondition: The head node has been removed and returned to the heap;
//     head_ptr is now the head pointer of the new, shorter linked list.
//
//   template <class Item>
//   void list_insert(node<Item>* previous_ptr, const Item& entry)
//     Precondition: previous_ptr points to a node in a linked list.
//     Postcondition: A new node containing the given entry has been added
//     after the node that previous_ptr points to.
//
//   template <class Item>
//   size_t list_length(const node<Item>* head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The value returned is the number of nodes in the linked
//     list.
//
//   template <class NodePtr, class SizeType>
//   NodePtr list_locate(NodePtr head_ptr, SizeType position)
//   The NodePtr may be either node<Item>* or const node<Item>*
//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0.
//     Postcondition: The return value is a pointer that points to the node at
//     the specified position in the list. (The head node is position 1, the
//     next node is position 2, and so on). If there is no such position, then
//     the null pointer is returned.
//
//   template <class Item>
//   void list_remove(node<Item>* previous_ptr)
//     Precondition: previous_ptr points to a node in a linked list, and this
//     is not the tail node of the list.
//     Postcondition: The node after previous_ptr has been removed from the
//     linked list.
//
//   template <class NodePtr, class Item>
//   NodePtr list_search
//   (NodePtr head_ptr, const Item& target)
//   The NodePtr may be either node<Item>* or const node<Item>*
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The return value is a pointer that points to the first
//     node containing the specified target in its data member. If there is no
//     such node, the null pointer is returned.
//
// DYNAMIC MEMORY usage by the toolkit:
//   If there is insufficient dynamic memory, then the following functions throw
//   bad_alloc: the constructor, list_head_insert, list_insert, list_copy.

#ifndef SCU_COEN70_NODE2_H
#define SCU_COEN70_NODE2_H
#include <cstdlib>   // Provides NULL and size_t
#include <iterator>  // Provides iterator and forward_iterator_tag
#include <cassert>    // Provides assert

namespace scu_coen70_6B
{
    template <class Item>
    class node
    {
    public:
        // TYPEDEF
        typedef Item value_type;
        // CONSTRUCTOR
        node(const Item& init_data=Item( ), node<Item>* init_link=NULL)
        { data_field = init_data; link_field = init_link; }
        // MODIFICATION MEMBER FUNCTIONS
        Item& data( ) { return data_field; }
        node<Item>* link( ) { return link_field; }
        void set_data(const Item& new_data) { data_field = new_data; }
        void set_link(node<Item>* new_link) { link_field = new_link; }
        // CONST MEMBER FUNCTIONS
        const Item& data( ) const { return data_field; }
        const node<Item>* link( ) const { return link_field; }
    private:
        Item data_field;
        node *link_field;
    };

#pragma mark - Linked List Functions
    // FUNCTIONS to manipulate a linked list:
    template <class Item>
    void list_clear(node<Item>*& head_ptr);

    template <class Item>
    void list_copy
    (const node<Item>* source_ptr, node<Item>*& head_ptr, node<Item>*& tail_ptr);

    template <class Item>
    void list_head_insert(node<Item>*& head_ptr, const Item& entry);

    template <class Item>
    void list_head_remove(node<Item>*& head_ptr);

    template <class Item>
    void list_insert(node<Item>* previous_ptr, const Item& entry);

    template <class Item>
    std::size_t list_length(const node<Item>* head_ptr);

    template <class NodePtr, class SizeType>
    NodePtr list_locate(NodePtr head_ptr, SizeType position);

    template <class Item>
    void list_remove(node<Item>* previous_ptr);

    template <class NodePtr, class Item>
    NodePtr list_search(NodePtr head_ptr, const Item& target);

    // FORWARD ITERATORS to step through the nodes of a linked list
    // A node_iterator of can change the underlying linked list through the
    // * operator, so it may not be used with a const node. The
    // node_const_iterator cannot change the underlying linked list
    // through the * operator, so it may be used with a const node.
    // WARNING:
    // This classes use std::iterator as its base class;
    // Older compilers that do not support the std::iterator class can
    // delete everything after the word iterator in the second line:

#pragma mark - Node Iterator
    template <class Item>
    class node_iterator
    // : public std::iterator<std::forward_iterator_tag, Item>
    {
    public:
        node_iterator(node<Item>* initial = NULL)
        { current = initial; }
        Item& operator *( ) const
        { return current->data( ); }
        node_iterator& operator ++( ) // Prefix ++
        {
            current = current->link( );
            return *this;
        }
        node_iterator operator ++(int) // Postfix ++
        {
            node_iterator original(current);
            current = current->link( );
            return original;
        }
        bool operator ==(const node_iterator other) const
        { return current == other.current; }
        bool operator !=(const node_iterator other) const
        { return current != other.current; }
    private:
        node<Item>* current;
    };

#pragma mark - Const Node Iterator
    template <class Item>
    class const_node_iterator
    // : public std::iterator<std::forward_iterator_tag, const Item>
    {
    public:
        const_node_iterator(const node<Item>* initial = NULL)
        { current = initial; }
        const Item& operator *( ) const
        { return current->data( ); }
        const_node_iterator& operator ++( ) // Prefix ++
        {
            current = current->link( );
            return *this;
        }
        const_node_iterator operator ++(int) // Postfix ++
        {
            const_node_iterator original(current);
            current = current->link( );
            return original;
        }
        bool operator ==(const const_node_iterator other) const
        { return current == other.current; }
        bool operator !=(const const_node_iterator other) const
        { return current != other.current; }
    private:
        const node<Item>* current;
    };

#pragma mark - Implementation
// *** IMPLEMENTATION ***

    // IMPLEMENTS: The functions of the node template class and the
    // linked list toolkit (see node2.h for documentation).
    //
    // NOTE:
    //   Since node is a template class, this file is included in node2.h.
    //   Therefore, we should not put any using directives in this file.
    //
    // INVARIANT for the node class:
    //   The data of a node is stored in data_field, and the link in link_field.
    
    template <class Item>
    void list_clear(node<Item>*& head_ptr)
    // Library facilities used: cstdlib
    {
        while (head_ptr != NULL)
            list_head_remove(head_ptr);
    }

    template <class Item>
    void list_copy(
                   const node<Item>* source_ptr,
                   node<Item>*& head_ptr,
                   node<Item>*& tail_ptr
                   )
    // Library facilities used: cstdlib
    {
        head_ptr = NULL;
        tail_ptr = NULL;
        
        // Handle the case of the empty list
        if (source_ptr == NULL)
            return;
        
        // Make the head node for the newly created list, and put data in it
        list_head_insert(head_ptr, source_ptr->data( ));
        tail_ptr = head_ptr;
        
        // Copy rest of the nodes one at a time, adding at the tail of new list
        source_ptr = source_ptr->link( );
        while (source_ptr != NULL)
        {
            list_insert(tail_ptr, source_ptr->data( ));
            tail_ptr = tail_ptr->link( );
            source_ptr = source_ptr->link( );
        }
    }

    template <class Item>
    void list_head_insert(node<Item>*& head_ptr, const Item& entry)
    {
        head_ptr = new node<Item>(entry, head_ptr);
    }

    template <class Item>
    void list_head_remove(node<Item>*& head_ptr)
    {
        node<Item> *remove_ptr;
        
        remove_ptr = head_ptr;
        head_ptr = head_ptr->link( );
        delete remove_ptr;
    }

    template <class Item>
    void list_insert(node<Item>* previous_ptr, const Item& entry)
    {
        node<Item> *insert_ptr;
        
        insert_ptr = new node<Item>(entry, previous_ptr->link( ));
        previous_ptr->set_link(insert_ptr);
    }

    template <class Item>
    std::size_t list_length(const node<Item>* head_ptr)
    // Library facilities used: cstdlib
    {
        const node<Item> *cursor;
        std::size_t answer;
        
        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            ++answer;
        
        return answer;
    }

    template <class NodePtr, class SizeType>
    NodePtr list_locate(NodePtr head_ptr, SizeType position)
    // Library facilities used: cassert, cstdlib
    {
        NodePtr cursor;
        SizeType i;
        
        assert(0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); ++i)
            cursor = cursor->link( );
        return cursor;
    }

    template <class Item>
    void list_remove(node<Item>* previous_ptr)
    {
        node<Item> *remove_ptr;
        
        remove_ptr = previous_ptr->link( );
        previous_ptr->set_link(remove_ptr->link( ));
        delete remove_ptr;
    }

    template <class NodePtr, class Item>
    NodePtr list_search(NodePtr head_ptr, const Item& target)
    // Library facilities used: cstdlib
    {
        NodePtr cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            if (target == cursor->data( ))
                return cursor;
        return NULL;
    }
    
    template <class Item>
    void list_piece(const node<Item>* start_ptr, const node<Item>* end_ptr, node<Item>*& head_ptr, node<Item>*& tail_ptr)
    {
        head_ptr = NULL;
        tail_ptr = NULL;
        
        // Handle the case of the empty list.
        if (start_ptr == end_ptr)
            return;
        
        // Make the head node for the newly created list, and put data in it.
        list_head_insert(head_ptr, start_ptr->data( ));
        tail_ptr = head_ptr;
        
        // Copy the rest of the nodes one at a time, adding at the tail of new list.
        start_ptr = start_ptr->link( );
        while (start_ptr != end_ptr)
        {
            list_insert(tail_ptr, start_ptr->data( ));
            tail_ptr = tail_ptr->link( );
            start_ptr = start_ptr->link( );
        }
    }
    
}
#endif