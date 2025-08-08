#include "worldmap.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<int>> gph;
vector<vector<int>> pushing;

vector<int> vis, instk;
vector<int> din, dout, dep;
vector<int> seq;

void dfs(int x, int p) {
	din[x] = sz(seq);
	seq.push_back(x);
	vis[x] = instk[x] = 1;
	for (auto &y : gph[x]) {
		if (y == p)
			continue;
		if (!vis[y]) {
			dep[y] = dep[x] + 1;
			dfs(y, x);
			seq.push_back(x);
		} else {
			if (!instk[y]) {
				pushing[din[y]].push_back(dep[x]);
			}
		}
	}
	dout[x] = sz(seq);
	instk[x] = 0;
}

vector<vector<int>> create_map(int N, int M, vector<int> A, vector<int> B) {
	cr(gph, N);
	cr(vis, N);
	cr(instk, N);
	cr(din, N);
	cr(dout, N);
	cr(dep, N);
	cr(seq, 0);
	cr(pushing, 2 * N);
	for (int i = 0; i < M; i++) {
		A[i]--;
		B[i]--;
		gph[A[i]].push_back(B[i]);
		gph[B[i]].push_back(A[i]);
	}
	dfs(0, -1);
	vector<vector<int>> ans(2 * N, vector<int>(2 * N, 0));
	vector<int> ord(N);
	iota(all(ord), 0);
	sort(all(ord), [&](int x, int y) { return dep[x] < dep[y]; });
	for (auto &i : ord) {
		for (int j = 2 * dep[i]; j < 2 * N; j++) {
			for (int k = din[i]; k < dout[i]; k++) {
				ans[j][k] = i;
			}
		}
	}
	for (int i = 0; i < 2 * N; i++) {
		sort(all(pushing[i]));
		for (int j = 0; j < sz(pushing[i]);) {
			int k = j + 1;
			while (k < sz(pushing[i]) && pushing[i][k] == pushing[i][k - 1] + 1)
				k++;
			ans[2 * pushing[i][k - 1] + 2][i] = ans[2 * pushing[i][k - 1] + 1][i];
			for (int l = j; l < k; l++) {
				ans[2 * pushing[i][l] + 1][i] = seq[i];
			}
			j = k;
		}
	}
	for (auto &x : ans)
		for (auto &y : x)
			y++;
	return ans;
}
