#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include "SortedPQ.h"
#include "UnsortedPQ.h"
#include "HeapPQ.h"
#include "stopwatch.h"

using namespace std;

// DECLARING CONSTANTS
const string input_filename{ "numbers.txt" }; // File name for reading
const string output_filename{ "times.txt" }; // File name for recording times
const unsigned QUEUE_CHOICE = 0; // Queue choice and size for experiment (does not effect reading from input file) 
const unsigned TEST_SIZE = 1000; // Should be divisible by 100 for exactly 100 evenly spaced data points

int main() try 
{
	// DECLARING VARIABLES
	//########################################################################
	UnsortedPQ<int>* unsorted_queue; // Declaring priority queue implementations
	SortedPQ<int>* sorted_queue;
	HeapPQ<int>* heap_queue;
	CStopWatch stopwatch; // Declaring stopwatch to time implementations
	ofstream ostream; // Declaring File IO streams
	ifstream istream;
	unsigned queue_choice, // Determines which queue to implement
			 interval,     // Logs time every 'interval' iterations
			 size;         // Total number of data values for testing
	//########################################################################

	// READING INPUT FILE
	//########################################################################
	// Opens input file and reads contents into array
	istream.open(input_filename.c_str()); // Open input file
	if (!istream) throw runtime_error("Could not open " + input_filename + "!");
	
	cout << "Reading data from input file " << input_filename << endl << endl;
	if(!(istream >> queue_choice >> size)) // Read queue_choice and size from input file
		throw runtime_error("Error reading " + input_filename + "! Is the file empty?");

	//  Reading data from file
	int* arr = new int[size]; // Dynamically allocate new array
	for (unsigned i = 0; i < size; i++) 
	{ // Insert the number of elements specified by file into array
		if (!(istream >> arr[i]))
			throw runtime_error("Error reading " + input_filename + "!");
	}

	istream.close(); // Close input file
	//########################################################################*/

	// PRINTING OUTPUT FROM NUMBERS.TXT
	//########################################################################*/
	switch (queue_choice)
	{
	case 0:
		// If queue choice was unsorted queue
		cout << "Priority Queue (Unsorted list implementation)" << endl << "Removing " << size << " items: " << endl;
		unsorted_queue = new UnsortedPQ<int>(arr, size); // Instantiate unsorted list priority queue implementation

		for (unsigned i = 0; i < size; i++) // Output removed data to console
			printf("%i\n", unsorted_queue->removeMin());

		delete unsorted_queue; // Frees dynamically allocated memory
		break;

	case 1: // If queue choice was sorted queue
		cout << "Priority Queue (Sorted list implementation)" << endl << "Removing " << size << " items: " << endl;
		sorted_queue = new SortedPQ<int>(arr, size);  // Instantiate sorted list priority queue implementation

		for (unsigned i = 0; i < size; i++) // Output removed data to console
			printf("%i\n", sorted_queue->removeMin());

		delete sorted_queue; // Frees dynamically allocated memory
		break;

	case 2: // If queue choice was heap queue
		cout << "Priority Queue (Heap implementation)" << endl << "Removing " << size << " items: " << endl;
		heap_queue = new HeapPQ<int>(arr, size);  // Instantiate heap priority queue implementation

		for (unsigned i = 0; i < size; i++) // Output removed data to console
			printf("%i\n", heap_queue->removeMin());

		delete heap_queue; // Frees dynamically allocated memory
		break;

	default:
		throw runtime_error("Invalid queue selection!");
	}

	delete[] arr; // Frees dynamically allocated memory
	//########################################################################*/

	// GENERATING RANDOM NUMBERS FOR EXPERIMENT
	//########################################################################
	// Generates 'size' random numbers and stores them in a dynamic array
	srand(time(NULL)); // Seeding RNG

	size = TEST_SIZE;
	interval = ((size / 100 == 0) ? 1 : (size / 100)); // Set timing interval to size / 100 with a minimum of 1 if size < 100
	queue_choice = QUEUE_CHOICE;

	arr = new int[size]; // Dynamically allocate new array

	for (unsigned i = 0; i < size; i++) // Insert size random numbers [0, 100) into array
		arr[i] = rand() % 100;
	//########################################################################

	// RECORDING EXPERIMENTAL DATA
	//########################################################################*/
	// Inserts and removes 'n' numbers into the chosen priority queue implementation and logs insertion/removal times to an output file
	cout << "\nBeginning Experiment with size n = " << size << " . . ." << endl;

	ostream.open(output_filename.c_str()); // Open output file
	if (!ostream) throw runtime_error("\nCould not open " + output_filename + " to output times!");

	switch (queue_choice)
	{
	case 0: // If queue choice was unsorted queue
		cout << "\nChosen implementation: Unsorted queue" << endl;

		unsorted_queue = new UnsortedPQ<int>(); // Instantiate unsorted list priority queue implementation for insertion

		cout << "\nTiming insertion . . ." << endl;
		ostream << "Unsorted Queue Insertion (s):\n\n";
		stopwatch.Reset();

		for (unsigned i = 1; i <= size; i++)
		{ // Inserting items. . .
			unsorted_queue->insertItem(arr[i-1]); 
			if (i % interval == 0) 
				ostream << stopwatch.GetElapsedSeconds() << "\n"; // Recording insertion time
		}

		delete unsorted_queue;

		unsorted_queue = new UnsortedPQ<int>(); // Instantiate unsorted list priority queue implementation for sort

		cout << "\nTiming sort . . ." << endl;
		ostream << "\n\nUnsorted Queue Sort (s):\n\n";

		for (unsigned i = 1; i <= size / interval; i++)
		{ // Clocking sort times for a total of 100 data points over the interval [0, size)
			stopwatch.Reset();
			for (unsigned j = 0; j < i*interval; j++) // Inserting items. . .
				unsorted_queue->insertItem(arr[j]);

			for (unsigned j = 0; j < i*interval; j++) // Removing items. . .
				unsorted_queue->removeMin();

			ostream << stopwatch.GetElapsedSeconds() << "\n"; // Record sort time
		}
		break;

	case 1: // If queue choice was sorted queue
		cout << "\nChosen implementation: Sorted queue" << endl;

		sorted_queue = new SortedPQ<int>(); // Instantiate sorted list priority queue implementation for insertion

		cout << "\nTiming insertion . . ." << endl;
		ostream << "Sorted Queue Insertion (s):\n\n";
		stopwatch.Reset();

		for (unsigned i = 1; i <= size; i++)
		{ // Inserting items. . .
			sorted_queue->insertItem(arr[i-1]);
			if (i % interval == 0)
				ostream << stopwatch.GetElapsedSeconds() << "\n"; // Recording insertion time
		}

		delete sorted_queue;

		sorted_queue = new SortedPQ<int>(); // Instantiate sorted list priority queue implementation for sort

		cout << "\nTiming sort . . ." << endl;
		ostream << "\n\nSorted Queue Sort (s):\n\n";

		for (unsigned i = 1; i <= size / interval; i++)
		{ // Clocking sort times for a total of 100 data points over the interval [0, size)
			stopwatch.Reset();
			for (unsigned j = 0; j < i*interval; j++) // Inserting items. . .
				sorted_queue->insertItem(arr[j]);

			for (unsigned j = 0; j < i*interval; j++) // Removing items. . .
				sorted_queue->removeMin();

			ostream << stopwatch.GetElapsedSeconds() << "\n"; // Record sort time
		}
		break;

	case 2: // If queue choice was heap queue
		cout << "\nChosen implementation: Heap queue" << endl;

		cout << "\nTiming bottom-up construction . . ." << endl; 
		ostream << "Heap Queue bottom up construction (s):\n\n";

		for (unsigned i = 1; i <= size / interval; i++)
		{ // Clocking construction times for a total of 100 data points over the interval [0, size)
			stopwatch.Reset();
			heap_queue = new HeapPQ<int>(arr, i*interval);
			ostream << stopwatch.GetElapsedSeconds() << "\n"; // Recording construction time
			delete heap_queue;
		}

		heap_queue = new HeapPQ<int>(); // Instantiate heap priority queue implementation for insertion

		cout << "\nTiming insertion . . ." << endl;
		ostream << "\n\nHeap Queue Insertion (s):\n\n";
		stopwatch.Reset();

		for (unsigned i = 1; i <= size; i++)
		{ // Inserting items. . .
			heap_queue->insertItem(arr[i-1]);
			if (i % interval == 0)
				ostream << stopwatch.GetElapsedSeconds() << "\n"; // Recording insertion time
		}

		delete heap_queue;

		heap_queue = new HeapPQ<int>(); // Instantiate heap priority queue implementation for sort

		cout << "\nTiming sort . . ." << endl;
		ostream << "\n\nHeap Queue Sort (s):\n\n";

		for (unsigned i = 1; i <= size / interval; i++)
		{ // Clocking sort times for a total of 100 data points over the interval [0, size)
			stopwatch.Reset();
			for (unsigned j = 0; j < i*interval; j++) // Inserting items. . .
				heap_queue->insertItem(arr[j]);

			for (unsigned j = 0; j < i*interval; j++) // Removing items. . .
				heap_queue->removeMin();

			ostream << stopwatch.GetElapsedSeconds() << "\n"; // Record sort time
		}
		break;

	default:
		throw runtime_error("\nInvalid queue selection for experiment!");
	}
	//########################################################################*/

	cout << "\nExperiment complete! Times logged to " << output_filename << endl << endl;
	ostream.close(); // Close output file
	system("PAUSE");
	return 0;
}
catch (const exception & e) { //Catch errors using removeMin() and minValue() functions with empty queues or opening/reading the input/output file
	cout << "Exception: " << e.what() << endl;
	system("PAUSE");
	return 1;
}
catch (...) { //Catch all misc. errors natively defined in std::exception (included in queue implementations)
	cout << "An undefined exception occured." << endl;
	system("PAUSE");
	return 2;
}

