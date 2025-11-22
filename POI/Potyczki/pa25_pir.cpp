#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

const int MAXT = 25571557;
struct node {
	int l, r;
	int sz;
} tree[MAXT];

int piv;
int newnode() { return ++piv; }

int getsz(int p) { return tree[p].sz; }

void pull(int p) { tree[p].sz = tree[tree[p].l].sz + tree[tree[p].r].sz; }

void add(int s, int e, int x, int p) {
	assert(p);
	if (s == e) {
		assert(!tree[p].sz);
		tree[p].sz = 1;
		return;
	}
	int m = (s + e) / 2;
	if (x <= m) {
		if (!tree[p].l)
			tree[p].l = newnode();
		add(s, m, x, tree[p].l);
	} else {
		if (!tree[p].r)
			tree[p].r = newnode();
		add(m + 1, e, x, tree[p].r);
	}
	pull(p);
}

void merge(int p, int src) {
	assert(p);
	if (tree[src].l) {
		if (!tree[p].l)
			tree[p].l = tree[src].l;
		else
			merge(tree[p].l, tree[src].l);
	}
	if (tree[src].r) {
		if (!tree[p].r)
			tree[p].r = tree[src].r;
		else
			merge(tree[p].r, tree[src].r);
	}
	pull(p);
}

pi split(int p, int l) {
	if (l == 0)
		return pi{0, p};
	if (l == tree[p].sz)
		return pi{p, 0};
	assert(p);
	auto a1 = split(tree[p].l, min(tree[tree[p].l].sz, l));
	auto a2 = split(tree[p].r, max(0, l - tree[tree[p].l].sz));
	int p1 = newnode();
	int p2 = newnode();
	tree[p1].l = a1[0];
	tree[p1].r = a2[0];
	tree[p2].l = a1[1];
	tree[p2].r = a2[1];
	pull(p1);
	pull(p2);
	return pi{p1, p2};
}

int query(int x, int l, int r, int p) {
	if (!p)
		return 0;
	if (x > r)
		return tree[p].sz;
	if (l == r) {
		return 0;
	}
	int m = (l + r) / 2;
	if (x <= m)
		return query(x, l, m, tree[p].l);
	return tree[tree[p].l].sz + query(x, m + 1, r, tree[p].r);
}

void trav(int p, int s, int e, int op, vector<int> &dp) {
	if (!p || tree[p].sz == 0)
		return;
	if (s == e) {
		dp[s] = op;
		return;
	}
	int m = (s + e) / 2;
	trav(tree[p].l, s, m, op, dp);
	trav(tree[p].r, m + 1, e, op, dp);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	int roots[69][69], minus[69]; // [ai][cur]
	memset(roots, 0, sizeof(roots));
	memset(minus, 0, sizeof(minus));
	auto binsearch = [&](vector<int> roots, int thres) {
		int s = 0, e = n;
		while (s != e) {
			int m = (s + e + 1) / 2;
			int ans = 0;
			for (int i = 0; i < sz(roots); i++) {
				ans += getsz(roots[i]) - query(m, 0, n - 1, roots[i]);
			}
			if (ans >= thres)
				s = m;
			else
				e = m - 1;
		}
		vector<int> ans(sz(roots));
		for (int i = 0; i < sz(roots); i++)
			ans[i] = query(s, 0, n - 1, roots[i]);
		return ans;
	};
	auto guard = [&](int &p) {
		if (!p)
			p = newnode();
	};
	pi corner{-1, -1};
	for (int i = n - 1; i >= 0; i--) {
		int thres = (n - i - 1) / 2;
		int cur = 0;
		for (int j = 1; j <= 64; j++) {
			cur += getsz(minus[j]);
		}
		if (cur >= thres) {
			for (int a = 1; a <= 64; a++) {
				guard(roots[a][0]);
				merge(roots[a][0], minus[a]);
				minus[a] = 0;
				for (int b = 1; b <= 64; b++) {
					merge(roots[a][0], roots[a][b]);
					roots[a][b] = 0;
				}
			}
			if (corner[0] != -1) {
				int dokdul = corner[0];
				guard(roots[a[dokdul]][0]);
				add(0, n - 1, dokdul, roots[a[dokdul]][0]);
				corner = pi{-1, -1};
			}
			if (m > 64) {
				corner = pi{i, m};
			} else {
				guard(roots[a[i]][m]);
				add(0, n - 1, i, roots[a[i]][m]);
			}
			continue;
		}
		int cost = 0;
		int idx = i;
		for (int i = 0; i <= 65; i++) {
			if (i == 65)
				assert(0);
			int ncur = cur;
			for (int j = 1; j <= i; j++) {
				ncur += getsz(roots[j][i - j]);
			}
			if (ncur >= thres) {
				cost += i * (thres - cur);
				if (cost > m) {
					guard(minus[a[idx]]);
					add(0, n - 1, idx, minus[a[idx]]);
					break;
				}
				vector<int> rt;
				for (int j = 1; j <= i; j++) {
					rt.push_back(roots[j][i - j]);
				}
				auto sol = binsearch(rt, thres - cur);
				int oroots[69][69], ominus[69];
				memcpy(oroots, roots, sizeof(oroots));
				memcpy(ominus, minus, sizeof(ominus));
				memset(roots, 0, sizeof(roots));
				memset(minus, 0, sizeof(minus));
				for (int j = 1; j <= i; j++) {
					auto sp = split(oroots[j][i - j], sol[j - 1]);
					if (sp[0]) {
						guard(roots[j][0]);
						merge(roots[j][0], sp[0]);
					}
					if (sp[1]) {
						guard(roots[j][i]);
						merge(roots[j][i], sp[1]);
					}
				}
				for (int a = 1; a <= 64; a++) {
					guard(roots[a][0]);
					for (int b = 0; b <= 64; b++) {
						if (a + b < i) {
							if (tree[oroots[a][b]].sz) {
								guard(roots[a][b + a]);
								merge(roots[a][b + a], oroots[a][b]);
							}
						} else if (a + b > i) {
							merge(roots[a][0], oroots[a][b]);
						}
					}
					merge(roots[a][0], ominus[a]);
				}
				if (corner[0] != -1) {
					int dokdul = corner[0];
					guard(roots[a[dokdul]][0]);
					add(0, n - 1, dokdul, roots[a[dokdul]][0]);
					corner = pi{-1, -1};
				}
				if (m - cost > 64) {
					corner = pi{idx, m - cost};
				} else {
					guard(roots[a[idx]][m - cost]);
					add(0, n - 1, idx, roots[a[idx]][m - cost]);
				}
				break;
			}
			cost += i * (ncur - cur);
			cur = ncur;
		}
	}
	vector<int> dp(n, -1);
	for (int i = 1; i <= 64; i++) {
		for (int j = 0; j <= 64; j++) {
			trav(roots[i][j], 0, n - 1, j, dp);
		}
	}
	if (corner[0] != -1)
		dp[corner[0]] = corner[1];
	for (int i = 0; i < n; i++)
		cout << dp[i] << (i + 1 == n ? " \n" : " ");
}