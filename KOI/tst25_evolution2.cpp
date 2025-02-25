#include "evolution2.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<int>> gph;

vector<int> merge(vector<int> &a, vector<int> &b) {
	if (sz(a) < sz(b))
		swap(a, b);
	pi ans{int(1e9), -1};
	for (int i = 0; i < 15; i++) {
		// how many bandwidth for binsearch?
		int merge_sort = sz(b) + (sz(a) + 1) / (1 << i) - 1;
		int bin_search = sz(b) * i;
		ans = min(ans, pi{merge_sort + bin_search, i});
	}
	int B = ans[1];
	vector<int> ptr(sz(b));
	int j = (1 << B) - 1;
	for (int i = 0; i < sz(b); i++) {
		while (j < sz(a) && compare(a[j], b[i]) == 1)
			j += (1 << B);
		ptr[i] = j;
	}
	for (int i = 0; i < sz(b); i++) {
		int l = ptr[i] - (1 << B) + 1, r = min(ptr[i], sz(a));
		while (l != r) {
			int m = (l + r) / 2;
			if (compare(a[m], b[i]))
				l = m + 1;
			else
				r = m;
		}
		ptr[i] = l;
	}
	j = 0;
	vector<int> ret;
	for (int i = 0; i < sz(a); i++) {
		while (j < sz(b) && ptr[j] == i)
			ret.push_back(b[j++]);
		ret.push_back(a[i]);
	}
	while (j < sz(b))
		ret.push_back(b[j++]);
	return ret;
}

vector<int> dfs(int x) {
	vector<int> mrg;
	for (auto &y : gph[x]) {
		auto v = dfs(y);
		mrg = merge(mrg, v);
	}
	mrg.insert(mrg.begin(), x);
	return mrg;
}

std::vector<int> recover(int N, std::vector<int> U, std::vector<int> V) {
	cr(gph, N);
	for (int i = 0; i < N - 1; i++) {
		gph[U[i]].push_back(V[i]);
	}
	auto p = dfs(0);
	vector<int> inv(N);
	for (int i = 0; i < N; i++)
		inv[p[i]] = i;
	return inv;
}
