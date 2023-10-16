#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

const int MAXT = 2100000;

vector<int> vect, cgrp;
int n, t;
vector<int> a, l, r, x;
multiset<pi> tree[MAXT];
vector<set<pi>> pushed;
using node = array<lint, 3>;
priority_queue<node, vector<node>, greater<node>> pq;

lint up(lint a, lint b) {
	if (a >= b)
		return a;
	lint z = (b - a + t - 1) / t;
	return a + t * z;
}

void eliminate(int color, int l, int r, lint T) {
	color = lower_bound(all(cgrp), color) - cgrp.begin();
	auto it = pushed[color].lower_bound({l, -1});
	while (it != pushed[color].end() && (*it)[0] <= r) {
		int i = (*it)[1];
		int opp = (color > 0 ? -1 : a[i]);
		opp = lower_bound(all(cgrp), opp) - cgrp.begin();
		pushed[opp].erase(*it);
		it = pushed[color].erase(it);
		pq.push({up(a[i], T), x[i], i});
	}
}

void add(int s, int e, int ps, int pe, int p, pi v) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e) {
		tree[p].insert(v);
		return;
	}
	int pm = (ps + pe) / 2;
	add(s, e, ps, pm, 2 * p, v);
	add(s, e, pm + 1, pe, 2 * p + 1, v);
}

void init(int s, int e, int p, int col = -1, int upper = 2e9) {
	if (sz(tree[p])) {
		if ((*tree[p].begin())[0] != (*tree[p].rbegin())[0]) {
			return;
		}
		auto z = *tree[p].begin();
		if (col != -1 && z[0] != col)
			return;
		col = z[0];
		upper = min(upper, z[1]);
	}
	if (s == e) {
		if (col == -1) {
			eliminate(-1, s + 1, sz(vect), -1);
		} else {
			eliminate(col, s + 1, upper, -1);
		}
		return;
	}
	int m = (s + e) / 2;
	init(s, m, 2 * p, col, upper);
	init(m + 1, e, 2 * p + 1, col, upper);
}

void recurse_down(int s, int e, int p, lint T, int col, int upper) {
	if (col == -2)
		return;
	if (sz(tree[p])) {
		if ((*tree[p].begin())[0] != (*tree[p].rbegin())[0]) {
			return;
		}
		auto z = *tree[p].begin();
		if (col != -1 && z[0] != col)
			return;
		col = z[0];
		upper = min(upper, z[1]);
	}
	if (s + 1 > upper)
		return;
	if (s == e) {
		if (col == -1) {
			eliminate(-1, s + 1, sz(vect), T);
		} else {
			eliminate(col, s + 1, upper, T);
		}
		return;
	}
	int m = (s + e) / 2;
	recurse_down(s, m, 2 * p, T, col, upper);
	recurse_down(m + 1, e, 2 * p + 1, T, col, upper);
}

void recurse_down_special(int s, int e, int p, lint T, int col, int upper, int lowupper) {
	if (lowupper > upper)
		return;
	if (col == -2)
		return;
	if (sz(tree[p])) {
		if ((*tree[p].begin())[0] != (*tree[p].rbegin())[0]) {
			return;
		}
		auto z = *tree[p].begin();
		if (col != -1 && z[0] != col)
			return;
		col = z[0];
		upper = min(upper, z[1]);
	}
	if (s + 1 > upper)
		return;
	if (s == e) {
		if (col == -1) {
			eliminate(-1, s + 1, sz(vect), T);
		} else {
			eliminate(col, s + 1, upper, T);
		}
		return;
	}
	int m = (s + e) / 2;
	recurse_down_special(s, m, 2 * p, T, col, upper, lowupper);
	recurse_down_special(m + 1, e, 2 * p + 1, T, col, upper, lowupper);
}

void remove(int s, int e, int ps, int pe, int p, pi v, lint T, int col = -1, int upper = 2e9) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e) {
		auto uniq = [&]() { return sz(tree[p]) > 0 && (*tree[p].begin())[0] == (*tree[p].rbegin())[0]; };
		bool suniq = uniq();
		tree[p].erase(tree[p].find(v));
		if (suniq && uniq()) {
			if (v[1] < (*tree[p].begin())[1]) {
				int g = lower_bound(all(cgrp), v[0]) - cgrp.begin();
				auto it = pushed[g].lower_bound({v[1] + 1, -1});
				if (it != pushed[g].end() && (*it)[1] <= (*tree[p].begin())[1]) {
					recurse_down_special(ps, pe, p, T, col, upper, (*it)[1]);
				}
				return;
			}
		}
		recurse_down(ps, pe, p, T, col, upper);
		return;
	}

	if (sz(tree[p])) {
		if ((*tree[p].begin())[0] != (*tree[p].rbegin())[0]) {
			col = -2;
		}
		auto z = *tree[p].begin();
		if (col != -1 && z[0] != col)
			col = -2;
		else if (col != -2)
			col = z[0];
		upper = min(upper, z[1]);
	}
	int pm = (ps + pe) / 2;
	remove(s, e, ps, pm, 2 * p, v, T, col, upper);
	remove(s, e, pm + 1, pe, 2 * p + 1, v, T, col, upper);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> t;
	a.resize(n);
	l.resize(n);
	r.resize(n);
	x.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> l[i] >> r[i] >> a[i];
		vect.push_back(x[i]);
		vect.push_back(l[i]);
		vect.push_back(r[i]);
		cgrp.push_back(a[i]);
	}
	cgrp.push_back(-1);
	vect.push_back(0);
	sort(all(cgrp));
	cgrp.resize(unique(all(cgrp)) - cgrp.begin());
	sort(all(vect));
	vect.resize(unique(all(vect)) - vect.begin());
	vector<lint> dap(n, -1);
	pushed.resize(sz(cgrp));
	for (int i = 0; i < n; i++) {
		x[i] = lower_bound(all(vect), x[i]) - vect.begin();
		l[i] = lower_bound(all(vect), l[i]) - vect.begin();
		r[i] = lower_bound(all(vect), r[i]) - vect.begin();
		add(l[i], r[i] - 1, 0, sz(vect) - 1, 1, pi{a[i], x[i]});
		int col = lower_bound(all(cgrp), a[i]) - cgrp.begin();
		pushed[0].insert({x[i], i});
		pushed[col].insert({x[i], i});
	}
	init(0, sz(vect) - 1, 1);
	while (sz(pq)) {
		auto [T, _, idx] = pq.top();
		pq.pop();
		dap[idx] = T;
		remove(l[idx], r[idx] - 1, 0, sz(vect) - 1, 1, pi{a[idx], x[idx]}, T);
	}
	for (int i = 0; i < n; i++)
		cout << dap[i] << "\n";
}
