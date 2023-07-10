#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

struct jaryoguzo {
	int n, m;
	set<pi> lowPath;
	vector<set<int>> rows, cols;
	void init(int _n, int _m) {
		n = _n;
		m = _m;
		rows.resize(n);
		cols.resize(m);
		lowPath.insert({int(1e9), n});
		lowPath.insert({-1, -int(1e9)});
	}
	bool cross_path(int x, int y) {
		auto it = lowPath.upper_bound({y, -int(1e9)});
		if ((*it)[1] <= x)
			return false;
		if ((*it)[1] == x + 1)
			return true;
		if ((*prev(it))[0] == y - 1 && (*prev(it))[1] <= x + 1)
			return true;
		return false;
	}
	void insert(int x, int y) {
		auto it = lowPath.lower_bound({y, -int(1e9)});
		while (it != lowPath.end() && (*it)[0] <= y) {
			it = lowPath.erase(it);
		}
		while (it != lowPath.begin() && (*prev(it))[1] >= x) {
			it--;
			it = lowPath.erase(it);
		}
		int lo = (*prev(it))[0];
		int hi = (*it)[1];
		lowPath.insert({y, x});
		if (y + 1 < sz(cols) && x - 1 >= 0 && cols[y + 1].count(x - 1)) {
			insert(x - 1, y + 1);
			return;
		}
		if (y + 1 < sz(cols)) {
			auto it = cols[y + 1].lower_bound(x - 1);
			if (it != cols[y + 1].end() && *it < hi)
				insert(*it, y + 1);
		}
		if (x - 1 >= 0) {
			auto it = rows[x - 1].upper_bound(y);
			if (it != rows[x - 1].begin() && *prev(it) > lo && cross_path(x - 1, *prev(it)))
				insert(x - 1, *prev(it));
		}
	}
	void insert_point(int x, int y) {
		rows[x].insert(y);
		cols[y].insert(x);
	}
} ds[2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	ds[0].init(n, m);
	ds[1].init(m, n);
	lint x = 0;
	for (int i = 0; i < q; i++) {
		int r, c, z;
		cin >> r >> c >> z;
		r ^= x;
		c ^= x;
		r %= n;
		c %= m;
		bool eval0 = ds[0].cross_path(r, c);
		bool eval1 = ds[1].cross_path(c, r);
		if (eval0 && eval1) {
			x ^= z;
			cout << "TAK\n";
			continue;
		}
		cout << "NIE\n";
		if (eval0)
			ds[0].insert(r, c);
		if (eval1)
			ds[1].insert(c, r);
		ds[0].insert_point(r, c);
		ds[1].insert_point(c, r);
	}
}