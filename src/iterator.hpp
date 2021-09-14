#ifndef _bst_iterator
#define _bst_iterator
#include "node.hpp"

#include <iterator>
#include <utility>
#include <memory>

/**
 * *********  Class iterator  **********
 * 
 * template class for forwarding iterator 
 * it is used to traverse the binary search tree in order
 * every instance of the iterator is a raw pointer to a node
 * it is a subclass of class bst
 * 
 * @param o --> template for the iterator
 * @param k_t --> template for key type
 * @param v_t --> template for value type
 */

template<typename O, typename k_t, typename v_t>
class _iterator{
    
    using node = _node<k_t,v_t>;
    node* current;    //raw pointer to the node
    
 public:
    using value_type = O;         
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    
     /**
      * function curr_node
      * returns a pointer to the current node 
      */
     node* current_ptr() const noexcept{return current;}

    /** default ctor */
    _iterator() noexcept = default;

    /**
     * custom ctor
     * input arg --> a pointer to node 
     * output --> an iterator pointing to x
     * no implicit conversion form node* to iterator
     */
    explicit _iterator(node* x) noexcept : current{x} {}

    /** default dtor */
    ~_iterator() noexcept = default;

    /**
     * pre-increment operator
     * returns an iterator which points to the next node, on right or left, with respect to ordering rule of bst
     */
    _iterator& operator++() {
        if (current->_right){
            current = current->_right.get();       //move current to the right child
            while(current->_left){
                current = current->_left.get();   //if the new current has any left node, traverse it and update current
            }
        }
        /** if current doesnt have right child, assign its parent to tmp
        * we visit back the parent node until either we meet
        * a node whose key is bigger or; if the starting node
        * is the right most one we return nullptr*/
        else{
            auto tmp = current->_parent;      // current doesnt have right child, assign its parent to tmp
            while(tmp && current != tmp->_left.get()) {     
                current = tmp;
                tmp = tmp->_parent;
            }
            current = tmp; 
        }
        return *this;  //this is a pointer to current. *this is current itself which is a pointer(iterator)
    }
    
    /**
     * post-increment operator
     * returns an iterator which points to the next node, on right or left with respect to ordering rule of bst
     */
     _iterator operator++(int) {
        auto tmp{*this};
        ++(*this);
        return tmp;
    }

    /**
     * arrow operator->
     * returns a pointer to the key of the node the iterator points to 
     */
     pointer operator->() const noexcept{ return &**this; } 

     /**
     * dereference operator*
     * returns the key of the node the iterator points to 
     * (for list example we had only one value in the node-> return current->value;)
     */
     reference operator*() const noexcept {return current->_pair.first;}

     /**
      * function value
      * returns the associated value of the node pointed to by iterator
      */
     v_t& value () {return current->_pair.second;}

      /**
      * function value - const
      * returns the const associated value of the node pointed to by iterator
      */
     const v_t& value () const {return current->_pair.second;}

     /** operator == */ 
     friend 
     bool operator==(const _iterator &a, const _iterator &b) noexcept{
     return a.current_ptr() == b.current_ptr();  //they are pointing to the same node
     }

     /** operator != */
     friend
     bool operator!=(const _iterator& a, const _iterator& b) noexcept {return !(a == b);} 

};

#endif
