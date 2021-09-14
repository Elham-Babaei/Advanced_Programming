// Elham Babaei - AP Project
#include "src/bst.hpp"
#include "src/iterator.hpp"
#include "src/node.hpp"

#include <iostream>

int main() {

    try {

        // Create the binary search tree
        bst<int,int> tree;
        std::cout << "****** Created tree ******" << "\n";
        std::cout << tree << std::endl;
      

        // Inserting some pairs of key and value
        tree.insert(std::pair<int,int>{8,99});
        tree.insert(std::pair<int,int>{3,99});
        tree.insert(std::pair<int,int>{1,99});
        tree.insert(std::pair<int,int>{6,99});
        tree.insert(std::pair<int,int>{4,99});
        tree.insert(std::pair<int,int>{7,99});
        tree.insert(std::pair<int,int>{10,99});
        tree.insert(std::pair<int,int>{14,99});
        tree.insert(std::pair<int,int>{13,99});
        

        std::cout << "\n****** Tree after insertions (Test on Inset function) ******" << "\n";
        std::cout << tree << std::endl;

        // Deep Copy and Move semantics
        std::cout << "\n****** Test on Deep Copy and Move semantics ******" << "\n";

        bst<int,int> copy_ctor_tree {tree};
        std::cout << "\nTree by deep copy constructor: \n" << copy_ctor_tree << "\n";

        bst<int,int> copy_assi_tree = tree;
        std::cout << "\nTree by copy assignment: \n" << copy_assi_tree << "\n";
        
        bst<int,int> move_ctor_tree{std::move(copy_ctor_tree)};
        std::cout << "\nTree by move constructor: \n" << move_ctor_tree << "\n";

        bst<int,int> move_assi_tree = std::move(copy_assi_tree);
        std::cout << "\nTree by move assignment: \n" << move_assi_tree << std::endl;


        // Erase function
        std::cout << "\n****** Test on Erase function *******" << "\n";
        std::cout << "\nAfter erasing node 8: \n" << " " ;
        tree.erase(8);                          
        std::cout << tree << "\n";
        std::cout << "\nAfter erasing node 6: \n" << " ";
        tree.erase(6);
        std::cout << tree << std::endl;
        

        // Emplace_Back function
        std::cout << "\n ****** Test on Emplace_Back function ******" << "\n\n";
        bst<int,int> emplace_tree {tree};
        emplace_tree.emplace(2,88);
        emplace_tree.emplace(20,88);
        std::cout << "Tree after adding nodes (2,88) and (20,88) by emplace_back: \n" << emplace_tree << std::endl;
         

        // Subscripting operator
        std::cout << "\n***** Test on Subscripting operstor*****" << "\n\n";
        std::cout << tree << std::endl;
        bst<int,int> subsc_tree {tree};
        std::cout <<"subsc_tree [3]: " << subsc_tree[3] << "\n";
        std::cout <<"subsc_tree [7]: " << subsc_tree[7] << "\n";
        std::cout <<"subsc_tree [30]: " << subsc_tree[30] << "\n";
        std::cout <<"subsc_tree [-5]: " << subsc_tree[-5] << std::endl;

        // Put-to operator
        std::cout << "\n****** Test on Put-to operstor ******" << "\n\n";
        std::cout << tree << std::endl;

        // Balance function
        std::cout <<"\n****** Test on Balance function ******" << "\n\n";
        tree.balance();
        std::cout << "After balance: \n" << tree << std::endl;
  
        // Clear function
        std::cout << "\n****** Test on Clear function ******" << "\n\n";
        //bst<int,int> clear_tree {tree};
        std::cout << "After clear: \n" << "";
        tree.clear();
        std::cout << tree << std::endl;
       
    }

    catch(std::logic_error& e){
        std::cout << "Standard exception: " << e.what() << std::endl;
    };
    
    return 0;
}