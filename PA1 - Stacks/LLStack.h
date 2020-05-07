#ifndef LLSTACK
#define LLSTACK

#include "Node.h"
#include <exception>

template<class T>
class LLStack { // Templated stack implementation using a singly linked list
	Node<T> *head;
	int sizestack;

public:
	LLStack() : head{ nullptr }, sizestack{ 0 } { // Constructor with default initialization values
	}

	~LLStack() { // Destructor frees all dynamically allocated memory
		while (head != nullptr) {
			Node<T>* temp = head->next;
			delete head;
			head = temp;
		}
	}

	void push(T data) { // Add new element to the top of the stack and increase size by 1
		if (head == nullptr) { // If stack is empty
			head = new Node<T>; 
			head->data = data;
			head->next = nullptr;
			sizestack++;
		}
		else { // If stack is not empty 
			Node<T> *temp = new Node<T>;
			temp->data = data;
			temp->next = head;
			head = temp;
			sizestack++;
		}
	}

	T pop() { // Free element from top of stack and returns a copy of the data member deleted
		if (head == nullptr) { // If stack is empty already, throw an exception
			throw std::logic_error("Attempting to remove element from empty stack.");
		}
		Node<T> *temp = head;
		T tempdata = head->data;
		head = head->next;
		delete temp; // Free first element
		sizestack--; // Decrement size
		return tempdata;
	}

	T& top() const { // Returns a reference to the first stack element
		if (head == nullptr) { // If stack is empty, throw an exception
			throw std::logic_error("Attempting to access element in empty stack.");
		}
		return head->data; // otherwise, return reference to data member
	}

	int size() const {
		return sizestack; // Return number of elements in the stack
	}

	bool isEmpty() const { // Returns a boolean indicating if the stack is empty
		return (sizestack == 0);
	}

};

#endif