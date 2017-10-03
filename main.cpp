#include <iostream>
#include "eytzinger.hpp"

int main(){

	int eytzingerArray[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,  7,  9,  11, 13, 15};
	int sortedArray[] =    {1, 2, 3,  4, 5, 6,  7,  8, 9, 10, 11, 12, 13, 14, 15};
	int n = 15;

	//int current = 7;
	//for(int i = 0;3i < n; i ++){
	//	std::cout << eytzingerArray[current] << " " << std::endl;
	
	///std::cout << "Looking for the index of the prev element before: " << eytzingerArray[11] << ", At position " << 11  << std::endl;
	int next = eytzinger_prev(1, n);
	std::cout << "WE GOT: " << next << std::endl;

	std::cout << std::endl;


	next = eytzinger_prev(5, n);
	std::cout << "WE GOT: " << next << std::endl;


	// next = eytzinger_prev(13, n);
	// std::cout << "WE GOT: " << next << std::endl;


	// next = eytzinger_prev(14, n);
	// std::cout << "WE GOT: " << next << std::endl;

	//}

	// to_eyzinger(sortedArray);

	// std::cout << "Got:" << std::endl;
	// for(int i = 0; i < n; i ++){
	// 	std::cout << sortedArray[i] << " ";
	// }

	// std::cout << std::endl << std::endl << "Looking For:" << std::endl;
	// for(int i = 0; i < n; i++){
	// 	std::cout << eytzingerArray[i] << " ";
	// }

	// std::cout << std::endl;

}

// Stuff i was playing around with, not ready to delete just yet...
// --------------------------------------


// int n = 15;					    // the length of the array

// template<typename Data, size_t size>
// void to_eyzinger(Data (&array)[size]) {
// 	for(int i = 0; i < size ; i++){

// 	}
// }

// // This is the fastest implementation in preliminary tests
// template<typename I>
// inline I outshuffle_perm3(I i, I n) {
// 	I out = i/2;
// 	I fix = (i & 1) ? 0 : n/2;
// 	return out+fix;
// }

// template<typename Data, typename Index>
// void jain_outshuffle(Data *a, Index n) {


// 	if (n <= 1) return;
// 	// Compute appropriate value of m
// 	Index m = 1;
// 	while (3*m-1 <= n) m *= 3;
// 	m -= 1;

// 	std::cout << "m: " << m << std::endl;

// 	// Use Jain's trick to shuffle a[0,...,m-1];
// 	for (Index g = 1; g < m; g *= 3) {
// 		Index cur = g-1;
// 		Data t[2];
// 		int flipflop = 0;
// 		t[flipflop] = a[cur];
// 		do {
// 			Index nxt = outshuffle_perm3(cur, m);
// 			t[!flipflop] = a[nxt];
// 			a[nxt] = t[flipflop];
// 			flipflop = !flipflop;
// 			cur = nxt;
// 		} while (cur != g-1);
// 	}

// 	// Recurse on a[m,...n-1]
// 	jain_outshuffle(a+m, n-m);

// 	// Regroup odds and evens
// 	std::rotate(a+m/2, a+m, a+m+(n-m)/2);
// }


// // Returns the item at position i in a sorted array, within the eyzinger array arr
// int get_at_pos(int arr[], int i){

// 	cout << "Getting successor of " << arr[i] << ", which is at position " << i << " in arr..." << endl;

// 	bitset<8> x(i + 1);
//     cout << "Binary represenation of i + 1 is: " << x << "\n";

// 	int k = __builtin_ffs(~(i + 1));
// 	cout << "Index of first 0 in said binary is: " << k << endl;

// 	int j = (i + 1) >> k;
// 	bitset<8> y(j);

// 	cout << "Right hifting i + 1 (" << i + 1 << ") by k bits yields: " << j << " (" << y << ")" << endl;

// 	cout << "Array at j - 1 is then: " << arr[j-1] << endl;

// 	return 0;

// }
// 0 - >        00000
// 1 - >        00001
// 2 - > 		00010
// 3 - > 		00011
// 4 - >		00100
// 5 - >		00101



// // 1 -> 8
// // 2 -> 4
// // 3 -> 9  -> 12
// // 5 -> 10 -> 6
// // 7 -> 11 -> 13
// // 15

// int get_eytzinger_pos(int orderedPos, int arrayLength){

// 	int k = __builtin_ffs((orderedPos + 1));
// 	int height = ceil(log2(arrayLength));

// 	return pow(2, height - k) - 1 + (int)(orderedPos) / pow(2, k);

// }

// int get_ordered_pos(int eytzingerPos, int arrayLength){

// 	int k = (int) log2(eytzingerPos + 1);
// 	int height = ceil(log2(arrayLength));

// 	int every = pow(2, height - k);
// 	int starting_at = every / 2 - 1;

// 	return ((eytzingerPos + 1) % (int)pow(2, k)) * every + starting_at;

// }