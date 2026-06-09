#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

// Fast (prime) mod inverse.
// Usage: Call fast_inv<998244353>::inv(x).
// Credit: https://qoj.ac/submission/1202471
constexpr bool is_prime_constexpr(int n) {
	if (n == 998244353 || n == 1000000007)
		return true;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}

template <int mod> struct fast_inv {
  private:
	static_assert(2 * (1 << 20) < mod && mod < (1 << 30));
	static_assert(is_prime_constexpr(mod));
	static vector<pair<uint16_t, uint16_t>> frac;
	static vector<uint32_t> small_inv;

  public:
	static inline int inv(unsigned x) {
		auto [a, b] = frac[x >> 10];
		return (long long)small_inv[2 * (1 << 20) + x * b - a * mod] * b % mod;
	}
};

template <int mod>
vector<pair<uint16_t, uint16_t>> fast_inv<mod>::frac = []() {
	vector<pair<uint16_t, uint16_t>> res(1 << 20);
	array<tuple<int, int, int, int>, 2048> st;
	int p = 0;
	st[p++] = {0, 1, 1, 1};
	while (p) {
		auto [a, b, c, d] = st[--p];
		if (b + d < 2048) {
			st[p++] = {a + c, b + d, c, d};
			st[p++] = {a, b, a + c, b + d};
		} else {
			int s = (long long)a * mod / (1024 * b);
			int t = (long long)c * mod / (1024 * d);
			res[s] = {a, b};
			res[t] = {c, d};
			if (a > c)
				a = c;
			if (b > d)
				b = d;
			for (int i = s + 1; i < t; i++)
				res[i] = {a, b};
		}
	}
	return res;
}();

template <int mod>
vector<uint32_t> fast_inv<mod>::small_inv = []() {
	vector<uint32_t> res(4 * (1 << 20) + 1);
	res[2 * (1 << 20) + 1] = 1;
	res[2 * (1 << 20) - 1] = mod - 1;
	for (int i = 2; i <= 2 * (1 << 20); i++) {
		uint32_t x = (long long)(mod - res[2 * (1 << 20) + (mod % i)]) * (mod / i) % mod;
		res[2 * (1 << 20) + i] = x;
		res[2 * (1 << 20) - i] = mod - x;
	}
	return res;
}();

void init(int p) {}
int inv(int x) { return fast_inv<998244353>::inv(x); }
