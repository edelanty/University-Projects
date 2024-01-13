/*
Evan Delanty
4/23/23
Queues Implemented With Doubly Linked Lists
*/

#ifndef SIEVE_H
#define SIEVE_H

#include <iostream>
#include <cmath>
#include "DoublyLinkedQueue.h"

using namespace std;

class Sieve {
	private:
		int n;
		DoublyLinkedQueue * numsQ; 
		DoublyLinkedQueue * primesQ;
	public:
		Sieve(); // DVC
		Sieve(string); // EVC
		~Sieve(); // destructor
		int getN() const;
		void setN(int);
		void computePrimes();
		int reportResults(double&);
		void run();
};

#endif