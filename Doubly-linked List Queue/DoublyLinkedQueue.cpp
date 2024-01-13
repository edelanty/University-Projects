/*
Evan Delanty
4/23/23
Queues Implemented With Doubly Linked Lists
*/

#include "DoublyLinkedQueue.h"

void DoublyLinkedQueue::displayQueue() {
	Node * currNode = head;
	
	while (currNode != NULL) {
		cout << currNode->value << " ";

		currNode = currNode->next;
	}

	cout << endl;
}

void DoublyLinkedQueue::enqueue(int newValue) {
	addToEnd(newValue);
}

int DoublyLinkedQueue::dequeue() {
	return deleteAtFront();
}

void DoublyLinkedQueue::clear() {
	destroyList();
}

bool DoublyLinkedQueue::isEmpty() {
	bool status = false;

	if (head == NULL) {
		status = true;
	}

	return status;
}

int DoublyLinkedQueue::size() {
	int count = 0;

    Node * currNode = head;
    
    while (currNode != NULL) {
        count++;
        currNode = currNode->next;
    }
    
    return count;
}

void DoublyLinkedQueue::removeDivisibleBy(int p) {
	Node * currNode = head;
	Node * toDelete = NULL;

    while (currNode != NULL) {
        if (currNode->value % p == 0) {
            toDelete = currNode;
            currNode = currNode->next;
            deleteNode(toDelete->value);
        } else {
            currNode = currNode->next;
        }
    }
}