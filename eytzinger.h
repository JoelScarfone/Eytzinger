#include <iostream>
#include <algorithm>
#include "math.h" // should not need once i clean up log2


//TODO this should not be declared here...
int n = 15;

// Implemented branchy_search straight from Eytzinger paper
int branchy_search_original(int element, int arr[]){
	
	int i = 0;

	while (i < n){
		i = ( element <= arr[i]) ? (2 * i + 1) : (2 * i + 2);
	}

	int j = (i + 1) >> __builtin_ffs(~(i + 1));
	return (j == 0) ? n : j - 1;

}

// Returns the item successing they eyztinger layed-out array element arr[i],
//TODO fix log_2 builting clz 9 counts leading 0s 
int eytzinger_next(int i){

	if (2 * i + 2 > n - 1){
		int j = (i + 1) >> __builtin_ffs(~(i + 1));
		return (j > n) ? -1 : j - 1;
	}else{

		int iDepth = log2(i + 1);
		int treeDepth = log2(n);

		int path = i + 1;

		path = path << 1;

		path |= 1 << 0;
		path = path << (treeDepth - iDepth - 2);

		return path - 1;
	}
}

/*----------------------------------------------------
Everything below here is dealing with in place algorythms
to move from sorted order to eytzinger order, and vise-versa
----------------------------------------------------*/

// This is the fastest implementation in preliminary tests
template<typename I>
inline I outshuffle_perm3(I i, I n) {
	I out = i/2;
	I fix = (i & 1) ? 0 : n/2;
	return out+fix;
}

template<typename Data, typename Index>
void jain_outshuffle(Data *a, Index n) {


	if (n <= 1) return;
	// Compute appropriate value of m
	Index m = 1;
	while (3*m-1 <= n) m *= 3;
	m -= 1;

	// std::cout << "m: " << m << std::endl;

	// Use Jain's trick to shuffle a[0,...,m-1];
	for (Index g = 1; g < m; g *= 3) {
		Index cur = g-1;
		Data t[2];
		int flipflop = 0;
		t[flipflop] = a[cur];
		do {
			Index nxt = outshuffle_perm3(cur, m);
			t[!flipflop] = a[nxt];
			a[nxt] = t[flipflop];
			flipflop = !flipflop;
			cur = nxt;
		} while (cur != g-1);
	}

	// Recurse on a[m,...n-1]
	jain_outshuffle(a+m, n-m);

	// Regroup odds and evens
	std::rotate(a+m/2, a+m, a+m+(n-m)/2);
}

template<typename Data, size_t size>
void to_eyzinger(Data (&array)[size]) {
	int todo = size;
	while(todo > 1){
		jain_outshuffle(array, todo);
		todo = todo / 2;
	}
}

