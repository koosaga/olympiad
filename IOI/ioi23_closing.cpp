#include "closing.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

pair<vector<lint>, vector<lint>> doConvex(vector<pi> p) {
	vector<lint> v;
	for (auto &[a, b] : p) {
		v.push_back(a);
		v.push_back(b - a);
	}
	sort(all(v));
	reverse(all(v));
	v.insert(v.begin(), 0);
	for (int i = 1; i < sz(v); i++)
		v[i] += v[i - 1];
	vector<lint> ans[2];
	for (int i = 0; i < sz(v); i++) {
		ans[(i + 1) % 2].push_back(v[i]);
	}
	return make_pair(ans[0], ans[1]);
}

pair<vector<lint>, vector<lint>> doConcave(vector<pi> p) {
	vector<lint> v[2];
	sort(all(p), [&](const pi &a, const pi &b) { return a[1] > b[1]; });
	vector<lint> curmin(sz(p) + 1);
	curmin[sz(p)] = -2e18;
	for (int i = sz(p) - 1; i >= 0; i--) {
		curmin[i] = max(curmin[i + 1], p[i][0]);
	}
	lint sum = 0;
	v[1].push_back(0);
	for (int i = 0; i < sz(p); i++) {
		sum += p[i][1];
		v[1].push_back(sum);
	}
	sum = 0;
	lint bamax = -2e18;
	for (int i = 0; i < sz(p); i++) {
		sum += p[i][1];
		bamax = max(bamax, p[i][0] - p[i][1]);
		v[0].push_back(max(sum + bamax, sum - p[i][1] + curmin[i]));
	}
	for (int i = 1; i + 1 < sz(v[0]); i++) {
		lint le = v[0][i] - v[0][i - 1];
		lint ri = v[0][i + 1] - v[0][i];
		assert(le >= ri);
	}
	return make_pair(v[0], v[1]);
}

vector<lint> solve(vector<pi> inp) {
	int n = sz(inp);
	lint sum = 0;
	vector<pi> convex, concave;
	for (auto &[a, b] : inp) {
		sum += b;
		a = b - a;
		if (a * 2 >= b)
			convex.push_back({a, b});
		else
			concave.push_back({a, b});
	}
	auto [odd1, even1] = doConcave(concave);
	auto [odd2, even2] = doConvex(convex);
	auto conv = [&](vector<lint> a, vector<lint> b) {
		if (sz(a) == 0)
			return b;
		if (sz(b) == 0)
			return a;
		vector<lint> v;
		lint sum = a[0] + b[0];
		for (int i = 1; i < sz(a); i++)
			v.push_back(a[i] - a[i - 1]);
		for (int i = 1; i < sz(b); i++)
			v.push_back(b[i] - b[i - 1]);
		sort(all(v));
		reverse(all(v));
		v.insert(v.begin(), sum);
		for (int i = 1; i < sz(v); i++)
			v[i] += v[i - 1];
		return v;
	};
	vector<lint> ans(2 * n + 1, 0);
	{
		auto comb1 = conv(odd1, odd2);
		for (int i = 0; i < sz(comb1) && 2 * i + 2 < sz(ans); i++)
			ans[2 * i + 2] = max(ans[2 * i + 2], comb1[i]);
	}
	{
		auto comb1 = conv(odd1, even2);
		for (int i = 0; i < sz(comb1) && 2 * i + 1 < sz(ans); i++)
			ans[2 * i + 1] = max(ans[2 * i + 1], comb1[i]);
	}
	{
		auto comb1 = conv(even1, odd2);
		for (int i = 0; i < sz(comb1) && 2 * i + 1 < sz(ans); i++)
			ans[2 * i + 1] = max(ans[2 * i + 1], comb1[i]);
	}
	{
		auto comb1 = conv(even1, even2);
		for (int i = 0; i < sz(comb1) && 2 * i + 0 < sz(ans); i++)
			ans[2 * i + 0] = max(ans[2 * i + 0], comb1[i]);
	}

	for (auto &x : ans)
		x = sum - x;
	reverse(all(ans));
	return ans;
}

vector<vector<pi>> gph;
int par[MAXN];
lint dist[2][MAXN];

void dfs(int x, int p, int d) {
	for (auto &[w, y] : gph[x]) {
		if (y == p)
			continue;
		dist[d][y] = dist[d][x] + w;
		par[y] = x;
		dfs(y, x, d);
	}
}

int max_score(int N, int X, int Y, long long K, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
	gph.clear();
	gph.resize(N);
	for (int i = 0; i < N - 1; i++) {
		gph[U[i]].push_back({W[i], V[i]});
		gph[V[i]].push_back({W[i], U[i]});
	}
	for (int i = 0; i < N; i++)
		dist[0][i] = dist[1][i] = 0;
	dfs(Y, -1, 1);
	dfs(X, -1, 0);
	vector<int> chk(N);
	vector<int> paths;
	for (int i = Y; i != X; i = par[i]) {
		paths.push_back(i);
		chk[i] = 1;
	}
	paths.push_back(X);
	reverse(all(paths));
	chk[X] = 1;
	vector<pi> coins;
	for (int i = 0; i < N; i++) {
		if (!chk[i]) {
			coins.push_back({dist[0][i], dist[1][i]});
		}
	}
	for (auto &[x, y] : coins)
		if (x > y)
			swap(x, y);

	auto s1 = solve(coins);

	vector<lint> s2(sz(paths), 2e18);
	{
		vector<lint> g1(sz(paths)), g2(sz(paths));
		lint tot = 0;
		for (int i = 0; i < sz(paths); i++) {
			tot += max(dist[1][paths[i]], dist[0][paths[i]]);
			g1[i] = max(dist[1][paths[i]], dist[0][paths[i]]) - dist[0][paths[i]];
			g2[i] = max(dist[1][paths[i]], dist[0][paths[i]]) - dist[1][paths[i]];
		}
		int l = 0, r = sz(paths);
		while (l < r) {
			s2[r - l - 1] = min(s2[r - l - 1], tot);
			if (g1[l] > g2[r - 1]) {
				tot -= g1[l++];
			} else
				tot -= g2[--r];
		}
	}
	int ans = 0;
	int j = sz(s2);
	for (int i = 0; i < sz(s1); i++) {
		while (j && s1[i] + s2[j - 1] > K)
			j--;
		if (j)
			ans = max(ans, i + j + sz(paths));
	}
	{
		lint cursum = 0;
		vector<lint> sums;
		for (int i = 0; i < N; i++) {
			sums.push_back(dist[0][i]);
			sums.push_back(dist[1][i]);
		}
		sort(all(sums));
		for (int i = 0; i < sz(sums); i++) {
			cursum += sums[i];
			if (cursum > K)
				break;
			ans = max(ans, i + 1);
		}
	}
	return ans;
}
