#ifndef BST_HPP
#define BST_HPP

#include <iostream>

class binary_search_tree {
    private:
        struct Node {
            int value;
            Node * left;
            Node * right;
            Node():value(0), left(nullptr), right(nullptr) {}
            Node(int data):value(data), left(nullptr), right(nullptr) {}
        };

        Node * root;
    public:
        binary_search_tree();
        ~binary_search_tree();

        void destroyTree(Node* node);
        bool insertion(int value);
        bool deletion(int value);
        bool search(int value);
        void in_order_traversal(Node * node);
        void in_order_traversal_helper();
};

void insertion_test(binary_search_tree& tree, int value);
void search_test(binary_search_tree& tree, int value);
void deletion_test(binary_search_tree& tree, int value);
void deletion_output_helper(binary_search_tree& tree, int insert);

#endif