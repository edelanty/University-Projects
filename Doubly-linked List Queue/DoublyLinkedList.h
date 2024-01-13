/*
Evan Delanty
4/23/23
Queues Implemented With Doubly Linked Lists
*/

#ifndef DOUBLY_LINKEDLIST_H
#define DOUBLY_LINKEDLIST_H

#include <iostream>

using namespace std;

struct Node {
	int value; 
	struct Node * next; 
	struct Node * prev; // makes the Node have double links
}; 
		
class DoublyLinkedList {
	protected:
	   	Node * head; // list head pointer
	   	Node * tail; // list tail pointer

	public:
	   	DoublyLinkedList(); // DVC
	   	~DoublyLinkedList(); // destructor
	   	
	   	Node * getHead() const;
	   	Node * getTail() const;
	   	void setHeadAndTail(Node *, Node *);
		  
	   	// common linked list operations
	   	// implementations provided
	   	void destroyList();
	   	void displayList();
	   	
	   	// needed by DoublyLinkedQueue
	   	// implementations not provided
		void addToEnd(int); // AKA insert at end, append
	    int deleteAtFront();
	   	int deleteNode(int);
	   	
	   	// not needed by DoublyLinkedQueue
	   	// implementations not provided
	   	// implement for BONUS
		void addToFront(int);
	   	int deleteAtEnd();
	    void insertInOrder(int);
};

#endif