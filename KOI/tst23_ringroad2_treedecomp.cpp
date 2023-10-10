#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 400005;
const lint inf = 2e18;

// Check camp17_railway_trip_alternative.cpp for application
struct treeDecomp {
	bool valid;
	vector<int> par;
	vector<vector<int>> bags;
} dcmp;

namespace ghost {
vector<int> gph[MAXN];
pi binfo[MAXN];

int dfs(int x, int p, treeDecomp &ret) {
	if (sz(gph[x]) == 0) {
		int curSz = sz(ret.par);
		ret.par.push_back(curSz + 1);
		ret.par.push_back(-1);
		vector<int> v1 = {(int)binfo[x].first, (int)binfo[x].second};
		vector<int> v2 = {p, (int)binfo[x].first, (int)binfo[x].second};
		ret.bags.push_back(v1);
		ret.bags.push_back(v2);
		return curSz + 1;
	}
	vector<int> sons;
	for (auto &y : gph[x]) {
		sons.push_back(dfs(y, x, ret));
	}
	while (sz(sons) >= 2) {
		int b2 = sons.back();
		sons.pop_back();
		int b1 = sons.back();
		sons.pop_back();
		assert(sz(ret.bags[b1]) == 3);
		assert(sz(ret.bags[b2]) == 3);
		int curSz = sz(ret.par);
		ret.par[b1] = curSz;
		ret.par[b2] = curSz;

		ret.par.push_back(curSz + 1);
		vector<int> v1 = {ret.bags[b1][0], ret.bags[b1][1], ret.bags[b2][2], ret.bags[b2][1]};
		ret.bags.push_back(v1);

		ret.par.push_back(-1);
		vector<int> v2 = {ret.bags[b1][0], ret.bags[b1][1], ret.bags[b2][2]};
		ret.bags.push_back(v2);

		sons.push_back(sz(ret.par) - 1);
	}
	int curSz = sz(ret.par);
	int b = sons[0];
	if (p != -1) {
		vector<int> v = {x, p, ret.bags[b][1], ret.bags[b][2]};
		ret.par[b] = curSz;
		ret.par.push_back(curSz + 1);
		ret.bags.push_back(v);
		v.erase(v.begin());
		ret.par.push_back(-1);
		ret.bags.push_back(v);
		return curSz + 1;
	}
	return sons[0];
}

// assumes that par follows DFS preorder, cycles contain vertices in order of increasing preorder
treeDecomp tree_decomposition_halin(int n, vector<int> par) {
	if (n <= 4) {
		vector<int> ord(n);
		iota(all(ord), 0);
		return {true, vector<int>(1, -1), vector<vector<int>>(1, ord)};
	}
	for (int i = 0; i < n; i++)
		gph[i].clear();
	for (int i = 0; i < n - 1; i++) {
		gph[par[i]].push_back(i + 1);
	}
	vector<int> cyc;
	for (int i = 0; i < n; i++) {
		if (sz(gph[i]) == 0)
			cyc.push_back(i);
	}
	treeDecomp ret;
	ret.valid = 1;
	for (int i = 0; i < sz(cyc); i++) {
		binfo[cyc[i]] = pi(cyc[i], cyc[(i + 1) % sz(cyc)]);
	}
	dfs(0, -1, ret);
	for (int i = 0; i < sz(ret.bags); i++) {
		sort(all(ret.bags[i]));
		ret.bags[i].resize(unique(all(ret.bags[i])) - ret.bags[i].begin());
	}
	/*
	for(int i = 0; i < sz(ret.bags); i++){
		cout << ret.par[i] << " " << i << endl;
	}
	for(int i = 0; i < sz(ret.bags); i++){
		for(auto &j : ret.bags[i]) cout << j <<  " ";
		cout << endl;
	}*/
	return ret;
}
}; // namespace ghost

map<pi, lint> costMap;
lint dp[MAXN][16];
vector<int> gph[MAXN];

void dfs(int x) {
	lint adj[4][4] = {};
	for (int i = 0; i < sz(dcmp.bags[x]); i++) {
		for (int j = 0; j < sz(dcmp.bags[x]); j++) {
			int a = dcmp.bags[x][i], b = dcmp.bags[x][j];
			auto z = costMap.find({a, b});
			if (z != costMap.end()) {
				adj[i][j] = adj[j][i] = z->second;
				costMap.erase(z);
			}
		}
	}
	for (auto &y : gph[x]) {
		dfs(y);
		vector<pi> v;
		for (int i = 0; i < sz(dcmp.bags[x]); i++) {
			for (int j = 0; j < sz(dcmp.bags[y]); j++) {
				if (dcmp.bags[x][i] == dcmp.bags[y][j]) {
					v.push_back({i, j});
				}
			}
		}
		for (int i = 0; i < (1 << sz(dcmp.bags[x])); i++) {
			lint opt_decision = inf;
			for (int j = 0; j < (1 << sz(dcmp.bags[y])); j++) {
				bool ok = 1;
				for (auto &[z1, z2] : v) {
					if ((i >> z1) % 2 != (j >> z2) % 2)
						ok = 0;
				}
				if (ok)
					opt_decision = min(opt_decision, dp[y][j]);
			}
			dp[x][i] += opt_decision;
			dp[x][i] = min(dp[x][i], inf);
		}
	}
	for (int k = 0; k < (1 << sz(dcmp.bags[x])); k++) {
		for (int i = 0; i < sz(dcmp.bags[x]); i++) {
			for (int j = 0; j < i; j++) {
				if ((k >> i) % 2 == (k >> j) % 2) {
					dp[x][k] += adj[i][j];
				}
			}
		}
	}
}

long long place_police(vector<int> P, vector<long long> C, vector<long long> W) {
	int n = sz(P) + 1;
	dcmp = ghost::tree_decomposition_halin(n, P);
	vector<int> chk(n), leaves;
	for (int i = 0; i < sz(C); i++) {
		int u = P[i], v = i + 1;
		costMap[{u, v}] = C[i];
		chk[P[i]] = 1;
	}
	for (int i = 0; i < n; i++) {
		if (!chk[i])
			leaves.push_back(i);
	}
	for (int i = 0; i < sz(leaves); i++) {
		int u = leaves[i], v = leaves[(i + 1) % sz(leaves)];
		costMap[{u, v}] = W[i];
	}
	int r = -1;
	for (int i = 0; i < sz(dcmp.par); i++) {
		if (dcmp.par[i] == -1)
			r = i;
		else
			gph[dcmp.par[i]].push_back(i);
	}
	dfs(r);
	return *min_element(dp[r], dp[r] + (1 << sz(dcmp.bags[r])));
}