#ifndef INPUT_H
#define INPUT_H

#include "Sorting.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <exception>

using namespace std;

template<class T>
class Input 
{ // Reads templated data from file, and also produces n random floating point numbers [0, 1] in three different files, unsorted and sorted (increasing/decreasing) as test input
	string unsorted_input_filename, sorted_i_input_filename, sorted_d_input_filename; // Files for outputting test input
	int input_size, input_choice; // Keeps track of size and sorting choice for experiment
	ofstream ostream; // FileIO streams
	ifstream istream;

public:
	Input() : 
		unsorted_input_filename{ "unsorted_input.txt" }, // Initializing test input filenames and data members
		sorted_i_input_filename{ "sorted_i_input.txt" }, 
		sorted_d_input_filename{ "sorted_d_input.txt" },
		input_choice{ 0 },
		input_size{ 0 }
	{}

	~Input() {}

	void generate_input(int choice, int size)
	{ // Generates size random floating point numbers [0, 1] and stores them in three files, unsorted and sorted (increasing/decreasing) as test input
		srand(time(NULL)); // Seeding RNG
		T* arr = new T[size]; // Creating new array to hold values

		printf("Generate Input Mode Selected!\n");
		printf("The experiment will not run, however, new test input files will be generated.\n\n");

		for (int i = 0; i < size; i++) // Populating array with values
			arr[i] = static_cast<double>(rand()) / RAND_MAX;

		printf("Creating unsorted input . . . \n\n");
		ostream.open(unsorted_input_filename.c_str()); // Open output file for unsorted input
		if (!ostream) throw runtime_error("Could not create " + unsorted_input_filename + "!\n");

		ostream << choice << "\n" << size << "\n"; // Output sorting choice and size first

		for (int i = 0; i < size; i++) // Fill file with data
			ostream << arr[i] << "\n";

		ostream.close(); // Close output stream

		Sorting<double>::heap_sort(arr, size); // Sort data in increasing order

		printf("Creating sorted input (increasing) . . . \n\n");
		ostream.open(sorted_i_input_filename.c_str()); // Open output file for sorted input (increasing)
		if (!ostream) throw runtime_error("Could not create " + sorted_i_input_filename + "!\n");

		ostream << choice << "\n" << size << "\n"; // Output sorting choice and size first

		for (int i = 0; i < size; i++) // Fill file with sorted data
			ostream << arr[i] << "\n";

		ostream.close(); // Close output stream

		printf("Creating sorted input (decreasing) . . . \n\n");
		ostream.open(sorted_d_input_filename.c_str()); // Open output file for sorted input (decreasing)
		if (!ostream) throw runtime_error("Could not create " + sorted_d_input_filename + "!\n");

		ostream << choice << "\n" << size << "\n"; // Output sorting choice and size first

		for (int i = size - 1; i >= 0; i--) // Loop through data backwards to fill file with reverse-sorted data
			ostream << arr[i] << "\n";

		ostream.close(); // Close output stream
		delete[] arr; // Free dynamically allocated memory
		printf("Done!\n\n");
	}

	T* read_input(string input_filename)
	{ // Opens input file and reads contents into dynamic array

		istream.open(input_filename.c_str()); // Open input file
		if (!istream) throw runtime_error("Could not open " + input_filename + "!\n");

		printf("Reading data from input file %s\n", input_filename.c_str());
		if (!(istream >> input_choice >> input_size)) // Read input_choice and input_size from input file
			throw runtime_error("Error reading " + input_filename + "! Is the file empty?\n");
														   
		T* arr = new T[input_size]; // Dynamically allocate new array
		for (int i = 0; i < input_size; i++)
		{ // Insert the number of elements specified by file into array
			if (!(istream >> arr[i])) // Reading data from file
				throw runtime_error("Error reading " + input_filename + "! Is there a size mismatch?\n");
		}

		istream.close(); // Close input file
		return arr; // Return array
	}

	int get_size() 
	{ // Returns experiment size (specified by file)
		if (input_size == 0)
			throw runtime_error("Error retrieving size, is it zero?\n");
		else return input_size;
	}

	int get_choice()
	{ // Returns implementation choice (specified by file)
		return input_choice;
	}
};

#endif