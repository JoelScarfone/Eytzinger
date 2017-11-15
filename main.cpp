#include <iostream>
#include<chrono>
#include "eytzinger.hpp"

int main(){

	const int n = 20;

	auto *a = new std::uint32_t[n];
	std::iota(a, a+n, 0);

	preshuffle_2(a, n);

	for(int i = 0 ; i < n ; i ++){
		std::cout << a[i] << " ";
	}

}