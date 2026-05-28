#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int mod = 1e9 + 7;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// Polynomial composition is due to ecnerwala:
// https://judge.yosupo.jp/submission/336262
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

vector<vector<int>> gph;
vector<int> dfn, sz, msz;

void dfs(int x, int p = -1) {
	dfn.push_back(x);
	sz[x] = 1, msz[x] = 0;
	for (auto &y : gph[x]) {
		if (y != p) {
			dfs(y, x);
			sz[x] += sz[y];
			msz[x] = max(msz[x], sz[y]);
		}
	}
}

int get_center(int x) {
	dfn.clear();
	dfs(x);
	pi ret{int(1e9), -1};
	for (auto &x : dfn) {
		int w = max(sz(dfn) - sz[x], msz[x]);
		ret = min(ret, pi{w, x});
	}
	return ret[1];
}

pair<int, vector<int>> isomorphism(const vector<vector<int>> &g, int root) {
	const int n = g.size();
	vector<int> ids(n);
	vector<int> mp1(n, -1);
	vector<map<vector<int>, int>> mps(n);
	int next_id = 0;
	vector<int> ch_ids;
	ch_ids.reserve(n);
	auto dfs = [&](auto dfs, int u, int p) -> void {
		for (int v : g[u])
			if (v != p)
				dfs(dfs, v, u);
		for (int v : g[u])
			if (v != p)
				ch_ids.push_back(ids[v]);
		if (ch_ids.size() == 1) {
			int ch = ch_ids[0];
			ids[u] = mp1[ch] < 0 ? mp1[ch] = next_id++ : mp1[ch];
		} else {
			sort(ch_ids.begin(), ch_ids.end());
			auto [it, inserted] = mps[ch_ids.size()].try_emplace(ch_ids, next_id);
			next_id += inserted;
			ids[u] = it->second;
		}
		ch_ids.clear();
	};
	dfs(dfs, root, -1);
	return {next_id, ids};
}

mint f(int x, int p, vector<int> &q) {
	mint ans = 1;
	map<int, int> cnt;
	for (auto &y : gph[x]) {
		if (y == p)
			continue;
		ans *= f(y, x, q);
		cnt[q[y]]++;
	}
	for (auto &[k, v] : cnt) {
		for (int j = 2; j <= v; j++)
			ans *= mint(j);
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	cr(gph, n + 1);
	cr(sz, n + 1);
	cr(msz, n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	int c = get_center(0);
	dfs(c, -1);
	if (msz[c] * 2 == n) {
		for (auto &d : gph[c]) {
			if (sz[d] * 2 == n) {
				gph[n].push_back(c);
				gph[n].push_back(d);
				gph[d].erase(find(all(gph[d]), c));
				gph[d].push_back(n);
				d = n;
				break;
			}
		}
		c = n;
	}
	auto ans = isomorphism(gph, c).second;
	cout << f(c, -1, ans) << "\n";
}