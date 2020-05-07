#ifndef SORTEDPQ_H
#define SORTEDPQ_H

#include "Node.h"
#include <exception>

using namespace std;

template <class T>
class SortedPQ
{ // Sorted list-based priority queue implementation
private:
	Node<T>* head;
	int curr_size;

public:
	SortedPQ() : curr_size{ 0 }, head{ nullptr } {} // Constructor with default initialization values

	SortedPQ(T *dataArray, int n) : curr_size{ 0 }, head{ nullptr }
	{ // Builds new sorted list-based priority queue given array of elements and size
		for (int i = 0; i < n; i++) // Iterate through dataArray and insert elements
			insertItem(dataArray[i]);
	}

	~SortedPQ()
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
	{ // Inserts a data value into the queue
		Node<T>* temp = new Node<T>();
		Node<T>* iterator = head;
		temp->data = data;
		if (head == nullptr || temp->data < head->data)
		{ // If queue is empty or value is smaller than head value
			temp->next = head;
			head = temp;
			curr_size++;
		}
		else
		{ // If not inserting at the beginning
			while (iterator->next != nullptr && iterator->next->data <= temp->data)
				iterator = iterator->next; // Traverse list to find proper insertion point

			temp->next = iterator->next;
			iterator->next = temp;
			curr_size++;
		}
	}

	T removeMin()
	{ // Removes and returns minimum value of queue
		if (head == nullptr) // If queue is empty already, throw an exception
			throw std::logic_error("Attempting to remove element from empty queue!");

		Node<T> *temp = head;
		T tempdata = temp->data;
		head = head->next;
		delete temp; // Free first element
		curr_size--; // Decrement size

		return tempdata;
	}

	T minValue() const
	{ // Returns the minimum value in the queue without removing it
		if (head == nullptr) // If queue is empty, throw an exception
			throw std::logic_error("Attempting to access element in empty queue!");

		return head->data; // otherwise, return reference to data member
	}
};

#endif