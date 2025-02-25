#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 20000005;

struct node {
	int l, r;
	int cnt;
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

void upd(int pos, int s, int e, int val, int prv, int nxt) {
	if (s == e) {
		tree[nxt].cnt = tree[prv].cnt + 1;
		tree[nxt].sum = tree[prv].sum + val;
		return;
	}
	int m = (s + e) / 2;
	if (pos <= m) {
		tree[nxt].l = newnode();
		tree[nxt].r = tree[prv].r;
		upd(pos, s, m, val, tree[prv].l, tree[nxt].l);
	} else {
		tree[nxt].l = tree[prv].l;
		tree[nxt].r = newnode();
		upd(pos, m + 1, e, val, tree[prv].r, tree[nxt].r);
	}
	tree[nxt].cnt = tree[tree[nxt].l].cnt + tree[tree[nxt].r].cnt;
	tree[nxt].sum = tree[tree[nxt].l].sum + tree[tree[nxt].r].sum;
}

lint query(int s, int e, int k, int r1, int r2) {
	if (s == e) {
		if (k == 0)
			return 0;
		int tot = tree[r2].cnt - tree[r1].cnt;
		return (1ll * k * (tree[r2].sum - tree[r1].sum)) / tot;
	}
	int m = (s + e) / 2;
	int subcnt = tree[tree[r2].l].cnt - tree[tree[r1].l].cnt;
	if (subcnt > k) {
		return query(s, m, k, tree[r1].l, tree[r2].l);
	} else {
		return tree[tree[r2].l].sum - tree[tree[r1].l].sum + query(m + 1, e, k - subcnt, tree[r1].r, tree[r2].r);
	}
}

vector<pi> a;
vector<lint> sum;
vector<int> root;

lint f(int k, int l) { return sum[l] + query(0, sz(a) - 1, k, root[0], root[l]); }

void dnc(int s, int e, int ps, int pe, vector<lint> &ans) {
	if (s > e)
		return;
	int m = (s + e) / 2;
	pi dap{-lint(1e18), -1};
	for (int i = ps; i <= pe; i++) {
		if (m <= i)
			dap = max(dap, pi{f(m, i), -i});
	}
	ans[m] = dap[0];
	dnc(s, m - 1, ps, -dap[1], ans);
	dnc(m + 1, e, -dap[1], pe, ans);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	cr(a, n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
		a[i][1] *= -1;
	}
	vector<lint> ans(n + 1);
	sort(all(a), [&](const pi &a, const pi &b) { return a[0] - b[0] > a[1] - b[1]; });
	cr(sum, n + 1);
	cr(root, n + 1);
	vector<pi> v;
	for (int i = n - 1; i >= 0; i--) {
		sum[i] = sum[i + 1] + a[i][0];
		v.push_back(pi{-a[i][1], i});
	}
	sort(all(v));
	root[0] = newnode();
	init(0, sz(a) - 1, root[0]);
	for (int i = 0; i < n; i++) {
		root[i + 1] = newnode();
		int pos = lower_bound(all(v), pi{-a[i][1], i}) - v.begin();
		upd(pos, 0, sz(a) - 1, a[i][1], root[i], root[i + 1]);
	}
	dnc(0, n, 0, n, ans);
	vector<pi> todo;
	while (q--) {
		int k;
		cin >> k;
		cout << ans[k] << "\n";
	}
}