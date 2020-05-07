#ifndef SORTING_H
#define SORTING_H

template<class T>
class Sorting {

	static void swap(T &a, T &b)
	{ // Helper function for sorting algorithms. Swaps two objects
		T temp = a;
		a = b;
		b = temp;
	}

	static void heapify(T* arr, int count, int parent)
	{ // Helper function for heap_sort, max-heapifies dynamic array
		int left = 2 * parent + 1, // Updating indexes
		    right = 2 * parent + 2,
		    max = parent; // Setting max to parent

		if (left < count && arr[left] > arr[max]) // If left child exists and is larger than parent, update max
			max = left;

		if (right < count && arr[right] > arr[max]) // If right child exists and is larger than parent, update max
			max = right;

		if (max != parent) 
		{ // If max changed, swap max and parent and recursively call heapify
			swap(arr[max], arr[parent]);
			heapify(arr, count, max);
		}
	}

	static void merge(T* arr, int left, int mid, int right)
	{ // Helper function for merge_sort, merges two halves of a dynamic array
		int curr_left = left, // Making indexes for beginning of each sub-array
			curr_right = mid + 1,
			sorted_size = 0; // Size of merged array
		T* temp = new T[right - left + 1]; // New array for merged halves

		while (curr_left <= mid && curr_right <= right)
		{ // Loop through halves and place them in new array in sorted order until one half is empty
			if (arr[curr_left] < arr[curr_right])
				temp[sorted_size++] = arr[curr_left++];
			else
				temp[sorted_size++] = arr[curr_right++];
		}

		while (curr_left <= mid) // Finish filling new array with the non-empty half
			temp[sorted_size++] = arr[curr_left++];

		while (curr_right <= right)
			temp[sorted_size++] = arr[curr_right++];

		for (int i = left; i <= right; i++) // Put sorted new array back in proper location in original array
			arr[i] = temp[i - left];

		delete[] temp; // Free dynamically allocated memory
	}

public:
	// DEFINING SORTING FUNCTIONS
	static void selection_sort(T* arr, int n)
	{ // Sorts an array of n numbers using a selection sort algorithm 
		int min;
		for (int i = 0; i < n - 1; i++) // Traverse array (no need to visit last element)
		{
			min = i;
			for (int j = i; j < n; j++) // Traverse unsorted section of array to find min
			{
				if (arr[j] < arr[min])
					min = j;
			}

			if (i != min) // If min is not in place already, put it in proper location
				swap(arr[i], arr[min]);
		}
	}

	static void heap_sort(T* arr, int n)
	{ // Sorts an array of n numbers using a heap sort algorithm 
		for (int i = n / 2 - 1; i >= 0; i--) // Create a max-heap out of array
			heapify(arr, n, i);

		for (int i = n - 1; i >= 0; i--) 
		{ // Loop through array backwards, putting max at end and heapifying
			swap(arr[0], arr[i]);
			heapify(arr, i, 0);
		}
	}

	static void merge_sort(T* arr, int left, int right)
	{ // Sorts an array of n numbers using a merge sort algorithm 
		if (left < right) // If list is not empty
		{
			int mid = (right + left) / 2; // Find midpoint

			merge_sort(arr, left, mid); // Recursively sort each half
			merge_sort(arr, mid + 1, right);

			merge(arr, left, mid, right); // And merge them back together
		}
	}
};

#endif