#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<int> ans, vis;
vector<array<int, 4>> a;
int n;

vector<vector<pi>> tree;

void dfs(int x) {
	vis[x] = 1;
	for (int i = a[x][2]; i; i -= i & -i) {
		while (sz(tree[i]) && tree[i].back()[0] <= a[x][3]) {
			auto tp = tree[i].back();
			tree[i].pop_back();
			if (!vis[tp[1]])
				dfs(tp[1]);
		}
	}
	ans.push_back(x + 1);
}

void solve1() {
	cin >> n;
	cr(a, n);
	for (auto &[x1, y1, x2, y2] : a) {
		cin >> x1 >> y1 >> x2 >> y2;
	}
	cr(vis, n);
	cr(tree, 2 * n + 2);
	for (int i = 0; i < n; i++) {
		for (int j = a[i][0]; j < sz(tree); j += j & -j) {
			tree[j].push_back({a[i][1], i});
		}
	}
	for (int i = 0; i < sz(tree); i++) {
		sort(all(tree[i]));
		reverse(all(tree[i]));
	}
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	for (auto &x : ans)
		cout << x << " ";
	ans.clear();
	cout << "\n";
}

void solve2() {
	int n;
	cin >> n;
	vector<array<int, 3>> a;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		a.push_back({x1, y1, ~i});
		a.push_back({x2, y2, i});
	}
	sort(all(a));
	vector<int> ok(n, 1);
	vector<int> bit(2 * n + 5);
	for (int i = 0; i < sz(a); i++) {
		if (a[i][2] >= 0) {
			int cur = 0;
			for (int k = a[i][1]; k; k -= k & -k)
				cur = max(cur, bit[k]);
			if (cur > a[i][2]) {
				ok[a[i][2]] = 0;
			}
		} else {
			for (int k = a[i][1]; k < sz(bit); k += k & -k) {
				bit[k] = max(bit[k], ~a[i][2]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << ok[i];
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t, m;
	cin >> t >> m;
	while (t--) {
		if (m == 1)
			solve1();
		else
			solve2();
	}
}