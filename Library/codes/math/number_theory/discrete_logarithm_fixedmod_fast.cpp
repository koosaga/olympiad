// Returns the smallest K >= 0 such that pow(x, K) === y modulo MOD.
// when init, g should be a primitive root of MOD.
// Credit: maroonrk https://judge.yosupo.jp/submission/353347

#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

int mod;
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

struct discrete_log {
	const int p;
	mint root;
	int s;
	vector<int> sf;
	void linear_sieve() {
		vector<int> ps;
		sf.resize(s + 1, -1);
		for (int i = 2; i <= s; i++) {
			if (sf[i] == -1) {
				ps.push_back(i);
				sf[i] = i;
			}
			for (int j = 0; i * ps[j] <= s; j++) {
				sf[i * ps[j]] = ps[j];
				if (i % ps[j] == 0)
					break;
			}
		}
	}
	int B;
	vector<mint> baby, giant;
	void init_baby_giant() {
		B = min(s * 5, p - 1);
		baby.resize(B);
		mint z = 1;
		for (int i = 0; i < B; i++) {
			baby[i] = z;
			z *= root;
		}
		int C = (p - 1 + B - 1) / B;
		giant.resize(C);
		mint w = 1;
		for (int i = 0; i < C; i++) {
			giant[i] = w;
			w *= z;
		}
	}
	mint pow_root(int e) {
		int u = e / B, v = e % B;
		return giant[u] * baby[v];
	}
	vector<int> logbuf;
	void init_small_logs() {
		unordered_map<unsigned, int> table;
		table.reserve(B);
		for (int i = 0; i < B; i++)
			table[baby[i].val] = i;
		mint bigstep = ipow(root, mod - 1 - B);
		uint32_t cap = (p - 1) / root.val;

		logbuf.resize(s + 1);
		for (int i = 2; i <= s; i++) {
			if (sf[i] < i) {
				logbuf[i] = logbuf[sf[i]] + logbuf[i / sf[i]];
				if (logbuf[i] >= (p - 1))
					logbuf[i] -= (p - 1);
			} else if (i < 100) {
				mint cur = i;
				while (1) {
					auto itr = table.find(cur.val);
					if (itr == table.end()) {
						cur *= bigstep;
						logbuf[i] += B;
					} else {
						logbuf[i] += itr->second;
						break;
					}
				}
			} else {
				int k = 0;
				mint start = i;
				while (start.val <= cap) {
					k++;
					start *= root;
				}
				while (1) {
					k++;
					start *= root;

					mint cur = start;
					lint val = p - 1 - k;
					for (int d : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) {
						while (cur.val % d == 0) {
							cur.val /= d;
							val += logbuf[d];
						}
					}
					if ((int)cur.val > s)
						continue;
					bool bad = false;
					while (i <= (int)cur.val) {
						if (sf[cur.val] == (int)cur.val) {
							bad = true;
							break;
						}
						val += logbuf[sf[cur.val]];
						cur.val /= sf[cur.val];
					}
					if (bad)
						continue;
					val += logbuf[cur.val];
					logbuf[i] = val % (p - 1);
					break;
				}
			}
		}
	}
	discrete_log(int p, int g) : p(p), s(sqrtl(p)) {
		mod = p;
		root = mint(g);

		linear_sieve();
		init_baby_giant();
		init_small_logs();
	}
	int log(mint x) {
		lint ans = 0;
		while ((int)x.val > s) {
			int a = p / x.val, b = p % x.val;
			ans += (p - 1) / 2;
			ans += (p - 1) - logbuf[a];
			x = b;
		}
		ans += logbuf[x.val];
		return ans % (p - 1);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int p, g, q;
	cin >> p >> g >> q;
	discrete_log dl(p, g);
	while (q--) {
		int x;
		cin >> x;
		cout << dl.log(mint(x)) << "\n";
	}
}