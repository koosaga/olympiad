#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int mod = 998244353;
using lint = long long;
lint ipow(lint x, lint p) {
	lint ret = 1, piv = x;
	while (p) {
		if (p & 1)
			ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
vector<int> berlekamp_massey(vector<int> x) {
	vector<int> ls, cur;
	int lf, ld;
	for (int i = 0; i < x.size(); i++) {
		lint t = 0;
		for (int j = 0; j < cur.size(); j++) {
			t = (t + 1ll * x[i - j - 1] * cur[j]) % mod;
		}
		if ((t - x[i]) % mod == 0)
			continue;
		if (cur.empty()) {
			cur.resize(i + 1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<int> c(i - lf - 1);
		c.push_back(k);
		for (auto &j : ls)
			c.push_back(-j * k % mod);
		if (c.size() < cur.size())
			c.resize(cur.size());
		for (int j = 0; j < cur.size(); j++) {
			c[j] = (c[j] + cur[j]) % mod;
		}
		if (i - lf + (int)ls.size() >= (int)cur.size()) {
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for (auto &i : cur)
		i = (i % mod + mod) % mod;
	return cur;
}
int get_nth(vector<int> rec, vector<int> dp, lint n) {
	int m = rec.size();
	vector<int> s(m), t(m);
	s[0] = 1;
	if (m != 1)
		t[1] = 1;
	else
		t[0] = rec[0];
	auto mul = [&rec](vector<int> v, vector<int> w) {
		int m = v.size();
		vector<int> t(2 * m);
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < m; k++) {
				t[j + k] += 1ll * v[j] * w[k] % mod;
				if (t[j + k] >= mod)
					t[j + k] -= mod;
			}
		}
		for (int j = 2 * m - 1; j >= m; j--) {
			for (int k = 1; k <= m; k++) {
				t[j - k] += 1ll * t[j] * rec[k - 1] % mod;
				if (t[j - k] >= mod)
					t[j - k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while (n) {
		if (n & 1)
			s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	lint ret = 0;
	for (int i = 0; i < m; i++)
		ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}
int guess_nth_term(vector<int> x, lint n) {
	if (n < x.size())
		return x[n];
	vector<int> v = berlekamp_massey(x);
	if (v.empty())
		return 0;
	return get_nth(v, x, n);
}
struct elem {
	int x, y, v;
}; // A_(x, y) <- v, 0-based. no duplicate please..
vector<int> get_min_poly(int n, vector<elem> M) {
	// smallest poly P such that A^i = sum_{j < i} {A^j \times P_j}
	vector<int> rnd1, rnd2;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub) { return uniform_int_distribution<int>(lb, ub)(rng); };
	for (int i = 0; i < n; i++) {
		rnd1.push_back(randint(1, mod - 1));
		rnd2.push_back(randint(1, mod - 1));
	}
	vector<int> gobs;
	for (int i = 0; i < 2 * n + 2; i++) {
		int tmp = 0;
		for (int j = 0; j < n; j++) {
			tmp += 1ll * rnd2[j] * rnd1[j] % mod;
			if (tmp >= mod)
				tmp -= mod;
		}
		gobs.push_back(tmp);
		vector<int> nxt(n);
		for (auto &i : M) {
			nxt[i.x] += 1ll * i.v * rnd1[i.y] % mod;
			if (nxt[i.x] >= mod)
				nxt[i.x] -= mod;
		}
		rnd1 = nxt;
	}
	auto sol = berlekamp_massey(gobs);
	reverse(sol.begin(), sol.end());
	return sol;
}
lint det(int n, vector<elem> M) {
	vector<int> rnd;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub) { return uniform_int_distribution<int>(lb, ub)(rng); };
	for (int i = 0; i < n; i++)
		rnd.push_back(randint(1, mod - 1));
	for (auto &i : M) {
		i.v = 1ll * i.v * rnd[i.y] % mod;
	}
	auto sol = get_min_poly(n, M)[0];
	if (n % 2 == 0)
		sol = mod - sol;
	for (auto &i : rnd)
		sol = 1ll * sol * ipow(i, mod - 2) % mod;
	return sol;
}
// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.

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
		val = (lint)val * m.val % mod;
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

lint n, c;

const int MAXB = 35;
mint cnt[MAXB];
mint dp[MAXB][3][3][3]; // (len, fucked with, match, last)

void go1() {
	for (int i = 0; i < MAXB; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				for (int l = 0; l < 3; l++)
					dp[i][j][k][l] = 0;

	dp[2][0][0][0] = c;
	for (int slen = 2; slen < MAXB - 2; slen++) {
		for (int fuckedWith = 0; fuckedWith <= 2; fuckedWith++) {
			for (int last = 0; last <= 2; last++) {
				cnt[slen] += dp[slen][fuckedWith][last][0];
				for (int i = '0'; i <= '2'; i++) {
					int nf = fuckedWith;
					if (!fuckedWith) {
						if (i != '0')
							nf = 1;
					} else {
						if (last == 0 && i == '0')
							continue;
					}
					dp[slen + 1][nf][i - '0'][0] += dp[slen][fuckedWith][last][0] * (i == '2' ? mint(c - 2) : mint(1));
				}
			}
		}
	}
}

void go2() {
	for (int i = 0; i < MAXB; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				for (int l = 0; l < 3; l++)
					dp[i][j][k][l] = 0;
	dp[2][0][0][1] = mint(c * (c - 1));
	for (int slen = 2; slen < MAXB - 2; slen++) {
		for (int fuckedWith = 0; fuckedWith <= 2; fuckedWith++) {
			for (int match = 0; match <= 2; match++) {
				for (int last = 0; last <= 2; last++) {
					cnt[slen] += dp[slen][fuckedWith][match][last];
					for (int i = '0'; i <= '2'; i++) {
						int nf = fuckedWith;
						int nm = 0;
						if (!fuckedWith) {
							if (i != (slen % 2 ? '1' : '0'))
								nf = (i == '0' ? 2 : 1);
							if (nf == 2)
								nm = 1;
						} else {
							if (fuckedWith == 1 && last == 0 && i == '1')
								continue;
							if (fuckedWith == 2) {
								if (i == '0') {
									if (match == 2)
										continue;
									nm = 1;
								}
								if (i == '1') {
									if (match == 1)
										nm = 2;
									else {
										nm = 0;
										nf = 1;
									}
								}
								if (i == '2') {
									nm = 0;
									nf = 1;
								}
							}
						}
						dp[slen + 1][nf][nm][i - '0'] += dp[slen][fuckedWith][match][last] * (i == '2' ? mint(c - 2) : mint(1));
					}
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> c;
	if (c == 1) {
		cout << "1\n";
		return 0;
	}
	go1();
	go2();
	cnt[0] = 1;
	cnt[1] = c;
	vector<int> dp;
	for (int i = 0; i <= MAXB - 5; i++)
		dp.push_back(cnt[i].val);
	cout << guess_nth_term(dp, n) << "\n";
}