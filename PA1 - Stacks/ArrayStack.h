#ifndef ARRAYSTACK
#define ARRAYSTACK

#include "Node.h"
#include <exception>

	const int BASE_AMOUNT = 10000;
	const int INCREMENT_AMOUNT = 10000;

template<class T>
class ArrayStack { // Templated stack implementation using an array
	T* data;
	unsigned int capacity;
	unsigned int sizestack;

public:
	ArrayStack() : data{ new T[INCREMENT_AMOUNT] }, capacity{ INCREMENT_AMOUNT }, sizestack { 0 } { // Constructor with default initialization values
	}

	~ArrayStack() { // Destructor frees all dynamically allocated memory
		delete[] data;
	}

	void push(T num) { // Add new element to the top of the stack and increase size by 1
		if (sizestack == capacity) {
			capacity += INCREMENT_AMOUNT;
			T* temp = new T[capacity];
			for (unsigned i = 0; i < sizestack; i++) {
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}

		data[sizestack] = num;
		sizestack++;
	}

	T pop() { // Free element from top of stack and returns a copy of the data member deleted
		if (sizestack == 0) { // If stack is empty already, throw an exception
			throw std::logic_error("Attempting to remove element from empty stack.");
		}
		else {
			sizestack--;
			return data[sizestack];
		}
	}

	T& top() const { // Returns a reference to the first stack element
		if (sizestack == 0) { // If stack is empty, throw an exception
			throw std::logic_error("Attempting to access element in empty stack.");
		}
		else {
			return data[sizestack - 1];
		}

	}

	int size() const {
		return sizestack; // Return number of elements in the stack
	}

	bool isEmpty() const { // Returns a boolean indicating if the stack is empty
		return (sizestack == 0);
	}

};

#endif