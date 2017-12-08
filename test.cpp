#define CATCH_CONFIG_MAIN  

#include "catch.hpp"
#include "eytzinger.hpp"

const int n1 = 1;
const int n2 = 2;
const int n3 = 63;
const int n4 = 2000;
const int n5 = 33554431;

/*----------------------------------------
* Test helper functions
----------------------------------------*/

template<typename Data>
int is_sorted(Data *a, int length){

	for(int i = 0; i < length;  i++){
		if(i == length - 1){ return 1; }
		if(a[i] > a[i + 1]){ return 0; }
	}

	return 1;

}

/*----------------------------------------
* Test cases for eytzinger.hpp
----------------------------------------*/

TEST_CASE( "Eytzinger search", "[eytzinger]") {

	const int n = 20;
	int a[n] = {12, 7, 16, 3, 10, 14, 18, 1, 5, 9, 11, 13, 15, 17, 100, 0, 2, 4, 6, 8};

	Eytzinger<int, int> arr(a, n);

	REQUIRE( arr.search(12)  == 0);
	REQUIRE( arr.search(8)  == 19);
	REQUIRE( arr.search(3)  == 3);
	REQUIRE( arr.search(2)  == 16);
	REQUIRE( arr.search(100)  == 14);
	REQUIRE( arr.search(-1)  == n);

	REQUIRE( arr.upper_bound(99)  == 14);
	REQUIRE( arr.upper_bound(101)  == n);

}

TEST_CASE( "From sorted to eytzinger, and vise versa", "[eytzinger]" ) {

	auto *a1 = new std::uint32_t[n1];
	auto *a2 = new std::uint32_t[n2];
	auto *a3 = new std::uint32_t[n3];
	auto *a4 = new std::uint32_t[n4];
	auto *a5 = new std::uint32_t[n5];

	std::iota(a1, a1+n1, 0);
	std::iota(a2, a2+n2, 0);
	std::iota(a3, a3+n3, 0);
	std::iota(a4, a4+n4, 0);
	std::iota(a5, a5+n5, 0);

	to_eytzinger(a1, n1);
	to_eytzinger(a2, n2);
	to_eytzinger(a3, n3);
	to_eytzinger(a4, n4);
	to_eytzinger(a5, n5);

	REQUIRE( is_eytzinger(a1, n1) == 1);
	REQUIRE( is_eytzinger(a2, n2) == 1);
	REQUIRE( is_eytzinger(a3, n3) == 1);
	REQUIRE( is_eytzinger(a4, n4) == 1);
	REQUIRE( is_eytzinger(a5, n5) == 1);

	to_sorted(a1, n1);
	to_sorted(a2, n2);
	to_sorted(a3, n3);
	to_sorted(a4, n4);
	to_sorted(a5, n5);

	REQUIRE( is_sorted(a1, n1) == 1);
	REQUIRE( is_sorted(a2, n2) == 1);
	REQUIRE( is_sorted(a3, n3) == 1);
	REQUIRE( is_sorted(a4, n4) == 1);
	REQUIRE( is_sorted(a5, n5) == 1);

}

TEST_CASE( "Eytzinger forward iterator", "[eytzinger]" ) {

	const int n = 20;
	int a[n] = {12, 7, 16, 3, 10, 14, 18, 1, 5, 9, 11, 13, 15, 17, 19, 0, 2, 4, 6, 8};

	Eytzinger<int, int> arr(a,n);

	int j = 0;
	for(Eytzinger<int, int>::Iterator i = arr.begin(); i != arr.end(); ++i){
		REQUIRE(*i == j);
		j ++;
	}

}

TEST_CASE( "Eytzinger reverse iterator", "[eytzinger]" ) {
	
	const int n = 20;
	int a[n] = {12, 7, 16, 3, 10, 14, 18, 1, 5, 9, 11, 13, 15, 17, 19, 0, 2, 4, 6, 8};

	Eytzinger<int, int> arr(a,n);

	int j = n - 1;
	for(Eytzinger<int, int>::IteratorReverse i = arr.rbegin(); i != arr.rend(); ++i){
		REQUIRE(*i == j);
		j --;
	}

}