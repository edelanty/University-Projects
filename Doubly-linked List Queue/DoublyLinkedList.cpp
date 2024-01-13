/*
Evan Delanty
4/23/23
Queues Implemented With Doubly Linked Lists
*/

#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() {
	head = NULL;
	tail = NULL;
}

DoublyLinkedList::~DoublyLinkedList() {
	// free each Node's memory in the list
	destroyList();
}

Node * DoublyLinkedList::getHead() const {
	return head;
}

Node * DoublyLinkedList::getTail() const {
	return tail;
}

void DoublyLinkedList::setHeadAndTail(Node * newHead, Node * newTail) {
	if (head != NULL) {
		destroyList();
	}
	
	head = newHead;
	tail = newTail;
}

void DoublyLinkedList::destroyList() {
	Node * currNode = head;
	Node * nextNode = NULL;

	while (currNode != NULL) {
		// save the link to the next node
		nextNode = currNode->next;
		// can safely delete currNode
		delete currNode;
		currNode = nextNode;
	}

	head = NULL;
	tail = NULL;
}

void DoublyLinkedList::displayList() {
	Node * currNode = head;
	
	cout << "head->";
	while (currNode != NULL) {
		cout << currNode->value << "<->";
		// progress towards BC being false
		currNode = currNode->next;
	}

	cout << "NULL" << endl;

	if (tail != NULL) {
		cout << "tail->" << tail->value << endl;
	} else {
		cout << "tail->NULL" << endl;
	}
}

void DoublyLinkedList::addToEnd(int newValue) {
	Node * newNode = new Node;

	newNode->value = newValue;
	newNode->prev = tail;
	newNode->next = NULL;
	
	if (head == NULL) {
		head = newNode;
		tail = newNode;
	} else {
		tail->next = newNode;
		tail = newNode;
	}
}

int DoublyLinkedList::deleteAtFront() {
	int toDelete;

	if (head == NULL) {
		return -1;
	}
	
	toDelete = head->value;

	Node * nodeToDelete = head;
	head = head->next;

	if (head == NULL) {
		tail = NULL;
	} else {
		head->prev = NULL;
	}

	delete nodeToDelete;
	return toDelete;
}

int DoublyLinkedList::deleteNode(int targetValue) {
	int toDelete;

	if (head == NULL) {
		return -1;
	}

	Node * currNode = head;

	while (currNode != NULL && currNode->value != targetValue) {
		currNode = currNode->next;
	}

	if (currNode == NULL) {
		return -1;
	}

	toDelete = currNode->value;
	
	if (currNode == head) { //Setting up list if we need to delete the head
		head = currNode->next;

		if (head == NULL) { 
			tail = NULL;
		} else {
			head->prev = NULL;
		}

	} else if (currNode == tail) { //Setting up list if we need to delete the tail
		tail = currNode->prev;
		tail->next = NULL;
	} else { //Case if the target node isn't the head or tail
		currNode->prev->next = currNode->next;
		currNode->next->prev = currNode->prev;
	}

	delete currNode;
	return toDelete;
}

void DoublyLinkedList::addToFront(int newValue) {
	Node * newNode = new Node;

	newNode->value = newValue;
	newNode->prev = NULL;
	newNode->next = head;
	
	if (head == NULL) { //If No List Exists (Make One)
		head = newNode;
		tail = newNode;
	} else {
		head->prev = newNode;
		head = newNode;
	}
}

int DoublyLinkedList::deleteAtEnd() {
	int toDelete;

	if (head == NULL) { //If list is empty
        return -1;
    }

    toDelete = tail->value;
    Node * nodeToDelete = tail;

    if (head == tail) { //If list has only one node
        head = NULL;
        tail = NULL;
    } else { //If list has more than one node
        tail = tail->prev;
        tail->next = NULL;
    }

    delete nodeToDelete;
    return toDelete;
}

void DoublyLinkedList::insertInOrder(int newValue) {
	Node * newNode = new Node;

    newNode->value = newValue;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL) { //If list is empty
        head = newNode;
        tail = newNode;
        return;
    }

    Node * currNode = head;
    Node * prevNode = NULL;

    //Find the correct position to insert the new node
    while (currNode != NULL && currNode->value <= newValue) {
        prevNode = currNode;
        currNode = currNode->next;
    }

    //Insert the new node at the correct position
    if (prevNode == NULL) { //If new node should be inserted at the front
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (currNode == NULL) { //If new node should be inserted at the end
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else { //If new node should be inserted in the middle
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = currNode;
        currNode->prev = newNode;
    }
}