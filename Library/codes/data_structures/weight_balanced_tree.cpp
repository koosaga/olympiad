// Solution of BOJ 17486 with Weight-Balanced Tree.


#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 16571557;

struct node {
	lint lazy;
	int l, r, cnt;
	lint sum;
} pool[MAXT];

int piv;

int join(int l, int r) {
	int N = ++piv;
	pool[N] = {0, l, r, pool[l].cnt + pool[r].cnt, pool[l].sum + pool[r].sum};
	return N;
}

int init(int s, int e) {
	if (s + 1 == e) {
		int x;
		cin >> x;
		pool[e] = {0, 0, 0, 1, x};
		return e;
	}
	int m = (s + e) / 2;
	int l = init(s, m);
	int r = init(m, e);
	return join(l, r);
}

inline bool balanced_internal(int u, int v) {
	static const int alpha = 7;
	return u <= alpha * v && v <= alpha * u;
}

inline bool balanced(int u, int v) { return balanced_internal(pool[u].cnt, pool[v].cnt); }

void push(int x) {
	if (pool[x].lazy) {
		if (pool[x].l) {
			piv++;
			pool[piv] = pool[pool[x].l];
			pool[x].l = piv;
			pool[pool[x].l].lazy += pool[x].lazy;
			pool[pool[x].l].sum += pool[x].lazy * pool[pool[x].l].cnt;
		}
		if (pool[x].r) {
			piv++;
			pool[piv] = pool[pool[x].r];
			pool[x].r = piv;
			pool[pool[x].r].lazy += pool[x].lazy;
			pool[pool[x].r].sum += pool[x].lazy * pool[pool[x].r].cnt;
		}
		pool[x].lazy = 0;
	}
}

int merge(int l, int r) {
	if (l == 0)
		return r;
	if (r == 0)
		return l;
	if (balanced(l, r))
		return join(l, r);
	if (pool[l].cnt > pool[r].cnt) {
		push(l);
		int x = pool[l].l;
		int y = merge(pool[l].r, r);
		if (balanced(x, y))
			return join(x, y);
		if (balanced(x, pool[y].l) && balanced_internal(pool[x].cnt + pool[pool[y].l].cnt, pool[pool[y].r].cnt)) {
			return join(join(x, pool[y].l), pool[y].r);
		}
		int d = pool[y].r;
		push(pool[y].l);
		int c = pool[pool[y].l].r;
		int b = pool[pool[y].l].l;
		return join(join(x, b), join(c, d));
	} else {
		push(r);
		int x = merge(l, pool[r].l);
		int y = pool[r].r;
		if (balanced(x, y))
			return join(x, y);
		if (balanced(pool[x].r, y) && balanced_internal(pool[pool[x].l].cnt, pool[pool[x].r].cnt + pool[y].cnt)) {
			return join(pool[x].l, join(pool[x].r, y));
		}
		int a = pool[x].l;
		push(pool[x].r);
		int b = pool[pool[x].r].l;
		int c = pool[pool[x].r].r;
		return join(join(a, b), join(c, y));
	}
}

pi split(int v, int k) {
	assert(v && 0 <= k && k <= pool[v].cnt);
	if (k == 0)
		return pi{0, v};
	if (k == pool[v].cnt)
		return pi{v, 0};
	push(v);
	if (k <= pool[pool[v].l].cnt) {
		auto [p1, p2] = split(pool[v].l, k);
		return pi{p1, merge(p2, pool[v].r)};
	} else {
		auto [p1, p2] = split(pool[v].r, k - pool[pool[v].l].cnt);
		return pi{merge(pool[v].l, p1), p2};
	}
}

int split0(int v, int k) {
	assert(v && 0 <= k && k <= pool[v].cnt);
	if (k == 0)
		return 0;
	if (k == pool[v].cnt)
		return v;
	push(v);
	if (k <= pool[pool[v].l].cnt) {
		return split0(pool[v].l, k);
	} else {
		return merge(pool[v].l, split0(pool[v].r, k - pool[pool[v].l].cnt));
	}
}

int split1(int v, int k) {
	assert(v && 0 <= k && k <= pool[v].cnt);
	if (k == 0)
		return v;
	if (k == pool[v].cnt)
		return 0;
	push(v);
	if (k <= pool[pool[v].l].cnt) {
		return merge(split1(pool[v].l, k), pool[v].r);
	} else {
		return split1(pool[v].r, k - pool[pool[v].l].cnt);
	}
}

int copy(int v, int l, int r) {
	assert(v && 0 <= l && l < r && r <= pool[v].cnt);
	push(v);
	if (l == 0)
		return split0(v, r);
	if (r == pool[v].cnt)
		return split1(v, l);
	if (r <= pool[pool[v].l].cnt)
		return copy(pool[v].l, l, r);
	if (l >= pool[pool[v].l].cnt)
		return copy(pool[v].r, l - pool[pool[v].l].cnt, r - pool[pool[v].l].cnt);
	return merge(split1(pool[v].l, l), split0(pool[v].r, r - pool[pool[v].l].cnt));
}

lint query(int v, int l, int r) {
	assert(v && 0 <= l && l < r && r <= pool[v].cnt);
	if (l == 0 && r == pool[v].cnt)
		return pool[v].sum;
	lint ret = (r - l) * pool[v].lazy;
	int m = pool[pool[v].l].cnt;
	if (l < m)
		ret += query(pool[v].l, l, min(r, m));
	if (m < r)
		ret += query(pool[v].r, max(m, l) - m, r - m);
	return ret;
}

int update(int v, int l, int r, lint x) {
	assert(v && 0 <= l && l < r && r <= pool[v].cnt);
	if (l == 0 && r == pool[v].cnt) {
		pool[v].sum += pool[v].cnt * x;
		pool[v].lazy += x;
		return v;
	}
	if (pool[v].l) {
		piv++;
		pool[piv] = pool[pool[v].l];
		pool[v].l = piv;
		pool[pool[v].l].lazy += pool[v].lazy;
		pool[pool[v].l].sum += pool[v].lazy * pool[pool[v].l].cnt;
	}
	if (pool[v].r) {
		piv++;
		pool[piv] = pool[pool[v].r];
		pool[v].r = piv;
		pool[pool[v].r].lazy += pool[v].lazy;
		pool[pool[v].r].sum += pool[v].lazy * pool[pool[v].r].cnt;
	}
	pool[v].lazy = 0;
	int m = pool[pool[v].l].cnt;
	if (l < m)
		update(pool[v].l, l, min(r, m), x);
	if (m < r)
		update(pool[v].r, max(m, l) - m, r - m, x);
	pool[v].sum = pool[pool[v].l].sum + pool[pool[v].r].sum;
	return v;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n;
	piv = n;
	int rt = init(0, n);
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			piv++;
			pool[piv] = pool[rt];
			rt = piv;
			update(rt, l - 1, r, x);
		}
		if (t == 2) {
			int l, r, s, e;
			cin >> l >> r >> s >> e;
			auto v = copy(rt, s - 1, e);
			auto [r12, r3] = split(rt, r);
			int r1 = split0(r12, l - 1);
			rt = merge(merge(r1, v), r3);
		}
		if (t == 3) {
			int s, e;
			cin >> s >> e;
			cout << query(rt, s - 1, e) << "\n";
		}
	}
}
