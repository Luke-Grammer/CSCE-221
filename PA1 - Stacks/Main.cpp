#include <iostream>
#include <ctime>
#include "ArrayStack.h"
#include "DoublingArrayStack.h"
#include "LLStack.h"
#include "stopwatch.h"

const int NUM_TRIALS = 10000000;
const int TEST_INTERVAL = 10000;

int main() {
	try {
		srand((unsigned int)time(NULL));
		ArrayStack<int> stack1;
		DoublingArrayStack<int> stack2;
		LLStack<int> stack3;

		CStopWatch watch;
		for (int i = 0; i < NUM_TRIALS; i++) {
			if (i % TEST_INTERVAL == 0) {
				std::cout << watch.GetElapsedSeconds() << std::endl;
			}
			stack3.push(/*rand()*/ 100);
		}
		std::cout << "Current size is " << stack3.size() << std::endl;

	} 
	catch (const std::logic_error & e) { //Catch errors using pop() and top() functions with empty stacks
		std::cout << "Exception: " << e.what() << std::endl;
	}
	catch (...) { //Catch all misc. errors natively defined in std::exception (included in stack implementations)
		std::cout << "An undefined exception occured." << std::endl;
	}
	
	//Designed to keep window open after completion with compatibility for Windows, Mac, and Linux.
	//std::cout << "Press any key to continue . . ." << std::endl; 
	//char c;
	//std::cin >> c;
	return 0;
}