// FILE: bag6.h (part of the namespace scu_coen70_10)
// TEMPLATE CLASS PROVIDED: bag<Item>
//     (a container template class for a collection of items)
//
// TYPEDEFS for the bag<Item> class:
//   bag<Item>::value_type
//     bag<Item>::value_type is the data type of the items in the bag. It may
//     be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, a copy constructor, an assignment operator, and a
//     less-than operator forming a strict weak ordering.
//
//   bag<Item>::size_type
//     bag<Item>::size_type is the data type of any variable that keeps track
//     of how many items are in a bag.
//
// CONSTRUCTOR for the bag<Item> class:
//   bag( )
//     Postcondition: The bag is empty.
//
// MODIFICATION MEMBER FUNCTIONS for the bag<Item> class:
//   size_type erase(const Item& target)
//     Postcondition: All copies of target have been removed from the bag. The
//     return value is the number of copies removed (which could be zero).
//
//   bool erase_one(const Item& target)
//     Postcondition: If target was in the bag, then one copy of target has been
//     removed from the bag; otherwise the bag is unchanged. A true return value
//     indicates that one copy was removed; false indicates that nothing was
//     removed.
//
//   void insert(const Item& entry)
//     Postcondition: A new copy of entry has been inserted into the bag.
//
//   void operator +=(const bag& addend)
//     Postcondition: Each item in addend has been added to this bag.
//
// CONSTANT MEMBER FUNCTIONS for the bag<Item> class:
//   size_type size( ) const
//     Postcondition: Return value is the total number of items in the bag.
//
//   size_type count(const Item& target) const
//     Postcondition: Return value is number of times target is in the bag.
//
// NONMEMBER FUNCTIONS for the bag class:
//   bag operator +(const bag& b1, const bag& b2)
//     Postcondition: The bag returned is the union of b1 and b2.
//
// VALUE SEMANTICS for the bag class:
//   Assignments and the copy constructor may be used with bag objects.
//
// DYNAMIC MEMORY USAGE by the bag: 
//   If there is insufficient dynamic memory, then the following functions
//   throw bad_alloc: The constructors, insert, operator +=, operator +, and
//   the assignment operator.

#ifndef BAG6_H 
#define BAG6_H
#include <cassert>
#include <cstdlib>
#include "bintree.h"   // Provides binary_tree_node and related functions

namespace scu_coen70_10
{
    template <class Item>
    class bag
    {
    public:
        // TYPEDEFS
        typedef std::size_t size_type;
        typedef Item value_type;
        // CONSTRUCTORS and DESTRUCTOR
        bag( );
        bag(const bag& source);
        ~bag( );	
        // MODIFICATION functions
        size_type erase(const Item& target);
        bool erase_one(const Item& target);
        void insert(const Item& entry);
        void operator +=(const bag& addend);
        void operator =(const bag& source);	
        // CONSTANT functions
        size_type size( ) const;
        size_type count(const Item& target) const;
    private:
        binary_tree_node<Item> *root_ptr; // Root pointer of binary search tree
        void insert_all(binary_tree_node<Item>* addroot_ptr);
    };

    // NONMEMBER functions for the bag<Item> template class
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2);
}


// ----------------------
// Implementation section

namespace scu_coen70_10
{
    
    template <class Item>
    void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
    // Precondition: root_ptr is a root pointer of a non-empty binary
    // search tree.
    // Postcondition: The largest item in the binary search tree has been
    // removed, and root_ptr now points to the root of the new (smaller)
    // binary search tree. The reference parameter, removed, has been set
    // to a copy of the removed item.
    {
        assert(root_ptr != NULL);
        
        if(root_ptr->right() == NULL) {
            // there are no items to the right of this node, therefore it is the max
            removed = Item(root_ptr->data());
            bst_remove(root_ptr, root_ptr->data());
            return;
        }
        
        if (root_ptr->right()->is_leaf()) {
            //right child is the max
            removed = Item(root_ptr->right()->data());
            bst_remove(root_ptr, root_ptr->right()->data());
            return;
        }
        
        // there is a node to the right (so it is greater than this one)
        // recurse to the right child of this node
        bst_remove_max(root_ptr->right(), removed);
    }
    
    template <class Item>
    bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: If target was in the tree, then one copy of target
    // has been removed, and root_ptr now points to the root of the new
    // (smaller) binary search tree. In this case the function returns true.
    // If target was not in the tree, then the tree is unchanged (and the
    // function returns false).
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            return false;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            // Note: Any change made to root_ptr->left by this recursive
            // call will change the actual left pointer (because the return
            // value from the left() member function is a reference to the
            // actual left pointer.
            return bst_remove(root_ptr->left( ), target);
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            // Note: Any change made to root_ptr->right by this recursive
            // call will change the actual right pointer (because the return
            // value from the right() member function is a reference to the
            // actual right pointer.
            return bst_remove(root_ptr->right( ), target);
        }
        
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.
        
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right( );
            delete oldroot_ptr;
            return true;
        }
        
        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item in our left subtree.
        // Note: Any change made to root_ptr->left by bst_remove_max
        // will change the actual left pointer (because the return
        // value from the left() member function is a reference to the
        // actual left pointer.
        bst_remove_max(root_ptr->left(), root_ptr->data( ));
        return true;
    }
    
    template <class Item>
    typename bag<Item>::size_type bst_remove_all
    (binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: All copies of target have been removed from the tree
    // has been removed, and root_ptr now points to the root of the new
    // (smaller) binary search tree. The return value tells how many copies
    // of the target were removed.
    {
        /** STUDENT WORK
         ** Note: This implementation is similar to bst_remove, except that
         ** all occurrences of the target must be removed, and the return
         ** value is the number of copies that were removed.
         */
        
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            return 0;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            return bst_remove_all(root_ptr->left(), target);
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            return bst_remove_all(root_ptr->right(), target);
        }
        
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right( );
            delete oldroot_ptr;
            return 1;
        }
        
        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item in our left subtree. We then continue
        // searching for more copies of the target to remove.
        // This continued search must start at the current root (since
        // the maximum element that we moved up from our left subtree
        // might also be a copy of the target).
        bst_remove_max(root_ptr->left( ), root_ptr->data( ));
        return 1 + bst_remove_all(root_ptr, target);
    }
    
    template <class Item>
    bag<Item>::bag()
    {
        root_ptr = NULL;
    }
    
    template <class Item>
    bag<Item>::bag(const bag<Item>& source)
    // Library facilities used: bintree.h
    {
        root_ptr = tree_copy(source.root_ptr);
    }
    
    template <class Item>
    bag<Item>::~bag( )
    // Header file used: bintree.h
    {
        tree_clear(root_ptr);
    }
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::size( ) const
    // Header file used: bintree.h
    {
        return tree_size(root_ptr);
    }
    
    
    template <class Item>
    void bag<Item>::insert(const Item& entry)
    // Header file used: bintree.h
    {
        binary_tree_node<Item> *cursor = root_ptr;
        binary_tree_node<Item> *new_node = new binary_tree_node<Item>;
        bool done = false;
        
        if (root_ptr == NULL)
        {
            //***STUDENT WORK***
            new_node->set_data(entry);
            root_ptr = new_node;
            return;
        }
        
        do
        {
            if (cursor->data( ) >= entry)
            {   // Go left
                //***STUDENT WORK***
                if(cursor->left() == NULL) {
                    // Add node
                    new_node->set_data(entry);
                    cursor->left() = new_node;
                    return;
                }
                cursor = cursor->left();
            }
            else
            {   // Go right
                //***STUDENT WORK***
                if(cursor->right() == NULL) {
                    // Add node
                    new_node->set_data(entry);
                    cursor->right() = new_node;
                    return;
                }
                cursor = cursor->right();
            }
            
        } while (!done);
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::count(const Item& target) const
    {
        size_type answer = 0;
        binary_tree_node<Item> *cursor;
        
        cursor = root_ptr;
        //***STUDENT WORK***
        if(cursor == NULL)
            // Empty tree
            return 0;
        
        // Run through all nodes looking for target
        while (cursor != NULL) {
            if(cursor->data() == target) {
                // current node
                answer++;
            }
            if(target <= cursor->data() ){
                cursor = cursor->left();
            }
            else if (target > cursor->data()) {
                cursor = cursor->right();
            }
        }
        return answer;
    }
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::erase(const Item& target)
    {
        return bst_remove_all(root_ptr, target);
    }
    
    template <class Item>
    bool bag<Item>::erase_one(const Item& target)
    {
        return bst_remove(root_ptr, target);
    }
    
    template <class Item>
    void bag<Item>::operator =(const bag<Item>& source)
    // Header file used: bintree.h
    {
        //***STUDENT WORK***
        if(this->root_ptr == source.root_ptr)
            // check for self-assignment
            return;
        
        tree_clear(root_ptr);
        
        this->root_ptr = tree_copy(source.root_ptr);
    }
    
    template <class Item>
    void bag<Item>::operator +=(const bag<Item>& addend)
    {
        if (root_ptr == addend.root_ptr)
        {
            bag<Item> copy = addend;
            insert_all(copy.root_ptr);
        }
        else
            insert_all(addend.root_ptr);
    }
    
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
    {
        bag<Item> answer = b1;
        answer += b2;
        return answer;
    }
    
    template <class Item>
    void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
    // Precondition: addroot_ptr is the root pointer of a binary search tree that
    // is separate for the binary search tree of the bag that activated this
    // method.
    // Postcondition: All the items from the addroot_ptr's binary search tree
    // have been added to the binary search tree of the bag that activated this
    // method.
    {
        if (addroot_ptr != NULL)
        {
            insert(addroot_ptr->data( ));
            insert_all(addroot_ptr->left( ));
            insert_all(addroot_ptr->right( ));
        }
    }
}

#endif
