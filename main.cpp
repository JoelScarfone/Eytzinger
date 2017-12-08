#include <iostream>
#include<chrono>
#include "eytzinger.hpp"

// int get_pos_of(std::uint32_	t* arr, const int n, int l){
// 	for(int i = 0; i < n; i ++){
// 		if (arr[i] == l){
// 			return i;
// 		}
// 	}
// 	return -1;
// }

// void print_prime_cycle_to_stdout(const int n){

// 	auto *a = new std::uint32_t[n];
// 	std::iota(a, a+n, 0);
// 	blocked_outshuffle(a, n);

// 	int temp = 0;
// 	for(int i = 0; i < n; i++){
// 		temp = get_pos_of(a, n, temp);
// 		std::cout << temp << ", ";
// 	}
// }

int main(){

	const int n1 = 100;
	auto *a1 = new std::uint32_t[n1];
	std::iota(a1, a1+n1, 0);

	to_eyzinger(a1, n1);

	to_sorted(a1, n1);

	for(int i = 0; i < n1; i ++){
		std::cout << a1[i] << " ";
	}
	std::cout << std::endl;
}