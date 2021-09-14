#ifndef _bst_node
#define _bst_node
#include <iostream>
#include <utility>  //std::move , std::pair
#include <memory>  //std::unique_ptr

/** 
 * ********* Class node *********
 * 
 * template class for the nodes of Binary Search Tree 
 * each tree has several nodes
 * each node has its own associated pair of key and value
 * we define a unique pointer to each of the children of a parent node (left child and right child)
 * and a raw pointer to the parent node itself
 * k_t --> template for key type
 * v_t --> template for value type
*/
template<typename k_t, typename v_t>
struct _node{
    
    /** pair of key and value */
    std::pair<k_t,v_t> _pair;    
    /** unique pointer to right child */
    std::unique_ptr<_node> _right;
    /** unique pointer to left child */
    std::unique_ptr<_node> _left;
    /** raw pointer to parent node */
    _node* _parent;


    /** default constructor */
    _node() noexcept = default; 
    /** 
     * custom ctor - l_value reference 
     * it returns a node of input pair
     * no implicit conversion from pair to node --> explicit
     */
    explicit _node (const std::pair<k_t, v_t>& pair) noexcept: _pair(pair) {}
    /**
     * custom ctor - r_value reference
     * it returns a node of input pair
     * no implicit conversion from pair to node --> explicit
     */
    explicit _node (std::pair<k_t, v_t>&& pair) noexcept: _pair(std::move(pair)) {}
    /**
     * custom ctor
     * to construct a new left or right child for a parent node
     * @param x unique pointer to the node to copy from (we use it for copy semantics)
     * @param parent raw pointer to the parent node
     */
   explicit _node (const std::unique_ptr<_node>& x, _node* parent) noexcept :  //explicit because the argument raw pointer parent 
            _pair{x->_pair}, _parent{parent}                                                                  // is "this"
            {    
            //right
            if (x->_right){        // if x is a right child
                _right.reset(new _node{x->_right, this});  //this node is the parent of its child
            }
            else{_right.reset();}   //if it is not a right child, _right points to nullptr
            // left
            if (x->_left){        //if x is a left child
                _left.reset(new _node{x->_left, this});
            }
            else{_left.reset();}   //if it is not a left child, _left points to nullptr

        }


    /** default destructor */
    ~_node() noexcept = default;  
    
};
#endif
