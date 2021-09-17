#ifndef _bst
#define _bst
#include "node.hpp"
#include "iterator.hpp"

#include <iostream>
#include <iterator>
#include <utility>
#include <memory>
#include <vector>

/**
 * ********* Class bst **********
 * 
 * template class for Binary Search Tree
 * includes a pointer to the root node of tree
 
 * @param k_t --> template for key type
 * @param v_t --> template for value type
 * @param OP  --> template for Operator Comparison (OP) which is std::less<k_t>
 */ 

template <typename k_t, typename v_t, typename OP = std::less<k_t> >
class bst{

 private:   
    // overloading of classes node and iterator 
    using node =  _node< k_t, v_t>;
    using iterator = _iterator<k_t,k_t,v_t>;
    using const_iterator = _iterator<const k_t,k_t,v_t>;  //const key type for iterator

    /** private members of the class*/
    std::unique_ptr<node> head;
    OP comp;                         //comparision 
   
    /** auxiliary function */
    bool _is_empty() const noexcept {return head == nullptr;}

    /**
     * function left_most
     * returns an iterator to the node with smallest key value
     */ 
    iterator left_most() noexcept {
        auto tmp = head.get();  //raw pointer
        while (tmp->_left) {
            tmp = tmp->_left.get();
        }
        return iterator{tmp};
    }

    /**
     * function left_most - const
     * returns a const_iterator to the node with smallest key value
     */ 
    const_iterator left_most() const noexcept {
        auto tmp = head.get();  //raw pointer
        while (tmp->_left) {
            tmp = tmp->_left.get();
        }
        return const_iterator{tmp};
    }
    /** private function _insert 
     * is used to insert a new node in the tree
     * the bool is true if a new node has been allocated, false otherwise (i.e. the key already exists)
     * @return returns a pair of an iterator (pointing to the node) and a bool. 
     * */
    template<typename O>
    std::pair<iterator, bool> _insert(O&& x);    //declaration 

    /** @brief private function make_balance
     * is used to balance the tree
     * @param v --> vector of pairs
     * @param start --> first index
     * @param end --> last index
     */
    template <typename P>
    void make_balance(std::vector<P> v, int start, int end) ;  //declaration
                        
 public:

    //using of private function _insert in public part by defining insert function

    /** function insert - l-value reference to the pair . 
     * is used to insert a new node in the tree
     * @return  returns a pair of an iterator (pointing to the node) and a bool. 
     * the bool is true if a new node has been allocated, false otherwise (i.e. the key already exists)
     */
    std::pair<iterator, bool> insert(const std::pair<k_t, v_t>& x)  {return _insert(x);}

     /** function insert - r-value reference to the pair . 
     * is used to insert a new node in the tree
     * @return returns a pair of an iterator (pointing to the node) and a bool. 
     * the bool is true if a new node has been allocated, false otherwise (i.e. the key already exists)
      */
    std::pair<iterator, bool> insert(std::pair<k_t, v_t>&& x) {return _insert(std::move(x));}

    /** function to balance the tree - uses the private function make_balance 
     * it traverse the bst inorder and stores all the pairs in a vector v;
     * then clears the tree and insert the nodes
     * starting from the median of v and again recursively on the left and right subvectors of v
    */
    void balance();
    
    /**  default ctor */
    bst() noexcept = default;

    /** default dtor */
    ~bst() noexcept = default;

    // Move Semanticsb
    /** move ctor */
    //explicit bst(bst&& x) noexcept = default;
    bst(bst&& x) noexcept: head{std::move(x.head)}, comp{std::move(x.comp)} {}

    /** move assignment */
    //bst& operator=(bst&& x) noexcept = default;
    bst& operator=(bst&& x) noexcept{
        head = std::move(x.head);
        comp = std::move(x.comp);
        return *this;
    }

    // Deep Copy Semantics
    /** deep copy ctor */
    bst(const bst& x) : comp {x.comp} {
        if (x.head) {
            head.reset(new node{x.head, x.head->_parent});  //if x is not empty, we call node ctor recursively to copy it
        }
    }
 
    /** deep copy assignment */
    bst& operator=(const bst& x){
        clear();                  // clean my memory
        auto tmp{x};             //copy ctor
        *this = std::move(tmp);   //move assi
        return *this;
    }

    /** function begin 
     * uses the private function left_most
     * @return returns an iterator to the leftmost node in the tree */
    iterator begin() noexcept {return left_most();}

    /** function begin - const
     * uses the private function left_most
     * @return returns a const_iterator to the leftmost node in the tree */
    const_iterator begin() const noexcept {return left_most();}

    /** function cbegin 
     * @return returns a const_iterator to the leftmost node in the tree*/
    const_iterator cbegin() const noexcept {return left_most();}

    /** function end
     * @return returns an iterator to one past the last node */
    iterator end() noexcept {return iterator{nullptr};}

    /** function end - const
    * @return returns a const_iterator to one past the last node */
    const_iterator end() const noexcept {return const_iterator{nullptr};}

    /** function cend 
     *  @return returns an iterator to one past the last node */
    const_iterator cend() const noexcept {return const_iterator{nullptr};}

    /** function find 
     *  finds a given key. If the key is present, returns an iterator to the proper node, otherwise returns 
     *  a nullptr, equivalent to output of function end() .
     *  @return returns an iterator to the key or iterator to one past the last node */

    iterator find(const k_t& x) noexcept {

        auto tmp{head.get()};
        while (tmp)  {            // traverse the bst until tmp is nullptr  

            if(!comp(tmp->_pair.first,x) && !comp(x,tmp->_pair.first)){  //  key(x) == key(tmp) 
                return iterator{tmp};
                
            }
            else{                                  // otherwise move to the right or left child
                if( comp(tmp->_pair.first,x) ){    
                    tmp = tmp->_right.get();      // key(tmp) < key(x) --> traverse the right side of tree
                }
                else{ tmp = tmp->_left.get();}     // key(tmp) > key(x) --> traverse the left side of tree
            }
        
        }
        return end();   // calls "iterator end()" function - nullptr
    }


    /** function find - const
     *  finds a given key. If the key is present, returns an iterator to the proper node, otherwise returns 
     *  a nullptr, equivalent to output of function end() .
     *  @return returns a const_iterator to the key or iterator to one past the last node */

    const_iterator find(const k_t& x) const noexcept {
        
        auto tmp{head.get()};
        while (tmp)  {            // traverse the bst until tmp is nullptr  

            if(!comp(tmp->_pair.first,x) && !comp(x,tmp->_pair.first)){  //  key(x) == key(tmp) 
                return iterator{tmp};
                
            }
            else{                                  // otherwise move to the right or left child
                if( comp(tmp->_pair.first,x) ){    
                    tmp = tmp->_right.get();      // key(tmp) < key(x) --> traverse the right side of tree
                }
                else{ tmp = tmp->_left.get();}     // key(tmp) > key(x) --> traverse the left side of tree
            }
        }
        return end();   // calls "iterator end()" function - nullptr
    }

       

       
    /** function emplace 
     * inserts a new element into the container constructed in-place
     *  with the given args if there is no element with the key in the container
     *  
     * @param args both the key and the value of the node to be inserted 
     * @return a pair of an iterator (pointing to the node) and a bool
     */
    template <typename... Types >
    std::pair<iterator,bool> emplace(Types&&... args){           //forwarding reference         
        return insert(std::pair<k_t,v_t>{std::forward<Types>(args)...});  
    }

    /** Clears the content of the tree */
    void clear() noexcept {head.reset();} 
    


    /** function erase  
     * removes the element (if one exists) with the key equivalent to key.
     * @param x l-value reference of the key of the node to be deleted */
    void erase(const k_t& x);         //declaration


    /**  put-to operator*/
    friend                                    // friend since is_empty is private
    std::ostream& operator<<(std::ostream& os, const bst& x)  {
        if(x._is_empty()) {
            os << "WARNING: empty tree"; 
            return os;
        }

        for(auto& key : x){
            os << key << " ";
        }
        os << std::endl;
        return os;
    }


     /** subscripting operator 
     * Returns a reference to the value that is mapped
     * to a key equivalent to x, performing an insertion if such key does not already exist
     * @param x l-value reference to the key
     * @return reference to the value of the node
     */
    v_t& operator[](const k_t& x) noexcept {
         
        if(find(x) != iterator{nullptr}){   // if the key is already present
            auto address = find(x);         // we return the associated value
            return address.value();
        }
       
        auto def_value = v_t{};                   // otherwise we insert a new key with requested k_t and default v_t
        auto new_node = emplace(x,def_value);     // emplace uses insert function
        return new_node.first.value();         // function value is defined in class _iterator which returns the value 
                                               // of the node pointed to by iterator
    }


    /** subscripting operator 
     * Returns a reference to the value that is mapped
     * to a key equivalent to x, performing an insertion if such key does not already exist
     * @param x r-value reference to the key
     * @return reference to the value of the node
     */

    v_t& operator[](k_t&& x) noexcept {        //non-const because of rvalue

        auto tmp{std::move(x)};
        if(find(tmp) != iterator{nullptr}){   // if the key is already present
            auto address = find(tmp);         // we return the associated value
            return address.value();
        }
     
        auto def_value = v_t{};            // otherwise we insert a new key withe requested k_t nad default v_t
        auto new_node = emplace(tmp,def_value);     // emplace uses insert function
        return new_node.first.value();           // function value is defined in class _iterator which returns the value 
                                               // of the node pointed to by iterator
    }
};

// END OF CLASS bst




// definition of function _insert - out of the class bst ( works with both r-value and l-value input)

/** private function _insert 
* is used to insert a new node in the tree 
* the bool is true if a new node has been allocated, false otherwise (i.e. the key already exists) 
* @return returns a pair of an iterator (pointing to the node) and a bool. 
*/
template<typename k_t, typename v_t, typename OP>
template <typename O>
std::pair<typename bst<k_t, v_t, OP >::iterator, bool>   bst<k_t, v_t,OP> :: _insert (O&& x) {  //forwarding reference
        
    auto tmp = head.get();
    auto new_node{new node{std::forward<O>(x)}};

    // base case: empty bst --> the new node is added
    if(!head){
        head.reset(new_node);
        return std::pair<iterator, bool>{iterator{new_node},true};
    }

    // if a node with the same key is already present,
    //return an iterator to that node and flag false for new insertion
    if (find(x.first)!=iterator{nullptr}){    
        return  std::pair<iterator, bool>{find(x.first), false}; 
    }

        
    // other than the above two cases, we search the tree to find
    // the location of the new node, on the left or on the right
    else{
        while(tmp){                                  
            new_node->_parent = tmp; 
                // go right                            //tmp is the parent of the new node.
            if( comp(tmp->_pair.first, x.first) ){     //if the key of tmp is less than the key of x
                if(!tmp->_right.get()){                // and if there is no node on the right hand side of tmp
                    tmp->_right.reset(new_node);       // we put the new node on the right of tmp,
                    tmp = nullptr;                   
                }
                else{tmp = tmp->_right.get();}     // otherwise we update tmp as the node on its right hand side
            }
            else{  //go left
                if(!tmp->_left.get()){           //if the key of tmp is greater than the key of x,
                    tmp->_left.reset(new_node);  //we do the same seeking on the left side of tree
                    tmp = nullptr;
                }
                else{tmp = tmp->_left.get();}   // otherwise we update tmp as the node on its left hand side
            }
        }
           
    }
    return std::pair<iterator, bool>{iterator{new_node}, true};
}




// definition of function make_balance - out of the class

/** @brief private function make_balance 
 * is used to balance the tree
  *  @param v --> vector of pairs
  *  @param start --> first index
  *  @param end --> last index
  */
template<typename k_t, typename v_t, typename OP>
template <typename P>
void bst<k_t, v_t, OP>::make_balance (std::vector<P> v, int start, int end){

    // base Case 
    if (start > end) {
        return;
    } 
  
    // get the median element 
    int median = (start + end)/2; 
    
    insert(v[median]);
    make_balance(v, start, median-1);
    make_balance(v, median+1,  end);
    return ;
}



// definition of function balance - out of the class

/** function to balance the tree - uses the private function make_balance 
 * it traverse the bst inorder and stores all the pairs in a vector v;
 * then clears the tree and insert the nodes
 * starting from the median of v and again recursively on the left and right subvectors of v
 */
template<typename k_t, typename v_t, typename OP>
void bst<k_t, v_t, OP >:: balance(){

    std::vector<std::pair<k_t,v_t>> v;

    // fill v with inorder elements of the bst
    for(const_iterator i = cbegin(); i != cend() ; ++i){
        v.emplace_back(*i, i.value());
    }
        
    // clear the bst (*this) 
    clear();
    // rebuild the bst
    make_balance(v, 0, v.size()-1);
    return;
}





// definition of function erase - out of class bst

/** function erase  
* removes the element (if one exists) with the key equivalent to key.
* @param x l-value reference of the key of the node to be deleted */

template<typename k_t, typename v_t, typename OP>   
void bst<k_t, v_t, OP> :: erase(const k_t& x) {
    
    if(find(x)!=iterator{nullptr}){       // if the key is present in the bst - (or --> != end() ) 

        node* starting_node = find(x).current_ptr();     // starting_node points to the node x which we want to delete;
        // possible cases
        // 1: the node is a leaf (no child)
        if(!starting_node->_left && !starting_node->_right){   // if the node x has no child             
           
            auto key_of_parent = starting_node->_parent->_pair.first;
            auto parent = starting_node->_parent;                 // ptr to parent node
            
            if(comp(x,key_of_parent))  {   // if key(x) < key(its parent) --> x is a left child of its parent
                parent->_left.release();   // we release and reset the pointer to the left child of parent (x)
                parent->_left.reset();     // reset to nullptr
            } 
            else{                          // otherwise x is a right child of its parent  
                parent->_right.release();
                parent->_right.reset();     // reset to nullptr
            }
        } 
        

        // 2: the node has only one child
        if((!starting_node->_left && starting_node->_right) || (starting_node->_left && !starting_node->_right)) {        // if the node x has only one child
        
            if(starting_node->_left){                                // if x has a left child
                
                auto left_child = starting_node->_left.release();    // ptr to the unique left child
                auto parent = starting_node->_parent;                // ptr to parent node
                auto key_of_parent = parent->_pair.first;

                if(comp(x,key_of_parent)) {      // if key(x) < key(its parent) --> x is a left child of its parent
                    parent->_left.release();
                    parent->_left.reset(left_child);   // reset the left pointer of parent of x to left child of x (not x itself anymore)
                    left_child->_parent = parent;
                }  
                else{                               // otherwise x is a right child  of its parent
                    parent->_right.release();
                    parent->_right.reset(left_child); 
                    left_child->_parent = parent;
                    
                } 
                                
            }
            else{                                                      // if x has a right child
                auto right_child = starting_node->_right.release();    // ptr to unique right child
                auto parent = starting_node->_parent;                   // ptr to parent node
                auto key_of_parent = parent->_pair.first;

                if(comp(x,key_of_parent)) {          // if key(x) < key(its parent) --> x is a left child of its parent
                    parent->_left.release();
                    parent->_left.reset(right_child);  // reset the left pointer of parent of x to left child of x (not x itself anymore)
                    right_child->_parent = parent;
                }
                else {                                // otherwise x is a right child  of its parent
                    parent->_right.release();
                    parent->_right.reset(right_child);
                    right_child->_parent = parent;
                }              
            }
        }

        //3: the node has two children
        if(starting_node->_left && starting_node->_right){      // x has either a right and a left child
            
            auto swap_node = starting_node->_right.get();      //swap_node is the right child of x
            while(swap_node->_left){                           //if there is a left child for swap_node, go to it  
                swap_node = swap_node->_left.get();            //and update swap_node to its left child
            }
            
            starting_node->_pair = swap_node->_pair;       // exchange keys and values 
            if(swap_node->_parent != starting_node){       // swap_node is not the child of node to be deleted
                if(swap_node->_right){                      // and has a right child
                    swap_node->_right->_parent = swap_node->_parent;
                }

                auto tmp = swap_node->_right.release(); 
                swap_node->_parent->_left.reset(tmp);    // attach the subtree to the parent
                
            }
            else{                                          // swap_node is the child of node to be deleted
                if(swap_node->_right){                 
                    swap_node->_right->_parent = starting_node;
                }

                auto tmp = swap_node->_right.release();
                starting_node->_right.reset(tmp);
                
            }
           
        }
        
    }

    else{
        std::cerr << "ERROR: there is no node with key = " << x << std::endl;
    }
}

#endif