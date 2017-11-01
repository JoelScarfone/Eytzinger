#include <iostream>
#include <algorithm>

#include <bitset> // for debugging purposes

// Implemented branchy_search straight from Eytzinger paper
template<typename Data, size_t n>
int branchy_search_original(Data (&arr)[n], Data element){

	int i = 0;
	
	while (i < n){
		i = ( element <= arr[i]) ? (2 * i + 1) : (2 * i + 2);
	}

	int j = (i + 1) >> __builtin_ffs(~(i + 1));
	return (j == 0) ? n : j - 1;

}

// Returns the index of the item successing they eyztinger layed-out array element arr[i], with |arr| = n
int eytzinger_next(int i, int n){

	if (2 * i + 2 > n - 1){
		int j = (i + 1) >> __builtin_ffs(~(i + 1));
		return (j > n) ? -1 : j - 1;
	}else{

		int iDepth = 32 - __builtin_clz(i + 1);
		int treeDepth = 32 - __builtin_clz(n);

		int path = i + 1;
		path = path << 1;
		path |= 1 << 0;
		path = path << (treeDepth - iDepth - 1);
		return path - 1;

	}
}

//TODO: bounds check for going past the start of the sorted array
int eytzinger_prev(int i, int n){
	if (2 * i + 2 > n - 1){
		int j = (i + 1) >> __builtin_ffs(i + 1);
		return j - 1;
	}else{

		int iDepth = 32 - __builtin_clz(i + 1);
		int treeDepth = 32 - __builtin_clz(n);

		int j = ~(~((i + 1) << 1) << (treeDepth - iDepth - 1));

		return j - 1;	
	}
}

/*----------------------------------------------------
Everything below here is dealing with in place algorithms
to move from sorted order to eytzinger order, and vise-versa
----------------------------------------------------*/

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

// 	std::cout << "\nm: " << m << std::endl;

// 	// Use Jain's trick to shuffle a[0,...,m-1];
// 	for (Index g = 1; g < m; g *= 3) {
// 		std::cout << "\ng: " << g << std::endl; 
// 		Index cur = g-1;
// 		Data t[2];
// 		int flipflop = 0;
// 		t[flipflop] = a[cur];
// 		do {

// 			std::cout << "\ncur: " << cur << std::endl;
// 			Index nxt = outshuffle_perm3(cur, m);
// 			std::cout << "nxt: " << nxt << std::endl;
// 			std::cout << "flipflop: " << flipflop << std::endl;
// 			t[!flipflop] = a[nxt];
// 			a[nxt] = t[flipflop];
// 			flipflop = !flipflop;
// 			cur = nxt;
// 		} while (cur != g-1);
// 	}

// 	for (int i = 0; i < n; i ++){
// 		std::cout << a[i] << " ";
// 	}

// 	std::cout << std::endl;

// 	// Recurse on a[m,...n-1]
// 	jain_outshuffle(a+m, n-m);

// 	std::cout << "Done most, now calling rotate on a = ";

// 	for (int i = 0; i < n; i ++){
// 		std::cout << a[i] << " ";
// 	}

// 	// Regroup odds and evens
// 	std::rotate(a+m/2, a+m, a+m+(n-m)/2);

// 	std::cout << "\nDone rotate, now a = ";

// 	for (int i = 0; i < n; i ++){
// 		std::cout << a[i] << " ";
// 	}

// 	std::cout << std::endl;


// }

template<typename Data, typename Index>
void outshuffle(Data *a, Index n) {

	if (n <= 1) return;

	if (n <= 3){
		std::rotate(a, a + 1, a + 2);
		return;
	}

	int i = 1;
	int every = 4;

	while(i < n / 2){
		for(int j = i; j < n; j += every){
			std::rotate(a + j, a + j + i, a + j + i * 2);
		}
		i *= 2;
		every *= 2;
	}

	std::rotate(a, a + n / 2 + 1, a + n);

}

template<typename Data, typename Index>
int preshuffle(Data *a, Index n) {

	// No need to preshufle
	if (((n + 1) & n) == 0) return n;

	int i = 0;
	i |= 1 << (32 - __builtin_clz(n) - 1);

	int items = n - (i - 1);

	i = 2 * items - 1;
	for(int j = 2 * items - 3; j >= 1; j-= 2){
		std::rotate(a + j, a + j + 1, a + i);
		i -= 1;
	}

	std::rotate(a, a + items, a + n);

	return n - items;
}

template<typename Data, size_t n>
void to_eyzinger(Data (&array)[n]) {

	int todo = preshuffle(array, n);

	while(todo > 1){
		outshuffle(array, todo);
		todo = todo / 2;
	}

}

