#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXT = 25000000;

struct node {
	int l, r, cnt;
	lint sum;
} tree[MAXT];
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

void add(int pos, int s, int e, int v, int p1, int p2) {
	if (s == e) {
		tree[p2].cnt = tree[p1].cnt + 1;
		tree[p2].sum = tree[p1].sum + v;
		return;
	}
	int m = (s + e) / 2;
	if (pos <= m) {
		tree[p2].l = newnode();
		tree[p2].r = tree[p1].r;
		add(pos, s, m, v, tree[p1].l, tree[p2].l);
	} else {
		tree[p2].r = newnode();
		tree[p2].l = tree[p1].l;
		add(pos, m + 1, e, v, tree[p1].r, tree[p2].r);
	}
	tree[p2].cnt = tree[tree[p2].l].cnt + tree[tree[p2].r].cnt;
	tree[p2].sum = tree[tree[p2].l].sum + tree[tree[p2].r].sum;
}

lint query(int s, int e, int k, int p1, int p2) {
	if (k == 0)
		return 0;
	if (k == tree[p2].cnt - tree[p1].cnt)
		return tree[p2].sum - tree[p1].sum;
	int m = (s + e) / 2;
	int lcnt = tree[tree[p2].l].cnt - tree[tree[p1].l].cnt;
	return query(s, m, min(lcnt, k), tree[p1].l, tree[p2].l) + query(m + 1, e, max(k - lcnt, 0), tree[p1].r, tree[p2].r);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		a[i][1] = i;
	}
	sort(all(a));
	vector<int> rev(n);
	for (int i = 0; i < n; i++)
		rev[a[i][1]] = i;
	vector<int> root(n + 1);
	root[0] = newnode();
	init(0, n - 1, root[0]);
	for (int i = 1; i <= n; i++) {
		int rp = rev[i - 1];
		root[i] = newnode();
		add(rp, 0, n - 1, a[rp][0], root[i - 1], root[i]);
	}
	for (int i = 0; i < q; i++) {
		int s, e, x, l, r;
		cin >> s >> e >> x >> l >> r;
		s--;
		e--;
		auto f = [&](int s, int e, int x, int k) {
			e = min(e, s + k + x);
			return query(0, n - 1, k, root[s], root[e]);
			// a[s], a[s + 1], ..., a[e - 1]
			// get sum of x minimums
		};
		cout << f(s, e + 1, x, r) - f(s, e + 1, x, l - 1) << "\n";
	}
};