#include "bst.hpp"

binary_search_tree::binary_search_tree() {
    root = nullptr;
}

binary_search_tree::~binary_search_tree() {
    destroyTree(root);
}

void binary_search_tree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);

        delete node; //Deletes nodes as we recurse through the tree
    }
}

bool binary_search_tree::insertion(int value) { 
    Node * node_to_insert = new Node(value);

    if (!root) { //Edge case for if the tree doesn't exist
        root = node_to_insert;
        return true;
    }

    Node * current_node = root; 
    Node * adopter = nullptr; //We must keep track of the "previous" node in order to insert

    while (current_node != nullptr) {
        adopter = current_node;

        if (value > current_node->value) { //Traverse right
            current_node = current_node->right;
        } else if (value < current_node->value) { //Traverse left
            current_node = current_node->left;
        } else { //Repeated value
            delete node_to_insert;

            return false;
        }
    }

    if (value > adopter->value) { //We know to insert right of parent
        adopter->right = node_to_insert;
    } else { //We will automatically know to insert left if previous condition is failed
        adopter->left = node_to_insert;
    }

    return true;
}

void insertion_test(binary_search_tree& tree, int value) {
    if (tree.insertion(value)) {
        std::cout << "Insertion of " << value << " Successful" << std::endl;

        return;
    }

    std::cout << "Insertion of " << value << " Unsuccessful" << std::endl;
}

bool binary_search_tree::deletion(int value) {
    Node * current = root;
    Node * parent_node = nullptr;

    while (current != nullptr) { //Searching for our node placement
        if (current->value == value) { 
            break;
        } else if (value > current->value) { //We move right
            parent_node = current;
            current = current->right;
        } else { //Or we move left
            parent_node = current;
            current = current->left;
        }
    }

    if (current == nullptr) { //We didn't find the node to delete
        return false;
    }

    if (current->left == nullptr && current->right == nullptr) { //Case for no children
        if (parent_node == nullptr) { //Root case safety
            delete root;
            root = nullptr;

            return true;
        } else if (parent_node->left == current) { //If the node we are deleting is on the left
            parent_node->left = nullptr;
        } else { //If the node we are deleting is on the right
            parent_node->right = nullptr;
        }

        delete current;

        return true;
    } else if (current->left == nullptr && current->right != nullptr) { //Case for right child
        if (parent_node == nullptr) {
            root = root->right;
        } else if (parent_node->left == current) { //If the node we are deleting is on the left
            parent_node->left = current->right;
        } else { //If the node we are deleting is on the right
            parent_node->right = current->right;
        }

        delete current;

        return true;
    } else if (current->left != nullptr && current->right == nullptr) { //Case for left child
        if (parent_node == nullptr) {
            root = current->left;
        } else if (parent_node->left == current) { //If the node we are deleting is on the left
            parent_node->left = current->left;
        } else { //If the node we are deleting is on the right
            parent_node->right = current->left;
        }

        delete current;

        return true;
    } else { //Case if there are two children
        Node * in_order_successor_parent = current;
        Node * in_order_successor = current->right;

        while (in_order_successor->left != nullptr) { //Finding the in order successor of the node we are deleting
            in_order_successor_parent = in_order_successor;
            in_order_successor = in_order_successor->left;
        }

        if (in_order_successor_parent != current) {
            in_order_successor_parent->left = in_order_successor->right;
        } else {
            in_order_successor_parent->right = in_order_successor->right;
        }

        current->value = in_order_successor->value; //Switching values

        delete in_order_successor;

        return true;
    }
}

void deletion_test(binary_search_tree& tree, int value) {
    if (tree.deletion(value)) {
        std::cout << "Deletion of " << value << " Successful" << std::endl;
    } else {
        std::cout << "Deletion of " << value << " Unsuccessful" << std::endl;
    }

    std::cout << "What your tree is now holding: ";
    
    tree.in_order_traversal_helper();

    std::cout << std::endl;
}

void deletion_output_helper(binary_search_tree& tree, int insert) {
    if (insert != -1) {
        insertion_test(tree, insert);
    }

    std::cout << "Current Tree: ";

    tree.in_order_traversal_helper();

    std::cout << std::endl << std::endl;
}

bool binary_search_tree::search(int value) {
    Node * current = root; //We must iterate through the tree

    while (current != nullptr) { //Stopping condition for the search
        if (current->value == value) { //Visit
            return true;
        } else if (value > current->value) { //We move right
            current = current->right;
        } else { //Or we move left
            current = current->left;
        }
    }

    return false;
}

void search_test(binary_search_tree& tree, int value) {
    if (tree.search(value)) {
        std::cout << "Search of " << value << " Successful" << std::endl;
    } else {
        std::cout << "Search of " << value << " Unsuccessful" << std::endl;
    }
}

void binary_search_tree::in_order_traversal(Node * node) {
    if (node == nullptr) { //Recursive stop
        return;
    }

    in_order_traversal(node->left);

    std::cout << node->value << " ";

    in_order_traversal(node->right);
}

void binary_search_tree::in_order_traversal_helper() {
    in_order_traversal(root);
}