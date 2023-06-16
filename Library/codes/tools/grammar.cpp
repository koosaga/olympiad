// vimrc : set nu sc ci si ai sw=4 ts=4 bs=2  mouse=a syntax on
// options : -fsanitize=address -Wfatal-errors
// Maybe want to split the code or idk

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   1. Randoms                                       //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                             2. Comparator Overloads                                //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

auto cmp = [](seg a, seg b){ return a.func() < b.func(); };
set<seg, decltype(cmp)> s(cmp);
map<seg, int, decltype(cmp)> mp(cmp);
priority_queue<seg, vector<seg>, decltype(cmp)> pq(cmp); // max heap

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                              3. Hash Map Overloads                                 //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

struct point{
	int x, y;
	bool operator==(const point &p)const{ return x == p.x && y == p.y; }
};
struct hasher {
	size_t operator()(const point &p)const{ return p.x * 2 + p.y * 3; }
};
unordered_map<point, int, hasher> hsh;

struct chash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   4. PBDS                                          //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set X;
X.insert(1); X.insert(2); X.insert(4); X.insert(8); X.insert(16);

cout<<*X.find_by_order(1)<<endl; // 2
cout<<*X.find_by_order(2)<<endl; // 4
cout<<*X.find_by_order(4)<<endl; // 16
cout<<(end(X)==X.find_by_order(6))<<endl; // true

cout<<X.order_of_key(-5)<<endl;  // 0
cout<<X.order_of_key(1)<<endl;   // 0
cout<<X.order_of_key(3)<<endl;   // 2
cout<<X.order_of_key(4)<<endl;   // 2
cout<<X.order_of_key(400)<<endl; // 5


////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                     5. GCC Bitsets and weird template hack?                        //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

bitset<17>BS;
BS[1] = BS[7] = 1;
cout<<BS._Find_first()<<endl; // prints 1

bitset<17>BS;
BS[1] = BS[7] = 1;
cout<<BS._Find_next(1)<<','<<BS._Find_next(3)<<endl; // prints 7,7

// Arbitrary sized bitset
template <int len = 1>
void solve(int n) {
    if (n > len) {
        solve<std::min(len*2, MAXLEN)>(n);
        return;
    }
    // solution using bitset<len>
}

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                   6. Stupid pragmas, and not-so-stupid AVX                         //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma")

int main() {
	for (int i = 0; i < n; i += 1024) {
		for (int j = 0; j < m; j++) {
			// Process queries offline
			// use the fact that page size is 4kb
			int l = max(s[j], i);
			int r = min(e[j] + 1, i + 1024);
			while (l < r && l % 8 != 0)
				a[l] = abs(a[l] - x[j]), l++;
			while (l < r && r % 8 != 0)
				r--, a[r] = abs(a[r] - x[j]);
			 // duplicate 8 copies of x[j], to use vectorization
			__m256i foo = _mm256_set1_epi32(x[j]);
			__m256i bar;
			for (int i = l; i < r; i += 8) {
				bar = _mm256_load_si256((__m256i *)(a + i));
				bar = _mm256_abs_epi32(_mm256_sub_epi32(bar, foo));
				_mm256_store_si256((__m256i *)(a + i), bar);
			}
		}
	}
}

struct StupidGCCCantEvenCompileThisSimpleCode{
	pair<int, int> array[1000000];
}; // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=68203
