#include <iostream>
#include<chrono>
#include "eytzinger.hpp"

int main(){

	const int n = 2000;

	auto *a = new std::uint32_t[n];
	std::iota(a, a+n, 1);
	
	std::cout << "To eytzinger: " << std::endl;
	to_eyzinger(a, n);
	std::cout << "Result: " << std::endl;
	for(int i = 0 ; i < n ; i ++){
		std::cout << a[i] << " ";
	}

	std::cout << std::endl;

	//int b[15] = {1, 3,  5,  7, 9, 11, 13, 15, 2, 4, 6, 8, 10, 12, 14};

	std::cout << "To sorted: " << std::endl;
	to_sorted(a, n);
	std::cout << "Result: " << std::endl;
	for(int i = 0 ; i < n ; i ++){
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

}