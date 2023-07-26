#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
int mod;

inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
	unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
	asm("divl %4; \n\t" : "=a"(d), "=d"(m) : "d"(xh), "a"(xl), "r"(y));
#else
	__asm {
		mov edx, dword ptr[xh];
		mov eax, dword ptr[xl];
		div dword ptr[y];
		mov dword ptr[d], eax;
		mov dword ptr[m], edx;
	}
	;
#endif
	out_d = d;
	out_m = m;
}
// x < 2^32 * MOD !
inline unsigned Mod(unsigned long long x) {
	unsigned y = mod;
	unsigned dummy, r;
	fasterLLDivMod(x, y, dummy, r);
	return r;
}

struct mint {
	int val;
	mint() { val = 0; }
	mint(const lint &v) {
		val = (-mod <= v && v < mod) ? v : v % mod;
		if (val < 0)
			val += mod;
	}

	friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
	friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint &operator+=(const mint &m) {
		if ((val += m.val) >= mod)
			val -= mod;
		return *this;
	}
	mint &operator-=(const mint &m) {
		if ((val -= m.val) < 0)
			val += mod;
		return *this;
	}
	mint &operator*=(const mint &m) {
		val = Mod((lint)val * m.val);
		return *this;
	}
	friend mint ipow(mint a, lint p) {
		mint ans = 1;
		for (; p; p /= 2, a *= a)
			if (p & 1)
				ans *= a;
		return ans;
	}
	mint inv() const { return ipow(*this, mod - 2); }
	mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n >> mod;
	vector<array<mint, 2>> dp(n + 3);
	dp[1][1] = 1;
	dp[2][0] = 1;
	vector<mint> fact(2 * n + 2), invf(2 * n + 2);
	fact[0] = invf[0] = 1;
	for (int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i - 1] * mint(i);
		invf[i] = mint(1) / fact[i];
	}
	for (int i = 0; i <= n; i++) {
		if (dp[i][0].val) {
			mint fac = dp[i][0];
			for (int j = 0; i + j + 2 <= n + 2; j++) {
				dp[i + j + 2][0] += fac * mint(j + 2) * mint(j + 1);
				dp[i + j + 1][1] += fac * mint(j + 1);
				fac *= 2 * i - 2 + j;
			}
		}
		if (dp[i][1].val) {
			mint fac = dp[i][1];
			for (int j = 0; i + j + 2 <= n + 2; j++) {
				dp[i + j + 2][0] += fac * mint(j + 1);
				dp[i + j + 1][1] += fac;
				fac *= 2 * i - 1 + j;
			}
		}
	}
	mint ans = dp[n + 1][1];
	{
		mint tot = 1;
		for (int i = 1; i <= n; i++)
			tot *= mint(2 * i - 1);
		ans = tot - ans;
	}
	cout << ans << endl;
}
