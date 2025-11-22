#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

struct segtree {
	vector<int> tree;
	int lim;
	void init(vector<pi> &v) {
		if (sz(v) == 0)
			return;
		for (lim = 1; lim <= sz(v); lim <<= 1)
			;
		cr(tree, 2 * lim + 1);
		fill(all(tree), 1e9);
		for (int i = 0; i < sz(v); i++) {
			tree[i + lim] = v[i][1];
		}
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	void eraseAt(int p) {
		p += lim;
		tree[p] = 1e9;
		while (p > 1) {
			p >>= 1;
			tree[p] = min(tree[2 * p], tree[2 * p + 1]);
		}
	}
	int query(int x) {
		if (sz(tree) == 0)
			return 1e9;
		int l = lim, r = x + lim - 1, ret = 1e9;
		while (l < r) {
			if (l % 2 == 1)
				ret = min(ret, tree[l++]);
			if (r % 2 == 0)
				ret = min(ret, tree[r--]);
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			ret = min(ret, tree[l]);
		return ret;
	}
};
vector<vector<pi>> nodes;
vector<segtree> trees;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	vector<int> crd;
	for (auto &[x, y] : a)
		cin >> x;
	for (auto &[x, y] : a) {
		cin >> y, y += x;
		crd.push_back(x);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for (auto &[x, y] : a) {
		x = lower_bound(all(crd), x) - crd.begin();
		y = lower_bound(all(crd), y + 1) - crd.begin() - 1;
	}
	int lim;
	for (lim = 1; lim <= sz(crd); lim <<= 1)
		;
	cr(nodes, 2 * lim + 5);
	cr(trees, 2 * lim + 5);
	vector<int> ord(n);
	iota(all(ord), 0);
	sort(all(ord), [&](int x, int y) { return pi{a[x][1], x} < pi{a[y][1], y}; });
	for (auto &i : ord) {
		for (int j = a[i][0] + lim; j; j >>= 1) {
			nodes[j].push_back({a[i][1], i});
		}
	}
	for (int i = 0; i < sz(nodes); i++) {
		trees[i].init(nodes[i]);
	}
	// remove min-index interval contained in [l, r]. If none such exist return -1
	auto Pop = [&](int l, int r) {
		if (l > r)
			return -1;
		int ll = l + lim, rr = r + lim, ans = 1e9;
		while (ll < rr) {
			if (ll % 2 == 1) {
				int pos = lower_bound(all(nodes[ll]), pi{r + 1, -1}) - nodes[ll].begin();
				ans = min(ans, trees[ll++].query(pos));
			}
			if (rr % 2 == 0) {
				int pos = lower_bound(all(nodes[rr]), pi{r + 1, -1}) - nodes[rr].begin();
				ans = min(ans, trees[rr--].query(pos));
			}
			ll >>= 1;
			rr >>= 1;
		}
		if (ll == rr) {
			int pos = lower_bound(all(nodes[ll]), pi{r + 1, -1}) - nodes[ll].begin();
			ans = min(ans, trees[ll++].query(pos));
		}
		if (ans > 1e8)
			return -1;
		int i = ans;
		for (int j = a[i][0] + lim; j; j >>= 1) {
			auto it = lower_bound(all(nodes[j]), pi{a[i][1], i}) - nodes[j].begin();
			trees[j].eraseAt(it);
		}
		return ans;
	};
	vector<int> ans(n);
	int counts = 0;
	for (int c = 0; counts < n; c++) {
		queue<pi> que;
		que.push({0, sz(crd) - 1});
		while (sz(que) && counts < n) {
			auto [l, r] = que.front();
			que.pop();
			auto pp = Pop(l, r);
			if (pp == -1)
				continue;
			ans[pp] = c;
			counts++;
			que.push({l, a[pp][0] - 1});
			que.push({a[pp][1] + 1, r});
		}
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i] << (i + 1 < n ? " " : "\n");
	}
}