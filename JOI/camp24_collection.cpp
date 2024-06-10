#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 530000;

struct seg {
	array<lint, 3> tree[MAXT];
	int lim;
	void init(int n) {
		fill(tree, tree + MAXT, array<lint, 3>{-lint(1e10), 0, 0});
		for (lim = 1; lim <= n; lim <<= 1)
			;
	}
	void upd(int x, array<lint, 3> v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = max(tree[2 * x], tree[2 * x + 1]);
		}
	}
	array<lint, 3> query(int s, int e) {
		s += lim;
		e += lim;
		array<lint, 3> ret{-lint(1e10), 0, 0};
		while (s < e) {
			if (s % 2 == 1)
				ret = max(ret, tree[s++]);
			if (e % 2 == 0)
				ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = max(ret, tree[s]);
		return ret;
	}
} seg;

vector<int> solve(vector<pi> a, vector<pi> b) {
	vector<int> ans;
	vector<int> vx, vy;
	for (auto &[x, y] : a) {
		vx.push_back(x);
		vy.push_back(y);
	}
	sort(all(vx));
	vx.resize(unique(all(vx)) - vx.begin());
	sort(all(vy));
	vy.resize(unique(all(vy)) - vy.begin());
	vector<int> fix(sz(vx), 1e9);
	vector<int> xmin(sz(vx) + 1, 1e9), ymin(sz(vy) + 1, 1e9);
	for (int i = 0; i < sz(a); i++) {
		int px = lower_bound(all(vx), a[i][0]) - vx.begin();
		int py = lower_bound(all(vy), a[i][1]) - vy.begin();
		fix[px] = min(fix[px], i);
		xmin[px] = min(xmin[px], i);
		ymin[py + 1] = min(ymin[py + 1], i);
	}
	for (int i = 1; i <= sz(vy); i++)
		ymin[i] = min(ymin[i], ymin[i - 1]);
	for (int i = sz(vx); i; i--)
		xmin[i - 1] = min(xmin[i - 1], xmin[i]);
	ans.resize(sz(b), 1e9);
	vector<array<lint, 3>> coords;
	vector<vector<array<lint, 3>>> events(sz(a));
	vector<int> X(sz(b));
	for (int i = 0; i < sz(b); i++) {
		int px = lower_bound(all(vx), b[i][0]) - vx.begin();
		if (px == sz(vx) || vx[px] != b[i][0])
			continue;
		int x = fix[px];
		if (a[0][0] >= b[i][0] && a[0][1] <= b[i][1]) {
			ans[i] = x + 1;
		} else {
			int py = upper_bound(all(vy), b[i][1]) - vy.begin();
			int findp = min(xmin[px], ymin[py]) + 1;
			if (findp < sz(a)) {
				events[findp].push_back({b[i][0], b[i][1], i});
				coords.push_back({b[i][0], b[i][1], i});
				X[i] = x;
			}
		}
	}
	sort(all(coords));
	seg.init(sz(coords)); // max seg
	for (int i = 0; i < sz(a); i++) {
		for (auto &j : events[i]) {
			int c = lower_bound(all(coords), j) - coords.begin();
			seg.upd(c, array<lint, 3>{j[1], j[2], c});
		}
		int c = lower_bound(all(coords), array<lint, 3>{a[i][0] + 1, -lint(1e10), -lint(1e10)}) - coords.begin();
		while (true) {
			auto k = seg.query(0, c - 1);
			if (k[0] >= a[i][1]) {
				ans[k[1]] = max(X[k[1]], i + 1);
				seg.upd(k[2], array<lint, 3>{-lint(1e10), 0, 0});
			} else
				break;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<pi> a(n);
	vector<pi> query(q);
	for (auto &[x, y] : a)
		cin >> x >> y;
	for (auto &[x, y] : query)
		cin >> x >> y;
	vector<int> dap(q);
	auto dezeepgi = [&]() {
		for (auto &[x, y] : a)
			swap(x, y);
		for (auto &[x, y] : query)
			swap(x, y);
	};
	// special case?
	{
		vector<int> canWin(n, 1);
		for (int i = 0; i < 2; i++) {
			dezeepgi();
			{
				lint minx = 2e9, maxy = -2e9;
				for (int j = 0; j < n; j++) {
					if (j > 0 && !(minx <= a[j][0] || maxy >= a[j][1])) {
						canWin[j] = 0;
					}
					minx = min(minx, a[j][0]);
					maxy = max(maxy, a[j][1]);
				}
			}
			{
				lint minx = 2e9, maxy = -2e9;
				for (int j = n - 1; j >= 0; j--) {
					if (j < n - 1 && !(minx <= a[j][0] || maxy >= a[j][1])) {
						canWin[j] = 0;
					}
					minx = min(minx, a[j][0]);
					maxy = max(maxy, a[j][1]);
				}
			}
		}
		vector<pi> v;
		for (int i = 0; i < n; i++) {
			if (canWin[i])
				v.push_back(a[i]);
		}
		sort(all(v));
		for (int i = 0; i < q; i++) {
			if (binary_search(all(v), query[i]))
				dap[i] = 1;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			{
				auto ans0 = solve(a, query);
				dezeepgi();
				reverse(all(a));
				auto ans1 = solve(a, query);
				dezeepgi();
				reverse(all(a));
				for (int k = 0; k < q; k++)
					if (ans0[k] + ans1[k] <= n)
						dap[k] = 1;
			}
			dezeepgi();
		}
		for (auto &[x, y] : a)
			x *= -1, y *= -1;
		for (auto &[x, y] : query)
			x *= -1, y *= -1;
	}
	for (int i = 0; i < q; i++) {
		if (dap[i])
			cout << i + 1 << " ";
	}
}