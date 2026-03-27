#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} dsu;

lint solve(lint w, lint d, vector<lint> f) {
	if (w == 0) {
		return *max_element(all(f));
	}
	if (w >= d) {
		return d * (w / d) * (sz(f) - 1) + solve(w % d, d, f);
	}
	vector<pi> points;
	points.push_back({0, 0});
	for (auto &x : f) {
		points.push_back(pi{x, -1});
		points.push_back(pi{(x + w) % d, +1});
	}
	sort(all(points));
	dsu.init(sz(points));
	vector<lint> sums(sz(points) + 1);
	for (int i = 0; i + 1 < sz(points); i++) {
		if (points[i][0] == points[i + 1][0])
			dsu.uni(i, i + 1);
		sums[i + 1] = sums[i] + points[i][1];
	}
	for (auto &x : f) {
		int l = lower_bound(all(points), pi{x, -1}) - points.begin();
		int r = lower_bound(all(points), pi{(x + w) % d, +1}) - points.begin();
		dsu.uni(l, r);
	}
	lint ans = 0;
	vector<array<lint, 3>> edges;
	for (int i = 0; i < sz(points) - 1; i++) {
		edges.push_back({points[i + 1][0] - sums[i + 1] * d, i, i + 1});
		if (points[i][0] != points[i + 1][0]) {
			ans = max(ans, points[i + 1][0] - sums[i + 1] * d - d);
		}
	}
	sort(all(edges));
	for (auto &[w, u, v] : edges)
		if (dsu.uni(u, v))
			ans = max(ans, w);
	for (auto &x : f) {
		if (x > (x + w) % d)
			ans += d;
	}

	return ans - w;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, w, d;
	cin >> n >> w >> d;
	vector<lint> f(n);
	for (int i = 0; i < n; i++) {
		cin >> f[i];
	}
	cout << solve(w, d, f) << "\n";
}