#define CATCH_CONFIG_MAIN  

#include "catch.hpp"
#include "eytzinger.hpp"

/*----------------------------------------
* Test helper functions
----------------------------------------*/

template<typename Data>
int isEytzinger(Data *a, int length){
	
	for(int i = 0; i < length; i++){

		if(2 * i + 1 >= length){ continue; }
		if(a[i] < a[2 * i + 1]){ return 0; }

		if(2 * i + 2 >= length){ return 1; }
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

TEST_CASE( "From sorted to eytzinger", "[eytzinger]" ) {

	int sortedArray1[1];
	int sortedArray2[2];
	int sortedArray3[63];
	int sortedArray4[100];
	int sortedArray5[100000];

	int n1 = 1;
	int n2 = 2;
	int n3 = 63;
	int n4 = 100;
	int n5 = 100000;

	for(int i = 0; i < n1 ; i ++){
		sortedArray1[i] = i + 1;
	}

	for(int i = 0; i < n2 ; i ++){
		sortedArray2[i] = i + 1;
	}

	for(int i = 0; i < n3 ; i ++){
		sortedArray3[i] = i + 1;
	}

	for(int i = 0; i < n4 ; i ++){
		sortedArray4[i] = i + 1;
	}

	for(int i = 0; i < n5 ; i ++){
		sortedArray5[i] = i + 1;
	}

	to_eyzinger(sortedArray1);
	to_eyzinger(sortedArray2);
	to_eyzinger(sortedArray3);
	to_eyzinger(sortedArray4);
	to_eyzinger(sortedArray5);

	REQUIRE( isEytzinger(sortedArray1, n1) == 1);
	REQUIRE( isEytzinger(sortedArray2, n2) == 1);
	REQUIRE( isEytzinger(sortedArray3, n3) == 1);
	REQUIRE( isEytzinger(sortedArray4, n4) == 1);
	REQUIRE( isEytzinger(sortedArray5, n5) == 1);

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
