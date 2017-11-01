#include <iostream>
#include<chrono>
#include "eytzinger.hpp"

int main(){

	int n = 1000000;

	std::chrono::duration<double> elapsed;

	std::cout << "Building and filling...";
	std::cout.flush();
	auto *a = new std::uint32_t[n];

	std::iota(a, a+n, 0);
	std::cout << " done." << std::endl << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Testing: to_eyzinger" << std::endl;
	std::cout << "-------------------------------------" << std::endl << std::endl;

	std::cout << "Permuting using preshuffle + outshuffle...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	to_eyzinger(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Refilling...";
	std::cout.flush();
	std::iota(a, a+n, 0);
	std::cout << "done" << std::endl;

	std::cout << "Permuting using preshuffle + jain_outshuffle...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	to_eyzinger_jain(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

}
