#include "soccer.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;

int n;
map<array<int, 4>, int> mp;
vector<vector<int>> a;

int sum[MAXN][MAXN];

/// just chilling
vector<pi> get_interval(int r, int s, int e) {
	vector<pi> ans;
	for (int i = s; i <= e; i++) {
		if (a[r][i] == 1)
			continue;
		int j = i;
		while (j <= e && a[r][j] == 0)
			j++;
		ans.push_back({i, j - 1});
		i = j;
	}
	return ans;
}

int getsum(int i1, int i2, int j1, int j2) { return sum[i2 + 1][j2 + 1] - sum[i1][j2 + 1] - sum[i2 + 1][j1] + sum[i1][j1]; }
pi expand(int r, int u, int v) {
	pi ans;
	{
		int s = 0, e = r;
		while (s != e) {
			int m = (s + e) / 2;
			if (getsum(m, r, u, v) == 0)
				e = m;
			else
				s = m + 1;
		}
		ans[0] = s;
	}
	{
		int s = r, e = n - 1;
		while (s != e) {
			int m = (s + e + 1) / 2;
			if (getsum(r, m, u, v) == 0)
				s = m;
			else
				e = m - 1;
		}
		ans[1] = s;
	}
	return ans;
}

int f(int r1, int r2, int c1, int c2) {
	if (mp.count({r1, r2, c1, c2}))
		return mp[{r1, r2, c1, c2}];
	vector<pi> i1, i2;
	int ret = 0;
	if (r1 > 0) {
		auto intv = get_interval(r1 - 1, c1, c2);
		for (auto &[j1, j2] : intv) {
			auto [i1, i2] = expand(r1 - 1, j1, j2);
			ret = max(ret, f(i1, i2, j1, j2) + (i2 - i1 - (r2 - r1)) * (j2 - j1 + 1));
		}
	}
	if (r2 < n - 1) {
		auto intv = get_interval(r2 + 1, c1, c2);
		for (auto &[j1, j2] : intv) {
			auto [i1, i2] = expand(r2 + 1, j1, j2);
			ret = max(ret, f(i1, i2, j1, j2) + (i2 - i1 - (r2 - r1)) * (j2 - j1 + 1));
		}
	}
	return mp[{r1, r2, c1, c2}] = ret;
}

int biggest_stadium(int N, std::vector<std::vector<int>> F) {
	a = F;
	n = N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + F[i][j];
		}
	}
	int ret = 0;
	for (int i = 0; i < N; i++) {
		auto intv = get_interval(i, 0, N - 1);
		for (auto &[j1, j2] : intv) {
			auto [i1, i2] = expand(i, j1, j2);
			ret = max(ret, f(i1, i2, j1, j2) + (i2 - i1 + 1) * (j2 - j1 + 1));
		}
	}
	return ret;
}
