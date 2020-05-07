#ifndef HEAPPQ_H
#define HEAPPQ_H

#include <exception>

using namespace std;

template <class T>
class HeapPQ
{ // Heap-based priority queue implementation
private:
	T* arr;
	int curr_size;
	int max_size;

	void swap(T &a, T &b) 
	{ // Swaps two variables
		T temp = a;
		a = b;
		b = temp;
	}

	void bubbleUp(int child) 
	{ // Fixes heap using upward bubbling after insertion
		if (arr[child] < arr[(child - 1) / 2]) // If child is less then parent
		{
			swap(arr[child], arr[(child - 1) / 2]); // Swap them
			bubbleUp((child - 1) / 2); // Recursively call bubbleUp for parent if they made a swap
		}
	}

	void heapify(int parent)
	{ // Fixes heap using downward bubbling
		int left = 2 * parent + 1;
		int right = 2 * parent + 2;
		int min = parent;

		if (left < curr_size && arr[left] < arr[min]) // If parent has left child smaller than parent
			min = left;

		if (right < curr_size && arr[right] < arr[min]) // If parent has right child smaller than parent
			min = right;

		if (min != parent) 
		{ // If parent has a child smaller than it
			swap(arr[min], arr[parent]); // Swap them
			heapify(min); // Recursively call heapify for child if they made a swap
		}
	}

public:
	HeapPQ() : curr_size{ 0 }, max_size{ 1 }
	{ // Constructor with default initialization values
		arr = new T[max_size];
	}

	HeapPQ(T * const dataArray, int n) : curr_size{ 0 }, max_size{ n }
	{ // Builds new heap based priority queue given array of elements and size
		arr = new T[max_size];

		for (int i = 0; i < n; i++)
		{ // Copies data into arr
			arr[i] = dataArray[i];
			curr_size++;
		}

		for (int i = n / 2 - 1; i >= 0; i--) // Turn array into heap
			heapify(i);
	}

	~HeapPQ()
	{ // Frees all dynamically allocated memory
		delete[] arr;
	}

	bool isEmpty() const
	{ // Returns true if heap is empty, false if it is not
		return (curr_size == 0);
	}

	int size() const
	{ // Returns size of heap
		return curr_size;
	}

	void insertItem(T data)
	{ // Inserts a data value into the heap (doubles capacity if full)
		if (curr_size == max_size)
		{ // If the array is full, double the current size
			max_size *= 2;
			T* temp = new T[max_size];
			for (int i = 0; i < curr_size; i++)
				temp[i] = arr[i];

			delete[] arr;
			arr = temp;
		}

		arr[curr_size] = data; // Add new element
		bubbleUp(curr_size); // Fix heap using bubbling
		curr_size++;
	}


	T removeMin()
	{ // Removes and returns minimum value of queue
		if (curr_size == 0)
		{ // If queue is empty already, throw an exception
			throw std::logic_error("Attempting to remove element from empty queue.");
		}

		T return_val = arr[0];
		swap(arr[0], arr[curr_size - 1]); // Swap first element with last
		curr_size--; // Decrement size
		heapify(0); // Fix heap using bubbling

		return return_val;		
	}

	T minValue() const
	{ // Returns the minimum value in the queue without removing it
		if (curr_size == 0)
		{ // If queue is empty, throw an exception
			throw std::logic_error("Attempting to access element in empty queue.");
		}
		return arr[0]; // Otherwise, return value of smallest element
	}
};

#endif