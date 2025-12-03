#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 1050000;

struct node {
	int sx, ex, sy, ey;
	vector<int> idx;
	node() {
		sx = sy = 1e9;
		ex = ey = -1e9;
	}
} tree[MAXT];
bool vis[MAXT];

void init(vector<array<int, 3>> points, int p, int d) {
	for (auto &[x, y, i] : points) {
		tree[p].sx = min(tree[p].sx, x);
		tree[p].sy = min(tree[p].sy, y);
		tree[p].ex = max(tree[p].ex, x);
		tree[p].ey = max(tree[p].ey, y);
		tree[p].idx.push_back(i);
	}
	sort(all(tree[p].idx));
	reverse(all(tree[p].idx));
	if (sz(points) == 1)
		return;
	int m = sz(points) / 2;
	nth_element(points.begin(), points.begin() + m, points.end(), [&](array<int, 3> &a, array<int, 3> &b) { return a[d] < b[d]; });
	vector<array<int, 3>> L(points.begin(), points.begin() + m);
	vector<array<int, 3>> R(m + all(points));
	init(L, 2 * p, d ^ 1);
	init(R, 2 * p + 1, d ^ 1);
}

int query(int sx, int ex, int sy, int ey, int p) {
	if (tree[p].ex < sx || tree[p].sx > ex || tree[p].ey < sy || tree[p].sy > ey)
		return 1e9;
	while (sz(tree[p].idx) && vis[tree[p].idx.back()])
		tree[p].idx.pop_back();
	if (sz(tree[p].idx) == 0)
		return 1e9;
	if (sx <= tree[p].sx && tree[p].ex <= ex && sy <= tree[p].sy && tree[p].ey <= ey) {
		return tree[p].idx.back();
	}
	return min(query(sx, ex, sy, ey, 2 * p), query(sx, ex, sy, ey, 2 * p + 1));
}

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
	for (auto &[x, y] : a) {
		x = lower_bound(all(crd), x) - crd.begin();
		y = lower_bound(all(crd), y + 1) - crd.begin() - 1;
	}
	vector<array<int, 3>> points;
	for (int i = 0; i < n; i++) {
		points.push_back({a[i][0], a[i][1], i});
	}
	init(points, 1, 0);
	// remove min-index interval contained in [l, r]. If none such exist return -1
	auto Pop = [&](int l, int r) {
		int ans = query(l, r, l, r, 1);
		if (ans > 1e8)
			ans = -1;
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
			vis[pp] = 1;
			que.push({l, a[pp][0] - 1});
			que.push({a[pp][1] + 1, r});
		}
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i] << (i + 1 < n ? " " : "\n");
	}
}