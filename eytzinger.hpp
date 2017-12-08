#include <iostream>
#include <algorithm>

//shuffle primes
std::uint64_t sprimes[] = {2U, 4U, 10U, 12U, 18U, 28U, 36U, 52U, 66U, 82U, 106U, 138U, 172U, 226U, 292U, 372U, 466U, 586U, 756U, 946U, 1186U, 1482U, 1860U, 2332U, 2938U, 3676U, 4602U, 5778U, 7228U, 9058U, 11436U, 14340U, 17938U, 22468U, 28098U, 35140U, 43932U, 54916U, 68658U, 85828U, 107308U, 134212U, 167770U, 209716U, 262146U, 327706U, 409690U, 512146U, 640218U, 800332U, 1000428U, 1250628U, 1563292U, 1954156U, 2442778U, 3053482U, 3816876U, 4771162U, 5963980U, 7455028U, 9318810U, 11648530U, 14560690U, 18200932U, 22751236U, 28439140U, 35548938U, 44436276U, 55545388U, 69431826U, 86789788U, 108487242U, 135609090U, 169511428U, 211889322U, 264861658U, 331077100U, 413846482U, 517308106U, 646635330U, 808294258U, 1010367970U, 1262959986U, 1578699988U, 1973375050U, 2466718866U, 3083398690U, 3854248372U, 4817810466U, 6022263108U, 7527829092U, 9409786522U, 11762233276U, 14702791612U, 18378489532U, 22973111932U, 28716389956U, 35895487492U, 44869359396U, 56086699476U, 70108374388U, 87635468002U, 109544335002U, 136930418812U, 171163023556U, 213953779452U, 267442224346U, 334302780450U, 417878475612U, 522348094572U, 652935118228U, 816168897820U, 1020211122276U, 1275263902948U, 1594079878788U, 1992599848500U, 2490749810650U, 3113437263322U, 3891796579258U, 4864745724300U, 6080932155498U, 7601165194372U, 9501456493002U, 11876820616386U, 14846025770482U, 18557532213106U, 23196915266386U, 28996144083042U, 36245180103828U, 45306475129818U, 56633093912500U, 70791367390642U, 88489209238348U, 110611511547946U, 138264389435092U, 172830486793948U, 216038108492532U, 270047635616052U, 337559544520420U, 421949430650556U, 527436788313202U, 659295985391668U, 824119981739602U, 1030149977174508U, 1287687471468442U, 1609609339335562U, 2012011674169492U, 2515014592712002U, 3143768240890018U, 3929710301112762U, 4912137876391386U, 6140172345489250U, 7675215431861580U, 9594019289827018U, 11992524112283908U, 14990655140354892U, 18738318925443646U, 23422898656804578U, 29278623321005742U, 36598279151257260U, 45747848939071596U, 57184811173839588U, 71481013967299522U, 89351267459124412U, 111689084323905546U, 139611355404881950U, 174514194256102542U, 218142742820128186U, 272678428525160238U, 340848035656450306U, 426060044570562886U, 532575055713203610U, 665718819641504526U, 832148524551880686U, 1040185655689850860U, 1300232069612313576U, 1625290087015391988U, 2031612608769240016U, 2539515760961550178U, 3174394701201937726U, 3967993376502422170U, 4959991720628027716U, 6199989650785034706U, 7749987063481293456U, 9687483829351616830U, 12109354786689521098U, 15136693483361901396U};

/*--------------------------------------------
 General Utility Functions
--------------------------------------------*/

template<typename Data, typename Index>
int is_eytzinger(Data *a, Index length){
	
	for(Index i = 0; i < length; i++){

		if(2 * i + 1 >= length){ continue; }
		if(a[i] < a[2 * i + 1]){ return false; }

		if(2 * i + 2 >= length){ continue; }
		if(a[i] > a[2 * i + 2]){ return false; }	

	}

	return true;
}

/*--------------------------------------------
Algorythms to change from sorted to eytzinger in place
--------------------------------------------*/


template<typename I>
inline I outshuffle_perm3(I i, I n) {
	I out = i/2;
	I fix = (i & 1) ? 0 : n/2;
	return out+fix;
}

template<typename Data, typename Index>
void prime_outshuffle(Data *a, Index n) {
	if (n <= 1) return;

	// Compute appropriate value of m
	int i = 0;
	while (sprimes[i+1] <= n) i++;
	Index m = sprimes[i];

	// Follow the cycle through a[0,...,m-1];
	Index cur = 0;
	Data t[2];
	int flipflop = 0;
	t[flipflop] = a[cur];
	do {
		Index nxt = outshuffle_perm3(cur, m);
		t[!flipflop] = a[nxt];
		a[nxt] = t[flipflop];
		flipflop = !flipflop;
		cur = nxt;
	} while (cur != 0);

	// Recurse on a[m,...n-1]
	prime_outshuffle(a+m, n-m);

	// Regroup odds and evens
	std::rotate(a+m/2, a+m, a+m+(n-m)/2);
}

template<unsigned R, typename Data, typename Index>
void prime_outshuffle_pf(Data *a, Index n) {
	if (n <= 1) return;

	// Compute appropriate value of m
	int i = 0;
	while (sprimes[i+1] <= n) i++;
	Index m = sprimes[i];

	Index cur = 0;
	Index pf = cur;
	for (unsigned i = 0; i < R; i++)
		__builtin_prefetch(a+(pf = outshuffle_perm3(pf, m)), 1);
	Data t[2];
	int flipflop = 0;
	t[flipflop] = a[cur];
	do {
		__builtin_prefetch(a+(pf = outshuffle_perm3(pf, m)), 1);
		Index nxt = outshuffle_perm3(cur, m);
		t[!flipflop] = a[nxt];
		a[nxt] = t[flipflop];
		flipflop = !flipflop;
		cur = nxt;
	} while (cur != 0);

	// Recurse on a[m,...n-1]
	prime_outshuffle(a+m, n-m);

	// Regroup odds and evens
	std::rotate(a+m/2, a+m, a+m+(n-m)/2);
}

template<typename Data>
void rev_outshuffle192(Data *a) {

	const static int A = 2, B = 95;
	const static std::uint32_t cycles[A][B] = {
		{1, 96, 48, 24, 12, 6, 3, 97, 144, 72, 36, 18, 9, 100, 50, 25, 108, 54, 27, 109, 150, 75, 133, 162, 81, 136, 68, 34, 17, 104, 52, 26, 13, 102, 51, 121, 156, 78, 39, 115, 153, 172, 86, 43, 117, 154, 77, 134, 67, 129, 160, 80, 40, 20, 10, 5, 98, 49, 120, 60, 30, 15, 103, 147, 169, 180, 90, 45, 118, 59, 125, 158, 79, 135, 163, 177, 184, 92, 46, 23, 107, 149, 170, 85, 138, 69, 130, 65, 128, 64, 32, 16, 8, 4, 2},
		{7, 99, 145, 168, 84, 42, 21, 106, 53, 122, 61, 126, 63, 127, 159, 175, 183, 187, 189, 190, 95, 143, 167, 179, 185, 188, 94, 47, 119, 155, 173, 182, 91, 141, 166, 83, 137, 164, 82, 41, 116, 58, 29, 110, 55, 123, 157, 174, 87, 139, 165, 178, 89, 140, 70, 35, 113, 152, 76, 38, 19, 105, 148, 74, 37, 114, 57, 124, 62, 31, 111, 151, 171, 181, 186, 93, 142, 71, 131, 161, 176, 88, 44, 22, 11, 101, 146, 73, 132, 66, 33, 112, 56, 28, 14}
	};

	for (int i = 0; i < A; i++) {
		Data t1 = a[cycles[i][B-1]];
		for (int j = 0; j < B; j++) {
			Data t2 = a[cycles[i][j]];
			a[cycles[i][j]] = t1;
			t1 = t2;
		}
	}
}

template<unsigned B = 96, bool prefetch=false, typename Data, typename Index>
void blocked_outshuffle(Data *a, Index n) {
	Index r = n % (2*B);
	Index m = n - r;

	prime_outshuffle(a+m, r);

	for(Index i = 0; i < m/(2*B); i++) {
		static_assert(B==96, "Assuming B==96");

		rev_outshuffle192(a+(2*B)*i);

	}

	struct block { Data dummy[B];	};
	if (prefetch) {
		prime_outshuffle_pf<4>((block*)a, m/B);
	} else {
		prime_outshuffle((block*)a, m/B);
	}

	// Regroup odds and evens
	std::rotate(a+m/2, a+m, a+m+r/2);
}

template<typename Data, typename Index>
void to_eyzinger(Data *a, Index n) {

	const unsigned BLOCK=96;

	int i = 0;
	if (((n + 1) & n) != 0){
		i |= 1 << (32 - __builtin_clz(n) - 1);
		i = n - (i - 1);

		blocked_outshuffle<BLOCK>(a, i * 2);

		std::rotate(a, a + i, a + i * 2);
		std::rotate(a, a + i, a + n);
	}

	int todo = n - i;

	while(todo > 1){
		blocked_outshuffle<BLOCK>(a, todo);
		todo = todo / 2;
	}

}

/*--------------------------------------------
Algorythms to change from sorted to eytzinger in place
--------------------------------------------*/

template<typename I>
inline I inshuffle_perm3(I i, I n) {
	I out = 2*i + 1;
	I fix = (i < n/2) ? 0 : n+1;
	return out-fix;
}

template<typename Data, typename Index>
void prime_inshuffle(Data *a, Index n) {
	while (n > 1) {
		// Compute appropriate value of m
		int i = 0;
		while (sprimes[i+1] <= n) i++;
		Index m = sprimes[i];

		// Move correct m elements to front of the array
		std::rotate(a+m/2, a+n/2, a+n/2+m/2);

		// Now use Jain's trick to shuffle a[0,...,m-1];
		Index cur = 0;
		Data t = a[cur];
		do {
			Index nxt = inshuffle_perm3(cur, m);
			Data t2 = a[nxt];
			a[nxt] = t;
			t = t2;
			cur = nxt;
		} while (cur != 0);

		// Recurse on a[m,...n-1]
		a += m;
		n -= m;
	}
}

// implemented an inshuffle on 146 items
template<typename Data>
void inshuffle146(Data* a){

	const int A = 292;
	int cycle[A] = {146, 219, 109, 54, 173, 86, 189, 94, 193, 96, 194, 243, 121, 60, 176, 234, 263, 131, 65, 32, 162, 227, 113, 56, 174, 233, 116, 204, 248, 270, 281, 140, 216, 254, 273, 136, 214, 253, 126, 209, 104, 198, 245, 122, 207, 103, 51, 25, 12, 152, 222, 257, 128, 210, 251, 125, 62, 177, 88, 190, 241, 120, 206, 249, 124, 208, 250, 271, 135, 67, 33, 16, 154, 223, 111, 55, 27, 13, 6, 149, 74, 183, 91, 45, 22, 157, 78, 185, 92, 192, 242, 267, 133, 66, 179, 89, 44, 168, 230, 261, 130, 211, 105, 52, 172, 232, 262, 277, 138, 215, 107, 53, 26, 159, 79, 39, 19, 9, 4, 148, 220, 256, 274, 283, 141, 70, 181, 90, 191, 95, 47, 23, 11, 5, 2, 147, 73, 36, 164, 228, 260, 276, 284, 288, 290, 291, 145, 72, 182, 237, 118, 205, 102, 197, 98, 195, 97, 48, 170, 231, 115, 57, 28, 160, 226, 259, 129, 64, 178, 235, 117, 58, 175, 87, 43, 21, 10, 151, 75, 37, 18, 155, 77, 38, 165, 82, 187, 93, 46, 169, 84, 188, 240, 266, 279, 139, 69, 34, 163, 81, 40, 166, 229, 114, 203, 101, 50, 171, 85, 42, 167, 83, 41, 20, 156, 224, 258, 275, 137, 68, 180, 236, 264, 278, 285, 142, 217, 108, 200, 246, 269, 134, 213, 106, 199, 99, 49, 24, 158, 225, 112, 202, 247, 123, 61, 30, 161, 80, 186, 239, 119, 59, 29, 14, 153, 76, 184, 238, 265, 132, 212, 252, 272, 282, 287, 143, 71, 35, 17, 8, 150, 221, 110, 201, 100, 196, 244, 268, 280, 286, 289, 144, 218, 255, 127, 63, 31, 15, 7, 3, 1, 0};

	Data t1 = a[cycle[0]];
	for(int i = A - 1; i >= 0; i--){
		Data t2 = a[cycle[i]];
		a[cycle[i]] = t1;
		t1 = t2;
	}

}

template<unsigned B = 146, typename Data, typename Index>
void blocked_inshuffle(Data *a, Index n) {

	if (n <= 1) { return; }

	Index r = n % (2*B);
	Index m = n - r;

	// r items cant be shuffled using inshuffle18
	// m items can

	if(m > 0){
		std::rotate(a + m / 2, a + m / 2 + r / 2, a + m + r / 2);

		struct block { Data dummy[B];	};
		prime_inshuffle(((block*)a) + 1, m/B - 1);

		for(int i = 0; i < m/(2*B); i++) {
			inshuffle146(a+(2*B)*i);
		}
	}

	prime_inshuffle(a + m, r);
	
}

template<typename Data, typename Index>
void to_sorted(Data* a, Index n){

	if (n <= 1) { return; }

	int i = 0;
	if (((n + 1) & n) != 0){
		i |= 1 << (32 - __builtin_clz(n) - 1);
		i = n - (i - 1);
	}

	for(int j = 2; j - 1 <= n - i; j *= 2){
		blocked_inshuffle(a, j - 1);
	}

	std::rotate(a, a + n - i, a + n);

	blocked_inshuffle(a + 1, i * 2 - 1);

}


/*--------------------------------------------
Eytzinger class for traversal and searching
--------------------------------------------*/

template <class Data, typename Index>
class Eytzinger {

	Data *arr;
	Index n;

public:

	class Iterator{

	public:

		Iterator(Index *p, Eytzinger *d) : pos(p), data(d) {};
		Iterator(Iterator* src) : data(src->data) { pos = new Index(*src->pos); };
		~Iterator() { delete pos; }

		Iterator& operator++() {*pos = data->next(*pos); return *this; }
		Iterator operator++(int) {Iterator temp(this); *pos = data->next(*pos); return temp; }

		bool operator==(const Iterator& other){ return *pos == *other.pos; }
		bool operator!=(const Iterator& other){ return *pos != *other.pos; }

		Data& operator*() { return data->arr[*pos]; }

	protected:
		Index *pos;
		Eytzinger *data;

	};

	class IteratorReverse{

	public:

		IteratorReverse(Index *p, Eytzinger *d) : pos(p), data(d) {};
		IteratorReverse(IteratorReverse* src) : data(src->data) { pos = new Index(*src->pos); };
		~IteratorReverse() { delete pos; }

		IteratorReverse& operator++() {*pos = data->prev(*pos); return *this; }
		IteratorReverse operator++(int) {IteratorReverse temp(this); *pos = data->prev(*pos); return temp; }

		bool operator==(const IteratorReverse& other){ return *pos == *other.pos; }
		bool operator!=(const IteratorReverse& other){ return *pos != *other.pos; }

		Data& operator*() { return data->arr[*pos]; }

	protected:
		Index *pos;
		Eytzinger *data;

	};

	Iterator begin()
	{
    	Index* first = new Index((1 << (32 - __builtin_clz(n) - 1)) - 1);
        return Iterator(first, this);
    }

    Iterator end()
    {
    	Index* last = new Index(-1);
        return Iterator(last, this);
    }

   	IteratorReverse rbegin()
    {
    	Index* first = new Index(~(~0 << (32 - __builtin_clz(n + 1) - 1)) - 1);
        return IteratorReverse(first, this);
    }

    IteratorReverse rend()
    {
    	Index* last = new Index(-1);
        return IteratorReverse(last, this);
    }

	Eytzinger (Data *arr, Index n);
	Index search(Data element);
	Index upper_bound(Data element);
	Index next(Index i);
	Index prev(Index i);
};

template<class Data, typename Index>
Eytzinger<Data, Index>::Eytzinger(Data *arr, Index n) {
    if (!is_eytzinger(arr, n))
        throw std::invalid_argument("'Data* arr' of size 'n' given to Eytzinger<Data, Index>::Eytzinger(Data* arr, Index n) not of the form: Eytzinger.");
	this->arr = arr; 
	this->n = n;
}

// Implemented branchy_search straight from Eytzinger paper
template<class Data, typename Index>
Index Eytzinger<Data, Index>::search(Data element) {

	int i = 0;
	
	while (i < n){
		i = ( element <= arr[i]) ? (2 * i + 1) : (2 * i + 2);
	}

	Index j = (i + 1) >> __builtin_ffs(~(i + 1));
	return arr[j - 1] == element ? j - 1 : n;

}

// Implemented branchy_search straight from Eytzinger paper
template<class Data, typename Index>
Index Eytzinger<Data, Index>::upper_bound(Data element) {

	int i = 0;
	
	while (i < n){
		i = (element <= arr[i]) ? (2 * i + 1) : (2 * i + 2);
	}

	Index j = (i + 1) >> __builtin_ffs(~(i + 1));

	return (j == 0) ? n : j - 1;
}

// Returns the index of the item successing they eyztinger layed-out array element arr[i], with |arr| = n
template<class Data, typename Index>
Index Eytzinger<Data, Index>::next(Index i){

	if (2 * i + 2 > n - 1){
		int j = (i + 1) >> __builtin_ffs(~(i + 1));
		return j - 1;
	}else{
		int iDepth = 32 - __builtin_clz(i + 1);
		int treeDepth = 32 - __builtin_clz(n);
		int j = (((i + 1) << 1) + 1) << (treeDepth - iDepth - 1);
		return (j - 1) > (n - 1) ? (j - 1) >> 1 : (j - 1);
	}

}

template<class Data, typename Index>
Index Eytzinger<Data, Index>::prev(Index i){

	if (2 * i + 1 > n - 1){
		int j = (i + 1) >> __builtin_ffs(i + 1);
		return j - 1;
	}else{
		int iDepth = 32 - __builtin_clz(i + 1);
		int treeDepth = 32 - __builtin_clz(n);
		int j = ~(~((i + 1) << 1) << (treeDepth - iDepth - 1));
		return (j - 1) > (n - 1) ? ((j-1) >> 1) - 1 : j - 1;	
	}

}


/*----------------------------------------------------
Everything below here is dealing with in place algorithms
to move from sorted order to eytzinger order, and vise-versa. 
None of hese are not used in the implementation for to_eytzinger 
and to_sorted as they are currently lacking in preformance.
----------------------------------------------------*/

/*--------------------------------------------
Using Jain's trick for shuffles
--------------------------------------------*/

template<typename Data, typename Index>
void jain_inshuffle(Data *a, Index n) {
	while (n > 1) {
		// Compute appropriate value of m
		Index m = 1;
		while (3*m-1 <= n) m *= 3;
		m -= 1;

		// Move correct m elements to front of the array
		std::rotate(a+m/2, a+n/2, a+n/2+m/2);

		// Now use Jain's trick to shuffle a[0,...,m-1];
		for (Index g = 1; g < m; g *= 3) {
			Index cur = g-1;
			Data t = a[cur];
			do {
				Index nxt = inshuffle_perm3(cur, m);
				Data t2 = a[nxt];
				a[nxt] = t;
				t = t2;
				cur = nxt;
			} while (cur != g-1);
		}

		// Recurse on a[m,...n-1]
		a += m;
		n -= m;
	}
}

template<typename Data, typename Index>
void jain_outshuffle(Data *a, Index n) {


	if (n <= 1) return;
	// Compute appropriate value of m
	Index m = 1;
	while (3*m-1 <= n) m *= 3;
	m -= 1;

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

template<typename Data, typename Index>
int to_eyzinger_jain(Data *a, Index n) {

	int i = 0;
	if (((n + 1) & n) != 0){
	
		i |= 1 << (32 - __builtin_clz(n) - 1);
		i = n - (i - 1);

		jain_outshuffle(a, i * 2);

		std::rotate(a, a + i, a + i * 2);
		std::rotate(a, a + i, a + n);

	}

	int todo = n - i;

	while(todo > 1){
		jain_outshuffle(a, todo);
		todo = todo / 2;
	}

}

/*--------------------------------------------
Using rotate to block
--------------------------------------------*/

template<typename Data, typename Index>
void blockto_1024(Data *a, Index n){

	struct block1 { Data dummy[1]; };
	struct block2 { Data dummy[2]; };
	struct block4 { Data dummy[4]; };
	struct block8 { Data dummy[8]; };
	struct block16 { Data dummy[16]; };
	struct block32 { Data dummy[32]; };
	struct block64 { Data dummy[64]; };
	struct block128 { Data dummy[128]; };
	struct block256 { Data dummy[256]; };
	struct block512 { Data dummy[512]; };

	block1* b1 = (block1*) a;

	for(int i = 1; i < n / 1 - 1; i += 4){
		std::rotate(b1 + i, b1 + i + 1, b1 + i + 2);
	}

	block2* b2 = (block2*) a;

	for(int i = 1; i < n / 2 - 1; i += 4){
		std::rotate(b2 + i, b2 + i + 1, b2 + i + 2);
	}

	block4* b4 = (block4*) a;

	for(int i = 1; i < n / 4 - 1; i += 4){
		std::rotate(b4 + i, b4 + i + 1, b4 + i + 2);
	}	

	block8* b8 = (block8*) a;

	for(int i = 1; i < n / 8 - 1; i += 4){
		std::rotate(b8 + i, b8 + i + 1, b8 + i + 2);
	}

	block16* b16 = (block16*) a;

	for(int i = 1; i < n / 16 - 1; i += 4){
		std::rotate(b16 + i, b16 + i + 1, b16 + i + 2);
	}


	block32* b32 = (block32*) a;

	for(int i = 1; i < n / 32 - 1; i += 4){
		std::rotate(b32 + i, b32 + i + 1, b32 + i + 2);
	}

	block64* b64 = (block64*) a;

	for(int i = 1; i < n / 64 - 1; i += 4){
		std::rotate(b64 + i, b64 + i + 1, b64 + i + 2);
	}

	block128* b128 = (block128*) a;

	for(int i = 1; i < n / 128 - 1; i += 4){
		std::rotate(b128 + i, b128 + i + 1, b128 + i + 2);
	}

	block256* b256 = (block256*) a;

	for(int i = 1; i < n / 256 - 1; i += 4){
		std::rotate(b256 + i, b256 + i + 1, b256 + i + 2);
	}

	block512* b512 = (block512*) a;

	for(int i = 1; i < n / 512 - 1; i += 4){
		std::rotate(b512 + i, b512 + i + 1, b512 + i + 2);
	}

}

template<unsigned B=1024, bool prefetch=false, typename Data, typename Index>
void blocked_outshuffle_rotate(Data *a, Index n) {

	Index r = n % (2*B);
	Index m = n - r;

	prime_outshuffle(a+m, r);

	blockto_1024(a, m);

	struct block { Data dummy[B]; };
	prime_outshuffle((block*)a, m/B);

	// Regroup odds and evens
	std::rotate(a+m/2, a+m, a+m+r/2);
}



template<typename Data, typename Index>
int to_eyzinger_blocked_rotate(Data *a, Index n) {


	int i = 0;
	if (((n + 1) & n) != 0){
		i |= 1 << (32 - __builtin_clz(n) - 1);
		i = n - (i - 1);

		blocked_outshuffle_rotate(a, i * 2);

		std::rotate(a, a + i, a + i * 2);
		std::rotate(a, a + i, a + n);
	}

	int todo = n - i;

	while(todo > 1){
		blocked_outshuffle_rotate(a, todo);
		todo = todo / 2;
	}

}

/*--------------------------------------------
Using std::rotate as a building block for outshuffle
--------------------------------------------*/

template<typename Data, typename Index>
void outshuffle(Data *a, Index n) {

	if (n <= 1) return;

	if (n <= 3){
		std::rotate(a, a + 1, a + 2);
		return;
	}

	int last = n;
	int every = 4;

	for(int i = 1; i < n / 2; i *= 2){
		for(int j = i; j < n; j += every){
			std::rotate(a + j, a + j + i, a + j + i * 2);
		}
		every *= 2;
	}

	std::rotate(a, a + n / 2 + 1, a + n);

}

//This is O(N**2), as opposed to its linear counterpart preshuffle_2
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

template<typename Data, typename Index>
int preshuffle_2(Data *a, Index n) { 

	// No need to preshufle
	if (((n + 1) & n) == 0) return n;

	// we need to preshuffle i items, without messing up [last + 1..n-1]
	int i = 0;
	i |= 1 << (32 - __builtin_clz(n) - 1);
	i = n - (i - 1);
	int last = 2 * i - 1;

	int every = 4;

	for(int k = 1; k < i; k *= 2){
		for(int j = k; j + k < i * 2 ; j += every){
			int edge = j + k * 2;
			if(edge > last){
				edge = last;
				last = last - k;
			}
			std::rotate(a + j, a + j + k, a + edge);
		}
		every *= 2;
	}

	std::rotate(a, a + i, a + n);

	return n - i;
}

// Initial results showing this yeilds minimal improvment over preshuffle_2
// This is currently not working... ***
template<typename Data, typename Index>
int preshuffle_3(Data *a, Index n) {

	// No need to preshufle
	if (((n + 1) & n) == 0) return n;

	int i = 0;
	i |= 1 << (32 - __builtin_clz(n) - 1);
	i = n - (i - 1);

	int every = 4;
	for(int k = 1 ; k < i ; k *= 2){
		for(int j = k; j + k < i * 2 ; j += every){
			std::rotate(a + j, a + j + k, a + j + k * 2);
		}
		every *= 2;
	}

	std::rotate(a, a + i, a + n);

	// *** need to regroup l items, no clue how yet...
	// accounted for in preshuffle_2 but with an if statment in the nested for loop
	int l = 0;
	l |= 1 << (32 - __builtin_clz(i));
	l -= i;

	return n - i;
}

template<typename Data, typename Index>
int to_eyzinger_rotate(Data *a, Index n) {

	int todo = preshuffle_2(a, n);

	while(todo > 1){
		outshuffle(a, todo);
		todo = todo / 2;
	}
}

template<typename Data, typename Index>
void rev_outshuffle(Data *a, Index n) {

	if (n <= 1) return;

	if (n <= 3){
		std::rotate(a, a + 1, a + 2);		
		return;
	}

	std::rotate(a, a + n / 2 , a + n);

	int i = pow(2, 32 - __builtin_clz(n) - 2); 

	while(i > 0){
		for(int j = i; j < n; j += i * 4){
			std::rotate(a + j, a + j + i, a + j + i * 2);
		}
		i = i / 2;
	}

}

template<typename Data, typename Index>
int postshuffle(Data *a, Index n) {

	// No need to postshufle
	if (((n + 1) & n) == 0) return n;

	int i = 0;
	i |= 1 << (32 - __builtin_clz(n) - 1);
	i = n - (i - 1);

	std::rotate(a, a + n - i, a + n);

	for(int j = i - 1; j > 0; j --){
		std::rotate(a + j, a + j + 1, a + j * 2 + 1);
	}

}

