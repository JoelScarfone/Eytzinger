#include <iostream>
#include <algorithm>

const int pows[5] = {1,2,4,8,16};

template<typename Data, typename Index>
void swap_next(Data *a, Index i){
	Data x = a[i + 1];
	a[i+1] = a[i];
	a[i] = x;
}

//Need to get around this for a full block_swap to work...
template<typename Data, typename Index>
void block_swap(Data * a, Index n, const int B){
	struct block { Data dummy[B]; };
	block *arr = (block*)a;
	for(int i = 1; i < n/B; i+= 4){
		swap_next(arr, i);
	}
}

int main(){

	const int n = 100;
	auto *a = new std::uint32_t[n];
	std::iota(a, a+n, 0);

	block_swap(a, n, pows[0]);

	for(int i = 0 ;i < n; i++){
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

}

