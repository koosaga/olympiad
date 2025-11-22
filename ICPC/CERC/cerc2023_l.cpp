#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Various self-explanatory methods for string hashing.
 * Status: tested
 */
#pragma once
#define rep(i, a, b) for (int i = a; i < (b); ++i)

// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
struct H {
	typedef uint64_t ull;
	ull x;
	H(ull x = 0) : x(x) {}
#define OP(O, A, B)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    \
	H operator O(H o) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                \
		ull r = x;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
		asm(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            \
		return r;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
	}
	OP(+, , "d"(o.x)) OP(*, "mul %1\n", "r"(o.x) : "rdx") H operator-(H o) { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }
static H C = randint(1e10, 2e10) * 2 + 1;

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string &str) : ha(sz(str) + 1), pw(ha) {
		pw[0] = 1;
		rep(i, 0, sz(str)) ha[i + 1] = ha[i] * C + str[i], pw[i + 1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};
vector<vector<array<int, 3>>> gph;
vector<int> dfn, vis;
void dfs(int x) {
	if (vis[x])
		return;
	vis[x] = 1;
	for (auto &[y, _, __] : gph[x]) {
		dfs(y);
	}
	dfn.push_back(x);
}

struct edges {
	int u, v, l, r;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k, s;
	cin >> n >> m >> k >> s;
	cr(gph, n);
	cr(vis, n);
	s--;
	string str;
	cin >> str;
	auto hi = HashInterval(str);
	for (int i = 0; i < m; i++) {
		int u, v, p, l;
		cin >> u >> v >> p >> l;
		u--;
		v--;
		gph[u].push_back({v, p - 1, p - 1 + l});
	}
	auto cmp = [&](const vector<edges> &a, const vector<edges> &b) {
		int pa = 0, pb = 0, al = 0, bl = 0;
		while (true) {
			while (pa < sz(a) && al == a[pa].r - a[pa].l)
				al = 0, pa++;
			while (pb < sz(b) && bl == b[pb].r - b[pb].l)
				bl = 0, pb++;
			if (pa == sz(a) && pb == sz(b)) {
				return false;
			}
			if (pa == sz(a))
				return true;
			if (pb == sz(b))
				return false;
			int rems = min(a[pa].r - a[pa].l - al, b[pb].r - b[pb].l - bl);
			if (hi.hashInterval(al + a[pa].l, al + a[pa].l + rems) == hi.hashInterval(bl + b[pb].l, bl + b[pb].l + rems)) {
				al += rems;
				bl += rems;
			} else {
				int s = 0, e = rems - 1;
				while (s != e) {
					int m = (s + e + 1) / 2;
					if (hi.hashInterval(al + a[pa].l, al + a[pa].l + m) == hi.hashInterval(bl + b[pb].l, bl + b[pb].l + m))
						s = m;
					else
						e = m - 1;
				}
				return str[al + a[pa].l + s] < str[bl + b[pb].l + s];
			}
		}
	};
	dfs(s);
	for (int t = 0; t < n; t++) {
		if (vis[t] == 0) {
			cout << "0\n";
			continue;
		}
		if (s == t) {
			cout << "1 " << s + 1 << "\n";
			continue;
		}
		vector<int> ok(n);
		vector<vector<edges>> paths(n);
		for (auto &x : dfn) {
			if (x == t) {
				ok[x] = 1;
				continue;
			}
			for (auto &[y, l, r] : gph[x]) {
				if (ok[y] == 0)
					continue;
				if (!ok[x]) {
					ok[x] = 1;
					auto np = paths[y];
					np.insert(np.begin(), edges{x, y, l, r});
					paths[x] = np;
				} else {
					auto np = paths[y];
					np.insert(np.begin(), edges{x, y, l, r});
					paths[x] = min(paths[x], np, cmp);
				}
			}
		}
		cout << sz(paths[s]) + 1 << " " << paths[s][0].u + 1;
		for (int j = 0; j < sz(paths[s]); j++)
			cout << " " << paths[s][j].v + 1;
		cout << "\n";
	}
}