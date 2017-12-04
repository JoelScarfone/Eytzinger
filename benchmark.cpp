#include <iostream>
#include <chrono>
#include <string>
#include "eytzinger.hpp"

void benchmark_outshuffle(){

	const int n = 134217727;

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Benchmarking: outshuffles" << std::endl;
	std::cout << "-------------------------------------" << std::endl << std::endl;

	std::cout << "Building and filling...";
	std::cout.flush();
	auto *a = new std::uint32_t[n];

	std::iota(a, a+n, 0);
	std::cout << " done." << std::endl << std::endl;

	std::cout << "Permuting using outshuffle...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	outshuffle(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Refilling...";
	std::cout.flush();
	std::iota(a, a+n, 0);
	std::cout << "done" << std::endl;

	std::cout << "Permuting using jain_outshuffle...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	jain_outshuffle(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Refilling...";
	std::cout.flush();
	std::iota(a, a+n, 0);
	std::cout << "done" << std::endl;

	std::cout << "Permuting using blocked_outshuffle...";
	
	const unsigned BLOCK=96;

	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	blocked_outshuffle<BLOCK>(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Finished." << std::endl << std::endl;

	std::cout << "Refilling...";
	std::cout.flush();
	std::iota(a, a+n, 0);
	std::cout << "done" << std::endl;

	std::cout << "Permuting using blocked_outshuffle_2...";
	
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	blocked_outshuffle_2(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Finished." << std::endl << std::endl;

}

void benchmark_to_eytzinger(){

	const int n = 1000000000;

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Benchmarking: to_eytzinger" << std::endl;
	std::cout << "-------------------------------------" << std::endl << std::endl;

	std::cout << "Building and filling...";
	std::cout.flush();
	auto *a = new std::uint32_t[n];

	std::iota(a, a+n, 0);
	std::cout << " done." << std::endl << std::endl;

	std::cout << "Permuting using to_eyzinger...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	//to_eyzinger(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Refilling...";
	std::cout.flush();
	std::iota(a, a+n, 0);
	std::cout << "done" << std::endl;

	std::cout << "Permuting using to_eyzinger_blocked...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	to_eyzinger_blocked(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Refilling...";
	std::cout.flush();
	std::iota(a, a+n, 0);
	std::cout << "done" << std::endl;

	std::cout << "Permuting using to_eyzinger_blocked_2...";
	
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	to_eyzinger_blocked_2(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Finished." << std::endl << std::endl;

}

void benchmark_presuffle(){

	const int n = 100000000;

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Benchmarking: preshuffles" << std::endl;
	std::cout << "-------------------------------------" << std::endl << std::endl;

	std::cout << "Building and filling...";
	std::cout.flush();
	auto *a = new std::uint32_t[n];

	std::iota(a, a+n, 0);
	std::cout << " done." << std::endl << std::endl;

	std::cout << "Permuting using preshuffle_2...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	preshuffle_2(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Refilling...";
	std::cout.flush();
	std::iota(a, a+n, 0);
	std::cout << "done" << std::endl;

	std::cout << "Permuting using preshuffle_3...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	preshuffle_3(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	// Commented out because preshuffle is just too slow
	// std::cout << "Refilling...";
	// std::cout.flush();
	// std::iota(a, a+n, 0);
	// std::cout << "done" << std::endl;

	// std::cout << "Permuting using preshuffle...";
	// std::cout.flush();
	// start = std::chrono::high_resolution_clock::now();
	// preshuffle(a, n);
	// stop =  std::chrono::high_resolution_clock::now();
	// elapsed = stop - start;
	// std::cout << "done (" << elapsed.count() << "s)" << std::endl;

}

int main(int argc, char* argv[]){

	int task = 0;

	if (argc > 1){

		std::string str1 (argv[1]);
	  	std::string str2 ("outshuffle");
  		std::string str3 ("preshuffle");
  		std::string str4 ("eytzinger");

		if (str1.compare(str2) == 0){
			task = 1;
		}
		if (str1.compare(str3) == 0){
			task = 2;
		}
		if (str1.compare(str4) == 0){
			task = 3;
		}
	}

	switch(task){
		case 1: benchmark_outshuffle();
				break;
		case 2: benchmark_presuffle();
				break;
		case 3: benchmark_to_eytzinger();
				break;
		default:benchmark_outshuffle();
				benchmark_presuffle();
				benchmark_to_eytzinger();
				break;
	}

}
