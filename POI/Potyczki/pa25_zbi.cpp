#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

struct point {
	pi a[5];
	point() {}
	point(int x, int y) {
		a[0] = pi{(x - y) >> 1, x + y};
		a[1] = pi{(x - y + 1) >> 1, x + y};
		a[2] = pi{(x + y) >> 1, x - y};
		a[3] = pi{(x + y + 1) >> 1, x - y};
		a[4] = pi{x, y};
	}
};

const int MAXT = 155557;
struct bit {
	int tree[MAXT];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXT; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit[4];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k, q;
	cin >> n >> m >> k >> q;
	vector<point> P(k), U(q);
	vector<pi> crd[4];
	for (auto &x : P) {
		int p, q;
		cin >> p >> q;
		x = point(p, q);
		for (int i = 0; i < 4; i++)
			crd[i].push_back(x.a[i]);
	}
	for (auto &x : U) {
		int p, q;
		cin >> p >> q;
		x = point(p, q);
		for (int i = 0; i < 4; i++)
			crd[i].push_back(x.a[i]);
	}
	for (int i = 0; i < 4; i++) {
		sort(all(crd[i]));
		crd[i].resize(unique(all(crd[i])) - crd[i].begin());
	}
	set<pi> S[4], T[4];
	set<pi> s;
	map<pi, int> t;
	int ans = 0;
	auto query = [&]() { return sz(s) - ans; };
	auto compIf = [&](int i, pi l, pi r) {
		if (l[0] != r[0])
			return 0;
		int lp = lower_bound(all(crd[i]), pi{l[0], l[1] + 1}) - crd[i].begin();
		int rp = lower_bound(all(crd[i]), r) - crd[i].begin();
		if (bit[i].query(rp) - bit[i].query(lp) != r[1] - l[1] - 1)
			return 0;
		return (int)(r[1] - l[1] - 1);
	};
	auto setActive = [&](pi pin, int dx) {
		point p(pin[0], pin[1]);
		bool prv = (t[pin] > 0);
		t[pin] += dx;
		bool cur = (t[pin] > 0);
		if (t[pin] == 0)
			t.erase(pin);
		if (prv == cur)
			return;
		if (cur) {
			ans++;
			for (int i = 0; i < 4; i++) {
				auto it = T[i].lower_bound(p.a[i]);
				if (it != T[i].begin() && it != T[i].end())
					ans -= compIf(i, *prev(it), *it);
				if (it != T[i].end())
					ans += compIf(i, p.a[i], *it);
				if (it != T[i].begin())
					ans += compIf(i, *prev(it), p.a[i]);
				T[i].insert(p.a[i]);
			}
		} else {
			ans--;
			for (int i = 0; i < 4; i++) {
				T[i].erase(p.a[i]);
				auto it = T[i].lower_bound(p.a[i]);
				if (it != T[i].begin() && it != T[i].end())
					ans += compIf(i, *prev(it), *it);
				if (it != T[i].end())
					ans -= compIf(i, p.a[i], *it);
				if (it != T[i].begin())
					ans -= compIf(i, *prev(it), p.a[i]);
			}
		}
	};
	auto ins = [&](point p) {
		s.insert(p.a[4]);
		for (int i = 0; i < 4; i++) {
			auto it = T[i].lower_bound(p.a[i]);
			S[i].insert(p.a[i]);
			auto pp = lower_bound(all(crd[i]), p.a[i]) - crd[i].begin();
			bit[i].add(pp + 1, +1);
			if (it != T[i].begin() && it != T[i].end())
				ans += compIf(i, *prev(it), *it);
		}
		bool cont[3][3] = {};
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if (s.count(pi{p.a[4][0] + x, p.a[4][1] + y})) {
					cont[x + 1][y + 1] = 1;
				}
			}
		}
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				if (cont[x][y] && cont[x][y + 1] && cont[x + 1][y] && cont[x + 1][y + 1]) {
					for (int k = 0; k < 2; k++) {
						for (int l = 0; l < 2; l++) {
							setActive({p.a[4][0] + x + k - 1, p.a[4][1] + y + l - 1}, +1);
						}
					}
				}
			}
		}
	};
	auto del = [&](point p) {
		bool cont[3][3] = {};
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if (s.count(pi{p.a[4][0] + x, p.a[4][1] + y})) {
					cont[x + 1][y + 1] = 1;
				}
			}
		}
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				if (cont[x][y] && cont[x][y + 1] && cont[x + 1][y] && cont[x + 1][y + 1]) {
					for (int k = 0; k < 2; k++) {
						for (int l = 0; l < 2; l++) {
							setActive({p.a[4][0] + x + k - 1, p.a[4][1] + y + l - 1}, -1);
						}
					}
				}
			}
		}
		s.erase(p.a[4]);
		for (int i = 0; i < 4; i++) {
			auto it = T[i].lower_bound(p.a[i]);
			if (it != T[i].begin() && it != T[i].end())
				ans -= compIf(i, *prev(it), *it);
			S[i].erase(p.a[i]);
			auto pp = lower_bound(all(crd[i]), p.a[i]) - crd[i].begin();
			bit[i].add(pp + 1, -1);
		}
	};
	for (auto &x : P) {
		ins(x);
	}
	cout << query() << "\n";
	for (auto &x : U) {
		if (s.count(x.a[4]))
			del(x);
		else
			ins(x);
		cout << query() << "\n";
	}
}