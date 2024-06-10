#include "train.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 15571557;

struct event {
	int t, v, idx;
	int mode;
	bool operator<(const event &e) const {
		if (t != e.t)
			return t < e.t;
		return mode < e.mode;
	}
};

struct node {
	int l, r, sum;
} tree[MAXT];

int piv;
int newnode() { return ++piv; }

void init(int s, int e, int p) {
	if (s == e) {
		return;
	}
	int m = (s + e) / 2;
	tree[p].l = newnode();
	tree[p].r = newnode();
	init(s, m, tree[p].l);
	init(m + 1, e, tree[p].r);
}

void upd(int pos, int s, int e, int prv, int cur) {
	tree[cur].sum = tree[prv].sum + 1;
	if (s == e) {
		return;
	}
	int m = (s + e) / 2;
	if (pos <= m) {
		tree[cur].l = newnode();
		tree[cur].r = tree[prv].r;
		upd(pos, s, m, tree[prv].l, tree[cur].l);
	} else {
		tree[cur].l = tree[prv].l;
		tree[cur].r = newnode();
		upd(pos, m + 1, e, tree[prv].r, tree[cur].r);
	}
}

int query(int s, int e, int ps, int pe, int p) {
	if (e < ps || pe < s)
		return 0;
	if (s <= ps && pe <= e)
		return tree[p].sum;
	int pm = (ps + pe) / 2;
	return query(s, e, ps, pm, tree[p].l) + query(s, e, pm + 1, pe, tree[p].r);
}

long long solve(int N, int M, int W, std::vector<int> T, std::vector<int> X, std::vector<int> Y, std::vector<int> A, std::vector<int> B, std::vector<int> C, std::vector<int> L, std::vector<int> R) {
	vector<event> events;
	vector<int> v = {0};
	for (int i = 0; i < M; i++) {
		v.push_back(A[i]);
		v.push_back(B[i]);
	}
	for (int i = 0; i < W; i++) {
		v.push_back(L[i]);
		v.push_back(R[i]);
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for (int i = 0; i < M; i++) {
		A[i] = lower_bound(all(v), A[i]) - v.begin();
		B[i] = lower_bound(all(v), B[i]) - v.begin();
	}
	vector<vector<int>> nxt(sz(v));
	for (int i = 0; i < W; i++) {
		L[i] = lower_bound(all(v), L[i]) - v.begin();
		R[i] = lower_bound(all(v), R[i]) - v.begin();
		nxt[L[i]].push_back(R[i]);
	}
	vector<int> roots(sz(v) + 1);
	roots[sz(v)] = newnode();
	init(0, sz(v) - 1, roots[sz(v)]);
	for (int i = sz(v) - 1; i >= 0; i--) {
		roots[i] = roots[i + 1];
		for (auto &j : nxt[i]) {
			int nn = newnode();
			upd(j, 0, sz(v) - 1, roots[i], nn);
			roots[i] = nn;
		}
	}
	for (int i = 0; i < M; i++) {
		events.push_back({A[i], X[i], i, +1});
		events.push_back({B[i], Y[i], i, -1});
	}
	events.push_back({0, 0, M, -1});
	events.push_back({sz(v), N - 1, M + 1, +1});
	vector<lint> dp(M + 2);
	C.resize(M + 2);
	sort(all(events));
	// log N
	auto cost = [&](int l, int r) { return query(0, r - 1, 0, sz(v) - 1, roots[l + 1]); };
	auto eval = [&](pi p, int t, int v) { return 1ll * T[v] * cost(p[0], t) + p[1]; };
	// log^2 N
	auto cross = [&](pi p, pi q, int vi) {
		int s = q[0], e = sz(v) + 1;
		while (s != e) {
			int m = (s + e) / 2;
			if (eval(p, m, vi) < eval(q, m, vi))
				s = m + 1;
			else
				e = m;
		}
		return s;
	};
	vector<deque<pi>> points(N);
	for (auto &e : events) {
		if (e.mode == -1) {
			pi p = {e.t, dp[e.idx] + C[e.idx]};
			while (sz(points[e.v]) >= 2 && cross(points[e.v][sz(points[e.v]) - 2], points[e.v].back(), e.v) >= cross(points[e.v].back(), p, e.v)) {
				points[e.v].pop_back();
			}
			points[e.v].push_back(p);
		} else {
			if (sz(points[e.v]) == 0)
				dp[e.idx] = 1e18;
			else {
				while (sz(points[e.v]) >= 2 && eval(points[e.v][0], e.t, e.v) >= eval(points[e.v][1], e.t, e.v))
					points[e.v].pop_front();
				dp[e.idx] = eval(points[e.v][0], e.t, e.v);
			}
		}
	}
	if (dp[M + 1] > 1e17)
		return -1;
	return dp[M + 1];
}
