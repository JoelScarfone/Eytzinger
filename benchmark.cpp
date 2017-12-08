#include <iostream>
#include <chrono>
#include <string>
#include "eytzinger.hpp"

/*--------------------------------------------
Framework Functions
--------------------------------------------*/

void title(const char* title){

	std::cout  << std::endl << "-------------------------------------" << std::endl;
	std::cout << "Benchmarking: " << title << std::endl;
	std::cout << "-------------------------------------" << std::endl << std::endl;
}

template<bool refill = false>
void fill(std::uint32_t *a, const int n){
	if(!refill){
		std::cout << "Building and filling...";
		std::cout.flush();
		std::iota(a, a+n, 0);
		std::cout << "done" << std::endl << std::endl;
	}else{
		std::cout << "Refilling...";
		std::cout.flush();
		std::iota(a, a+n, 0);
		std::cout << "done" << std::endl << std::endl;
	}
}

/*--------------------------------------------
Benchmark Functions
--------------------------------------------*/

void benchmark_outshuffle(){

	const int n = 100000000;
	auto *a = new std::uint32_t[n];

	title("outshuffle");
	fill(a, n);

	std::cout << "Permuting using blocked_outshuffle...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	blocked_outshuffle(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	fill<true>(a, n);

	std::cout << "Permuting using prime_outshuffle...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	prime_outshuffle(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	fill<true>(a, n);

	std::cout << "Permuting using jain_outshuffle...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	jain_outshuffle(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	fill<true>(a, n);

	std::cout << "Permuting using blocked_outshuffle_rotate...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	blocked_outshuffle_rotate(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

}

void benchmark_inshuffle(){

	const int n = 100000000;
	auto *a = new std::uint32_t[n];

	title("inshuffle");
	fill(a, n);

	std::cout << "Permuting using blocked_inshuffle...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	blocked_inshuffle(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	fill<true>(a, n);

	std::cout << "Permuting using prime_inshuffle...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	prime_inshuffle(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;


}

void benchmark_to_eytzinger(){

	const int n = 100000000;
	auto *a = new std::uint32_t[n];

	title("to_eytzinger");
	fill(a,n);
	
	std::cout << "Permuting using to_eytzinger...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	to_eytzinger(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	fill<true>(a, n);

	std::cout << "Permuting using to_eytzinger_jain...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	to_eytzinger_jain(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	fill<true>(a, n);

	std::cout << "Permuting using to_eytzinger_blocked_rotate...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	to_eytzinger_blocked_rotate(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	fill<true>(a, n);

	std::cout << "Permuting using to_eytzinger_rotate...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	to_eytzinger_rotate(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

}

void benchmark_to_sorted(){

	const int n = 100000000;
	auto *a = new std::uint32_t[n];

	title("to_sorted");
	fill(a,n);
	
	std::cout << "Permuting using to_sorted...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	to_sorted(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;
}

void benchmark_itteration(){

	const int n = 100000000;
	auto *a = new std::uint32_t[n];
	int temp = 0;

	title("itteration");
	fill(a,n);
	std::cout << "Prepping eytzinger...";
	to_eytzinger(a, n);
	Eytzinger<uint32_t, int> arr(a, n);
	std::cout << "Done." << std::endl << std::endl;

	std::cout << "Basic itteration with sorted array...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < n; i ++){
		temp = temp + a[i] % 2;
	}
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "pre incerement iteration with eytzinger...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	for(Eytzinger<uint32_t, int>::Iterator i = arr.begin(); i != arr.end(); ++i){
		temp = temp + *i % 2;
	}
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "post incerement iteration with eytzinger...";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	for(Eytzinger<uint32_t, int>::Iterator i = arr.begin(); i != arr.end(); i++){
		temp = temp + *i % 2;
	}
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

}

int main(int argc, char* argv[]){

	int task = 0;

	if (argc > 1){

		std::string str1 (argv[1]);
	  	std::string str2 ("outshuffle");
  		std::string str3 ("inshuffle");
  		std::string str4 ("eytzinger");
  		std::string str5 ("sorted");
  		std::string str6 ("iteration");

		if (str1.compare(str2) == 0){
			task = 1;
		}		
		if (str1.compare(str3) == 0){
			task = 2;
		}
		if (str1.compare(str4) == 0){
			task = 3;
		}		
		if (str1.compare(str5) == 0){
			task = 4;
		}
		if (str1.compare(str6) == 0){
			task = 5;
		}
	}

	switch(task){
		case 1: benchmark_outshuffle();
				break;
		case 2: benchmark_inshuffle();
				break;
		case 3: benchmark_to_eytzinger();
				break;
		case 4: benchmark_to_sorted();
				break;
		case 5: benchmark_itteration();
				break;
		default:benchmark_outshuffle();
				benchmark_inshuffle();
				benchmark_to_eytzinger();
				benchmark_to_sorted();
				benchmark_itteration();
				break;
	}

}
