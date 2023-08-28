#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int n;
vector<int> gph[250005];
int sz[250005], maxsz[250005], a[250005];

void dfs(int x, int p) {
	sz[x] = a[x];
	maxsz[x] = 0;
	for (auto &i : gph[x]) {
		if (i == p)
			continue;
		dfs(i, x);
		sz[x] += sz[i];
		maxsz[x] = max(maxsz[x], sz[i]);
	}
}

lint dfs2(int x, int p, lint d) {
	sz[x] = a[x];
	lint ret = d * a[x];
	for (auto &i : gph[x]) {
		if (i == p)
			continue;
		ret += dfs2(i, x, d + a[x]);
		sz[x] += sz[i];
	}
	return ret;
}

int sum;

lint solve(int r) {
	lint ret = 0;
	vector<int> v;
	for (auto &i : gph[r]) {
		ret += dfs2(i, r, a[r]);
		v.push_back(sz[i]);
	}
	int ans = 0;
	vector<int> v1 = {0}, v2 = {0};
	for (int i = 0; i < sz(v) / 2; i++) {
		vector<int> w1 = v1, w2 = v1;
		for (auto &x : w2)
			x += v[i];
		v1.resize(sz(w1) + sz(w2));
		merge(all(w1), all(w2), v1.begin());
	}
	for (int i = sz(v) / 2; i < sz(v); i++) {
		vector<int> w1 = v2, w2 = v2;
		for (auto &x : w2)
			x += v[i];
		v2.resize(sz(w1) + sz(w2));
		merge(all(w1), all(w2), v2.begin());
	}
	for (auto &x : v1) {
		int z = (sum - a[r]) / 2 - x;
		if (z < 0)
			continue;
		auto it = upper_bound(all(v2), z);
		if (it != v2.begin())
			ans = max(ans, *prev(it) + x);
	}
	return ret + 1ll * ans * (sum - a[r] - ans);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) {
		int s = i + 1, e;
		scanf("%d", &e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	lint ret = 0;
	sum = accumulate(a + 1, a + n + 1, 0ll);
	for (int i = 1; i <= n; i++) {
		int p = max(sum - sz[i], maxsz[i]);
		if (p <= sum / 2)
			ret = max(ret, solve(i));
	}
	for (int i = 1; i <= n; i++)
		ret += a[i] * (a[i] - 1);
	printf("%lld\n", ret);
}