#ifndef UNSORTEDPQ_H
#define UNSORTEDPQ_H

#include "Node.h"
#include <exception>

using namespace std;

template <class T>
class UnsortedPQ
{ // Unsorted list-based priority queue implementation
private:
	Node<T>* head;
	int curr_size;

public:
	UnsortedPQ() : curr_size{ 0 }, head{ nullptr } {} // Constructor with default initialization values

	UnsortedPQ(T *dataArray, int n) : curr_size{ 0 }, head{ nullptr }
	{ // Builds new unsorted list-based priority queue given array of elements and size
		for (int i = 0; i < n; i++)
			// Iterate through dataArray and insert elements
			insertItem(dataArray[i]);
	}

	~UnsortedPQ()
	{ // Destructor frees all dynamically allocated memory
		while (head != nullptr)
		{ // Iterate through all nodes and remove them
			Node<T>* temp = head->next;
			delete head;
			head = temp;
		}
	}

	bool isEmpty() const
	{ // Returns true if queue is empty, false if it is not
		return (curr_size == 0);
	}

	int size() const
	{ // Returns size of queue
		return curr_size;
	}

	void insertItem(T data)
	{ // Inserts a data value into the front of the queue
		Node<T>* temp = new Node<T>();
		temp->data = data;

		temp->next = head;
		head = temp;
		curr_size++;
	}

	T removeMin()
	{ // Removes and returns minimum value of queue
		if (head == nullptr)
			// If queue is empty already, throw an exception
			throw std::logic_error("Attempting to remove element from empty queue.");

		Node<T>* temp = head->next; // Traverses list to find minimum value
		Node<T>* min_prev = head; // Stays behind temp to update min_prev_temp if necessary
		Node<T>* min_prev_temp = head; // Pointer to the node behind the current min

		T min = head->data;
		while (temp != nullptr)
		{ // Traverse list to find minimum value
			if (temp->data < min)
			{ // If a new minimum value is found
				min_prev_temp = min_prev;
				min = temp->data;
			}
			min_prev = min_prev->next;
			temp = temp->next;
		}

		if (head->data == min)
		{ // If the head node contains the minimum value, remove it
			temp = head->next;
			delete head;
			head = temp;
		}
		else
		{ // Otherwise, the minimum value is not at the front of the list
			temp = min_prev_temp->next->next;
			delete min_prev_temp->next;
			min_prev_temp->next = temp;
		}

		curr_size--; // Decrement size and return the value
		return min;
	}

	T minValue() const
	{ // Returns the minimum value in the queue without removing it
		if (head == nullptr)
			// If queue is empty, throw an exception
			throw std::logic_error("Attempting to access element in empty queue.");

		Node<T>* temp = head;
		T min = temp->data;
		while (temp != nullptr)
		{ // Traverse list to find minimum value 
			if (temp->data < min)
				min = temp->data;
			temp = temp->next;
		}

		return min; // Return minimum value
	}
};

#endif