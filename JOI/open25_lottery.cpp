#include "lottery.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 1050000;
const int MAXP = 45571557;
struct seg {
	lint tree[MAXT], lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		memset(tree, 0x3f, sizeof(tree));
	}
	void upd(int x, int v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = min(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int query(int s, int e) {
		s += lim;
		e += lim;
		lint ret = 2e9;
		while (s < e) {
			if (s % 2 == 1)
				ret = min(ret, tree[s++]);
			if (e % 2 == 0)
				ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = min(ret, tree[s]);
		return ret;
	}
} seg;

struct node {
	int l, r, cnt;
	lint sum;
} tree[MAXP];
int piv;

int newnode() { return ++piv; }

void init(int s, int e, int p) {
	if (s == e)
		return;
	int m = (s + e) / 2;
	tree[p].l = newnode();
	tree[p].r = newnode();
	init(s, m, tree[p].l);
	init(m + 1, e, tree[p].r);
}

void upd(int s, int e, int p, int v, int p1, int p2) {
	if (s == e) {
		tree[p2].cnt = tree[p1].cnt + 1;
		tree[p2].sum = tree[p1].sum + v;
		return;
	}
	int m = (s + e) / 2;
	if (p <= m) {
		tree[p2].r = tree[p1].r;
		tree[p2].l = newnode();
		upd(s, m, p, v, tree[p1].l, tree[p2].l);
	} else {
		tree[p2].l = tree[p1].l;
		tree[p2].r = newnode();
		upd(m + 1, e, p, v, tree[p1].r, tree[p2].r);
	}
	tree[p2].cnt = tree[tree[p2].l].cnt + tree[tree[p2].r].cnt;
	tree[p2].sum = tree[tree[p2].l].sum + tree[tree[p2].r].sum;
}

array<lint, 3> descend(int l, int r, int p1, int p2, lint pcnt, lint psum, int n, vector<pi> &crd) {
	if (l == r)
		return array<lint, 3>{l, pcnt + tree[p2].cnt - tree[p1].cnt, psum + tree[p2].sum - tree[p1].sum};
	int m = (l + r) / 2;
	lint cnt = tree[tree[p2].l].cnt - tree[tree[p1].l].cnt + pcnt;
	lint sum = tree[tree[p2].l].sum - tree[tree[p1].l].sum + psum;
	int T = crd[m + 1][0];
	if (sum >= T * (cnt - n / 2))
		return descend(m + 1, r, tree[p1].r, tree[p2].r, cnt, sum, n, crd);
	return descend(l, m, tree[p1].l, tree[p2].l, pcnt, psum, n, crd);
}

struct ainta {
	vector<pi> crd;
	vector<int> roots;
	void initsex(vector<int> &a) {
		int n = sz(a);
		for (int i = 0; i < sz(a); i++) {
			crd.push_back({a[i], i});
		}
		crd.push_back({0, -1});
		cr(roots, n + 1);
		sort(all(crd));
		roots[0] = newnode();
		init(0, n, roots[0]);
		for (int i = 0; i < n; i++) {
			int z = lower_bound(all(crd), pi{a[i], i}) - crd.begin();
			roots[i + 1] = newnode();
			upd(0, n, z, a[i], roots[i], roots[i + 1]);
		}
	}
	int solve(int L, int R) {
		auto [fok, cnt, sum] = descend(0, sz(crd) - 1, roots[L], roots[R], 0, 0, R - L, crd);
		if (cnt <= (R - L) / 2)
			return crd[fok + 1][0];
		return max(crd[fok][0], sum / (cnt - (R - L) / 2));
	}
} prob[2];

void init(int N, int Q, std::vector<int> X, std::vector<int> Y) {
	seg.init(N);
	for (int i = 0; i < N; i++) {
		seg.upd(i, X[i] + Y[i]);
	}
	prob[0].initsex(X);
	prob[1].initsex(Y);
}

int max_prize(int L, int R) {
	R++;
	return min({seg.query(L, R - 1), prob[0].solve(L, R), prob[1].solve(L, R)});
}
