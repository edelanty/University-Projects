#include "bst.hpp"

int main() {
    //Test for Insertion: Specifically testing whether or not insertion works for the left and right children
    binary_search_tree tester;

    std::cout << std::endl << "INSERTION TESTING" << std::endl << std::endl;

    insertion_test(tester, 4); //Root
    insertion_test(tester, 2); //Left leaf
    insertion_test(tester, 6); //Right leaf
    insertion_test(tester, 5); //Left child of right leaf
    insertion_test(tester, 7); //Right child of right leaf
    insertion_test(tester, 1); //Left child of left leaf
    insertion_test(tester, 3); //Right child of left leaf
    insertion_test(tester, 6); //Duplicate failure test

    std::cout << std::endl;

    std::cout << "IN ORDER TRAVERSAL TESTING" << std::endl << std::endl;

    tester.in_order_traversal_helper();

    std::cout << std::endl << std::endl;

    std::cout << "SEARCH TESTING" << std::endl << std::endl;

    search_test(tester, 4); //Root
    search_test(tester, 2); //Left leaf
    search_test(tester, 6); //Right leaf
    search_test(tester, 5); //Left child of right leaf
    search_test(tester, 7); //Right child of right leaf
    search_test(tester, 1); //Left child of left leaf
    search_test(tester, 3); //Right child of left leaf
    search_test(tester, 6); //Duplicate failure test

    std::cout << std::endl;

    std::cout << "DELETION TESTING" << std::endl << std::endl;

    deletion_output_helper(tester, -1);
    deletion_test(tester, 1); //Deleting a left leaf
    deletion_test(tester, 7); //Deleting a right leaf
    deletion_test(tester, 2); //Deleting node with 1 right child
    deletion_test(tester, 6); //Deleting node with 1 left child
    deletion_test(tester, 4); //Deleting root/two children
    deletion_test(tester, 5); //Deleting root node with left child
    deletion_test(tester, 3); //Deleting root node with no children

    std::cout << std::endl;

    std::cout << "TESTS HAVE PASSED" << std::endl;

    return 0;
}