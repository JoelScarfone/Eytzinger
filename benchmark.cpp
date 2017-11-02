#include <iostream>
#include<chrono>
#include "eytzinger.hpp"

int main(){

	int n = 33554431;

	std::chrono::duration<double> elapsed;

	std::cout << "Building and filling...";
	std::cout.flush();
	auto *a = new std::uint32_t[n];

	std::iota(a, a+n, 0);
	std::cout << " done." << std::endl << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Testing: to_eyzinger" << std::endl;
	std::cout << "-------------------------------------" << std::endl << std::endl;

	std::cout << "Permuting using outshuffle...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	outshuffle(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
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

}
