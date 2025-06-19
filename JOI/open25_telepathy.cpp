#include "telepathy.h"
#include <bits/stdc++.h>

using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 205;
int ipow(int it) { return (int)pow(1.685, it); }

vector<int> gen(int n) {
	vector<int> seq;
	int l = 0, r = 0;
	for (int i = 0; sz(seq) < 10 * n; i++) {
		if (i % 2 == 0) {
			int nr = ipow(i);
			int prv = l;
			for (int i = l + 1; i <= r; i++) {
				if (!(i & 1))
					seq.push_back(i - prv), prv = i;
			}
			seq.push_back(r + 1 - prv);
			for (int i = r + 2; i <= nr; i++)
				seq.push_back(+1);
			r = nr;
		} else {
			int nl = -ipow(i);
			int prv = r;
			for (int i = r - 1; i >= l; i--) {
				if (i & 1)
					seq.push_back(i - prv), prv = i;
			}
			seq.push_back(l - 1 - prv);
			for (int i = l - 2; i >= nl; i--)
				seq.push_back(-1);
			l = nl;
		}
	}
	seq.resize(10 * n);
	return seq;
}

vector<vector<int>> gph;
vector<int> dfn;
int sz[MAXN], msz[MAXN], par[MAXN];
vector<int> dep;

void dfs(int x, int p = -1) {
	dfn.push_back(x);
	sz[x] = 1, msz[x] = 0;
	for (auto &y : gph[x]) {
		if (y != p) {
			dfs(y, x);
			sz[x] += sz[y];
			msz[x] = max(msz[x], sz[y]);
		}
	}
}

void dfs2(int x, int p = -1) {
	for (auto &y : gph[x]) {
		if (y != p) {
			dep[y] = dep[x] + 1;
			par[y] = x;
			dfs2(y, x);
		}
	}
}
vector<int> get_center(int x = 0) {
	dfn.clear();
	dfs(x);
	vector<int> ans;
	for (auto &x : dfn) {
		int w = max(sz(dfn) - sz[x], msz[x]);
		if (w * 2 <= sz(dfn))
			ans.push_back(x);
	}
	return ans;
}

std::vector<int> Aitana(int N, std::vector<int> A, std::vector<int> B, int S, int subtask) {
	cr(gph, N);
	cr(dep, N);
	for (int i = 0; i < N - 1; i++) {
		gph[A[i]].push_back(B[i]);
		gph[B[i]].push_back(A[i]);
	}
	auto cen = get_center();
	dfs2(S);
	sort(all(cen), [&](const int &a, const int &b) { return dep[a] < dep[b]; });
	vector<int> path = {cen[0]};
	for (int i = cen[0]; i != S; i = par[i])
		path.push_back(par[i]);
	reverse(all(path));
	auto seq = gen(N);
	vector<int> ans(10 * N + 1);
	int cur = 0;
	for (int i = 0; i < sz(ans); i++) {
		ans[i] = path[clamp(cur, 0, sz(path) - 1)];
		if (i < sz(seq)) {
			if (seq[i] > 0)
				cur++;
			else if (seq[i] == -2)
				cur--;
		}
	}
	return ans;
}

std::vector<int> Bruno(int N, std::vector<int> A, std::vector<int> B, int S, int subtask) {
	cr(gph, N);
	cr(dep, N);
	for (int i = 0; i < N - 1; i++) {
		gph[A[i]].push_back(B[i]);
		gph[B[i]].push_back(A[i]);
	}
	auto cen = get_center();
	dfs2(S);
	sort(all(cen), [&](const int &a, const int &b) { return dep[a] < dep[b]; });
	vector<int> path = {cen[0]};
	for (int i = cen[0]; i != S; i = par[i])
		path.push_back(par[i]);
	reverse(all(path));
	auto seq = gen(N);
	vector<int> ans(10 * N + 1);
	int cur = 0;
	for (int i = 0; i < sz(ans); i++) {
		ans[i] = path[clamp(cur, 0, sz(path) - 1)];
		if (i < sz(seq)) {
			if (seq[i] < 0)
				cur++;
			else if (seq[i] == +2)
				cur--;
		}
	}
	if (sz(cen) == 2) {
		for (int i = 1; i < 10 * N; i++) {
			if (ans[i - 1] == cen[0] && ans[i + 1] == cen[0])
				ans[i] = cen[1];
		}
	}
	return ans;
}