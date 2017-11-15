#define CATCH_CONFIG_MAIN  

#include "catch.hpp"
#include "eytzinger.hpp"

const int n1 = 1;
const int n2 = 2;
const int n3 = 63;
const int n4 = 100;
const int n5 = 33554431;

/*----------------------------------------
* Test helper functions
----------------------------------------*/

template<typename Data>
int isEytzinger(Data *a, int length){
	
	for(int i = 0; i < length; i++){

		if(2 * i + 1 >= length){ continue; }
		if(a[i] < a[2 * i + 1]){ return 0; }

		if(2 * i + 2 >= length){ continue; }
		if(a[i] > a[2 * i + 2]){ return 0; }	

	}

	return 1;
}

template<typename Data>
int isSorted(Data *a, int length){

	for(int i = 0; i < length;  i++){
		if(i >= length){ continue; }
		if(a[i] > a[i + 1]){ return 0; }
	}

	return 1;

}

/*----------------------------------------
* Test cases for eytzinger.hpp
----------------------------------------*/

//TODO: Add basic test cases for arrays not of length 2^n - 1

TEST_CASE( "Eytzinger search", "[eytzinger]" ) {

	int eytzingerArray[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,  7,  9,  11, 13, 15};

	REQUIRE(branchy_search_original(eytzingerArray, 8) == 0);
	REQUIRE(branchy_search_original(eytzingerArray, 15) == 14);
	REQUIRE(branchy_search_original(eytzingerArray, 1) == 7);
	REQUIRE(branchy_search_original(eytzingerArray, 3) == 8);

}

TEST_CASE( "From sorted to eytzinger (using outshuffle + preshufle)", "[eytzinger]" ) {

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

	to_eyzinger(a1, n1);
	to_eyzinger(a2, n2);
	to_eyzinger(a3, n3);
	to_eyzinger(a4, n4);
	to_eyzinger(a5, n5);

	REQUIRE( isEytzinger(a1, n1) == 1);
	REQUIRE( isEytzinger(a2, n2) == 1);
	REQUIRE( isEytzinger(a3, n3) == 1);
	REQUIRE( isEytzinger(a4, n4) == 1);
	REQUIRE( isEytzinger(a5, n5) == 1);

}


TEST_CASE( "From sorted to eytzinger (using outshuffle_jain)", "[eytzinger]" ) {

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

	to_eyzinger_jain(a1, n1);
	to_eyzinger_jain(a2, n2);
	to_eyzinger_jain(a3, n3);
	to_eyzinger_jain(a4, n4);
	to_eyzinger_jain(a5, n5);

	REQUIRE( isEytzinger(a1, n1) == 1);
	REQUIRE( isEytzinger(a2, n2) == 1);
	REQUIRE( isEytzinger(a3, n3) == 1);
	REQUIRE( isEytzinger(a4, n4) == 1);
	REQUIRE( isEytzinger(a5, n5) == 1);

}

TEST_CASE( "From sorted to eytzinger (using outshuffle_blocked)", "[eytzinger]" ) {

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

	to_eyzinger_blocked(a1, n1);
	to_eyzinger_blocked(a2, n2);
	to_eyzinger_blocked(a3, n3);
	to_eyzinger_blocked(a4, n4);
	to_eyzinger_blocked(a5, n5);

	REQUIRE( isEytzinger(a1, n1) == 1);
	REQUIRE( isEytzinger(a2, n2) == 1);
	REQUIRE( isEytzinger(a3, n3) == 1);
	REQUIRE( isEytzinger(a4, n4) == 1);
	REQUIRE( isEytzinger(a5, n5) == 1);

}

TEST_CASE( "From eytzinger to sorted", "[eytzinger]" ) {

}

TEST_CASE( "Eytzinger next", "[eytzinger]" ) {

	int eytzingerArray[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,  7,  9,  11, 13, 15};
	int length = 15;

	REQUIRE( eytzinger_next(7, length) == 3);
	REQUIRE( eytzinger_next(3, length) == 8);
	REQUIRE( eytzinger_next(8, length) == 1);
	REQUIRE( eytzinger_next(1, length) == 9);

}

TEST_CASE( "Eytzinger prev", "[eytzinger]" ) {
	
	int eytzingerArray[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,  7,  9,  11, 13, 15};
	int length = 15;

	REQUIRE( eytzinger_prev(3, length) == 7);
	REQUIRE( eytzinger_prev(8, length) == 3);
	REQUIRE( eytzinger_prev(1, length) == 8);

}