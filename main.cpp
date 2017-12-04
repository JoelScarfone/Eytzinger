#include <iostream>
#include<chrono>
#include "eytzinger.hpp"

int main(){

	int n = 100;
	auto *a = new std::uint32_t[n];
	std::iota(a, a+n, 0);

	to_eyzinger(a, n);

	Eytzinger<uint32_t, int> arr(a, n);

 	std::cout << arr.search(80) << std::endl;

	for(Eytzinger<uint32_t, int>::Iterator i = arr.begin(); i != arr.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

}