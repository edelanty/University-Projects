/*
Evan Delanty
4/23/23
Queues Implemented With Doubly Linked Lists
*/

#ifndef DOUBLY_LINKED_QUEUE_H
#define DOUBLY_LINKED_QUEUE_H

#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

class DoublyLinkedQueue : public DoublyLinkedList {
    public:    
		// common queue operations
		// implementation provided
		void displayQueue();

		// implementations not provided
		void enqueue(int);
		int dequeue();
		void clear();
		bool isEmpty();
		int size();

		// sieve specific queue operation
		// implementation not provided
		void removeDivisibleBy(int);

};

#endif