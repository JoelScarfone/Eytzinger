#define CATCH_CONFIG_MAIN  

#include "catch.hpp"
#include "eytzinger.hpp"

/*----------------------------------------
* Test helper functions
----------------------------------------*/

template<typename Data>
int equal(Data *a, Data* b, int length){
	for(int i = 0; i < n; i ++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	return 1;
}

/*----------------------------------------
* Test cases for eytzinger.hpp
----------------------------------------*/

TEST_CASE( "Eytzinger search", "[eytzinger]" ) {

	int eytzingerArray[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,  7,  9,  11, 13, 15};

	REQUIRE(branchy_search_original(eytzingerArray, 8) == 0);
	REQUIRE(branchy_search_original(eytzingerArray, 15) == 14);
	REQUIRE(branchy_search_original(eytzingerArray, 1) == 7);
	REQUIRE(branchy_search_original(eytzingerArray, 3) == 8);

}

TEST_CASE( "From sorted to eytzinger", "[eytzinger]" ) {

	int eytzingerArray[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,  7,  9,  11, 13, 15};
	int sortedArray[] =    {1, 2, 3,  4, 5, 6,  7,  8, 9, 10, 11, 12, 13, 14, 15};
	int length = 15;

	to_eyzinger(sortedArray);

    REQUIRE( equal(eytzingerArray, sortedArray, length) == 1);
    
}

TEST_CASE( "From eytzinger to sorted", "[eytzinger]" ) {

}

TEST_CASE( "Eytzinger next", "[eytzinger]" ) {

	int eytzingerArray[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,  7,  9,  11, 13, 15};

	REQUIRE( eytzinger_next(7, n) == 3);
	REQUIRE( eytzinger_next(3, n) == 8);
	REQUIRE( eytzinger_next(8, n) == 1);
	REQUIRE( eytzinger_next(1, n) == 9);

}

TEST_CASE( "Eytzinger prev", "[eytzinger]" ) {

}
