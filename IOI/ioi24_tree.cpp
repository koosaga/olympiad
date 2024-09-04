#include "tree.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

struct disj {
	int pa[MAXN], sum[MAXN];
	void init(int n) {
		iota(pa, pa + n, 0);
		fill(sum, sum + n, -1);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		sum[p] += sum[q];
		return 1;
	}
	void incdeg(int x, int v) { sum[find(x)] += v; }
	int query(int x) { return sum[find(x)]; }
} disj;

int n;
vector<vector<int>> gph;
vector<int> a, par;
vector<lint> csum, dsum;
vector<pi> vect;
lint leafs;

void init(std::vector<int> P, std::vector<int> W) {
	n = sz(W) + 1;
	cr(a, n);
	cr(par, n);
	for (int i = 0; i < n; i++) {
		a[i + 1] = W[i];
		par[i + 1] = P[i] + 1;
	}
	par[1] = 0;
	n = sz(a);
	cr(gph, n);
	for (int i = 1; i < n; i++)
		gph[par[i]].push_back(i);
	vector<int> ord(n - 1);
	iota(all(ord), 1);
	sort(all(ord), [&](int x, int y) { return a[x] > a[y]; });
	ord.push_back(0);
	disj.init(n);
	for (int i = 1; i < n; i++) {
		disj.incdeg(par[i], +1);
		if (sz(gph[i]) == 0)
			leafs += a[i];
	}
	vector<int> chk(n);
	for (int i = 0; i + 1 < sz(ord); i++) {
		int v = ord[i];
		chk[v] = 1;
		auto ANNUL = [&](int p) { vect.push_back({disj.query(p) + 1, -a[ord[i]]}); };
		if (sz(gph[v]) == 0) {
			disj.incdeg(v, 1);
		}
		if (chk[par[v]]) {
			ANNUL(par[v]);
			disj.uni(v, par[v]);
		}
		for (auto &j : gph[v]) {
			if (chk[j]) {
				ANNUL(j);
				disj.uni(j, v);
			}
		}
		vect.push_back({disj.query(v) + 1, a[ord[i]]});
	}
	sort(all(vect));
	cr(csum, sz(vect) + 1);
	cr(dsum, sz(vect) + 1);
	for (int i = 1; i <= sz(vect); i++) {
		csum[i] = csum[i - 1] + vect[i - 1][0] * vect[i - 1][1];
		dsum[i] = dsum[i - 1] + vect[i - 1][1];
	}
}

lint query(int LL, int RR) {
	lint L = LL;
	lint R = RR;
	int l = lower_bound(all(vect), pi{(R + L - 1) / L, -lint(1e18)}) - vect.begin();
	return leafs * L + L * (csum[sz(vect)] - csum[l]) - R * (dsum[sz(vect)] - dsum[l]);
}