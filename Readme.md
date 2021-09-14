# Advanced Programming exam 2020/2021
### Elham Babaei SM3500466
### Binary Search Tree

## Problem statement

The aim of this project is to Implement a templated Binary Search Tree (BST), a data structure with the following properties:

- The left subtree of a node contains only nodes with keys smaller than the node’s key
- The right subtree of a node contains only nodes with keys greater than the node’s key
- Left and right subtree each must also be a binary search tree

Each node of the tree stores a pair of a `key` and the associated `value` and the tree is traversed from the smaller key to the biggest. This is the so called in-order traversal which is only one among the different methods to traverse a tree.

## Implementation

The code includes 3 resource files (classes) `node.hpp`, `iterator.hpp`, and `bst.hpp` in folder *src*.
In the `main.cpp` file all the functions that were implemented for the binary search tree are tested. 
The command line arguments are specified in the `makefile`, so the program can be executed with the *make* command. However, the main commands to compile the code are:

- g++ -I src -g -std=c++17 -Wall -Wextra  -c -o main.o main.cpp
- g++ main.o -o main.x

*-std=c++17* specifies the version of C++ to be used.
*-Wall -Wextra* asks for almost all warnings.

## Classes

### Node
The struct `node` is defined to store the pairs of key and value.
#### Members
- a `pair` with key and value
- a unique pointer to the `right child`
- a unique pointer to the `left child`
- a raw pointer to the `parent node`

### Iterator
The class `iterator`, is defined as a *forwarding iterator* to traverse the tree inorder.
#### Private members
- A raw pointer to a node
#### Public interface
- Default constructor and destructor
- Custom constructor that takes a pointer to a node and creates an iterator pointing to that node
- Pre-increment operator 
- Post-increment operator 
- Arrow operator 
- Dereferencing operator 
- Function value() returns the value of the pointed node 
- Function current_ptr() returns the current position in the tree
- Comparison operators

### BST
The class `bst` is defined to combine things together and implement BST.
#### Private members
- A pointer to the head (root) of the tree
- An instance of the comparison operator of type OP in which `OP = std::less<k_t>`
- `left_most`: auxiliary funtion to retrieve the left most node in the tree
- `_insert`: auxiliary function to insert a node in the tree
- `make_balance`: auxiliary function invoked in function `balance`
- `_is_empty`: auxiliary function to check whether the tree is empty

#### Public members
- Default constructor and desctructor
- Deep copy and move semantics
- `(c)begin`: return an (const)interator to the left most node
- `(c)end`: return an (const)interator to one past the last node 

- `find`: given a key it returns, if present, an iterator to the node with that key; `end()` otherwise. Starting from the root we traverse top-bottom the tree comparing the keys; if they are equal we return an iterator to the current node otherwise, if the key we are looking for is smaller than the current one we move to the left; if it is greater we move to the right. The procedure goes on until either we find the key or we get to a leaf node, meaning that the key of interest is not in the tree.

- `insert`: given a pair it inserts a new node and returns an iterator to the newly inserted node and a bool to check whether the insertion can been performed (`False` if the key of the node was already present). After checking if the tree is empty and if the key is not already present we can then procede by finding the place where the node must be inserted and placing it there.

- `emplace`: given a key and a value it creates a pair out of them and inserts a new node, following the same idea of `insert`
- `clear`: clears the content of the tree
- `balance`: it balances the tree in place. After storing the pairs (sorted by key) in a vector, we clear the bst and recursively insert the median of the (sub)vector until all the nodes have been inserted again.

- `erase`: given a key, if present, it erases the corresponding node. We distinguished three cases:
  - the node is a leaf: we simply delete it
  - the node has just one (left)right child: we delete it after connecting its parent to the (left)right child
  - the node has two children: we swap the node with the left most node in the right subtree and then delete such node, that is now a leaf
  
- `operator put to` prints the keys by reading the tree inorder
- `subscripting operator` given a key, if it is present in the tree it returns the corresponding value, otherwise a new node with the key and the default value is inserted



