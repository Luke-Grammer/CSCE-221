#include <iostream>
#include <fstream>
#include "Sorting.h"
#include "Input.h"
#include "stopwatch.h"

using namespace std;

// DECLARING CONSTANTS
// File name for reading (change to unsorted_input.txt, sorted_i_input.txt, or sorted_d_input.txt after running in GEN_INPUT_MODE once for pre-generated random inputs)
const string input_filename{ "numbers.txt" },
			 output_filename{ "times.txt" }; // File name for recording times

const bool GEN_INPUT_MODE = false;  // Generate new random input for testing
const int  GEN_INPUT_SIZE = 50000;  // Number of random inputs to generate (if generating inputs)
const int  GEN_CHOICE = 2;			// Sorting implementation choice for new test files

const bool PRINT_SORTED = true;     // Print sorted output to console?
		   
int main() try 
{
	Input<double> input;    // Class to generate random input and read data from file
	double *arr, *orig_arr; // Dynamic array to hold original data and another to hold sorted data
	CStopWatch stopwatch;   // Declaring stopwatch to time implementations
	ofstream ostream;	    // Declaring File Output stream
	int interval = 0,       // Logs time every 'interval' iterations (choice, interval, and size are read from input file)
		choice = 0,		    // Determines which sorting algorithm to implement 
		size = 0;           // Total number of data values for testing

	if (GEN_INPUT_MODE) 
	{ // Generate n random inputs and store them in three files, one unsorted and two sorted (increasing/decreasing), then exit.
		input.generate_input(GEN_CHOICE, GEN_INPUT_SIZE);
		system("PAUSE");
		return 0;
	}

	orig_arr = input.read_input(input_filename); // Read data from input file into array
	choice = input.get_choice();
	size = input.get_size();
	interval = ((size / 100 == 0) ? 1 : (size / 100)); // Set timing interval to size / 100 with a minimum of 1 if size < 100

	ostream.open(output_filename.c_str()); // Open output file
	if (!ostream) throw runtime_error("Could not open " + output_filename + " to output times!\n");

	printf("\nBeginning Experiment with size n = %i . . .\n", size);

	switch (choice) 
	{ // Outputs information about chosen implementation to console and file
	case 1:
		printf("\nChosen implementation: Selection sort\n");
		ostream << "Selection Sort (s):\n\n";
		break;
	case 2:
		printf("\nChosen implementation: Heap sort\n");
		ostream << "Heap Sort (s):\n\n";
		break;
	case 3:
		printf("\nChosen implementation: Merge sort\n");
		ostream << "Merge Sort (s):\n\n";
		break;
	default:
		throw runtime_error("Invalid selection for experiment!\n"); // Make sure implementation choice is valid from here on
	}

	printf("\nTiming sort . . .\n");
	ostream << "n = " << size << "\n\n";

	for (int i = 1; i <= size / interval; i++)
	{ // Clocking sort times for a total of 100 data points over the interval [0, size)
		arr = new double[i * interval];
		for (int j = 0; j < i*interval; j++) // Copying items to new array. . .
			arr[j] = orig_arr[j];

		if (choice == 1) // Implementation choice 1 is selection sort
		{
			stopwatch.Reset();
			Sorting<double>::selection_sort(arr, i * interval); // Sorting items. . .
		}
		else if (choice == 2) // Implementation choice 2 is heap sort
		{
			stopwatch.Reset();
			Sorting<double>::heap_sort(arr, i * interval); // Sorting items. . .
		}
		else // Implementation choice 3 is merge sort
		{
			stopwatch.Reset();
			Sorting<double>::merge_sort(arr, 0, i * interval - 1); // Sorting items. . .
		}

		ostream << stopwatch.GetElapsedSeconds() << "\n"; // Record sort time

		if (i == size / interval && PRINT_SORTED) // Print sorted output if selected
		{
			char print_override = 'y';  // If n is large and print is selected, check if user wants to proceed
			if (size > 100)
			{
				printf("\nYou have chosen to print sorted elements, however, a large number of elements have been sorted.\n");
				printf("Print anyway? (Y/N): ");
				cin >> print_override;
			}
			if (tolower(print_override) == 'y')
				for (int i = 0; i < size; i++)
					printf("%f\n", arr[i]);
		}
			
		delete[] arr;
	}

	printf("\nExperiment complete! Times logged to %s\n\n", output_filename.c_str());
	ostream.close(); // Close output file
	system("PAUSE");
	return 0;
}
catch (const exception & e) { //Catch errors opening/reading the input/output file
	printf("\nException: %s\n", e.what());
	system("PAUSE");
	return 1;
}
catch (...) { //Catch all misc. errors natively defined in std::exception
	printf("\nAn undefined exception occured.\n");
	system("PAUSE");
	return 2;
}