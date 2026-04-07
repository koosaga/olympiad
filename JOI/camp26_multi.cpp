#include "multi.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using ulint = unsigned long long;
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
} disj;

vector<vector<int>> gph;
vector<int> par;

void dfs(int x, int p) {
	par[x] = p;
	for (auto &y : gph[x]) {
		if (y != p)
			dfs(y, x);
	}
}

vector<int> gen_parent_from_spantree(int n, vector<pi> edges) {
	cr(gph, n);
	cr(par, n);
	fill(all(par), -2);
	for (auto &[u, v] : edges) {
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		if (par[i] == -2)
			dfs(i, -1);
	}
	for (int i = 0; i < n; i++)
		if (par[i] == -1)
			par[i] = i;
	return par;
}

vector<ulint> r0(int n, int i, vector<ulint> A, vector<ulint> B) {
	if (n == 2) {
		return {A[1 - i]};
	}
	vector<pi> edges;
	for (int j = 0; j < n; j++) {
		if (i != j)
			edges.push_back({A[j], j});
	}
	sort(all(edges));
	ulint val = ulint(edges[0][1]) | (ulint(edges[1][1]) << 8) | (ulint(edges[1][0]) << 16);
	return vector<ulint>(n, val);
}

vector<ulint> r1(int n, int i, vector<ulint> A, vector<ulint> B) {
	disj.init(n);
	vector<pi> spantree;
	for (int j = 0; j < n; j++) {
		int p = (B[j] & 255);
		if (disj.uni(j, p)) {
			spantree.push_back({j, p});
		}
	}
	vector<vector<int>> whom(n);
	for (int i = 0; i < n; i++) {
		whom[disj.find(i)].push_back(i);
	}
	vector<array<lint, 3>> edges;
	for (int i = 0; i < n; i++) {
		assert(sz(whom[i]) != 1);
		if (sz(whom[i]) == 2) {
			array<lint, 3> emin{lint(1e18), 0, 0};
			for (auto &j : whom[i]) {
				int x = (B[j] >> 8) & 255;
				lint cost = (B[j] >> 16);
				emin = min(emin, {cost, j, x});
			}
			edges.push_back(emin);
		}
	}
	sort(all(edges));
	for (auto &[w, u, v] : edges) {
		if (disj.uni(u, v)) {
			spantree.push_back({u, v});
		}
	}
	pi nxt{lint(1e18), 0};
	for (int j = 0; j < n; j++) {
		if (disj.find(j) != disj.find(i))
			nxt = min(nxt, pi{A[j], j});
	}
	int par = gen_parent_from_spantree(n, spantree)[i];
	ulint val = par | (ulint(nxt[1]) << 8) | (ulint(nxt[0]) << 16);
	return vector<ulint>(n, val);
}

vector<ulint> r2(int n, int v, vector<ulint> A, vector<ulint> B) {
	disj.init(n);
	vector<pi> spantree;
	for (int i = 0; i < n; i++) {
		if (disj.uni(i, B[i] & 255)) {
			spantree.push_back({i, B[i] & 255});
		} else
			assert((B[i] & 255) == i);
	}
	if (sz(spantree) < n - 1) {
		vector<array<lint, 3>> nxt(n, array<lint, 3>{lint(1e18), -1, -1});
		for (int j = 0; j < n; j++) {
			array<lint, 3> rec = {(B[j] >> 16), (B[j] >> 8) & 255, j};
			nxt[disj.find(j)] = min(nxt[disj.find(j)], rec);
		}
		for (int j = 0; j < n; j++) {
			if (nxt[j][2] == -1)
				continue;
			if (disj.uni(nxt[j][1], nxt[j][2])) {
				spantree.push_back({nxt[j][1], nxt[j][2]});
			}
		}
	}
	int par = gen_parent_from_spantree(n, spantree)[v];
	// round 2: do next it
	{
		pi nxt{lint(1e18), 0};
		for (int j = 0; j < n; j++) {
			if (disj.find(j) != disj.find(v))
				nxt = min(nxt, pi{A[j], j});
		}
		ulint val = par | (ulint(nxt[1]) << 8) | (ulint(nxt[0]) << 16);
		return vector<ulint>(n, val);
	}
}

vector<ulint> r3(int n, int v, vector<ulint> A, vector<ulint> B) {
	disj.init(n);
	vector<pi> spantree;
	for (int i = 0; i < n; i++) {
		if (disj.uni(i, B[i] & 255)) {
			spantree.push_back({i, B[i] & 255});
		} else
			assert((B[i] & 255) == i);
	}
	if (sz(spantree) < n - 1) {
		vector<array<lint, 3>> nxt(n, array<lint, 3>{lint(1e18), -1, -1});
		for (int j = 0; j < n; j++) {
			array<lint, 3> rec = {(B[j] >> 16), (B[j] >> 8) & 255, j};
			nxt[disj.find(j)] = min(nxt[disj.find(j)], rec);
		}
		for (int j = 0; j < n; j++) {
			if (nxt[j][2] == -1)
				continue;
			if (disj.uni(nxt[j][1], nxt[j][2])) {
				spantree.push_back({nxt[j][1], nxt[j][2]});
			}
		}
	}
	auto par = gen_parent_from_spantree(n, spantree);
	// round 3: compress the graph
	vector<int> comps;
	for (int i = 0; i < n; i++) {
		if (par[i] == i) {
			comps.push_back(i);
		}
	}
	vector<int> cid(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < sz(comps); j++) {
			if (disj.find(i) == disj.find(comps[j]))
				cid[i] = j;
		}
	}
	vector<vector<int>> ids(sz(comps), vector<int>(sz(comps), -1));
	int piv = 1;
	for (int i = 0; i < sz(comps); i++) {
		for (int j = i + 1; j < sz(comps); j++) {
			ids[i][j] = ids[j][i] = piv++;
		}
	}
	vector<array<lint, 3>> opts(piv, array<lint, 3>{lint(1e18), -1, -1});
	for (int i = 0; i < n; i++) {
		if (cid[v] == cid[i])
			continue;
		int id = ids[cid[v]][cid[i]];
		opts[id] = min(opts[id], array<lint, 3>{A[i], v, i});
	}
	vector<ulint> ans(n);
	ans[0] = A[par[v]];
	for (int i = 1; i < piv; i++) {
		if (opts[i][1] == -1)
			continue;
		ans[i] = 1 + (ulint(opts[i][0]) << 1);
	}
	return ans;
}

// todo: gather mins and send to one machine
vector<ulint> r4(int n, int v, vector<ulint> A, vector<ulint> B) {
	if (v == 0) {
		lint ws = accumulate(all(B), 0ll);
		return vector<ulint>(n, ws);
	} else {
		lint wmin = 1e18;
		for (int j = 0; j < n; j++) {
			if (B[j] == 0)
				continue;
			wmin = min(wmin, lint(B[j]) >> 1);
		}
		return vector<ulint>(n, wmin);
	}
}

// todo: machine 0 just solves it
vector<ulint> r5(int n, int v, vector<ulint> A, vector<ulint> B) {
	if (v != 0)
		return vector<ulint>(n, 0);
	lint cur_mst = B[0];
	int j = 1;
	while (B[j] < 1e17)
		j++;
	int comp_size = 1;
	while (j - 1 > comp_size * (comp_size - 1) / 2)
		comp_size++;
	assert(j - 1 == comp_size * (comp_size - 1) / 2);
	int piv = 1;
	vector<array<lint, 3>> edges;
	for (int i = 0; i < comp_size; i++) {
		for (int j = i + 1; j < comp_size; j++) {
			edges.push_back({B[piv++], i, j});
		}
	}
	disj.init(comp_size);
	sort(all(edges));
	for (auto &[w, u, v] : edges)
		if (disj.uni(u, v))
			cur_mst += w;
	return {cur_mst};
}

std::vector<unsigned long long> strategy(int N, int r, int i, std::vector<unsigned long long> A,
										 std::vector<unsigned long long> B) {
	if (r == 0)
		return r0(N, i, A, B);
	if (r == 1)
		return r1(N, i, A, B);
	if (r == 2)
		return r2(N, i, A, B);
	if (r == 3)
		return r3(N, i, A, B);
	if (r == 4)
		return r4(N, i, A, B);
	return r5(N, i, A, B);
}
