#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXN = 605;
const int mod = 1e9 + 7;
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
	friend mint inv(const mint &a) {
		assert(a.val);
		return ipow(a, mod - 2);
	}
	mint &operator/=(const mint &m) { return (*this) *= inv(m); }

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
	cout.precision(69);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	{
		auto v = a;
		sort(all(v));
		for (auto &x : a)
			x = lower_bound(all(v), x) - v.begin();
	}
	if (is_sorted(all(a))) {
		cout << "0\n";
		return 0;
	}
	vector<vector<int>> seqs;
	while (true) {
		vector<int> vis(n);
		vector<vector<int>> cycles;
		bool notnow = 0;
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				vector<int> cyc;
				for (int j = i; !vis[j]; j = a[j]) {
					vis[j] = 1;
					cyc.push_back(j);
				}
				if (sz(cyc) >= 2)
					cycles.push_back(cyc);
				if (sz(cyc) >= 3)
					notnow = 1;
			}
		}
		vector<int> L, R;
		for (auto &x : cycles) {
			for (int j = 0; j < sz(x) / 2; j++) {
				L.push_back(x[j]);
				R.push_back(x[2 * (sz(x) / 2) - 1 - j]);
			}
		}
		vector<int> seq;
		reverse(all(R));
		for (auto &x : L)
			seq.push_back(x);
		for (auto &x : R)
			seq.push_back(x);

		for (int i = 0; i < sz(seq) / 2; i++) {
			swap(a[seq[i]], a[seq[sz(seq) - 1 - i]]);
		}
		seqs.push_back(seq);
		if (!notnow) {
			assert(is_sorted(all(a)));
			cout << sz(seqs) << "\n";
			for (auto &x : seqs) {
				cout << sz(x) << "\n";
				for (auto &z : x)
					cout << z + 1 << " ";
				cout << "\n";
			}
			break;
		}
	}
}